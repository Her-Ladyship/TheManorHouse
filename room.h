
#pragma once

#include <string>
#include <vector>

#include "helpers.h"
#include "player.h"
#include "object.h"

class Room {
private:
    std::string name;
    std::vector<std::string> description;
    Coords location;
    std::vector<std::string> exits;
    std::vector<Item> items;
    std::vector<Object> objects;
    std::vector<std::string> locked_exits;

public:
    Room(std::string n, std::vector<std::string> d, Coords l, std::vector<std::string> e, std::vector<Item> i, std::vector<Object> o)
        : name(n), description(d), location(l), exits(e), items(i), objects(o) {
    }

    // getters
    std::string get_name() const;
    const std::vector<std::string>& get_description() const;
    Coords get_location() const;
    const std::vector<std::string>& get_exits() const;

    // mutable accessors (unchanged behaviour)
    std::vector<Item>& get_items();
    std::vector<Object>& get_objects();

    // read-only accessors (new overloads)
    const std::vector<Item>& get_items() const;
    const std::vector<Object>& get_objects() const;

    void set_item(const Item & i);
    void set_object(const Object & o);
    void add_exit(std::string direction);
    void set_description(std::string new_text, int text_num);

    bool is_exit_locked(const std::string& direction) const;
    void lock_exit(const std::string& direction);
    void unlock_exit(const std::string& direction);
    bool has_exit(const std::string& direction) const;

    std::string room_direction_list();
    std::string room_item_list();
    std::string room_interactable_list();
};

// Room list reference
extern std::vector<Room> room_list;