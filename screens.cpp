
#include <conio.h>
#include <limits>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <array>
#include <unordered_map>

#include "screens.h"
#include "colours.h"
#include "lettering.h"
#include "room_ops.h"
#include "player.h"
#include "helpers.h"
#include "room.h"
#include "game.h"
#include "inventory.h"

const int ITEMS_PER_PAGE = 11;

namespace {
    constexpr size_t BOX_LINES = 10;

    void fit_lines(std::vector<std::string>& v, size_t n = BOX_LINES) {
        if (v.size() < n) v.insert(v.end(), n - v.size(), "");
        else if (v.size() > n) v.resize(n);
    }
}

static std::vector<std::string> build_consumables_list(const Player& p) {
    std::map<std::string, int> count;
    for (const Item& it : p.get_inventory()) {
        if (it.is_consumable()) count[it.get_name()]++;
    }
    std::vector<std::string> out;
    out.reserve(count.size());
    for (const auto& kv : count) {
        if (kv.second > 1) out.push_back(kv.first + " x" + std::to_string(kv.second));
        else               out.push_back(kv.first);
    }
    if (out.empty()) out.push_back("       - none -");
    return out;
}

static std::vector<std::string> build_throwables_list(const Player& p) {
    std::unordered_map<std::string, int> count;
    for (const Item& it : p.get_inventory()) {
        if (it.is_throwable()) {
            count[it.get_name()]++;
        }
    }
    std::vector<std::string> out;
    for (const auto& kv : count) {
        out.push_back(kv.first + " x" + std::to_string(kv.second));
    }
    if (out.empty()) out.push_back("- none -");
    return out;
}

void show_title_screen() {

    system("CLS");

    std::cout << col("violet") << " +" << col("Lblue") << std::string(117, '-') << col("violet") << "+\n";
    std::cout << col("Lblue") << " |" << std::string(117, ' ') << "|\n";

    // THE + MANOR block (12 rows)
    for (int i = 0; i < 12; i++) {
        std::string line = " |";

        if (i < 6) {
            line += col("seafoam") + "\x1B[2m" + "   " + wordTHE[i];
        }
        else {
            line += std::string(31, ' ');
        }

        line += std::string(6, ' ') + "\x1B[0m";
        line += apply_tinted_gradient(wordMANOR[i], i);
        line += col("Lblue") + "   |\n";

        std::cout << line;
    }

    // Spacer row between MANOR and HOUSE
    std::cout << " |" << std::string(117, ' ') << "|\n";

    // HOUSE block (12 rows)
    for (int i = 0; i < 12; i++) {
        std::string line = " |";
        if (i < 7) {
            line += std::string(39, ' ');
        }
        else {
            line += std::string(6, ' ');
            line += tag_box[i - 7];
            line += std::string(11, ' ');
        }

        for (char c : wordHOUSE[i]) {
            line += tint_house_char(c);
        }

        line += col("Lblue") + std::string(7, ' ') + "|\n";
        std::cout << line;
    }

    std::cout << " |" << std::string(117, ' ') << "|\n";
    std::cout << " |" << std::string(117, ' ') << "|\n";
    std::cout << col("violet") << " +" << col("Lblue") << std::string(117, '-') << col("violet") << "+";
}

