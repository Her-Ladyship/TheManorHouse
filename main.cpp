
#include "room.h"
#include "screens.h"

// PROTOTYPES
string game_setup();
void play_check();
void combine_items(Player& player, int& selected_index, vector<string>& inv_hint, string& question, vector<string>& option);
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
vector<string> inv_hint = { "","","","","" };
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

void combine_items(Player& player, int& selected_index, vector<string>& inv_hint, string& question, vector<string>& option) {

    vector<Item>& inventory = player.get_inventory();

    if (inventory.size() < 2) {
        inv_hint = {"", "You need at least two items", "", "to attempt a combination", ""};
        return;
    }

    Item first = inventory[selected_index];

    inv_hint = {"Select an item to", "", "combine with", "", first.get_name()};

    bool selecting = true;
    int second_index = selected_index;
    int new_second_index = second_index / ITEMS_PER_PAGE;

    while (selecting) {
        question = "What will you combine?";
        option = {"1. Choose second item", "", "3. Return to inventory"};
        show_inventory_screen(player, second_index, inv_hint, question, option, current_sort_mode, 
                                new_second_index, max_pages);

        char key = _getch();
        if (key == 0 || key == -32) {
            key = _getch();
            switch (key) {
            case 72: // Up
                if (second_index > 0) second_index--;
                break;
            case 80: // Down
                if (second_index < inventory.size() - 1) second_index++;
                break;
            }
        }
        else {
            switch (key) {
            case '1':
                if (second_index == selected_index) {
                    inv_hint = { "You can't combine the", "", first.get_name(), "", "with itself" };
                    load_inv_main_question(question, option);
                    show_inventory_screen(player, second_index, inv_hint, question, option, current_sort_mode,
                        new_second_index, max_pages);
                    return;
                }
                else {
                    Item second = inventory[second_index];
                    auto key = make_combo_key(first.get_name(), second.get_name());

                    if (combination_recipes.find(key) != combination_recipes.end()) {
                        Item result = combination_recipes[key];

                        // Remove both items (remove higher index first)
                        if (selected_index > second_index) {
                            inventory.erase(inventory.begin() + selected_index);
                            inventory.erase(inventory.begin() + second_index);
                        }
                        else {
                            inventory.erase(inventory.begin() + second_index);
                            inventory.erase(inventory.begin() + selected_index);
                        }

                        player.add_to_inventory(result);
                        inv_hint = { "", "The items combined into", "", result.get_name(), ""};
                        load_inv_main_question(question, option);
                        show_inventory_screen(player, second_index, inv_hint, question, option, current_sort_mode,
                            new_second_index, max_pages);
                    }
                    else {
                        inv_hint = {"", "Nothing happened", "", "They don't seem to combine", ""};
                        load_inv_main_question(question, option);
                        show_inventory_screen(player, second_index, inv_hint, question, option, current_sort_mode,
                            new_second_index, max_pages);
                    }

                    selecting = false;
                }
                break;
            case '3': // Escape
                inv_hint = {"", "", "Combination cancelled", "", ""};
                load_inv_main_question(question, option);
                show_inventory_screen(player, second_index, inv_hint, question, option, current_sort_mode,
                    new_second_index, max_pages);
                selecting = false;
                break;
            }
        }
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
        for (int i = 0; i < 5; i++) { inv_hint[i] = ""; }
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
        question = "What would you like to do?";
        option = { "1. Use an item","2. Combine items","3. Return to exploration","","","" };

        while (in_inventory) {
            if (redraw) {
                show_inventory_screen(player, selected_item_index, inv_hint, question, option,
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
                    // use_item();
                    //redraw = true;  // optionally redraw if it changes state
                    break;
                case '2':
                    combine_items(player, selected_item_index, inv_hint, question, option);
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
    //player.add_to_inventory(mirror_shard);
    player.add_to_inventory(broken_fork);
    player.add_to_inventory(lavender);
    player.add_to_inventory(wax_finger);
    //player.add_to_inventory(notebook);
    player.add_to_inventory(salt_packet);
    //player.add_to_inventory(spare_key);
    player.add_to_inventory(lemon);
    player.add_to_inventory(whistle);
    player.add_to_inventory(tarot);
}