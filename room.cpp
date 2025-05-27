
#include "room.h"
#include "screens.h"

// ----- Room Getters -----

string Room::get_name() { return name; }

vector<string> Room::get_description() { return description; }

Coords Room::get_location() { return location; }

vector<string> Room::get_exits() { return exits; }

vector<Item>& Room::get_items() { return items; }

vector<Object> Room::get_objects() { return objects; }

// ----- Room Setters -----

void Room::set_item(Item i) { items.push_back(i); }

void Room::set_object(Object o) { objects.push_back(o); }

// ----- Room List Definitions -----

Room porch("Porch",
    {"The old porch groans under your weight. Every board bends in slow, aching protest.",
    "Faded paint flakes from the railings, drifting aimlessly in the breeze." ,
    "A warped rocking chair sits motionless at the edge of the boards.",
    "Something about the silence feels deliberate - like it's waiting for you to speak first.",
    "The doorknob ahead is warm to the touch. The wind, meanwhile, is not."},
    { 0, 0 }, { "North" },
    { coin, bell, lemon, salt_packet },
    { chair, knocker}
);

Room hallway("Hallway",
    {"The hallway is narrow, the walls pressing in like they've grown tired of standing apart.",
    "Dust clings to picture frames whose subjects have faded into blankness.",
    "A threadbare rug trails down the centre, marked with paths worn by long-forgotten feet.",
    "Light filters in through grime-caked windows, casting shadows that don't quite match the shapes.",
    "Behind you, the porch creaks once. Then nothing."},
    { 0, 1 }, { "South", "East", "West" },
    { broken_fork, wax_finger, whistle },
    {}
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
    {},
    {}
);

// Master room list
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

string room_direction_list(Room*& current_room) {
    string direction_list;
    for (string direction : current_room->get_exits()) {
        direction_list += direction + ", ";
    }
    if (direction_list.length() >= 2) {
        direction_list = direction_list.substr(0, direction_list.length() - 2);
    }
    return direction_list;
}

string room_item_list(Room*& current_room) {
    string item_list;
    for (Item item : current_room->get_items()) {
        item_list += item.get_name() + ", ";
    }
    if (item_list.length() >= 2) {
        item_list = item_list.substr(0, item_list.length() - 2);
    }
    return item_list;
}

string room_interactable_list(Room*& current_room) {
    string object_list;
    for (Object object : current_room->get_objects()) {
        object_list += object.get_name() + ", ";
    }
    if (object_list.length() >= 2) {
        object_list = object_list.substr(0, object_list.length() - 2);
    }
    return object_list;
}

void change_room(string& question, vector<string>& option, Player& player, Room*& current_room,
    string& error_message, GameState& game_state, vector<string>& prompt) {

    question = "Which direction do you want to move?";

    option[0] = "1. North";
    option[1] = "2. South";
    option[2] = "3. East";
    option[3] = "4. West";
    option[4] = "";
    option[5] = "5. Back to Menu";

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
            // Invalid input — stay in loop
            break;
        }

        if (!waiting_for_input) {
            Room* next_room = find_room_by_coords(room_list, new_location);

            if (next_room != nullptr) {
                player.set_location(new_location);
                load_main_question(question, option);
                error_message = "";
            }
            else {
                error_message = "You can't go that way. There's nothing there.";
                waiting_for_input = true; // loop again since move failed
            }
        }
    }

    load_main_question(question, option);
}
