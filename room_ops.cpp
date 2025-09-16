
#include "room_ops.h"
#include "screens.h"
#include "directions.h"
#include "helpers.h"
#include "player.h"
#include "room.h"
#include "game.h"
#include "actions.h"

#include <conio.h>

extern std::vector<Room> room_list;

Room* find_room_by_coords(const std::vector<Room>& rooms, Coords target) {
    for (const Room& room : rooms) {
        if (room.get_location().x == target.x && room.get_location().y == target.y) {
            return const_cast<Room*>(&room);
        }
    }
    return nullptr;
}

void change_room(Game& g) {

    g.question = "Which direction do you want to move?";
    g.option = { "1. North" , "2. South", "3. East", "4. West", "", "5. Back to Menu" };
    g.prompt = make_blank_prompt();

    bool waiting_for_input = true;
    bool redraw = true;

    while (waiting_for_input) {
        if (redraw) {
            show_explore_screen(g);
            redraw = false;
        }

        char key = _getch();

        Coords current = g.player.get_location();
        Coords new_location = current;

        // Map key to a Direction
        Direction dir = direction_from_key(key);

        // '5' means “Back to Menu” — keep that behaviour
        if (key == '5') {
            waiting_for_input = false;
            redraw = true;
            // fall through to the end-of-loop where we call load_main_question
            // without changing rooms
        }
        else if (dir != Direction::None) {
            // We have a real direction; propose a move and process it
            new_location = moved(current, dir);
            waiting_for_input = false;
            redraw = true;
        }
        else {
            // Invalid key — ignore and keep looping
            continue;
        }

        if (!waiting_for_input) {
            Room* next_room = find_room_by_coords(room_list, new_location);

            if (next_room != nullptr && dir != Direction::None) {
                // We know exactly which direction was attempted
                std::string direction = to_string(dir);

                if (g.current_room->is_exit_locked(direction)) {
                    g.error_message = "The door to the " + direction + " is locked.";
                    waiting_for_input = true; // Stay in the loop
                }
                else if (!gate_enemy_locked_room_on_entry(g, next_room)) {
                    // The gate intercepted entry.
                    // If it flipped to COMBAT, bail out so main loop renders combat.
                    if (g.game_state == GameState::COMBAT) {
                        return; // do NOT fall through to load_main_question
                    }
                    // Otherwise, we stayed in EXPLORE after a Run choice: keep the loop alive.
                    waiting_for_input = false;
                    redraw = true;
                }
                else {
                    g.player.set_location(new_location);
                    g.current_room = next_room;
                    load_main_question(g.question, g.option);
                    g.error_message = "";
                }
            }
            else if (key != '5') {
                g.error_message = "You can't go that way. There's nothing there.";
                waiting_for_input = true;
            }
        }
    }

    load_main_question(g.question, g.option);
    //g.error_message = "";
}

void initialise_locked_doors() {
    room_list[0].lock_exit("North");
    room_list[1].lock_exit("West");
    room_list[1].lock_exit("North");
}