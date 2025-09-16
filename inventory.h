
#pragma once

#include <string>
#include <vector>

#include "player.h"
#include "item.h"
#include "room.h"
#include "helpers.h"
#include "game.h"

void use_item(Game& g, bool& in_inv);
void combine_items(Game& g);
