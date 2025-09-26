
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
    bool consumable = false;
    int heal_amount = 0;
    bool throwable = false;
    int  damage_amount = 0;

public:
    Item() : name(""), desc(""), lore({}) {}
    Item(std::string n, std::string d, std::vector<std::string> l) : name(n), desc(d), lore(l) {}

    std::string get_name() const;
    std::string get_desc() const;
    const std::vector<std::string>& get_lore() const;

    bool is_consumable() const;
    void set_consumable(bool v);
    int  get_heal_amount() const;
    void set_heal_amount(int v);

    bool is_throwable() const;
    void set_throwable(bool v);
    int  get_damage_amount() const;
    void set_damage_amount(int v);
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
extern Item curio_hook;
extern Item fire_axe;
extern Item steel_parasol;
extern Item paperweight;
extern Item hearth_poker;
extern Item letter_opener;
extern Item ashwood_cane;
extern Item bandage;
extern Item field_dressing;
extern Item rock;
extern Item smelling_salts;
extern Item nice_cuppa;
extern Item suture_kit;
extern Item old_sandwich;
extern Item rotten_fish;
extern Item throat_sweet;
extern Item brandy;

// Combining stuff
extern std::map<std::pair<std::string, std::string>, Item> combination_recipes;
std::pair<std::string, std::string> make_combo_key(std::string a, std::string b);
void initialise_combination_recipes();

// Puzzle stuff
extern std::map<std::pair<std::string, std::string>, bool> puzzle_recipes;
std::pair<std::string, std::string> make_puzzle_key(std::string item, std::string object);
void initialise_puzzle_solutions();
