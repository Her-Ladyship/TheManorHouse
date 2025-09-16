
#include <algorithm>

#include "player.h"
#include "screens.h"

// ----- Constructor -----

Player::Player() {
    health = 100;
    location = { 0, 0 };
}

// ----- Function Definitions -----

std::string Player::get_name() const { return name; }
int Player::get_health() const { return health; }
std::vector<Item>& Player::get_inventory() { return inventory; }
const std::vector<Item>& Player::get_inventory() const { return inventory; }
Coords Player::get_location() const { return location; }

void Player::set_name(std::string n) { name = n; }
void Player::set_health(int h) { health = h; }
void Player::set_location(Coords c) { location = c; }

void Player::add_to_inventory(const Item& item) { inventory.push_back(item); }
void Player::remove_from_inventory_by_name(const std::string& item_name) {
    inventory.erase(
        std::remove_if(inventory.begin(), inventory.end(),
            [&item_name](const Item& item) {
                return item.get_name() == item_name;
            }),
        inventory.end()
    );
}




