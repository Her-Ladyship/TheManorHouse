
#include "player.h"
#include "screens.h"

// ----- Constructor -----

Player::Player() {
    health = 100;
    location = { 0, 0 };
}

// ----- Function Definitions -----

string Player::get_name() { return name; }
int Player::get_health() { return health; }
vector<Item>& Player::get_inventory() { return inventory; }
Coords Player::get_location() { return location; }

void Player::set_name(string n) { name = n; }
void Player::set_health(int h) { health = h; }
void Player::set_location(Coords c) { location = c; }

void Player::add_to_inventory(Item i) { inventory.push_back(i); }
