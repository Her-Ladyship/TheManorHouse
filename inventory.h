
#pragma once

#include <string>
#include <vector>

#include "player.h"
#include "item.h"
#include "room.h"
#include "helpers.h"
#include "game.h"

struct DisplayRow {
    std::string name;
    std::string desc;
    std::vector<int> indices;
};

std::vector<DisplayRow> build_grouped_inventory(const Player& p, bool alphabetical);
void use_item(Game& g, bool& in_inv);
void combine_items(Game& g);