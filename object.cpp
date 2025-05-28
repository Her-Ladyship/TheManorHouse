
#include "object.h"

// ----- Method Definitions -----
string Object::get_name() { return name; }
string Object::get_interaction_type() { return interaction_type; }
vector<string> Object::get_result_text() { return result_text; }
vector<string> Object::get_repeat_text() { return repeat_text; }
bool Object::has_been_used() { return used; }
void Object::mark_used() { used = true; }
Item Object::get_revealed_item() { return revealed_item; }
void Object::add_revealed_item(Item i) { revealed_item = i; }
string Object::get_unlock_direction() { return unlock_direction; }

// ----- Objects -----

Object chair(
    "Rocking Chair",
    "reveal",
    {
        "You nudge the chair aside.",
        "Beneath one of the rockers lies a coin.",
        "You pocket it without thinking.",
        "",
        "The chair begins to rock.",
        "No breeze. No sound.",
        "Just motion."
    },
    {
        "",
        "The chair continues to rock gently.",
        "",
        "Back and forth. Back and forth.",
        "",
        "It no longer hides anything.",
        ""
    }, "", coin
);

Object knocker(
    "Door Knocker",
    "unlock",
    {
        "",
        "The metal is heavy in your hand.",
        "You knock once - sharp and sudden.",
        "",
        "Somewhere inside, a lock clicks open.",
        "",
        ""
    },
    {
        "",
        "",
        "The knocker sits still against the door.",
        "",
        "Whatever it was meant to do, it's done.",
        "",
        ""
    }, "North"
);



//#include "object.h"
//
//// ----- Method Definitions -----
//
//string Object::get_name() { return name; }
//string Object::get_description() { return description; }
//string Object::get_interaction_type() { return interaction_type; }
//string Object::get_result_text() { return result_text; }
//string Object::get_repeat_text() { return repeat_text; }
//bool Object::has_been_used() { return used; }
//void Object::mark_used() { used = true; }
//Item Object::get_revealed_item() { return revealed_item; }
//
//// ----- Object Declarations -----
//
//Object chair("Rocking Chair", "", "flavour", "Any old shit...");
//Object knocker(
//    "Door Knocker",
//    "An old brass knocker shaped like a lion's head. It seems oddly warm to the touch.",
//    "unlock",
//    "You hear a *click* as the door unlocks itself.",
//    "The knocker sits still. The door is already unlocked."
//);
