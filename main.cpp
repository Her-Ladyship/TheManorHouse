
#include "room.h"
#include "screens.h"

// PROTOTYPES
string game_setup();
void play_check();
void game_loop();
void debug_load_items();

// GLOBALS
GameState game_state = EXPLORE;
SortMode current_sort_mode = CHRONOLOGICAL;
bool game_over = false;
int selected_item_index = 0;
int current_page = 0;
int max_pages = 0;

string error_message, question;
vector<string> option = {"","","","","",""};
Player player;
Room* current_room;

// MAIN
int main() {

    // DEBUG
    player.set_name("River");
    load_main_question(question, option);
    debug_load_items();
    initialise_combination_recipes();

	while (!game_over) {
        game_loop();
	}

	return 0;
}

// FUNCTIONS
string game_setup() {
    cout << "Hi. Welcome to the game.\n\n";
    cout << "What is your name? ";
    string player_name;
    getline(cin, player_name);

    if (player_name.length() > 18) {
        cout << "\nWoah there, superstar. Let's keep it under 18 characters.\n";
        player_name = player_name.substr(0, 18);
    }

    while (!yes_no_check("\nYou have entered " + player_name + " - is this correct? (Y/N) ")) {
        cout << "Ugh. Gross. Try again, I suppose.\n\n";
        cout << "What is your name? ";
        getline(cin, player_name);
        if (player_name.length() > 18) {
            cout << "\nI ALREADY TOLD YOU. 18 CHARACTERS OR LESS!\n";
            player_name = player_name.substr(0, 18);
        }
    }

    return player_name;
}

void play_check() {
    cout << "Well... Hello there " << player.get_name() << "...\n\n";
    if (!yes_no_check("Are you ready to enter THE MANOR HOUSE? (Y/N) ")) {
        cout << "Oh. Unexpected.\nI suppose you'll be leaving then...\n\n";
        game_over = true;
    }
    else {
        current_room = find_room_by_coords(room_list, player.get_location());
        game_state = EXPLORE;
        load_main_question(question, option);
    }
}

void game_loop() {

    switch (game_state) {
    case TITLE: {
        player.set_name(game_setup());
        play_check();
        break;
    }
    case EXPLORE: {
        show_explore_screen(player, current_room, question, error_message, option);

        bool waiting_for_input = true;

        while (waiting_for_input) {
            char key = _getch();

            switch (key) {
            case '1':
                change_room(question, option, player, current_room, error_message, game_state);
                waiting_for_input = false;
                break;
            case '2':
                // interact();  not implemented yet
                waiting_for_input = false;
                break;
            case '3':
                // take_item();  not implemented yet
                waiting_for_input = false;
                break;
            case '4':
                // use_item();  not implemented yet
                waiting_for_input = false;
                break;
            case '5':
                game_state = INVENTORY;
                waiting_for_input = false;
                break;
            case '6':
                game_over = true;
                waiting_for_input = false;
                break;
            default:
                // invalid key, do nothing — loop continues
                break;
            }
        }

        break;
    }
    case INVENTORY: {
        bool in_inventory = true;
        bool redraw = true;  // force initial draw

        while (in_inventory) {
            if (redraw) {
                show_inventory_screen(player, selected_item_index, error_message, question, option,
                    current_sort_mode, current_page, max_pages);
                redraw = false;
            }

            char key = _getch();

            if (key == 0 || key == -32) {  // arrow key or special key
                key = _getch();  // get the actual key code

                switch (key) {
                case 72:  // Up arrow
                    if (selected_item_index > 0) {
                        selected_item_index--;
                        int new_page = selected_item_index / ITEMS_PER_PAGE;
                        if (new_page != current_page) current_page = new_page;
                        redraw = true;
                    }
                    break;
                case 80:  // Down arrow
                    if (selected_item_index < player.get_inventory().size() - 1) {
                        selected_item_index++;
                        int new_page = selected_item_index / ITEMS_PER_PAGE;
                        if (new_page != current_page) current_page = new_page;
                        redraw = true;
                    }
                    break;
                case 75: // Left arrow
                    if (current_page > 0) {
                        current_page--;
                        selected_item_index = current_page * ITEMS_PER_PAGE;
                        redraw = true;
                    }
                    break;
                case 77: // Right arrow
                    if (current_page < max_pages) {
                        current_page++;
                        selected_item_index = current_page * ITEMS_PER_PAGE;
                        redraw = true;
                    }
                    break;
                }
            }
            else {
                switch (key) {
                case '1':
                    // use_item(player, selected_item_index); // if implemented
                    //redraw = true;  // optionally redraw if it changes state
                    break;
                case '2':
                    // examine_item(player, selected_item_index); // if implemented
                    //redraw = true;  // optionally redraw if it prints info
                    break;
                case '3':
                    in_inventory = false;
                    game_state = EXPLORE;
                    load_main_question(question, option);
                    break;
                case 's': case 'S':
                    current_sort_mode = (current_sort_mode == CHRONOLOGICAL) ? ALPHABETICAL : CHRONOLOGICAL;
                    redraw = true;
                    break;
                }
            }
        }
        break;
    }
    case COMBAT: {
        // combat stuff here
        break;
    }
    }    
}

void debug_load_items() {
    player.add_to_inventory(coin);
    player.add_to_inventory(leaf);
    player.add_to_inventory(bell);
    player.add_to_inventory(mirror_shard);
    player.add_to_inventory(broken_fork);
    player.add_to_inventory(lavender);
    player.add_to_inventory(wax_finger);
    player.add_to_inventory(notebook);
    player.add_to_inventory(salt_packet);
    player.add_to_inventory(spare_key);
    player.add_to_inventory(lemon);
    player.add_to_inventory(whistle);
    player.add_to_inventory(tarot);
}