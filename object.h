
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

public:
    Object(string n, string type = "flavour", vector<string> result = {}, vector<string> repeat = {},
            string unlock = "", Item item = Item(), bool u = false)
        : name(n), interaction_type(type), result_text(result), repeat_text(repeat),
            unlock_direction(unlock), revealed_item(item), used(u) {}

    string get_name();
    string get_interaction_type();
    vector<string> get_result_text();
    vector<string> get_repeat_text();
    bool has_been_used();
    void mark_used();
    Item get_revealed_item();
    void add_revealed_item(Item i);
    string get_unlock_direction();
};

// Declarations
extern Object chair;
extern Object knocker;



//#pragma once
//
//#include <string>
//#include "item.h"  // if you're going to store or spawn an item
//
//using namespace std;
//
//class Object {
//private:
//    string name;
//    string description;
//    string interaction_type;     // e.g. "flavour", "reveal", "unlock", "enemy"
//    string result_text;          // What prints after a successful interaction
//    string repeat_text;          // After object has been used successfully
//    bool used;
//    Item revealed_item;          // Optional: item this object can reveal
//
//public:
//    Object(string n, string d = "", string type = "flavour", string result = "", string repeat = "", Item item = Item(), bool u = false)
//        : name(n), description(d), interaction_type(type), result_text(result), repeat_text(repeat), revealed_item(item), used(u) {}
//
//    string get_name();
//    string get_description();
//    string get_interaction_type();
//    string get_result_text();
//    string get_repeat_text();
//    bool has_been_used();
//    void mark_used();
//    Item get_revealed_item();
//};
//
//extern Object chair;
//extern Object knocker;
