
#pragma once

#include <string>
#include <vector>

#include "item.h"
#include "helpers.h"

class Player {
private:
    std::string name;
    int health;
    std::vector<Item> inventory;
    Coords location;

public:
    Player();

    std::string get_name() const;
    int get_health() const;
    std::vector<Item>& get_inventory();                 // mutable access
    const std::vector<Item>& get_inventory() const;     // read-only access
    Coords get_location() const;

    void set_name(std::string n);
    void set_health(int h);
    void set_location(Coords c);

    void add_to_inventory(const Item& i);
    void remove_from_inventory_by_name(const std::string& item_name);
};
