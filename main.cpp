
#include "room.h"
#include "screens.h"
#include "inventory.h"

// PROTOTYPES
string game_setup();
void play_check();
void game_loop();
void take_item();
void interact();

// GLOBALS
GameState game_state = TESTING;
SortMode current_sort_mode = CHRONOLOGICAL;
bool game_over = false;
int selected_item_index = 0;
int current_page = 0;
int max_pages = 0;

string error_message, question;
vector<string> option = {"","","","","",""};
vector<string> inv_hint = { "","","","","" };
vector<string> prompt = {"","","","","","",""};
Player player;
Room* current_room;

// MAIN
int main() {

    // DEBUG
    player.set_name("River");
    initialise_combination_recipes();
    initialise_locked_doors();
    initialise_puzzle_solutions();
    load_main_question(question, option);

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
        initialise_combination_recipes();
        initialise_locked_doors();
        initialise_puzzle_solutions();
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
        bool redraw = true;
        bool waiting_for_input = true;

        while (waiting_for_input) {

            if (redraw) {
                show_explore_screen(player, current_room, question, error_message, option, prompt);
                redraw = false;
            }

            char key = _getch();
            switch (key) {
            case '1':
                error_message = "";
                change_room(question, option, player, current_room, error_message, game_state, prompt);
                waiting_for_input = false;
                redraw = true;
                break;
            case '2':
                interact();
                waiting_for_input = false;
                redraw = true;
                break;
            case '3':
                take_item();
                waiting_for_input = false;
                redraw = true;
                break;
            case '4':
                game_state = INVENTORY;
                waiting_for_input = false;
                break;
            case 'Q': case 'q':
                game_over = true;
                waiting_for_input = false;
                break;
            default:
                break;
            }
        }
        break;
    }
    case INVENTORY: {
        bool in_inventory = true;
        bool redraw = true;
        question = "What would you like to do?";
        option = { "1. Use an item","2. Combine items","3. Return to exploration","","","" };

        while (in_inventory) {
            if (redraw) {
                show_inventory_screen(player, selected_item_index, inv_hint, question, option,
                    current_sort_mode, current_page, max_pages);
                redraw = false;
            }

            char key = _getch();
            if (key == 0 || key == -32) {  // arrow key
                key = _getch();  // get the actual key code

                if (!player.get_inventory().empty()) {
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
                    inv_hint = { "","","","","" };
                }
            }
            else {
                switch (key) {
                case '1':
                    use_item(player, selected_item_index, current_room, error_message, question, option, inv_hint, current_sort_mode,
                                current_page, max_pages, game_state, prompt, in_inventory);
                    redraw = true;
                    break;
                case '2':
                    combine_items(player, selected_item_index, inv_hint, question, option,
                                    current_sort_mode, max_pages, current_page);
                    redraw = true;
                    break;
                case '3':
                    in_inventory = false;
                    game_state = EXPLORE;
                    load_main_question(question, option);
                    error_message = "";
                    prompt = { "","","","","","","" };
                    inv_hint = { "","","","","" };
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
    case TESTING: {
        show_title_screen();
        system("pause>nul");
        break;
    }
    }
}

void take_item() {

    vector<Item>& room_items = current_room->get_items();

    if (room_items.empty()) {
        error_message = "There's nothing here to take";
        return;
    }

    error_message = "";

    // Prompt message
    question = "";
    option = {"","","","","",""};
    prompt = {"", "What would you like to take?", "", "Type the item name and press Enter", "","",""};
    show_explore_screen(player, current_room, question, error_message, option, prompt);

    string input;
    getline(cin, input);

    string cleaned_input = capitalise_words(to_lower(input));

    auto it = find_if(room_items.begin(), room_items.end(), [&](Item& item) {
        return item.get_name() == cleaned_input;
        });

    if (it != room_items.end()) {
        player.add_to_inventory(*it);
        error_message = "You took the " + it->get_name();
        room_items.erase(it);
    }
    else {
        error_message = "There's no " + cleaned_input + " to take";
    }
    load_main_question(question, option);
    prompt = { "","","","","","","" };
}

void interact() {
    string interaction_target;
    question = "";
    option = { "","","","","","" };
    error_message = "";
    prompt = { "", "", "What do you want to interact with?", "", "Type the curiosity name and press Enter","","" };
    show_explore_screen(player, current_room, question, error_message, option, prompt);

    getline(cin, interaction_target);
    interaction_target = to_lower(interaction_target);
    bool found = false;

    for (Object& obj : current_room->get_objects()) {
        if (to_lower(obj.get_name()) == interaction_target) {
            found = true;

            string type = obj.get_interaction_type();
            
            if (type == "unlock") {
                if (!obj.has_been_used()) {
                    obj.mark_used();

                    current_room->unlock_exit(obj.get_unlock_direction());

                    prompt = obj.get_result_text();
                }
                else {
                    prompt = obj.get_repeat_text();
                }
            }
            else if (type == "flavour") {
                if (!obj.has_been_used()) {
                    obj.mark_used();
                    prompt = obj.get_result_text();
                }
                else {
                    prompt = obj.get_repeat_text();
                }
            }
            else if (type == "reveal") {
                if (!obj.has_been_used()) {
                    obj.mark_used();

                    Item revealed = obj.get_revealed_item();
                    player.add_to_inventory(revealed);

                    prompt = obj.get_result_text();
                    error_message = "You received the " + revealed.get_name();
                }
                else {
                    prompt = obj.get_repeat_text();
                }
            }
            else if (type == "puzzle") {
                if (!obj.has_been_used()) {
                    prompt = obj.get_result_text();
                }
                else {
                    prompt = obj.get_repeat_text();
                }
            }
            else if (type == "conditional") {
                if (obj.is_locked()) {
                    prompt = obj.get_result_text();
                }
                else {
                    if (!obj.has_been_used()) {
                        obj.mark_used();
                        Item revealed = obj.get_revealed_item();
                        player.add_to_inventory(revealed);

                        prompt = obj.get_puzzle_success_text();
                        error_message = "You received the " + revealed.get_name();
                    }
                    else {
                        prompt = obj.get_repeat_text();
                    }
                }
            }
            else { // FAILSAFE
                error_message = "Nothing happens. Yet.";
                prompt = { "","","","","","","" };
            }
            load_main_question(question, option);
        }
    }

    if (!found) {
        error_message = "There's no " + capitalise_words(interaction_target) + " to interact with.";
        load_main_question(question, option);
        prompt = { "","","","","","","" };
    }
}