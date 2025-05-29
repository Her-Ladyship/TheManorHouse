
#pragma once

#include <string>
#include <vector>

#include "item.h"
#include "helpers.h"

using namespace std;

class Player {
private:
    string name;
    int health;
    vector<Item> inventory;
    Coords location;

public:
    Player();

    string get_name();
    int get_health();
    vector<Item>& get_inventory();
    Coords get_location();

    void set_name(string n);
    void set_health(int h);
    void set_location(Coords c);

    void add_to_inventory(Item i);
    
};