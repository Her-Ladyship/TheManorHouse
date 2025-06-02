
#include "item.h"

// ----- Method Definitions -----

string Item::get_name() const { return name; }

string Item::get_desc() { return desc; }

vector<string> Item::get_lore() { return lore; }

// ----- Item Definitions -----

Item coin("Coin", "A worn brass coin with no visible markings.", // PORCH
    {"The coin bears no nation, no ruler, no date.",
    "There is no front, no back, and no clear way",
    "to spend it. It has been found in coat linings,",
    "sewer grates, rain gutters, and one piano.",
    "No one ever remembers dropping it."}
);

Item leaf("Leaf", "A dry, red leaf that doesn't match the season.", // PORCH
    {"The leaf remains untouched by decay. Its colour",
    "is vivid, unnatural, and never fades - even",
    "under moonlight. Scholars once attempted to",
    "classify it. Many of them died.",
    "The rest declined to try again."}
);

Item bell("Bell", "A small handbell with a cracked mouth.", // HALLWAY
    {"Crafted from bronze and left unmarked.",
    "Too light for ceremony. Too plain for display.",
    "No chime remains. Only a faint metallic scent,",
    "and the memory of motion held in the handle.",
    "Its maker is unknown. Its purpose, uncertain."}
);

Item mirror_shard("Mirror Shard", "A jagged sliver of glass.", // HALLWAY
    { "It reflects nothing. Not you, not the room,",
    "not even the light. When you turn it just so,",
    "you hear breathing - slow, shallow, and close.",
    "It seems to bend on its own if ignored",
    "as if trying to crack itself again." }
);

Item broken_fork("Broken Fork", "A silver fork with just one surviving tine.", // KITCHEN
    { "Not bent, but with two tines snapped off.",
    "The handle is engraved with initials that",
    "shift slightly each time you blink.",
    "People ask what it's for, then forget asking,",
    "entranced by the dull shine." }
);

Item lavender("Lavender Sachet", "A faded cloth pouch tied with lavender ribbon.", // HALLWAY
    { "The scent is gentle, persistent, and oddly",
    "personal. It calms your breath and steadies",
    "your thoughts - even the ones that don't",
    "quite belong to you. It hums faintly in moonlight.",
    "It was meant to be a gift, once." }
);

Item wax_finger("Wax Finger", "A pale wax replica of a human finger, slightly melted.", // STARTING ITEM
    { "It is warm to the touch, even in cold rooms.",
    "The nail is painted black, chipped at the edge.",
    "Holding it gives the vague sensation of",
    "being counted. You're unsure what number you are.",
    "It smells faintly of smoke and cloves." }
);

Item notebook("Notebook", "A water-damaged notebook with soft blue covers.", // STARTING ITEM
    { "The pages are warped, the ink half-faded.",
    "Only the last few entries are readable.",
    "They describe dreams you've had - or will have.",
    "One page is torn out. Another is still drying.",
    "The spine creaks like an old apology." }
);

Item salt_packet("Salt Packet", "A single-serve packet of salt, unopened.", // KITCHEN
    { "It has no brand, no expiry date, no tear line.",
    "The grains inside move exictedly when shaken.",
    "You could swear it's heavier than it should be.",
    "Every attempt to open it fails.",
    "You're not sure what would happen if it did open." }
);

Item spare_key("Spare Key", "A tarnished brass key with no tag.", // HALLWAY
    { "You recognise it. You don't know why.",
    "You don't know what it's the key for...",
    "Keeping it makes you feel watched, and yet",
    "leaving it behind feels like a betrayal.",
    "It rattles even when you walk carefully." }
);

Item lemon("Lemon", "A fresh lemon with a single bite missing.", // KITCHEN
    { "The bite is clean. Human-sized.",
    "There's no juice trail. No scent of citrus.",
    "It's never spoiled - not even browned.",
    "You don't remember taking it, but it",
    "always appears near the top of your bag." }
);

