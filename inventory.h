
#pragma once

#include <string>
#include <vector>
#include "player.h"
#include "item.h"
#include "room.h"

using namespace std;

void use_item(Player& player, int& selected_item_index, Room* current_room, string& error_message, string& question,
				vector<string>& option, vector<string>& inv_hint, SortMode current_sort_mode, int& current_page,
				int& max_pages, GameState& game_state, vector<string>& prompt, bool& in_inv);

void combine_items(Player& player, int& selected_index, vector<string>& inv_hint, string& question,
					vector<string>& option, SortMode& current_sort_mode, int max_pages, int& current_page);