void show_name_entry_screen(Player& player) {

    system("CLS");

    auto draw_border = [](std::string col1, std::string col2, int width) {
        return col(col1) + " +" + col(col2) + std::string(width, '-') + col(col1) + "+";
        };

    auto draw_blank_line = [](int width) {
        return col("Lblue") + " |" + std::string(width, ' ') + "|\n";
        };

    const int total_width = 117;
    const int box_width = 111;

    // Top outer border
    std::cout << draw_border("violet", "Lblue", total_width) << "\n";

    // Top banner box
    for (int i = 0; i < 10; i++) {
        if (i == 1 || i == 8) {
            std::cout << " |  " << col("violet") << "+" << col("gold") << std::string(box_width, '-') << col("violet") << "+" << col("Lblue") << "  |\n";
        }
        else if (i == 4) {
            std::string banner = "What is your name, wanderer?";
            int padding = (box_width - static_cast<int>(banner.length())) / 2;
            std::cout << " |  " << col("gold") << "|" << std::string(padding, ' ')
                << col("pink") << banner << std::string(box_width - static_cast<int>(banner.length()) - padding, ' ')
                << col("gold") << "|" << col("Lblue") << "  |\n";
        }
        else if (i > 1 && i < 8) {
            std::cout << " |  " << col("gold") << "|" << std::string(box_width, ' ') << "|" << col("Lblue") << "  |\n";
        }
        else {
            std::cout << draw_blank_line(total_width);
        }
    }

    // Panel box border (top)
    std::cout << col("violet") << " +"
        << col("Lblue") << std::string(30, '-') << col("violet") << "+  +"
        << col("gold") << std::string(49, '-') << col("violet") << "+  +"
        << col("Lblue") << std::string(30, '-') << col("violet") << "+\n" << col("Lblue");

    // Middle section
    for (int i = 0; i < 17; i++) {
        if (i == 5 || i == 9) {
            std::cout << " |" << std::string(30, ' ') << "|  "
                << col("gold") << "|  " << col("violet") << "+" << col("white") << std::string(43, '-') << col("violet") << "+  "
                << col("gold") << "|" << col("Lblue") << "  |" << std::string(30, ' ') << "|\n";
        }
        else if (i == 6 || i == 7 || i == 8) {
            std::cout << " |" << std::string(30, ' ') << "|  "
                << col("gold") << "|  " << col("white") << "|" << std::string(43, ' ') << "|" << col("gold") << "  |"
                << col("Lblue") << "  |" << std::string(30, ' ') << "|\n";
        }
        else if (i == 15) {
            std::cout << " |" << std::string(30, ' ') << "|" << col("violet") << "  +"
                << col("gold") << std::string(49, '-') << col("violet") << "+" << col("Lblue") << "  |"
                << std::string(30, ' ') << "|\n" << col("Lblue");
        }
        else if (i == 16) {
            std::cout << " |" << std::string(30, ' ') << "|" << std::string(55, ' ') << "|" << std::string(30, ' ') << "|\n";
        }
        else {
            // Default layout
            std::cout << " |" << std::string(30, ' ') << "|  ";
            std::cout << col("gold") << "|" << std::string(49, ' ') << "|  ";
            std::cout << col("Lblue") << "|" << std::string(30, ' ') << "|\n";
        }
    }

    // Bottom outer border
    std::cout << col("violet") << " +"
        << col("Lblue") << std::string(30, '-')
        << col("violet") << "+" << col("Lblue") << std::string(55, '-')
        << col("violet") << "+" << col("Lblue") << std::string(30, '-')
        << col("violet") << "+";

    std::string player_name;
    bool name_correct = false;

    while (!name_correct) {
        // Clear screen or redraw the name section if needed
        add_text(20, 44, std::string(35, ' '), "white");

        move_cursor(20, 44);
        player_name = get_limited_input(35);

        // Trim leading/trailing whitespace
        player_name.erase(0, player_name.find_first_not_of(" \t\n\r\f\v"));
        player_name.erase(player_name.find_last_not_of(" \t\n\r\f\v") + 1);

        // Check for empty
        if (player_name.empty()) {
            add_text(25, 44, std::string(37, ' '), "white");
            add_text(25, 51, "You must enter a name", "Lred");
            continue;
        }

        // Length check
        if (player_name.length() > 18) {
            add_text(25, 44, "That name is FAR too long. Try again", "Lred");
            continue;
        }

        while (true) {
            add_text(25, 44, std::string(37, ' '), "white");
            move_cursor(24, 51);
            std::cout << col("pink") << "Is this correct? (Y/N)";
            move_cursor(30, 123);

            char confirm = static_cast<char>(std::tolower(_getch()));

            if (confirm == 'y') {
                name_correct = true;
                break; // Name accepted!
            }
            else if (confirm == 'n') {
                add_text(20, 44, std::string(35, ' '), "white");
                add_text(25, 44, std::string(37, ' '), "white");
                break; // Loop again
            }
            else {
                add_text(26, 52, "Please press Y or N", "Lred");
            }
        }

        add_text(24, 51, std::string(25, ' '), "Lred");
        add_text(26, 51, std::string(25, ' '), "Lred");
    }

    add_text(20, 44, std::string(35, ' '), "white");
    add_text(25, 44, std::string(37, ' '), "white");
    player_name = capitalise_words(player_name);
    player.set_name(player_name);

    add_text(14, 93, "PLAYER NAME:", "pink");
    add_text(15, 93, player_name, "violet");

    add_text(6, 44, "What kind of adventurer will you be?", "pink");
    add_text(15, 10, "1. Curious", "seafoam");
    add_text(17, 10, "2. Brave", "rose");
    add_text(19, 10, "3. Timid", "lavender");
    add_text(21, 10, "4. Unbothered", "abyss");
    add_text(23, 10, "5. Fiery", "brass");
    add_text(25, 10, "6. Precise", "crimson");
    add_text(27, 10, "7. Thoughtful", "cyan");

    move_cursor(30, 121);

    char key = '0';
    std::string style;
    Item start_item;
    while (key == '0') {
        key = _getch();
        switch (key) {
        case '1': style = "Curious";     start_item = curio_hook;      break;
        case '2': style = "Brave";       start_item = fire_axe;        break;
        case '3': style = "Timid";       start_item = steel_parasol;   break;
        case '4': style = "Unbothered";  start_item = paperweight;     break;
        case '5': style = "Fiery";       start_item = hearth_poker;    break;
        case '6': style = "Precise";     start_item = letter_opener;   break;
        case '7': style = "Thoughtful";  start_item = ashwood_cane;    break;
        default:
            key = '0';
            add_text(25, 50, "Just pick a bloody number", "Lred");
            move_cursor(30, 121);
        }
    }
    add_text(25, 50, std::string(25, ' '), "white");

    add_text(18, 93, "ADVENTURE STYLE:", "pink");
    add_text(19, 93, style, "violet");
    add_text(22, 93, "STARTING ITEM:", "pink");
    add_text(23, 93, start_item.get_name(), "violet");
    player.add_to_inventory(start_item);

    add_text(6, 44, std::string(50, ' '), "white");

    for (int i = 0; i < 7; i++) {
        add_text(15 + (2 * i), 10, std::string(15, ' '), "white");
    }

    add_text(6, 48, "What is your biggest fear?", "pink");
    std::string input;

    while (input.empty()) {
        move_cursor(20, 44);
        input = get_limited_input(35);
        if (input.empty()) {
            add_text(25, 47, "You have to enter SOMETHING...", "Lred");
        }
    }

    add_text(6, 44, std::string(50, ' '), "white");
    add_text(20, 44, std::string(35, ' '), "white");
    add_text(26, 93, "PERSONALITY PROFILE:", "pink");
    add_text(27, 93, get_random_profile(), "violet");

    add_text(25, 45, "Press any key to start the game...", "Lred");
    move_cursor(30, 121);
}

