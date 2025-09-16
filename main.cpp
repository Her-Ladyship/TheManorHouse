
#include <conio.h>

#include "game.h"
#include "actions.h"
#include "room.h"
#include "screens.h"
#include "inventory.h"
#include "keys.h"
#include "ui_constants.h"
#include "room_ops.h"

// PROTOTYPES
void game_loop(Game& g);
void take_item(Game& g);
void interact(Game& g);

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
        g.question = "What would you like to do?";
        g.option = { "1. Use an item","2. Combine items","3. Return to exploration","","","" };
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
        g.player.set_name("River");
        g.player.add_to_inventory(curio_hook);
        g.player.add_to_inventory(fire_axe);
        g.player.add_to_inventory(steel_parasol);
        g.player.add_to_inventory(paperweight);
        g.player.add_to_inventory(hearth_poker);
        g.player.add_to_inventory(letter_opener);
        g.player.add_to_inventory(ashwood_cane);
        load_main_question(g.question, g.option);
        g.game_state = GameState::EXPLORE;
        break;
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