Item whistle("Whistle", "A polished metal whistle on a frayed cord.", // KITCHEN
    { "The kind used by coaches, referees, or people trying",
    "to seem in control. The engraving is too worn to read.",
    "It works perfectly, though the sound is sharp and",
    "slightly off-pitch - like it's echoing something else.",
    "It tastes faintly of copper." }
);

Item tarot("Tarot Card", "A card from a traditional tarot deck.", // STARTING ITEM
    { "Illustrated with a tower struck by lightning,",
    "people falling, arms flailing in panic.",
    "The ink is faded around the edges, like it's been drawn",
    "too many times. It was upright when you found it.",
    "You haven't turned it over since." }
);

Item broom("Broom", "A wooden broom with a scorched handle.", // PORCH
    { "The bristles are worn down unevenly,",
    "like it was used to scrub something that resisted.",
    "The handle is blackened near the base.",
    "Heat damage, maybe.",
    "It seems too heavy for sweeping."});

Item knife("Knife", "A kitchen knife with a thin, tapered blade.", // KITCHEN
    { "You found it on the kitchen floor.",
    "Not dropped. Placed.",
    "",
    "The edge gleams under the light.",
    "It doesn't look like it's ever touched food." });

Item teacup("Teacup", "A fine porcelain teacup with hairline cracks.", // STARTING ITEM
    { "The pattern depicts a hunting scene that seems to",
    "change every time you look away. There's a drop",
    "of something red dried near the rim.",
    "It smells faintly of bergamot and rust.",
    "It's never empty for long." });

Item milk_tooth("Milk Tooth", "A tooth wrapped in ribbon.", // STARTING ITEM
    { "Too large for a child. Too small for an adult.",
    "It was left beneath a pillow long ago.",
    "Sometimes it clicks against itself",
    "when no one's speaking.",
    "A dead message from another place." });

Item ticket("Ticket Stub", "A faded paper stub for an unknown event.", // STARTING ITEM
    { "No date. No location. Just a seat number:",
    "\"18G\". The ink glows faintly under candlelight.",
    "When you hold it and close your eyes",
    "you smell popcorn,",
    "and hear the low rumble of appluase." });

Item photo("Photograph", "A black & white photo of a house that doesn't exist.", // STARTING ITEM
    { "Blurry at the edges. Burnt at one corner.",
    "The windows are all lit,",
    "but there's no life inside.",
    "There's something watching from the attic.",
    "On the back, your name is written in ash."});

// Combining stuff
map<pair<string, string>, Item> combination_recipes;

pair<string, string> make_combo_key(string a, string b) {
    return (a < b) ? make_pair(a, b) : make_pair(b, a);
}

Item salt_bomb("Salt Bomb", "A volatile mix of salt and lemon, wrapped in paper.",
    { "The moment the two touched, they reacted.",
      "You don't know how, but this is now something",
      "you could throw at... something. You hope",
      "you won't need to. It pulses faintly in your",
      "bag like it resents existing." });

Item toll_chime("Toll Chime", "A fused object that rings softly when ignored.",
    { "The bell no longer swings. The coin is embedded",
      "at the rim, like it was always meant to be there.",
      "It makes no sound when struck - only when",
      "forgotten. It's heavier than it looks.",
      "And harder to lose." });

void initialise_combination_recipes() {
    combination_recipes[make_combo_key("Salt Packet", "Lemon")] = salt_bomb;
    combination_recipes[make_combo_key("Coin", "Bell")] = toll_chime;
}

// Puzzle Stuff
map<pair<string, string>, bool> puzzle_recipes;

pair<string, string> make_puzzle_key(string item, string object) {
    return make_pair(item, object);
}

void initialise_puzzle_solutions() {
    puzzle_recipes[make_puzzle_key("Broom", "Ceiling Fan")] = true;
    puzzle_recipes[make_puzzle_key("Whistle", "Mirror")] = true;
    puzzle_recipes[make_puzzle_key("Spare Key", "Keyhole")] = true;
}
