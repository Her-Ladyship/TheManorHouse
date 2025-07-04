
#include "room.h"
#include "screens.h"

// ----- Room Getters -----

string Room::get_name() { return name; }
vector<string> Room::get_description() { return description; }
Coords Room::get_location() { return location; }
vector<string> Room::get_exits() { return exits; }
vector<Item>& Room::get_items() { return items; }
vector<Object>& Room::get_objects() { return objects; }

// ----- Room Setters -----

void Room::set_item(Item i) { items.push_back(i); }
void Room::set_object(Object o) { objects.push_back(o); }
void Room::add_exit(string direction) { exits.push_back(direction); }
void Room::set_description(string new_text, int text_num) {
    description[text_num - 1] = new_text;
}

// ----- Locked Exits -----

bool Room::is_exit_locked(const string& direction) const {
    return find(locked_exits.begin(), locked_exits.end(), direction) != locked_exits.end();
}

void Room::lock_exit(const string& direction) {
    if (!is_exit_locked(direction)) {
        locked_exits.push_back(direction);
    }
}

void Room::unlock_exit(const string& direction) {
    auto it = find(locked_exits.begin(), locked_exits.end(), direction);
    if (it != locked_exits.end()) {
        locked_exits.erase(it);
    }
}

bool Room::has_exit(const string& direction) const {
    return find(exits.begin(), exits.end(), direction) != exits.end();
}

// ----- Other Class Functions -----

string Room::room_direction_list() {
    string direction_list;

    for (string& const direction : get_exits()) {
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

string Room::room_item_list() {
    string item_list;
    for (Item item : get_items()) {
        item_list += item.get_name() + ", ";
    }
    if (item_list.length() >= 2) {
        item_list = item_list.substr(0, item_list.length() - 2);
    }
    return item_list;
}

string Room::room_interactable_list() {
    string object_list;
    for (Object object : get_objects()) {
        object_list += object.get_name() + ", ";
    }
    if (object_list.length() >= 2) {
        object_list = object_list.substr(0, object_list.length() - 2);
    }
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
    {}
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
vector<Room> room_list = { porch, hallway, lounge, kitchen };

// ----- Room Utility Functions -----

Room* find_room_by_coords(vector<Room>& rooms, Coords target) {
    for (Room& room : rooms) {
        if (room.get_location().x == target.x && room.get_location().y == target.y) {
            return &room;
        }
    }
    return nullptr;
}

void change_room(string& question, vector<string>& option, Player& player, Room*& current_room,
    string& error_message, GameState& game_state, vector<string>& prompt) {

    question = "Which direction do you want to move?";
    option = { "1. North" , "2. South", "3. East", "4. West", "", "5. Back to Menu" };
    prompt = { "","","","","","","" };

    bool waiting_for_input = true;
    bool redraw = true;

    while (waiting_for_input) {

        if (redraw) {
            show_explore_screen(player, current_room, question, error_message, option, prompt);
            redraw = false;
        }        

        char key = _getch();

        Coords current = player.get_location();
        Coords new_location = current;

        switch (key) {
        case '1':
            new_location.y += 1;  // North
            waiting_for_input = false;
            redraw = true;
            break;
        case '2':
            new_location.y -= 1;  // South
            waiting_for_input = false;
            redraw = true;
            break;
        case '3':
            new_location.x += 1;  // East
            waiting_for_input = false;
            redraw = true;
            break;
        case '4':
            new_location.x -= 1;  // West
            waiting_for_input = false;
            redraw = true;
            break;
        case '5':
            waiting_for_input = false;
            redraw = true;
            break;
        default:
            // Invalid input � stay in loop
            break;
        }

        if (!waiting_for_input) {
            Room* next_room = find_room_by_coords(room_list, new_location);

            if (next_room != nullptr) {
                // Figure out which direction was attempted
                string direction;
                if (new_location.y > current.y) direction = "North";
                else if (new_location.y < current.y) direction = "South";
                else if (new_location.x > current.x) direction = "East";
                else if (new_location.x < current.x) direction = "West";

                if (current_room->is_exit_locked(direction)) {
                    error_message = "The door to the " + direction + " is locked.";
                    waiting_for_input = true; // Stay in the loop
                }
                else {
                    player.set_location(new_location);
                    current_room = next_room;
                    load_main_question(question, option);
                    error_message = "";
                }
            }
            else {
                error_message = "You can't go that way. There's nothing there.";
                waiting_for_input = true;
            }

        }
    }

    load_main_question(question, option);
}

void initialise_locked_doors() {
    room_list[0].lock_exit("North");
    room_list[1].lock_exit("West");
    room_list[1].lock_exit("North");
}
