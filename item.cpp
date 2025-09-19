
#include "item.h"
#include "colours.h"

#include <map>
#include <utility>
#include <string>
#include <vector>

// ----- Method Definitions -----
std::string Item::get_name() const { return name; }
std::string Item::get_desc() const { return desc; }
const std::vector<std::string>& Item::get_lore() const { return lore; }

bool Item::is_consumable() const { return consumable; }
void Item::set_consumable(bool v) { consumable = v; }
int Item::get_heal_amount() const { return heal_amount; }
void Item::set_heal_amount(int v) { heal_amount = v; }

bool Item::is_throwable() const { return throwable; }
void Item::set_throwable(bool v) { throwable = v; }
int  Item::get_damage_amount() const { return damage_amount; }
void Item::set_damage_amount(int v) { damage_amount = v; }

// ----- Item Definitions -----
Item coin("Coin", "A worn brass coin with no visible markings.", // PORCH
    { "The coin bears no nation, no ruler, no date.",
     "There is no front, no back, and no clear way",
     "to spend it. It has been found in coat linings,",
     "sewer grates, rain gutters, and one piano.",
     "No one ever remembers dropping it." }
);

Item leaf("Leaf", "A dry, red leaf that doesn't match the season.", // PORCH
    { "The leaf remains untouched by decay. Its colour",
     "is vivid, unnatural, and never fades - even",
     "under moonlight. Scholars once attempted to",
     "classify it. Many of them died.",
     "The rest declined to try again." }
);

Item bell("Bell", "A small handbell with a cracked mouth.", // HALLWAY
    { "Crafted from bronze and left unmarked.",
     "Too light for ceremony. Too plain for display.",
     "No chime remains. Only a faint metallic scent,",
     "and the memory of motion held in the handle.",
     "Its maker is unknown. Its purpose, uncertain." }
);

Item mirror_shard("Mirror Shard", "A jagged sliver of glass.", // HALLWAY - THROWABLE 10DMG
    { "It reflects nothing. Not you, not the room,",
     "not even the light. When you turn it just so,",
     "you hear breathing - slow, shallow, and close.",
     "It seems to bend on its own if ignored.",
     "10 DMG" }
);
static bool _mirror_flags = (mirror_shard.set_throwable(true), mirror_shard.set_damage_amount(10), true);

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

Item salt_packet("Salt Packet", "A single-serve packet of salt, unopened.", // KITCHEN
    { "It has no brand, no expiry date, no tear line.",
     "The grains inside move excitedly when shaken.",
     "You could swear it's heavier than it should be.",
     "Every attempt to open it fails, and",
     "you're not sure what would happen if it did open." }
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

Item tarot("Tarot Card", "A card from a traditional tarot deck.",
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
     "It seems too heavy for sweeping." }
);

Item knife("Knife", "A kitchen knife with a thin, tapered blade.", // KITCHEN - THROWABLE 15DMG
    { "You found it on the kitchen floor.",
     "Not dropped. Placed.",
     "The edge gleams under the light.",
     "It doesn't look like it's ever touched food.",
     "15 DMG"}
);
static bool _knife_flags = (knife.set_throwable(true), knife.set_damage_amount(15), true);

Item teacup("Teacup", "A fine porcelain teacup with hairline cracks.",
    { "The pattern depicts a hunting scene that seems to",
     "change every time you look away. There's a drop",
     "of something red dried near the rim.",
     "It smells faintly of bergamot and rust.",
     "It's never empty for long." }
);

Item milk_tooth("Milk Tooth", "A tooth wrapped in ribbon.",
    { "Too large for a child. Too small for an adult.",
     "It was left beneath a pillow long ago.",
     "Sometimes it clicks against itself",
     "when no one's speaking.",
     "A dead message from another place." }
);

Item ticket("Ticket Stub", "A faded paper stub for an unknown event.",
    { "No date. No location. Just a seat number:",
     "\"18G\". The ink glows faintly under candlelight.",
     "When you hold it and close your eyes",
     "you smell popcorn,",
     "and hear the low rumble of applause." }
);

Item photo("Photograph", "A black & white photo of a house that doesn't exist.",
    { "Blurry at the edges. Burnt at one corner.",
     "The windows are all lit,",
     "but there's no life inside.",
     "There's something watching from the attic.",
     "On the back, your name is written in ash." }
);

Item clock_hand("Clock Hand", "A thin metal clock hand, cool to the touch.", // LOUNGE - THROWABLE 10 DMG
    { "It fell off of the clock in the lounge.",
     "Slightly bent at the tip, like it resisted turning.",
     "It feels heavier than its size suggests, and",
     "holding it makes your own pulse feel off-beat.",
     "10 DMG"}
);
static bool _chand_flags = (clock_hand.set_throwable(true), clock_hand.set_damage_amount(10), true);

Item curio_hook("Curio Hook", "A slender brass hook for lifting display lids.", // STARTER WEAPON (Curious)
    { "Polished by other people's fingers;",
     "made to lift lids and poke theories.",
     "It remembers every \"Just a quick look\"...",
     "and how that went.",
     "You'll only check for a second. Honest." }
);

