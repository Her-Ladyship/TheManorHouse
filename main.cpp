
#include <conio.h>
#include <unordered_set>

#include "game.h"
#include "actions.h"
#include "room.h"
#include "screens.h"
#include "inventory.h"
#include "keys.h"
#include "ui_constants.h"
#include "room_ops.h"
#include "combat.h"

// PROTOTYPES
void game_loop(Game& g);
void take_item(Game& g);
void interact(Game& g);

// FUNCTIONS I DON'T WANT TO BE HERE BUT SEEM TO HAVE TO BE
static int count_consumable_rows(const Player& p) {
    std::unordered_set<std::string> names;
    for (const Item& it : p.get_inventory())
        if (it.is_consumable()) names.insert(it.get_name());
    return static_cast<int>(names.size());
}

static void clamp_cons_cursor(Game& g) {
    int n = count_consumable_rows(g.player);
    if (n <= 0) { g.consumable_cursor = 0; return; }
    if (g.consumable_cursor < 0)         g.consumable_cursor = 0;
    if (g.consumable_cursor >= n)        g.consumable_cursor = n - 1;
}

// utility: does `raw` represent an arrow-prefix from _getch() ?
static bool is_arrow_prefix(int raw) {
    return raw == Keys::Prefix0 || raw == static_cast<unsigned char>(Keys::PrefixExt);
}

// MAIN
int main() {

    Game g;
	while (!g.game_over) {
        game_loop(g);
	}

	return 0;
}

// FUNCTIONS