void show_explore_screen(Game& g) {

    g.current_room = find_room_by_coords(room_list, g.player.get_location());

    system("CLS");

    // Top Border
    std::cout << col("violet") << " +" << col("Lblue") << std::string(37, '-') << col("violet")
        << "+" << col("Lblue") << std::string(41, '-') << col("violet")
        << "+" << col("Lblue") << std::string(37, '-') << col("violet") << "+\n";

    // Title
    std::cout << col("Lblue") << " |      " << col("pink") << "Name: " << col("violet")
        << std::setw(24) << std::left << g.player.get_name() << col("Lblue") << " |           " << col("pink")
        << " Health: " << health_colour(g.player.get_health()) << std::setw(3) << std::right << g.player.get_health() << "\x1B[0m"
        << col("green") << " / 100            " << col("Lblue") << "|      " << col("pink")
        << "Location: " << col("violet") << std::setw(21) << std::left << g.current_room->get_name()
        << col("Lblue") << "|\n";

    // Break
    std::cout << col("violet") << " +" << col("Lblue") << std::string(37, '-') << col("violet")
        << "+" << col("Lblue") << std::string(41, '-') << col("violet")
        << "+" << col("Lblue") << std::string(37, '-') << col("violet") << "+\n";

    // Area Description
    std::cout << col("Lblue") << " |" << std::string(117, ' ') << "|\n";
    std::cout << " |" << col("gold") << centre_text(g.current_room->get_description()[0], 117) << col("Lblue") << "|\n";
    std::cout << " |" << col("gold") << centre_text(g.current_room->get_description()[1], 117) << col("Lblue") << "|\n";
    std::cout << " |" << col("gold") << centre_text(g.current_room->get_description()[2], 117) << col("Lblue") << "|\n";
    std::cout << " |" << col("gold") << centre_text(g.current_room->get_description()[3], 117) << col("Lblue") << "|\n";
    std::cout << " |" << col("gold") << centre_text(g.current_room->get_description()[4], 117) << col("Lblue") << "|\n";
    std::cout << " |" << std::string(117, ' ') << "|\n";

    // Break
    std::cout << col("violet") << " +" << col("Lblue") << std::string(58, '-') << col("violet") << "+"
        << col("Lblue") << std::string(58, '-') << col("violet") << "+\n";

    // Boxes
    std::cout << col("Lblue") << " |" << std::string(58, ' ') << "|" << std::string(58, ' ') << "|\n";
    std::cout << " |     " << col("pink") << "Exits     :  " << col("white") << pad_visual(g.current_room->room_direction_list(), 40)
        << col("Lblue") << "|" << col("violet") << centre_text(g.prompt[0], 58) << col("Lblue") << "|\n";
    std::cout << " |     " << col("pink") << "Items     :  " << col("white") << std::setw(40) << std::left
        << g.current_room->room_item_list() << col("Lblue") << "|" << col("violet")
        << centre_text(g.prompt[1], 58) << col("Lblue") << "|\n";
    std::cout << " |  " << col("pink") << "Curiosities  :  " << col("white") << std::setw(40) << std::left
        << g.current_room->room_interactable_list() << col("Lblue") << "|" << col("violet")
        << centre_text(g.prompt[2], 58) << col("Lblue") << "|\n";
    std::cout << " |" << std::string(58, ' ') << "|" << col("violet") << centre_text(g.prompt[3], 58) << col("Lblue") << "|\n";

    // Left break
    std::cout << col("violet") << " +" << col("Lblue") << std::string(58, '-') << col("violet") << "+"
        << col("violet") << centre_text(g.prompt[4], 58) << col("Lblue") << "|\n";

    // More boxes
    std::cout << " |" << col("pink") << centre_text(g.question, 58) << col("Lblue") << "|"
        << col("violet") << centre_text(g.prompt[5], 58) << col("Lblue") << "|\n";
    std::cout << " |" << std::string(58, ' ') << "|" << col("violet") << centre_text(g.prompt[6], 58) << col("Lblue") << "|\n";
    std::cout << " |   " << col("white") << std::setw(55) << std::left << g.option[0]
        << col("Lblue") << "|" << std::string(58, ' ') << "|\n";

    // Right break
    std::cout << " |   " << col("white") << std::setw(55) << std::left << g.option[1] << col("violet")
        << "+" << col("Lblue") << std::string(58, '-') << col("violet") << "+\n" << col("Lblue");
    std::cout << " |   " << col("white") << std::setw(55) << std::left << g.option[2]
        << col("Lblue") << "|" << std::string(58, ' ') << "|\n";
    std::cout << " |   " << col("white") << std::setw(55) << std::left << g.option[3]
        << col("Lblue") << "|" << std::string(58, ' ') << "|\n";
    std::cout << " |   " << col("white") << std::setw(55) << std::left << g.option[4] << col("Lblue") << "|"
        << col("Lred") << centre_text(g.error_message, 58) << col("Lblue") << "|\n";
    std::cout << " |   " << col("white") << std::setw(55) << std::left << g.option[5]
        << col("Lblue") << "|" << std::string(58, ' ') << "|\n";
    std::cout << " |" << std::string(58, ' ') << "|" << std::string(58, ' ') << "|\n";

    // Base line
    std::cout << col("violet") << " +" << col("Lblue") << std::string(58, '-') << col("violet") << "+"
        << col("Lblue") << std::string(58, '-') << col("violet") << "+\n\n";

    // Cursor input
    std::cout << col("white") << " > ";
}

