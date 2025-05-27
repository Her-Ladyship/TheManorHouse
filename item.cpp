
#include "item.h"

map<pair<string, string>, Item> combination_recipes;

// ----- Method Definitions -----

string Item::get_name() { return name; }

string Item::get_desc() { return desc; }

vector<string> Item::get_lore() { return lore; }

// ----- Item Definitions -----

Item coin("Coin", "A worn brass coin with no visible markings.",
    {"The coin bears no nation, no ruler, no date.",
    "There is no front, no back, and no clear way",
    "to spend it. It has been found in coat linings,",
    "sewer grates, rain gutters, and one piano.",
    "No one ever remembers dropping it."}
);

Item leaf("Leaf", "A dry, red leaf that doesn't match the season.",
    {"The leaf remains untouched by decay. Its colour",
    "is vivid, unnatural, and never fades - even",
    "under moonlight. Scholars once attempted to",
    "classify it. Many of them died.",
    "The rest declined to try again."}
);

Item bell("Bell", "A small handbell with a cracked mouth.",
    {"Crafted from bronze and left unmarked.",
    "Too light for ceremony. Too plain for display.",
    "No chime remains. Only a faint metallic scent,",
    "and the memory of motion held in the handle.",
    "Its maker is unknown. Its purpose, uncertain."}
);

Item mirror_shard("Mirror Shard", "A jagged sliver of glass wrapped in black thread.",
    { "It reflects nothing. Not you, not the room,",
    "not even the light. When you turn it just so,",
    "you hear breathing - slow, shallow, and close.",
    "The thread winds tighter on its own if ignored",
    "as if trying to crack the shard again." }
);

Item broken_fork("Broken Fork", "A silver fork with just one surviving tine.",
    { "Not bent, but with two tines snapped off.",
    "The handle is engraved with initials that",
    "shift slightly each time you blink.",
    "People ask what it's for, then forget asking,",
    "entranced by the dull shine." }
);

Item lavender("Lavender Sachet", "A faded cloth pouch tied with lavender ribbon.",
    { "The scent is gentle, persistent, and oddly",
    "personal. It calms your breath and steadies",
    "your thoughts - even the ones that don't",
    "quite belong to you. It hums faintly in moonlight.",
    "It was meant to be a gift, once." }
);

Item wax_finger("Wax Finger", "A pale wax replica of a human finger, slightly melted.",
    { "It is warm to the touch, even in cold rooms.",
    "The nail is painted black, chipped at the edge.",
    "Holding it gives the vague sensation of",
    "being counted. You're unsure what number you are.",
    "It smells faintly of smoke and cloves." }
);

Item notebook("Notebook", "A water-damaged notebook with soft blue covers.",
    { "The pages are warped, the ink half-faded.",
    "Only the last few entries are readable.",
    "They describe dreams you've had - or will have.",
    "One page is torn out. Another is still drying.",
    "The spine creaks like an old apology." }
);

Item salt_packet("Salt Packet", "A single-serve packet of salt, unopened.",
    { "It has no brand, no expiry date, no tear line.",
    "The grains inside move exictedly when shaken.",
    "You could swear it's heavier than it should be.",
    "Every attempt to open it fails.",
    "You're not sure what would happen if it did open." }
);

Item spare_key("Spare Key", "A tarnished brass key with no tag.",
    { "You recognise it. You don't know why.",
    "It fits no doors you've found... yet.",
    "Keeping it makes you feel watched, and yet",
    "leaving it behind feels like a betrayal.",
    "It rattles even when you walk carefully." }
);

Item lemon("Lemon", "A fresh lemon with a single bite missing.",
    { "The bite is clean. Human-sized.",
    "There's no juice trail. No scent of citrus.",
    "It's never spoiled - not even browned.",
    "You don't remember taking it, but it",
    "always appears near the top of your bag." }
);

Item whistle("Whistle", "A polished metal whistle on a frayed cord.",
    { "The kind used by coaches, referees, or people trying",
    "to seem in control. The engraving is too worn to read.",
    "It works perfectly, though the sound is sharp and",
    "slightly off-pitch - like it's echoing something else.",
    "It tastes faintly of copper." }
);

Item tarot("Tarot Card", "A card from a traditional tarot deck.",
    { "Illustrated with a tower struck by lightning,",
    "people falling, arms flailing in panic.",
    "The ink is faded around the edges, like it's been drawn",
    "too many times. It was upright when you found it.",
    "You haven't turned it over since." }
);

// Combining stuff
pair<string, string> make_combo_key(string a, string b) {
    return (a < b) ? make_pair(a, b) : make_pair(b, a);
}

void initialise_combination_recipes() {
    Item salt_bomb("Salt Bomb", "A volatile mix of salt and lemon, wrapped in paper.",
        { "The moment the two touched, they reacted.",
          "You don't know how, but this is now something",
          "you could throw at... something. You hope",
          "you won't need to. It pulses faintly in your",
          "bag like it resents existing." });

    Item toll_chime("Toll Chime", "A fused object that rings softly when moved.",
        { "The bell no longer swings. The coin is embedded",
          "at the rim, like it was always meant to be there.",
          "It makes no sound when struck - only when",
          "forgotten. It's heavier than it looks.",
          "And harder to lose." });

    combination_recipes[make_combo_key("Salt Packet", "Lemon")] = salt_bomb;
    combination_recipes[make_combo_key("Coin", "Bell")] = toll_chime;
}

