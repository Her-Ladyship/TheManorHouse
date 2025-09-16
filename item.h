
#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>

class Item {
private:
    std::string name;
    std::string desc;
    std::vector<std::string> lore;

public:
    Item() : name(""), desc(""), lore({}) {}
    Item(std::string n, std::string d, std::vector<std::string> l) : name(n), desc(d), lore(l) {}

    std::string get_name() const;
    std::string get_desc() const;
    const std::vector<std::string>& get_lore() const;
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
extern Item clock_hand;

// Combining stuff
extern std::map<std::pair<std::string, std::string>, Item> combination_recipes;
std::pair<std::string, std::string> make_combo_key(std::string a, std::string b);
void initialise_combination_recipes();

// Puzzle stuff
extern std::map<std::pair<std::string, std::string>, bool> puzzle_recipes;
std::pair<std::string, std::string> make_puzzle_key(std::string item, std::string object);
void initialise_puzzle_solutions();