void show_inventory_screen(Game& g) {

    system("CLS");

    // Header border
    std::cout << col("violet") << " +" << col("Lblue");
    std::cout << std::string(117, '-') << col("violet") << "+\n";

    std::string sort_type = "S: Sort (";
    if (g.current_sort_mode == SortMode::CHRONOLOGICAL) { sort_type += "CHRONOLOGICAL"; }
    if (g.current_sort_mode == SortMode::ALPHABETICAL) { sort_type += "ALPHABETICAL"; }
    sort_type += ")";

    // Build grouped view
    auto rows = build_grouped_inventory(g.player,
        g.current_sort_mode == SortMode::ALPHABETICAL);
    int inv_size = static_cast<int>(rows.size());

    // Pages from grouped size
    g.max_pages = (inv_size == 0) ? 0 : (inv_size - 1) / ITEMS_PER_PAGE;

    // Clamp page & selection before we show anything
    if (g.current_page > g.max_pages) g.current_page = g.max_pages;
    if (g.current_page < 0)           g.current_page = 0;

    if (inv_size == 0) {
        g.selected_item_index = 0;
    }
    else {
        if (g.selected_item_index < 0)         g.selected_item_index = 0;
        if (g.selected_item_index >= inv_size) g.selected_item_index = inv_size - 1;
    }

    int start = g.current_page * ITEMS_PER_PAGE;
    int end = std::min(start + ITEMS_PER_PAGE, inv_size);

    int total_pages = g.max_pages + 1;
    std::string page_info = "Page " + std::to_string(g.current_page + 1)
        + " / " + std::to_string(total_pages);

    // Title line
    std::cout << col("Lblue") << " |     " << col("pink") << std::setw(30) << std::left << page_info << std::string(19, ' ')
        << "INVENTORY" << col("violet") << std::setw(49) << std::right << sort_type << col("Lblue") << "     |\n";

    // Divider
    std::cout << col("violet") << " +" << col("Lblue") << std::string(30, '-') << col("violet") << "+"
        << col("Lblue") << std::string(86, '-') << col("violet") << "+\n";

    // Column headers
    std::cout << col("Lblue") << " |     " << col("pink") << std::setw(25) << std::left << "Item" << col("Lblue")
        << "|  " << col("pink") << std::setw(84) << std::left << "Description" << col("Lblue") << "|\n";

    // Divider
    std::cout << col("violet") << " +" << col("Lblue") << std::string(30, '-') << col("violet") << "+"
        << col("Lblue") << std::string(86, '-') << col("violet") << "+\n";

    // clamp selection to rows
    if (!rows.empty() && g.selected_item_index >= inv_size) g.selected_item_index = inv_size - 1;

    std::cout << col("Lblue") << " |" << std::string(30, ' ') << "|" << std::string(86, ' ') << "|\n";

    for (int i = start; i < end; ++i) {
        const auto& row = rows[i];
        std::string name = row.name;
        if (row.indices.size() > 1) name += " x" + std::to_string(row.indices.size());

        std::cout << " |  ";
        if (i == g.selected_item_index) std::cout << col("white") << ">"; else std::cout << " ";
        std::cout << "  " << col("violet") << std::setw(25) << std::left << name
            << col("Lblue") << "|  " << col("white") << std::setw(84) << std::left << row.desc
            << col("Lblue") << "|\n";
    }

    for (int i = 0; i < ((ITEMS_PER_PAGE - (end - start)) +1); i++) {
        std::cout << " |" << std::string(30, ' ') << "|" << std::string(86, ' ') << "|\n";
    }

    // Divider
    std::cout << col("violet") << " +" << col("Lblue");
    std::cout << std::string(30, '-') << col("violet") << "+" << col("Lblue") << std::string(56, '-')
        << col("violet") << "+" << col("Lblue") << std::string(29, '-') << col("violet") << "+\n";

    std::cout << col("Lblue") << " |" << std::string(30, ' ') << "|" << std::string(56, ' ') << "|" << std::string(29, ' ') << "|\n";

    Item selected;
    std::vector<std::string> lore_lines(5, "");
    if (!rows.empty()) {
        int idx = rows[g.selected_item_index].indices.front();
        selected = g.player.get_inventory()[idx];
        auto item_lore = selected.get_lore();
        for (size_t i = 0; i < item_lore.size() && i < 5; ++i) lore_lines[i] = item_lore[i];
    }

    // Render the screen section
    std::cout << col("Lblue") << " | " << col("pink") << centre_text(g.question, 29) << col("Lblue") << "|" << col("violet")
        << centre_text(lore_lines[0], 56) << col("Lblue") << "|" << col("Lred")
        << centre_text(g.inv_hint[0], 29) << col("Lblue") << "|\n";
    std::cout << " |" << std::string(30, ' ') << "|" << col("violet") << centre_text(lore_lines[1], 56) << col("Lblue") << "|"
        << col("Lred") << centre_text(g.inv_hint[1], 29) << col("Lblue") << "|\n";
    std::cout << " |  " << col("white") << std::setw(28) << std::left << g.option[0] << col("Lblue")
        << "|" << col("violet") << centre_text(lore_lines[2], 56) << col("Lblue")
        << "|" << col("Lred") << centre_text(g.inv_hint[2], 29) << col("Lblue") << "|\n";
    std::cout << " |  " << col("white") << std::setw(28) << std::left << g.option[1] << col("Lblue")
        << "|" << col("violet") << centre_text(lore_lines[3], 56) << col("Lblue")
        << "|" << col("Lred") << centre_text(g.inv_hint[3], 29) << col("Lblue") << "|\n";
    std::cout << " |  " << col("white") << std::setw(28) << std::left << g.option[2] << col("Lblue") << "|" << col("violet");

    if (selected.is_consumable()) { std::cout << col("green"); }
    if (selected.is_throwable()) { std::cout << col("Lred"); }

    std::cout << centre_text(lore_lines[4], 56) << col("Lblue")
        << "|" << col("Lred") << centre_text(g.inv_hint[4], 29) << col("Lblue") << "|\n";
    std::cout << " |" << std::string(30, ' ') << "|" << std::string(56, ' ') << "|" << std::string(29, ' ') << "|\n";

    // Final bottom border
    std::cout << col("violet") << " +" << col("Lblue") << std::string(30, '-') << col("violet") << "+"
        << col("Lblue") << std::string(56, '-') << col("violet") << "+" << col("Lblue")
        << std::string(29, '-') << col("violet") << "+\n\n";

    // Input prompt
    std::cout << col("white") << " > ";
}

