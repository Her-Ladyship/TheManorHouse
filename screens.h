
#pragma once

class Player;
class Game;

extern const int ITEMS_PER_PAGE;

void show_title_screen();
void show_name_entry_screen(Player& player);
void show_explore_screen(Game& g);
void show_inventory_screen(Game& g);
void show_combat_screen(Game& g);
