
#pragma once

#include <string>
#include <vector>

#include "helpers.h"
#include "player.h"
#include "object.h"
#include "conio.h"

using namespace std;

class Room {
private:
    string name;
    vector<string> description;
    Coords location;
    vector<string> exits;
    vector<Item> items;
    vector<Object> objects;
    vector<string> locked_exits;

public:
    Room(string n, vector<string> d, Coords l, vector<string> e, vector<Item> i, vector<Object> o)
        : name(n), description(d), location(l), exits(e), items(i), objects(o) {
    }

    string get_name();
    vector<string> get_description();
    Coords get_location();
    vector<string> get_exits();
    vector<Item>& get_items();
    vector<Object>& get_objects();

    void set_item(Item i);
    void set_object(Object o);
    void add_exit(string direction);

    bool is_exit_locked(const string& direction) const;
    void lock_exit(const string& direction);
    void unlock_exit(const string& direction);
    bool has_exit(const string& direction) const;
};

// Function prototypes
Room* find_room_by_coords(vector<Room>& rooms, Coords target);
string room_direction_list(Room*& current_room);
string room_item_list(Room*& current_room);
string room_interactable_list(Room*& current_room);
void change_room(string& question, vector<string>& option, Player& player, Room*& current_room,
    string& error_message, GameState& game_state, vector<string>& prompt);
void initialise_locked_doors();

// Room list reference
extern vector<Room> room_list;