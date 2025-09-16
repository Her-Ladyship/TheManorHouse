
#include "inventory.h"
#include "screens.h"
#include "item.h"
#include "player.h"
#include "game.h"
#include "keys.h"

#include <conio.h>
#include <algorithm>   // std::sort
#include <utility>     // std::pair
#include <string>      // std::string
#include <vector>      // std::vector

void use_item(Game& g, bool& in_inv) {

    if (g.player.get_inventory().empty()) {
        g.inv_hint = { "", "", "Your inventory is empty", "", "" };
        return;
    }

    Item selected_item = g.player.get_inventory()[g.selected_item_index];
    std::string item_name = selected_item.get_name();

    g.inv_hint = make_blank_inv_hints();
    g.question = "Use the " + item_name + " on what ? ";
    g.option = make_blank_options();
    std::vector<Object>& room_objects = g.current_room->get_objects();
    int num_objects = static_cast<int>(room_objects.size());

    for (int i = 0; i < num_objects && i < 3; ++i) {
        g.option[i] = std::to_string(i + 1) + ". " + room_objects[i].get_name();
    }

    show_inventory_screen(g);

    bool choosing = true;
    bool redraw = true;

    while (choosing) {
        if (redraw) {
            show_inventory_screen(g);
            redraw = false;
        }

        char key = _getch();
        int selected_index = key - '1';

        if (selected_index >= 0 && selected_index < num_objects) {
            Object& obj = room_objects[selected_index];

            std::pair<std::string, std::string> puzzle_key =
                make_puzzle_key(item_name, obj.get_name());

            if (puzzle_recipes.find(puzzle_key) != puzzle_recipes.end() &&
                obj.get_interaction_type() == "puzzle" && !obj.has_been_used()) {
                obj.mark_used();

                // Only add a revealed item if one actually exists
                const Item reward = obj.get_revealed_item();
                if (!reward.get_name().empty()) {
                    g.player.add_to_inventory(reward);
                }

                // SPECIAL CASE: Whistle used on Mirror unlocks Bureau
                if (item_name == "Whistle" && obj.get_name() == "Mirror") {
                    for (Object& other : g.current_room->get_objects()) {
                        if (other.get_name() == "Bureau") {
                            other.set_locked(false);
                            break;
                        }
                    }
                }

                if (!obj.get_unlock_direction().empty()) {
                    g.current_room->unlock_exit(obj.get_unlock_direction());
                }

                g.game_state = GameState::EXPLORE;
                g.error_message = "You used the " + item_name + " on the " + obj.get_name();
                g.prompt = obj.get_puzzle_success_text();

                // Only remove certain items from inventory after use
                if (selected_item.get_name() == "Broom" || selected_item.get_name() == "Spare Key") {
                    g.player.remove_from_inventory_by_name(selected_item.get_name());
                }

                load_main_question(g.question, g.option);
                choosing = false;
                in_inv = false;
            }
            else if (obj.get_interaction_type() == "puzzle" && obj.has_been_used()) {
                g.game_state = GameState::EXPLORE;
                g.inv_hint = { "", "", "You've done this already", "", "" };
                load_inv_main_question(g.question, g.option);
                redraw = true;
                choosing = false;
            }
            else {
                g.inv_hint = { "", "That doesn't seem", "to do anything", "", "" };
                load_inv_main_question(g.question, g.option);
                redraw = true;
                choosing = false;
            }
        }
    }
}

void combine_items(Game& g) {

    std::vector<Item> displayed_inventory = g.player.get_inventory();

    if (g.current_sort_mode == SortMode::ALPHABETICAL) {
        std::sort(displayed_inventory.begin(), displayed_inventory.end(),
            [](Item& a, Item& b) {
                return a.get_name() < b.get_name();
            });
    }

    std::vector<Item>& inventory = g.player.get_inventory();

    if (inventory.size() < 2) {
        g.inv_hint = { "", "You need at least two items", "", "to attempt a combination", "" };
        return;
    }

    Item first = displayed_inventory[g.selected_item_index];
    g.inv_hint = { "Select an item to", "", "combine with", "", first.get_name() };

    bool selecting = true;
    int second_index = g.selected_item_index;
    int new_second_index = second_index / ITEMS_PER_PAGE;
    bool redraw = true;

    while (selecting) {
        g.question = "What will you combine?";
        g.option = { "1. Choose second item", "", "3. Return to inventory" };
        if (redraw) {
            show_inventory_screen(g);
            redraw = false;
        }

        char key = _getch();
        if (key == Keys::Prefix0 || key == Keys::PrefixExt) {
            key = _getch();

            switch (key) {
            case Keys::ArrowUp:
                if (second_index > 0) {
                    second_index--;
                    int new_page = second_index / ITEMS_PER_PAGE;
                    if (new_page != new_second_index) new_second_index = new_page;
                    redraw = true;
                }
                break;

            case Keys::ArrowDown:
                if (second_index < static_cast<int>(inventory.size()) - 1) {
                    second_index++;
                    int new_page = second_index / ITEMS_PER_PAGE;
                    if (new_page != new_second_index) new_second_index = new_page;
                    redraw = true;
                }
                break;

            case Keys::ArrowLeft:
                if (new_second_index > 0) {
                    new_second_index--;
                    second_index = new_second_index * ITEMS_PER_PAGE;
                    redraw = true;
                }
                break;

            case Keys::ArrowRight:
                if (new_second_index < g.max_pages) {
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
                if (second_index == g.selected_item_index) {
                    g.inv_hint = { "You can't combine the", "", first.get_name(), "", "with itself" };
                    load_inv_main_question(g.question, g.option);
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
                        for (int i = 0; i < static_cast<int>(inventory.size()); ++i) {
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

                        g.player.add_to_inventory(result);
                        g.inv_hint = { "", "The items combined into", "", result.get_name(), "" };
                        load_inv_main_question(g.question, g.option);
                        redraw = true;
                    }
                    else {
                        g.inv_hint = { "", "Nothing happened", "", "They don't seem to combine", "" };
                        load_inv_main_question(g.question, g.option);
                        g.selected_item_index = second_index;
                        g.current_page = g.selected_item_index / ITEMS_PER_PAGE;
                        redraw = true;
                    }

                    selecting = false;
                }
                break;
            case '3':
                g.inv_hint = { "", "", "Combination cancelled", "", "" };
                load_inv_main_question(g.question, g.option);
                g.selected_item_index = second_index;
                g.current_page = g.selected_item_index / ITEMS_PER_PAGE;
                redraw = true;
                selecting = false;
                break;
            }
        }
    }
}