Item fire_axe("Fire Axe", "A wall-cabinet axe with chipped red paint.", // STARTER WEAPON (Brave)
    { "The cabinet was already open;",
     "someone braver or clumsier got there first.",
     "It doesn't promise subtlety -",
     "just results.",
     "Try not to redecorate the doors." }
);

Item steel_parasol("Parasol", "A collapsible parasol with a steel spine.", // STARTER WEAPON (Timid)
    { "Looks delicate, acts decisive.",
     "Open, it keeps weather and witnesses off you;",
     "closed, it makes a very polite point.",
     "If anyone asks,",
     "it was self-defence from drizzle." }
);

Item paperweight("Paperweight", "A smooth black sphere, reassuringly heavy.", // STARTER WEAPON (Unbothered)
    { "A small planet for your pocket; gravity included.",
     "It rolls exactly where it wants,",
     "usually towards the problem.",
     "",
     "Zen by way of bludgeoning." }
);

Item hearth_poker("Poker", "A dark iron rod with a blunt end.", // STARTER WEAPON (Fiery)
    { "Raised in embers; opinionated about ash.",
     "Good at rearranging coals,",
     "better at rearranging attitudes.",
     "If it glows, put it down -",
     "unless the conversation is going badly." }
);

Item letter_opener("Letter Opener", "A tasteful brass blade for impatient readers.", // STARTER WEAPON (Precise)
    { "Finds the seam in everything; envelopes,",
     "arguments, the occasional knot.",
     "Technically not a weapon,",
     "which is exactly why it's worrying.",
     "Please mind the stationery." }
);

Item ashwood_cane("Ashwood Cane", "A walking stick with a silver wolf's-head.", // STARTER WEAPON (Thoughtful)
    { "Helps you stand; helps others fall down.",
     "Tap-tap to think, swing-swing to conclude.",
     "The wolf on top looks wise,",
     "or at least convincingly judgmental.",
     "Either way, he hates you." }
);

Item bandage("Bandage", "A roll of linen secured with a pin.",  // CONSUMABLE 10HP
    { "Not sterile, but clean enough to keep you moving.",
     "Wrap, press, and breathe while the linen",
     "finds its way to your wounds.",
     "It smells faintly of soap and cupboards.",
     "+ 10HP" }
);
static bool _bandage_flags = (bandage.set_consumable(true), bandage.set_heal_amount(10), true);

Item field_dressing("Field Dressing", "A sealed pad with adhesive tape.",  // CONSUMABLE 20HP
    { "The pad knows where the blood wants to go",
     "and politely suggests it stay where it is.",
     "Instructions exist, somewhere;",
     "but you're doing fine without them.",
     "+ 20HP"}
);
static bool _fd_flags = (field_dressing.set_consumable(true), field_dressing.set_heal_amount(20), true);

Item rock("Rock", "A pocketable piece of bad ideas.",  // THROWABLE 5 DMG
    { "Fits the hand and fits most problems - ",
     "a solution you don't have to explain.",
     "Heavy enough to matter,",
     "and nobody will ask where you got it.",
     "5 DMG"}
);
static bool _rock_flags = (rock.set_throwable(true), rock.set_damage_amount(5), true);

// Combining stuff
std::map<std::pair<std::string, std::string>, Item> combination_recipes;

std::pair<std::string, std::string> make_combo_key(std::string a, std::string b) {
    return (a < b) ? std::make_pair(a, b) : std::make_pair(b, a);
}

Item salt_bomb("Salt Bomb", "A volatile mix of salt and lemon, wrapped in paper.", // THROWABLE 20 DMG
    { "The moment the two touched, they reacted.",
     "You don't know how, but this is now something",
     "you could throw at... something.",
     "You hope you won't need to.",
     "20 DMG" }
);
static bool _sb_flags = (salt_bomb.set_throwable(true), salt_bomb.set_damage_amount(20), true);

Item toll_chime("Toll Chime", "A fused object that rings softly when ignored.",
    { "The bell no longer swings. The coin is embedded",
     "at the rim, like it was always meant to be there.",
     "It makes no sound when struck - only when",
     "forgotten. It's heavier than it looks.",
     "And harder to lose." }
);

void initialise_combination_recipes() {
    combination_recipes[make_combo_key("Salt Packet", "Lemon")] = salt_bomb;
    combination_recipes[make_combo_key("Coin", "Bell")] = toll_chime;
}

// Puzzle Stuff
std::map<std::pair<std::string, std::string>, bool> puzzle_recipes;

std::pair<std::string, std::string> make_puzzle_key(std::string item, std::string object) {
    return std::make_pair(item, object);
}

void initialise_puzzle_solutions() {
    puzzle_recipes[make_puzzle_key("Broom", "Ceiling Fan")] = true;
    puzzle_recipes[make_puzzle_key("Whistle", "Mirror")] = true;
    puzzle_recipes[make_puzzle_key("Spare Key", "Keyhole")] = true;
}
