
#include <algorithm>

#include "room.h"
#include "screens.h"

// ----- Room Getters -----
std::string Room::get_name() const { return name; }
const std::vector<std::string>& Room::get_description() const { return description; }
Coords Room::get_location() const { return location; }
const std::vector<std::string>& Room::get_exits() const { return exits; }

std::vector<Item>& Room::get_items() { return items; }
std::vector<Object>& Room::get_objects() { return objects; }

const std::vector<Item>& Room::get_items() const { return items; }
const std::vector<Object>& Room::get_objects() const { return objects; }

// ----- Room Setters -----

void Room::set_item(const Item & i) { items.push_back(i); }
void Room::set_object(const Object & o) { objects.push_back(o); }
void Room::add_exit(std::string direction) { exits.push_back(direction); }
void Room::set_description(std::string new_text, int text_num) {
    description[text_num - 1] = new_text;
}

// ----- Locked Exits -----

bool Room::is_exit_locked(const std::string& direction) const {
    return std::find(locked_exits.begin(), locked_exits.end(), direction) != locked_exits.end();
}

void Room::lock_exit(const std::string& direction) {
    if (!is_exit_locked(direction)) {
        locked_exits.push_back(direction);
    }
}

void Room::unlock_exit(const std::string& direction) {
    auto it = std::find(locked_exits.begin(), locked_exits.end(), direction);
    if (it != locked_exits.end()) {
        locked_exits.erase(it);
    }
}

bool Room::has_exit(const std::string& direction) const {
    return std::find(exits.begin(), exits.end(), direction) != exits.end();
}

// ----- Other Class Functions -----

std::string Room::room_direction_list() {
    std::string direction_list;

    for (const std::string& direction : get_exits()) {
        bool is_locked = is_exit_locked(direction);

        if (is_locked) {
            direction_list += "\x1B[91m\x1B[9m" + direction + "\x1B[0m, ";
        }
        else {
            direction_list += direction + ", ";
        }
    }

    if (direction_list.length() >= 2) {
        direction_list = direction_list.substr(0, direction_list.length() - 2);
    }

    return direction_list;
}

std::string Room::room_item_list() {
    std::string item_list;
    for (const Item& item : get_items()) {
        item_list += item.get_name() + ", ";
    }
    if (!item_list.empty()) item_list.erase(item_list.size() - 2);
    return item_list;
}

std::string Room::room_interactable_list() {
    std::string object_list;
    for (const Object& object : get_objects()) {
        object_list += object.get_name() + ", ";
    }
    if (!object_list.empty()) object_list.erase(object_list.size() - 2);
    return object_list;
}

// ----- Room List Definitions -----

Room porch("Porch",
    {"The old porch groans under your weight. Every board bends in slow, aching protest.",
    "Faded paint flakes from the railings, drifting aimlessly in the breeze." ,
    "A warped rocking chair sits motionless at the edge of the boards.",
    "Something about the silence feels deliberate - like it's waiting for you to speak first.",
    "The doorknob ahead is warm to the touch. The wind, meanwhile, is not."},
    { 0, 0 }, { "North" },
    { leaf, broom },
    { chair, knocker}
);

Room hallway("Hallway",
    {"The hallway is narrow, the walls pressing in like they've grown tired of standing apart.",
    "Dust clings to picture frames whose subjects have faded into blankness.",
    "A threadbare rug trails down the centre, marked with paths worn by long-forgotten feet.",
    "A small bureau stands off to the side, with a grimy mirror hanging above.",
    "Behind you, the porch creaks once. Then nothing."},
    { 0, 1 }, { "North", "South", "East", "West"},
    { bell, lavender },
    { bureau, mirror, keyhole }
);

Room lounge("Lounge",
    {"Heavy curtains hang stiffly over the windows, sealing the room in perpetual dusk.",
    "A cracked leather sofa slumps in the centre, its cushions sunken and stained.",
    "The fireplace yawns open, cold and black, filled with ashes that look too recent.",
    "On the mantle, a clock ticks softly - though its hands never move.",
    "The air smells faintly of perfume and something sour beneath it."},
    { -1, 1 }, { "East" },
    {},
    { sofa, mantle_clock, fireplace }
);

Room kitchen("Kitchen",
    {"The kitchen is silent, but not still. A ceiling fan spins lazily, stirring stale air.",
    "Dishes rest in the sink beneath a window crusted with grime.",
    "The fridge hums softly - a sound that feels too loud in a room this quiet.",
    "Someone set the table for one. There's dust on the plate, but the glass is still half full.",
    "A knife lies on the floor, a little too carefully placed to be an accident."},
    { 1, 1 }, { "West" },
    { broken_fork, lemon, knife },
    { kitchen_drawer, ceiling_fan, kitchen_setting }
);

// ----- Master Room List -----
std::vector<Room> room_list = { porch, hallway, lounge, kitchen };