
#include "actions.h"
#include "item.h"
#include "room.h"
#include "game.h"
#include "screens.h"
#include "helpers.h"

#include <conio.h>
#include <cctype>  
#include <string>
#include <algorithm>

extern std::vector<Room> room_list;

// Skeleton gate state (keep it simple for now)
static bool g_room_locked_by_enemy = false;
static std::string g_locked_room_name;   // e.g. "Lounge"
static std::string g_locked_enemy_name;  // e.g. "Skeleton"

bool logic_take_item(Game& g, const std::string& cleaned_input) {

    std::vector<Item>& room_items = g.current_room->get_items();

    if (room_items.empty()) {
        g.error_message = "There's nothing here to take.";
        return false;
    }

    auto it = std::find_if(room_items.begin(), room_items.end(),
        [&](Item& item) { return item.get_name() == cleaned_input; });

    if (it != room_items.end()) {
        g.player.add_to_inventory(*it);

        // Remove line of description for Knife
        if (it->get_name() == "Knife") {
            room_list[3].set_description("", 5);
        }

        g.error_message = "You took the " + it->get_name() + ".";
        room_items.erase(it);
        return true;
    }
    else {
        g.error_message = "There's no " + cleaned_input + " to take.";
        return false;
    }
}

bool logic_interact(Game& g, const std::string& lower_input) {

    bool found = false;
    g.prompt.clear();

    for (Object& obj : g.current_room->get_objects()) {
        if (to_lower(obj.get_name()) == lower_input) {
            found = true;
            const std::string type = obj.get_interaction_type();

            if (type == "unlock") {
                if (!obj.has_been_used()) {
                    obj.mark_used();
                    g.current_room->unlock_exit(obj.get_unlock_direction());
                    g.prompt = obj.get_result_text();
                }
                else {
                    g.prompt = obj.get_repeat_text();
                }
            }
            else if (type == "flavour") {
                if (!obj.has_been_used()) {
                    obj.mark_used();
                    g.prompt = obj.get_result_text();
                }
                else {
                    g.prompt = obj.get_repeat_text();
                }
            }
            else if (type == "reveal") {
                if (!obj.has_been_used()) {
                    obj.mark_used();
                    Item revealed = obj.get_revealed_item();
                    if (!revealed.get_name().empty()) {
                        g.player.add_to_inventory(revealed);
                        g.prompt = obj.get_result_text();
                        g.error_message = "You received the " + revealed.get_name();
                    }
                    else {
                        g.error_message = "";
                    }
                }
                else {
                    g.prompt = obj.get_repeat_text();
                }
            }
            else if (type == "puzzle") {
                if (!obj.has_been_used()) {
                    g.prompt = obj.get_result_text();
                }
                else {
                    g.prompt = obj.get_repeat_text();
                }
            }
            else if (type == "conditional") {
                if (obj.is_locked()) {
                    g.prompt = obj.get_result_text();
                }
                else {
                    if (!obj.has_been_used()) {
                        obj.mark_used();
                        Item revealed = obj.get_revealed_item();
                        if (!revealed.get_name().empty()) {
                            g.player.add_to_inventory(revealed);
                            g.prompt = obj.get_puzzle_success_text();
                            g.error_message = "You received the " + revealed.get_name();
                        }
                        else {
                            g.error_message = "";
                        }
                    }
                    else {
                        g.prompt = obj.get_repeat_text();
                    }
                }
            }
            else if (type == "encounter") {
                if (!obj.has_been_used()) {
                    obj.mark_used();

                    // Show encounter flavour + a red status line
                    g.prompt = obj.get_result_text();
                    g.error_message = "Will you fight (F) or will you run (R)?";

                    g_locked_room_name = g.current_room->get_name();
                    if (g_locked_room_name == "Lounge") {
                        g_locked_enemy_name = "Skeleton";
                    }

                    // Draw the explore screen so player sees the reveal
                    show_explore_screen(g);

                    // Wait for a valid key: F or R
                    int ch = 0;
                    while (true) {
                        ch = std::toupper(_getch());
                        if (ch == 'F' || ch == 'R') break;
                    }
                    if (ch == 'R') {
                        // 1) mark Lounge as blocked by the Skeleton
                        g_room_locked_by_enemy = true;

                        // 2) shove the player through any unlocked exit
                        const bool moved = flee_through_any_unlocked_exit(g);

                        // 3) UI
                        g.prompt = make_blank_prompt();
                        g.error_message = moved
                            ? "You flee. The " + g_locked_enemy_name + " bars the " + g_locked_room_name + "."
                            : "You back away, but there’s nowhere safe to go.";
                    }
                    else { // 'F'
                        // Hand off to combat
                        g.pending_encounter = g_locked_enemy_name;
                        g.game_state = GameState::COMBAT;
                        g.prompt = make_blank_prompt();
                        g.error_message = "";
                    }
                }
                else {
                    g.prompt = obj.get_repeat_text();
                }
            }

            else { // failsafe
                g.error_message = "Nothing happens. Yet.";
                g.prompt = { "","","","","","","" };
            }

            break;
        }
    }

    if (!found) {
        g.error_message = "There's no " + capitalise_words(lower_input) + " to interact with.";
        g.prompt = { "","","","","","","" };
    }

    return found;
}

Room* find_adjacent_room_by_direction(Room* from, const std::string& dir) {
    if (!from) return nullptr;
    Coords c = from->get_location();
    if (dir == "North")      c.y += 1;
    else if (dir == "South") c.y -= 1;
    else if (dir == "East")  c.x += 1;
    else if (dir == "West")  c.x -= 1;
    else return nullptr;

    for (Room& r : room_list) {
        Coords rc = r.get_location();
        if (rc.x == c.x && rc.y == c.y) return &r;
    }
    return nullptr;
}

// ---- Try every unlocked exit; move through the first that has a real neighbour ----
bool flee_through_any_unlocked_exit(Game& g) {
    for (const std::string& dir : g.current_room->get_exits()) {
        if (!g.current_room->is_exit_locked(dir)) {
            if (Room* next = find_adjacent_room_by_direction(g.current_room, dir)) {
                // commit move
                g.player.set_location(next->get_location());
                g.current_room = next;
                return true;
            }
        }
    }
    return false;
}

bool gate_enemy_locked_room_on_entry(Game& g, Room* target) {   // <-- no 'static'
    if (!g_room_locked_by_enemy || !target) return true;
    if (target->get_name() != g_locked_room_name) return true;

    g.prompt = {"","","","","","",""};
    g.question = "";
    g.option = {"","","","","",""};
    g.error_message = "The " + g_locked_enemy_name + " blocks the " + g_locked_room_name + ". Fight (F) or Run (R)?";
    show_explore_screen(g);

    int ch = 0;
    while (true) {
        int raw = _getch();
        if (raw == 0 || raw == 224) { _getch(); continue; } // ignore arrows etc.
        ch = std::toupper(static_cast<unsigned char>(raw));
        if (ch == 'F' || ch == 'R') break;
    }

    if (ch == 'R') {
        g.error_message = "You hesitate and stay where you are.";
        return false;                 // blocked; remain in current room
    }
    else {
        g.pending_encounter = g_locked_enemy_name;
        g.game_state = GameState::COMBAT;  // hand off to combat
        return false;                 // intercepted navigation
    }
}
