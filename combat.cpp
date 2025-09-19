
#include <algorithm>
#include <unordered_set>

#include "combat.h"
#include "player.h"
#include "game.h"
#include "keys.h"

// Find the first consumable in the player's inventory; return its index or -1.
static int find_first_consumable_index(const Player& p) {
    const auto& inv = p.get_inventory();
    for (int i = 0; i < static_cast<int>(inv.size()); ++i) {
        if (inv[i].is_consumable() && inv[i].get_heal_amount() > 0) return i;
    }
    return -1;
}

void use_first_consumable(Game& g) {
    // If you’ve got a defined max HP somewhere, use it; otherwise 100 matches the UI.
    const int MAX_HP = 100;

    int idx = find_first_consumable_index(g.player);
    if (idx < 0) {
        g.combat_log.push_back("You fumble for a remedy, but have none.");
        return;
    }

    // Already full? Don’t waste the item.
    if (g.player.get_health() >= MAX_HP) {
        g.combat_log.push_back("You're already at full health.");
        return;
    }

    // Snapshot + apply heal, remove the item, log it.
    auto& inv = g.player.get_inventory();
    Item it = inv[idx]; // copy before erasing
    int heal = std::max(0, it.get_heal_amount());

    int new_hp = std::min(MAX_HP, g.player.get_health() + heal);
    g.player.set_health(new_hp);

    inv.erase(inv.begin() + idx);

    g.combat_log.push_back("You use the " + it.get_name() + ". (+" + std::to_string(heal) + " HP)");
}

// how many rows are in the Consumables panel (grouped by name)
static int count_consumable_rows(const Player& p) {
    std::unordered_set<std::string> names;
    for (const Item& it : p.get_inventory())
        if (it.is_consumable()) names.insert(it.get_name());
    return static_cast<int>(names.size());
}

static void clamp_cons_cursor(Game& g) {
    int n = count_consumable_rows(g.player);
    if (n <= 0) { g.consumable_cursor = 0; return; }
    if (g.consumable_cursor < 0)         g.consumable_cursor = 0;
    if (g.consumable_cursor >= n)        g.consumable_cursor = n - 1;
}

// utility: does `raw` represent an arrow-prefix from _getch() ?
static bool is_arrow_prefix(int raw) {
    return raw == Keys::Prefix0 || raw == static_cast<unsigned char>(Keys::PrefixExt);
}