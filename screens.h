
#pragma once

#include "player.h"
#include "helpers.h"
#include "room.h"

#include <iomanip>
#include <algorithm>

using namespace std;

extern const int ITEMS_PER_PAGE;

void show_title_screen();
void show_name_entry_screen(Player& player);
void show_explore_screen(Player& player, Room*& current_room, string question, string error_message,
							vector<string> option, vector<string>& prompt);
void show_inventory_screen(Player& player, int& selected_item_index, vector<string>& inv_hint,	string& question,
							vector<string>& option,	SortMode current_sort_mode, int& current_page, int& max_pages);