void show_combat_screen(Game& g) {

    // Enemy basics
    const std::string enemy_name = g.pending_encounter.empty() ? "Unknown" : g.pending_encounter;
    const int enemy_hp = (g.enemy_hp > 0 ? g.enemy_hp : 10);
    const int enemy_max = (g.enemy_hp_max > 0 ? g.enemy_hp_max : 10);

    // Super lightweight "equipped weapon" guess:
    // pick the first weapon found in inventory; fallback to "—".
    static const std::vector<std::string> starter_weapons = {
        "Curio Hook","Fire Axe","Parasol","Paperweight",
        "Poker","Letter Opener","Ashwood Cane"
    };
    std::string equipped_weapon = "-";
    for (const Item& it : g.player.get_inventory()) {
        if (std::find(starter_weapons.begin(), starter_weapons.end(), it.get_name()) != starter_weapons.end()) {
            equipped_weapon = it.get_name();
            break;
        }
    }

    std::vector<std::string> throwables;
    std::vector<std::string> consumables;

    if (g.combat_log.empty()) {
        g.combat_log = {
            "A " + enemy_name + " drags itself into view.",
            "It seems calm."
        };
    }
    
    while (g.combat_log.size() > 7) g.combat_log.erase(g.combat_log.begin());

    // ---- BUILD PANEL VECTORS ----

    // 1A: Enemy panel
    std::vector<std::string> box1A_text = {
        "",
        enemy_name,
        "",
        "HP: " + std::to_string(enemy_hp) + " / " + std::to_string(enemy_max),
        "Status: Calm",            // placeholder; later: last action/temper
        "Vulnerability: -",        // placeholder; easy to fill later
        "", "", "", ""
    };
    fit_lines(box1A_text);

    // 1C: Throwables list
    auto throw_list = build_throwables_list(g.player);
    std::vector<std::string> box1C_text = { "", "THINGS TO THROW", "" };
    for (const auto& s : throw_list) box1C_text.push_back(s);
    fit_lines(box1C_text);

    // 2A: Actions
    std::vector<std::string> box2A_text = g.combat_lines;
    fit_lines(box2A_text);

    // 2B: Combat log (older to newer, newest should be last line)
    // start with 10 empty lines
    std::vector<std::string> box2B_text(10, "");

    // Where we want lines to land (keep 7 blank as a spacer)
    static const std::array<int, 7> LOG_SLOTS = { 1, 2, 3, 4, 5, 6, 8 };

    // How many lines we can display at once
    int n = std::min<int>(static_cast<int>(g.combat_log.size()), static_cast<int>(LOG_SLOTS.size()));

    // Fill from newest to oldest into the chosen slots
    for (int i = 0; i < n; ++i) {
        const int src = static_cast<int>(g.combat_log.size()) - 1 - i;           // newest first
        const int dst = LOG_SLOTS[static_cast<int>(LOG_SLOTS.size()) - 1 - i];   // 8,6,5,4,3,2,1
        box2B_text[dst] = g.combat_log[src];
    }
    fit_lines(box2B_text);  // keep your padding/trim guard

    // 2C: Consumables list
    auto cons_list = build_consumables_list(g.player);          // keep the vector
    std::vector<std::string> box2C_text = { "", "CONSUMABLE ITEMS", "" };
    for (const auto& s : cons_list) box2C_text.push_back(s);
    fit_lines(box2C_text);

    // ----- CLEAR & BUILD SCREEN -----
    system("CLS");

    // Top Border
    std::cout << col("violet") << " +" << col("Lblue") << std::string(37, '-') << col("violet") << "+" << col("Lblue") << std::string(41, '-') << col("violet")
        << "+" << col("Lblue") << std::string(37, '-') << col("violet") << "+\n";

    // Title
    std::cout << col("Lblue") << " |      " << col("pink") << "Name: " << col("violet")
        << std::setw(24) << std::left << g.player.get_name() << col("Lblue") << " |           " << col("pink")
        << " Health: " << health_colour(g.player.get_health()) << std::setw(3) << std::right << g.player.get_health() << "\x1B[0m"
        << col("green") << " / 100            " << col("Lblue") << "|   " << col("pink")
        << "Equipped Weapon: " << col("violet") << std::setw(17) << std::left << equipped_weapon
        << col("Lblue") << "|\n";

    // Break
    std::cout << col("violet") << " +" << col("Lblue") << std::string(32, '-') << col("violet") << "+" << col("Lblue")
        << std::string(4, '-') << col("violet") << "+" << col("Lblue") << std::string(41, '-') << col("violet")
        << "+" << col("Lblue") << std::string(4, '-') << col("violet") << "+" << col("Lblue") << std::string(32, '-')
        << col("violet") << "+\n";

    // Top Boxes ------
    for (int i = 0; i < 10; i++) {
        std::cout << col("Lblue") << " |";
        if (i == 1) { std::cout << col("Lred"); }
        else { std::cout << col("white"); }
        std::cout << centre_text(box1A_text[i], 32) << col("Lblue") << "|" << std::string(51, ' ') << "|";
        if (i == 1) { std::cout << col("pink"); }
        else { std::cout << col("violet"); }
        std::cout << centre_text(box1C_text[i], 32) << col("Lblue") << "|\n";
    }

    // Break
    std::cout << col("violet") << " +" << col("Lblue") << std::string(32, '-') << col("violet") << "+" << col("Lblue")
        << std::string(51, '-') << col("violet") << "+" << col("Lblue") << std::string(32, '-')
        << col("violet") << "+\n";

    // Bottom Boxes
    for (int i = 0; i < 10; i++) {
        // QUESTIONS BOX
        std::cout << col("Lblue") << " |";
        if (i == 1) { std::cout << col("pink") << centre_text(box2A_text[i], 32); }
        else { std::cout << col("white") << "    " << std::setw(28) << std::left << box2A_text[i]; }

        // COMBAT LOG BOX
        std::cout << col("Lblue") << "|";
        if (i == 8) { std::cout << col("Lred"); }
        else { std::cout << col("gold"); }
        std::cout << centre_text(box2B_text[i], 51) << col("Lblue") << "|";

        // CONSUMABLES BOX
        if (i == 0 || i == 2) {
            std::cout << col("violet") << std::setw(32) << std::left << box2C_text[i]
                << col("Lblue") << "|\n";
        }
        else if (i == 1) {
            std::cout << col("pink") << centre_text(box2C_text[i], 32)
                << col("Lblue") << "|\n";
        }
        else if (i == 9) {
            // footer line: always blank (or show a scroll hint if you like)
            std::cout << col("violet") << std::setw(32) << std::left << ""
                << col("Lblue") << "|\n";
        }
        else {
            const int first_row = 3;     // first item line in the panel
            const int visible_max = 6;     // rows 3..8 are six lines tall
            const int line_idx = i - first_row;

            std::string line_text;

            if (g.choosing_consumable) {
                // draw from the cached, windowed list
                int row = g.consumable_top + line_idx;
                if (row >= 0 && row < static_cast<int>(g.consumable_rows.size()))
                    line_text = g.consumable_rows[row];
                else
                    line_text = "";
                const bool show_arrow = (row == g.consumable_cursor);
                std::cout << col("white") << (show_arrow ? "  >  " : "     ") << col("violet") << std::setw(27)
                    << std::left << line_text << col("Lblue") << "|\n";
            }
            else {
                if (line_idx < static_cast<int>(cons_list.size()))
                    line_text = cons_list[line_idx];
                else
                    line_text = "";
                std::cout << col("white") << "     " << col("violet") << std::setw(27) << std::left << line_text
                    << col("Lblue") << "|\n";
            }
        }
    }

    // Break
    std::cout << col("violet") << " +" << col("Lblue") << std::string(32, '-') << col("violet") << "+" << col("Lblue")
        << std::string(51, '-') << col("violet") << "+" << col("Lblue") << std::string(32, '-')
        << col("violet") << "+\n";

    // Base error message box
    std::cout << col("Lblue") << " |" << col("Lred") << centre_text(g.error_message, 117) << col("Lblue") << "|\n";

    // Bottom border
    std::cout << col("violet") << " +" << col("Lblue") << std::string(117, '-') << col("violet") << "+\n\n";

    // Cursor line
    std::cout << col("white") << " > ";

}