void game_loop(Game& g) {

    switch (g.game_state) {
    case GameState::TITLE: {
        show_title_screen();
        system("pause>nul");
        g.game_state = GameState::NAME_ENTRY;
        system("CLS");
        g.player.add_to_inventory(mirror_shard);
        g.player.add_to_inventory(mirror_shard);
        g.player.add_to_inventory(knife);
        g.player.add_to_inventory(clock_hand);
        g.player.add_to_inventory(rock);
        g.player.add_to_inventory(field_dressing);
        g.player.add_to_inventory(bandage);
        g.player.add_to_inventory(bandage);
        g.player.add_to_inventory(bandage);
        g.player.add_to_inventory(bandage);
        g.player.add_to_inventory(teacup);
        g.player.add_to_inventory(paperweight);
        g.player.add_to_inventory(lemon);
        g.player.add_to_inventory(salt_packet);
        g.player.add_to_inventory(bell);
        break;
    }
    case GameState::NAME_ENTRY: {
        show_name_entry_screen(g.player);
        system("pause>nul");
        initialise_combination_recipes();
        initialise_locked_doors();
        initialise_puzzle_solutions();
        load_main_question(g.question, g.option);
        g.game_state = GameState::EXPLORE;
        break;
    }
    case GameState::EXPLORE: {
        bool redraw = true;
        bool waiting_for_input = true;

        while (waiting_for_input) {

            if (redraw) {
                show_explore_screen(g);
                redraw = false;
            }

            char key = _getch();
            switch (key) {
            case '1':
                g.error_message = "";
                change_room(g);
                waiting_for_input = false;
                redraw = true;
                break;
            case '2':
                interact(g);
                waiting_for_input = false;
                redraw = true;
                break;
            case '3':
                take_item(g);
                waiting_for_input = false;
                redraw = true;
                break;
            case '4':
                g.game_state = GameState::INVENTORY;
                waiting_for_input = false;
                break;
            case 'Q': case 'q':
                g.game_over = true;
                waiting_for_input = false;
                break;
            default:
                break;
            }
        }
        break;
    }
    case GameState::INVENTORY: {
        bool in_inventory = true;
        bool redraw = true;
        load_inv_main_question(g.question, g.option);
        g.selected_item_index = 0;

        while (in_inventory) {
            if (redraw) {
                show_inventory_screen(g);
                redraw = false;
            }

            char key = _getch();
            if (key == Keys::Prefix0 || key == Keys::PrefixExt) {  // arrow key
                key = _getch();  // get the actual key code

                if (!g.player.get_inventory().empty()) {
                    switch (key) {
                    case Keys::ArrowUp:
                        if (g.selected_item_index > 0) {
                            g.selected_item_index--;
                            int new_page = g.selected_item_index / ITEMS_PER_PAGE;
                            if (new_page != g.current_page) g.current_page = new_page;
                            redraw = true;
                        }
                        break;
                    case Keys::ArrowDown:
                        if (g.selected_item_index < g.player.get_inventory().size() - 1) {
                            g.selected_item_index++;
                            int new_page = g.selected_item_index / ITEMS_PER_PAGE;
                            if (new_page != g.current_page) g.current_page = new_page;
                            redraw = true;
                        }
                        break;
                    case Keys::ArrowLeft:
                        if (g.current_page > 0) {
                            g.current_page--;
                            g.selected_item_index = g.current_page * ITEMS_PER_PAGE;
                            redraw = true;
                        }
                        break;
                    case Keys::ArrowRight:
                        if (g.current_page < g.max_pages) {
                            g.current_page++;
                            g.selected_item_index = g.current_page * ITEMS_PER_PAGE;
                            redraw = true;
                        }
                        break;
                    }
                    g.inv_hint = make_blank_inv_hints();
                }
            }
            else {
                switch (key) {
                case '1':
                    use_item(g, in_inventory);
                    redraw = true;
                    break;
                case '2':
                    combine_items(g);
                    redraw = true;
                    break;
                case '3':
                    in_inventory = false;
                    g.game_state = GameState::EXPLORE;
                    load_main_question(g.question, g.option);
                    g.error_message = "";
                    g.prompt = make_blank_prompt();
                    g.inv_hint = make_blank_inv_hints();
                    break;
                case 's': case 'S':
                    g.current_sort_mode = (g.current_sort_mode == SortMode::CHRONOLOGICAL)
                        ? SortMode::ALPHABETICAL : SortMode::CHRONOLOGICAL;
                    redraw = true;
                    break;
                }
            }
        }
        break;
    }
    case GameState::COMBAT: {
        // Simple stub: show who you’re facing, then any key returns to EXPLORE.
        system("CLS");
        add_text(3, 4, "COMBAT (stub)", "Lred");
        add_text(5, 4, "Enemy: " + (g.pending_encounter.empty() ? std::string("Unknown") : g.pending_encounter), "white");
        add_text(7, 4, "Press any key to return to exploration...", "white");
        //show_cursor(false);
        (void)_getch();

        // Important: DO NOT clear the Lounge lock here.
        // We only clear it after a real victory later.
        g.game_state = GameState::EXPLORE;
        load_main_question(g.question, g.option);
        g.error_message = "";
        g.prompt = make_blank_prompt();
        break;
    }
    case GameState::TESTING: {

        if (g.player.get_name().empty()) { g.player.set_name("River"); }
        if (g.player.get_inventory().empty()) {
            g.player.add_to_inventory(mirror_shard);
            g.player.add_to_inventory(mirror_shard);
            g.player.add_to_inventory(knife);
            g.player.add_to_inventory(clock_hand);
            g.player.add_to_inventory(rock);
            g.player.add_to_inventory(field_dressing);
            g.player.add_to_inventory(bandage);
            g.player.add_to_inventory(bandage);
            g.player.add_to_inventory(teacup);
            g.player.add_to_inventory(paperweight);
        }
        if (g.pending_encounter.empty()) { g.pending_encounter = "Skeleton"; }
        g.player.set_health(10);

        bool in_combat = true;
        bool redraw = true;
        load_combat_lines(g.combat_lines);

        while (in_combat) {
            if (redraw) {
                show_combat_screen(g);
                redraw = false;
            }

            char key = _getch();
            if (g.choosing_consumable) {
                if (key == Keys::Prefix0 || key == Keys::PrefixExt) {
                    int arrow = _getch();
                    switch (arrow) {
                    case Keys::ArrowUp: {
                        if (g.consumable_cursor > 0) {
                            --g.consumable_cursor;
                            redraw = true;
                        }
                        break;
                    }
                    case Keys::ArrowDown: {
                        int n = count_consumable_rows(g.player);
                        if (g.consumable_cursor < n - 1) {
                            ++g.consumable_cursor;
                            redraw = true;
                        }
                        break;
                    }
                    }
                    continue;
                }
                else if (key == Keys::Escape) {
                    load_combat_lines(g.combat_lines);
                    g.choosing_consumable = false;
                    redraw = true;
                    continue;
                }
                continue;
            }
            switch (key) {
            case '1':
                // strike
                break;
            case '2':
                // throw
                break;
            case '3':
                // guard
                break;
            case '4': {
                //if (g.choosing_consumable) break;

                int rows = count_consumable_rows(g.player);
                if (rows <= 0) {
                    g.combat_log.push_back("You have no consumables.");
                }
                else {
                    g.combat_lines = { "", "Using Consumable Menu", "", "", "",
                                       "", "", "Press 'Enter' to select", "Press 'Escape' to return", ""};
                    g.choosing_consumable = true;
                    g.consumable_cursor = 0;
                }
                redraw = true;
                break;
            }
            //case '4': {
            //    int rows = count_consumable_rows(g.player);
            //    if (rows <= 0) {
            //        g.combat_log.push_back("You have no consumables.");
            //    }
            //    else {
            //        //g.combat_lines = make_blank_combat_lines();
            //        g.combat_lines = {"", "Using Consumable Menu", "", "", "",
            //                          "", "", "Press 'Enter' to select", "Press 'Escape' to return", ""};
            //        g.choosing_consumable = !g.choosing_consumable;   // toggle
            //        if (g.choosing_consumable) g.consumable_cursor = 0;
            //    }
            //    redraw = true;
            //    break;
            //}

            case '5':
                // flee
                break;
            }
        }
    }
    }
}


void take_item(Game& g) {
    // If there are no items here, skip the prompt entirely
    if (g.current_room->get_items().empty()) {
        g.error_message = "There's nothing here to take";
        load_main_question(g.question, g.option);
        g.prompt = make_blank_prompt();
        return;
    }

    g.error_message = "";
    g.question = "";
    g.option = make_blank_options();
    g.prompt = { "", "What would you like to take?", "", "Type the item name and press Enter", "","","" };
    show_explore_screen(g);

    std::string input;
    std::getline(std::cin, input);

    std::string cleaned_input = capitalise_words(to_lower(input));
    (void)logic_take_item(g, cleaned_input);
    load_main_question(g.question, g.option);
    g.prompt = make_blank_prompt();
}

void interact(Game& g) {
    if (g.current_room->get_objects().empty()) {
        g.error_message = "There's nothing here to interact with.";
        load_main_question(g.question, g.option);
        g.prompt = make_blank_prompt();
        return;
    }

    g.question = "";
    g.option = make_blank_options();
    g.error_message = "";
    g.prompt = { "", "", "What do you want to interact with?", "", "Type the curiosity name and press Enter","","" };
    show_explore_screen(g);

    std::string input;
    std::getline(std::cin, input);

    std::string lower = to_lower(input);
    (void)logic_interact(g, lower);
    load_main_question(g.question, g.option);
}