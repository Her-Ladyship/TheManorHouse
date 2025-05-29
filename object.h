
#pragma once

#include <string>
#include <vector>
#include "item.h"

using namespace std;

class Object {
private:
    string name;
    string interaction_type;        // "flavour", "reveal", "unlock", etc.
    vector<string> result_text;     // First-time interaction result
    vector<string> repeat_text;     // Text shown on repeated interaction
    string unlock_direction;
    bool used;
    Item revealed_item;
    vector<string> puzzle_success_text;
    bool locked;

public:
    Object(string n, string type = "flavour", vector<string> result = {}, vector<string> repeat = {},
            string dir = "", vector<string> puzz = {}, Item item = Item(), bool u = false, bool l = false)
        : name(n), interaction_type(type), result_text(result), repeat_text(repeat),
            unlock_direction(dir), puzzle_success_text(puzz), revealed_item(item), used(u), locked(l) {}

    string get_name();
    string get_interaction_type();
    vector<string> get_result_text();
    vector<string> get_repeat_text();
    bool has_been_used();
    void mark_used();
    Item get_revealed_item();
    void add_revealed_item(Item i);
    string get_unlock_direction();
    vector<string> get_puzzle_success_text();
    bool is_locked();
    void set_locked(bool val);
};

// Declarations
extern Object chair;
extern Object knocker;
extern Object bureau;
extern Object kitchen_drawer;
extern Object ceiling_fan;
extern Object mirror;
extern Object keyhole;
extern Object kitchen_setting;
