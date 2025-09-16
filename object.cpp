
#include "object.h"

// ----- Method Definitions -----
std::string Object::get_name() const { return name; }
std::string Object::get_interaction_type() const { return interaction_type; }
const std::vector<std::string>& Object::get_result_text() const { return result_text; }
const std::vector<std::string>& Object::get_repeat_text() const { return repeat_text; }
bool Object::has_been_used() const { return used; }
void Object::mark_used() { used = true; }
void Object::mark_unused() { used = false; }
Item Object::get_revealed_item() const { return revealed_item; }
void Object::add_revealed_item(Item i) { revealed_item = i; }
std::string Object::get_unlock_direction() const { return unlock_direction; }
const std::vector<std::string>& Object::get_puzzle_success_text() const { return puzzle_success_text; }
bool Object::is_locked() const { return locked; }
void Object::set_locked(bool val) { locked = val; }

// ----- Objects -----

Object chair("Rocking Chair", "reveal", // PORCH
    {"You nudge the chair aside.",
    "Beneath one of the rockers lies a coin.",
    "You pocket it without thinking.",
    "",
    "The chair begins to rock.",
    "No breeze. No sound.",
    "Just motion."},
    {        "",
    "The chair continues to rock gently.",
    "",
    "Back and forth. Back and forth.",
    "",
    "It no longer hides anything.",
    "" }, "", {}, coin);

Object knocker("Door Knocker", "unlock", // PORCH
    {"",
    "The metal is heavy in your hand.",
    "You knock once - sharp and sudden.",
    "",
    "Somewhere inside, a lock clicks open.",
    "",
    ""},
    {"",
    "",
    "The knocker sits still against the door.",
    "",
    "Whatever it was meant to do, it's done.",
    "",
    ""}, "North");

Object bureau("Bureau", "conditional", // HALLWAY
    {"",
    "You try the drawer.",
    "No keyhole. No obvious mechanism.",
    "",
    "It refuses to budge.",
    "You press harder - nothing.",
    ""},
    {"",
    "You already emptied the drawer.",
    "",
    "It yawns open like a mouth missing its teeth.",
    "",
    "Dark and cold and growling.",
    ""}, "",
    {"The drawer lies ajar.",
    "The mirror frame has broken the lock.",
    "",
    "Amid torn paper and dust lies a key.",
    "It hums against your skin the moment you touch it.",
    "",
    "The rest of the drawer is empty." }, spare_key, false, true);


Object kitchen_drawer("Drawer", "reveal", // KITCHEN
    {"The drawer slides out smoothly,",
    "like it was expecting you.",
    "Inside, among the dust and crumbs, is a salt packet.",
    "It's heavier than it should be.",
    "",
    "You take it, trying not to think",
    "too hard about why it's warm."},
    {"",
    "The drawer rattles faintly when touched.",
    "",
    "Its gift already claimed, it now only offers dust.",
    "",
    "The air tastes faintly briny here.",
    "" }, "", {}, salt_packet);

Object ceiling_fan("Ceiling Fan", "puzzle", // KITCHEN
    {"The fan spins lazily overhead.",
    "A metal whistle dangles from a frayed cord,",
    "tauntingly out of reach.",
    "",
    "Even jumping wouldn't help.",
    "You need something long enough to knock it loose.",
    ""},
    {"",
    "",
    "The fan still spins, but the whistle is gone.",
    "",
    "You've already retrieved what you needed.",
    "",
    "" }, "", 
    {"",
    "You jab the broom upward. The whistle drops",
    "with a metallic clink, landing by your feet.",
    "",
    "You discard the broken broom and pocket",
    "the whistle. The fan keeps spinning, slowly.",
    "" }, whistle);

Object mirror("Mirror", "puzzle", // HALLWAY
    {"",
    "A mirror hangs awkwardly against the wall.",
    "Its surface is grimy, but beneath the filth",
    "your reflection feels... off.",
    "",
    "The frame is warped, like it's been twisted by heat.",
    ""},
    {"", 
    "The mirror is shattered. Shards glitter on the floor.",
    "Your face is still in some of them, watching you.",
    "",
    "The frame has fallen sideways.",
    "It made such a noise for something so flimsy.",
    ""}, "",
    {"You raise the whistle to your lips and blow.",
    "The pitch scrapes something just behind your eyes.",
    "",
    "The mirror shatters. The frame tumbles down with a thud,",
    "striking the bureau beneath it. You hear a click.",
    "",
    "You pocket one of the sharper shards.",
    ""}, mirror_shard);

Object keyhole("Keyhole", "puzzle", // HALLWAY
    {"",
    "At eye level, in the wood panelling,",
    "you spot a strange keyhole.",
    "",
    "Through it, you glimpse a room to the west.",
    "The lounge?",
    ""},
    {"The keyhole is empty now.",
    "Whatever locked mechanism it held has been triggered.",
    "",
    "The door to the west stands slightly ajar.",
    "You still see the lounge beyond.",
    "Only now it sees you back.",
    ""}, "West",
    {"The key slides in with a quiet finality.",
    "You turn it. Something clicks deep within the wood.",
    "",
    "The door to the west creaks open.",
    "",
    "The lounge breathes in your direction.",
    ""});

Object kitchen_setting("Table Setting", "flavour", // KITCHEN
    {"A place is set at the table.",
    "",
    "Plate, cutlery, glass - all covered",
    "with a fine layer of dust.",
    "",
    "The chair is tucked in.",
    "The glass is half full with water."},
    { "The setting hasn't changed.",
    "It still waits for someone who won't arrive.",
    "",
    "The water level never lowers.",
    "The glass never clouds.",
    "",
    "The chair remains tucked in."});

Object sofa("Sofa", "flavour", // LOUNGE
    {"You press a hand into the cushion.",
    "Dust puffs up in a tired little cloud.",
    "",
    "The leather is worn and sticky.",
    "Something creaks inside the frame.",
    "",
    "It doesn't look safe to sit."},
    {"",
    "You've seen enough of the sofa.",
    "",
    "It sighs when you touch it,",
    "like an old lung puffing out air.",
    "",
    ""});

Object mantle_clock("Clock", "reveal", // LOUNGE
    {"A small clock ticks softly.",
    "The hands show the wrong time.",
    "",
    "When you lift it, something rattles inside.",
    "A piece slides free and clinks onto the hearth.",
    "",
    "You pocket the clock hand."},
    {"",
    "",
    "The clock still ticks, faint and stubborn.",
    "",
    "Its face looks emptier without the hand.",
    "",
    ""}, "", {}, clock_hand);

Object fireplace("Fireplace", "encounter", // LOUNGE
    {"Cold ash slumps in the grate.",
    "You lean closer. The smell is wrong,",
    "too sweet and too sour.",
    "",
    "Something shifts in the darkness.",
    "Bone scrapes against brick.",
    "A skeleton pulls itself from the hearth."},
    {"",
    "",
    "Blackened bricks, scattered ash.",
    "",
    "Whatever waited here is gone.",
    "",
    ""});
