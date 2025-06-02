
#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class Item {
private:
    string name;
    string desc;
    vector<string> lore;

public:
    Item() : name(""), desc(""), lore({}) {}
    Item(string n, string d, vector<string> l) : name(n), desc(d), lore(l) {}

    string get_name();
    string get_desc();
    vector<string> get_lore();
};

// Item declarations
extern Item coin;
extern Item leaf;
extern Item bell;
extern Item mirror_shard;
extern Item broken_fork;
extern Item lavender;
extern Item wax_finger;
extern Item notebook;
extern Item salt_packet;
extern Item spare_key;
extern Item lemon;
extern Item whistle;
extern Item tarot;
extern Item broom;
extern Item knife;
extern Item teacup;
extern Item milk_tooth;
extern Item ticket;
extern Item photo;

// Combining stuff
extern map<pair<string, string>, Item> combination_recipes;
pair<string, string> make_combo_key(string a, string b);
void initialise_combination_recipes();

// Puzzle stuff
extern map<pair<string, string>, bool> puzzle_recipes;
pair<string, string> make_puzzle_key(string item, string object);
void initialise_puzzle_solutions();

