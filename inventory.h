
#pragma once

#include <string>
#include <vector>
#include "player.h"
#include "item.h"

using namespace std;

void combine_items(Player& player, int& selected_index, vector<string>& inv_hint, string& question,
					vector<string>& option, SortMode& current_sort_mode, int max_pages, int& current_page);
