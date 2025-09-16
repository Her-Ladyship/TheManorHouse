
#pragma once

#include <string>
#include <vector>
#include "item.h"

class Object {
private:
    std::string name;
    std::string interaction_type;        // "flavour", "reveal", "unlock", etc.
    std::vector<std::string> result_text;     // First-time interaction result
    std::vector<std::string> repeat_text;     // Text shown on repeated interaction
    std::string unlock_direction;
    std::vector<std::string> puzzle_success_text;
    Item revealed_item;
    bool used;
    bool locked;

public:
    Object(std::string n, std::string type = "flavour",
        std::vector<std::string> result = {}, std::vector<std::string> repeat = {},
        std::string dir = "", std::vector<std::string> puzz = {},
        Item item = Item(), bool u = false, bool l = false)
        : name(n),
        interaction_type(type),
        result_text(result),
        repeat_text(repeat),
        unlock_direction(dir),
        puzzle_success_text(puzz),
        revealed_item(item),
        used(u),
        locked(l) {
    }

    std::string get_name() const;
    std::string get_interaction_type() const;
    const std::vector<std::string>& get_result_text() const;
    const std::vector<std::string>& get_repeat_text() const;
    bool has_been_used() const;
    void mark_used();
    void mark_unused();
    Item get_revealed_item() const;
    void add_revealed_item(Item i);
    std::string get_unlock_direction() const;
    const std::vector<std::string>& get_puzzle_success_text() const;
    bool is_locked() const;
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
extern Object sofa;
extern Object mantle_clock;
extern Object fireplace;
