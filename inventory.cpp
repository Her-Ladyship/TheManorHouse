
#include "inventory.h"
#include "screens.h"
#include "item.h"
#include "player.h"
#include <conio.h>
#include <algorithm>

void use_item(Player& player, int& selected_item_index, Room* current_room, string& error_message, string& question,
                vector<string>& option, vector<string>& inv_hint, SortMode current_sort_mode, int& current_page,
                int&max_pages, GameState& game_state, vector<string>& prompt, bool& in_inv) {

    if (player.get_inventory().empty()) {
        inv_hint = { "", "", "Your inventory is empty", "", "" };
        return;
    }

    Item selected_item = player.get_inventory()[selected_item_index];
    string item_name = selected_item.get_name();

    inv_hint = {"","","","",""};
    question = "Use the " + item_name + " on what ? ";
    option = {"","","","","",""};
    vector<Object>& room_objects = current_room->get_objects();
    int num_objects = room_objects.size();

    for (int i = 0; i < num_objects && i < 3; ++i) {
        option[i] = to_string(i + 1) + ". " + room_objects[i].get_name();
    }

    show_inventory_screen(player, selected_item_index, inv_hint, question, option, current_sort_mode, current_page, max_pages);

    bool choosing = true;
    bool redraw = true;

    while (choosing) {
        if (redraw) {
            show_inventory_screen(player, selected_item_index, inv_hint, question, option, current_sort_mode, current_page, max_pages);
            redraw = false;
        }

        char key = _getch();
        int selected_index = key - '1';

        if (selected_index >= 0 && selected_index < num_objects) {
            Object& obj = room_objects[selected_index];

            pair<string, string> puzzle_key = make_puzzle_key(item_name, obj.get_name());

            if (puzzle_recipes.find(puzzle_key) != puzzle_recipes.end() &&
                obj.get_interaction_type() == "puzzle" && !obj.has_been_used()) {
                obj.mark_used();
                player.add_to_inventory(obj.get_revealed_item());

                // SPECIAL CASE: Whistle used on Mirror unlocks Bureau
                if (item_name == "Whistle" && obj.get_name() == "Mirror") {
                    for (Object& other : current_room->get_objects()) {
                        if (other.get_name() == "Bureau") {
                            other.set_locked(false);
                            break;
                        }
                    }
                }

                if (!obj.get_unlock_direction().empty()) {
                    current_room->unlock_exit(obj.get_unlock_direction());
                }

                game_state = EXPLORE;
                error_message = "You used the " + item_name + " on the " + obj.get_name();
                prompt = obj.get_puzzle_success_text();
                player.remove_from_inventory_by_name(selected_item.get_name());
                load_main_question(question, option);
                choosing = false;
                in_inv = false;
            }
            else if (obj.get_interaction_type() == "puzzle" && obj.has_been_used()) {
                game_state = EXPLORE;
                inv_hint = { "", "", "You've done this already", "", ""};
                load_inv_main_question(question, option);
                redraw = true;
                choosing = false;
            }
            else {
                inv_hint = { "", "That doesn't seem", "to do anything", "", "" };
                load_inv_main_question(question, option);
                redraw = true;
                choosing = false;
            }
        }
    }
}


void combine_items(Player& player, int& selected_index, vector<string>& inv_hint, string& question,
                    vector<string>& option, SortMode& current_sort_mode, int max_pages, int& current_page) {

    vector<Item> displayed_inventory = player.get_inventory();

    if (current_sort_mode == ALPHABETICAL) {
        sort(displayed_inventory.begin(), displayed_inventory.end(),
            [](Item& a, Item& b) {
                return a.get_name() < b.get_name();
            });
    }

    vector<Item>& inventory = player.get_inventory();

    if (inventory.size() < 2) {
        inv_hint = { "", "You need at least two items", "", "to attempt a combination", "" };
        return;
    }

    Item first = displayed_inventory[selected_index];
    inv_hint = { "Select an item to", "", "combine with", "", first.get_name() };

    bool selecting = true;
    int second_index = selected_index;
    int new_second_index = second_index / ITEMS_PER_PAGE;
    bool redraw = true;

    while (selecting) {
        question = "What will you combine?";
        option = { "1. Choose second item", "", "3. Return to inventory" };
        if (redraw) {
            show_inventory_screen(player, second_index, inv_hint, question, option, current_sort_mode,
                new_second_index, max_pages);
            redraw = false;
        }

        char key = _getch();
        if (key == 0 || key == -32) {
            key = _getch();

            switch (key) {
            case 72:  // Up arrow
                if (second_index > 0) {
                    second_index--;
                    int new_page = second_index / ITEMS_PER_PAGE;
                    if (new_page != new_second_index) new_second_index = new_page;
                    redraw = true;
                }
                break;

            case 80:  // Down arrow
                if (second_index < inventory.size() - 1) {
                    second_index++;
                    int new_page = second_index / ITEMS_PER_PAGE;
                    if (new_page != new_second_index) new_second_index = new_page;
                    redraw = true;
                }
                break;

            case 75: // Left arrow
                if (new_second_index > 0) {
                    new_second_index--;
                    second_index = new_second_index * ITEMS_PER_PAGE;
                    redraw = true;
                }
                break;

            case 77: // Right arrow
                if (new_second_index < max_pages) {
                    new_second_index++;
                    second_index = new_second_index * ITEMS_PER_PAGE;
                    redraw = true;
                }
                break;
            }
        }
        else {
            switch (key) {
            case '1':
                if (second_index == selected_index) {
                    inv_hint = { "You can't combine the", "", first.get_name(), "", "with itself" };
                    load_inv_main_question(question, option);
                    redraw = true;
                    return;
                }
                else {
                    Item second = displayed_inventory[second_index];
                    auto key = make_combo_key(first.get_name(), second.get_name());

                    if (combination_recipes.find(key) != combination_recipes.end()) {
                        Item result = combination_recipes[key];

                        // Find the positions of the selected items by name
                        int index1 = -1, index2 = -1;
                        for (int i = 0; i < inventory.size(); ++i) {
                            if (inventory[i].get_name() == first.get_name() && index1 == -1) {
                                index1 = i;
                            }
                            else if (inventory[i].get_name() == second.get_name() && index2 == -1) {
                                index2 = i;
                            }
                        }

                        // Now remove the items in correct order
                        if (index1 > index2) {
                            inventory.erase(inventory.begin() + index1);
                            inventory.erase(inventory.begin() + index2);
                        }
                        else {
                            inventory.erase(inventory.begin() + index2);
                            inventory.erase(inventory.begin() + index1);
                        }

                        player.add_to_inventory(result);
                        inv_hint = { "", "The items combined into", "", result.get_name(), "" };
                        load_inv_main_question(question, option);
                        redraw = true;
                    }
                    else {
                        inv_hint = { "", "Nothing happened", "", "They don't seem to combine", "" };
                        load_inv_main_question(question, option);
                        selected_index = second_index;
                        current_page = selected_index / ITEMS_PER_PAGE;
                        redraw = true;
                    }

                    selecting = false;
                }
                break;
            case '3':
                inv_hint = { "", "", "Combination cancelled", "", "" };
                load_inv_main_question(question, option);
                selected_index = second_index;
                current_page = selected_index / ITEMS_PER_PAGE;
                redraw = true;
                selecting = false;
                break;
            }
        }
    }
}