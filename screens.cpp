
#include "screens.h"
#include "colours.h"
#include "lettering.h"

#include <limits>

const int ITEMS_PER_PAGE = 11;

void show_title_screen() {

    system("CLS");

    cout << col("violet") << " +" << col("Lblue") << string(117, '-') << col("violet") << "+\n";
    cout << col("Lblue") << " |" << string(117, ' ') << "|\n";

    // THE + MANOR block (12 rows)
    for (int i = 0; i < 12; i++) {
        string line = " |";

        if (i < 6) {
            line += col("seafoam") + "\x1B[2m" + "   " + wordTHE[i];
        }
        else {
            line += string(31, ' ');
        }

        line += string(6, ' ') + "\x1B[0m";
        line += apply_tinted_gradient(wordMANOR[i], i);
        line += col("Lblue") + "   |\n";

        cout << line;
    }

    // Spacer row between MANOR and HOUSE
    cout << " |" << string(117, ' ') << "|\n";

    // HOUSE block (12 rows)
    for (int i = 0; i < 12; i++) {

        string line = " |";
        if (i < 7) {
                line += string(39, ' ');
            }
        else {
            line += string(6, ' ');
            line += tag_box[i - 7];
            line += string(11, ' ');
        }

        for (char c : wordHOUSE[i]) {
            line += tint_house_char(c);
        }

        line += col("Lblue") + string(7, ' ') + "|\n";

        cout << line;
    }

    cout << " |" << string(117, ' ') << "|\n";
    cout << " |" << string(117, ' ') << "|\n";

    cout << col("violet") << " +" << col("Lblue") << string(117, '-') << col("violet") << "+";
}

void show_name_entry_screen(Player& player) {

    system("CLS");

    auto draw_border = [](string col1, string col2, int width) {
        return col(col1) + " +" + col(col2) + string(width, '-') + col(col1) + "+";
        };

    auto draw_blank_line = [](int width) {
        return col("Lblue") + " |" + string(width, ' ') + "|\n";
        };

    const int total_width = 117;
    const int box_width = 111;

    // Top outer border
    cout << draw_border("violet", "Lblue", total_width) << "\n";

    // Top banner box
    for (int i = 0; i < 10; i++) {
        if (i == 1 || i == 8) {
            cout << " |  " << col("violet") << "+" << col("gold") << string(box_width, '-') << col("violet") << "+" << col("Lblue") << "  |\n";
        }
        else if (i == 4) {
            string banner = "What is your name, wanderer?";
            int padding = (box_width - banner.length()) / 2;
            cout << " |  " << col("gold") << "|" << string(padding, ' ')
                << col("pink") << banner << string(box_width - banner.length() - padding, ' ')
                << col("gold") << "|" << col("Lblue") << "  |\n";
        }
        else if (i > 1 && i < 8) {
            cout << " |  " << col("gold") << "|" << string(box_width, ' ') << "|" << col("Lblue") << "  |\n";
        }
        else {
            cout << draw_blank_line(total_width);
        }
    }

    // Panel box border (top)
    cout << col("violet") << " +"
        << col("Lblue") << string(30, '-') << col("violet") << "+  +"
        << col("gold") << string(49, '-') << col("violet") << "+  +"
        << col("Lblue") << string(30, '-') << col("violet") << "+\n" << col("Lblue");

    // Middle section
    for (int i = 0; i < 17; i++) {
        if (i == 5 || i == 9) {
            cout << " |" << string(30, ' ') << "|  "
                << col("gold") << "|  " << col("violet") << "+" << col("white") << string(43, '-') << col("violet") << "+  "
                << col("gold") << "|" << col("Lblue") << "  |" << string(30, ' ') << "|\n";
        }
        else if (i == 6 || i == 7 || i == 8) {
            cout << " |" << string(30, ' ') << "|  "
                << col("gold") << "|  " << col("white") << "|" << string(43, ' ') << "|" << col("gold") << "  |"
                << col("Lblue") << "  |" << string(30, ' ') << "|\n";
        }
        else if (i == 15) {
            cout << " |" << string(30, ' ') << "|" << col("violet") << "  +"
                << col("gold") << string(49, '-') << col("violet") << "+" << col("Lblue") << "  |"
                << string(30, ' ') << "|\n" << col("Lblue");
        }
        else if (i == 16) {
            cout << " |" << string(30, ' ') << "|" << string(55, ' ') << "|" << string(30, ' ') << "|\n";
        }
        else {
            // Default layout
            cout << " |" << string(30, ' ') << "|  ";
            cout << col("gold") << "|" << string(49, ' ') << "|  ";
            cout << col("Lblue") << "|" << string(30, ' ') << "|\n";
        }
    }

    // Bottom outer border
    cout << col("violet") << " +"
        << col("Lblue") << string(30, '-')
        << col("violet") << "+" << col("Lblue") << string(55, '-')
        << col("violet") << "+" << col("Lblue") << string(30, '-')
        << col("violet") << "+";

    string player_name;
    bool name_correct = false;

    while (!name_correct) {
        // Clear screen or redraw the name section if needed
        add_text(20, 44, string(35, ' '), "white");

        move_cursor(20, 44);
        player_name = get_limited_input(35);

        // Trim leading/trailing whitespace
        player_name.erase(0, player_name.find_first_not_of(" \t\n\r\f\v"));
        player_name.erase(player_name.find_last_not_of(" \t\n\r\f\v") + 1);

        // Check for empty
        if (player_name.empty()) {
            add_text(25, 44, string(37, ' '), "white");
            add_text(25, 51, "You must enter a name", "Lred");
            continue;
        }

        // Length check
        if (player_name.length() > 18) {
            add_text(25, 44, "That name is FAR too long. Try again", "Lred");
            continue;
        }

        while (true) {
            add_text(25, 44, string(37, ' '), "white");
            move_cursor(24, 51);
            cout << col("pink") << "Is this correct? (Y/N)";
            move_cursor(30, 123);

            char confirm = tolower(_getch());

            if (confirm == 'y') {
                name_correct = true;
                break; // Name accepted!
            }
            else if (confirm == 'n') {
                add_text(20, 44, string(35, ' '), "white"); // Clear name box
                add_text(25, 44, string(37, ' '), "white"); // Clear confirmation line
                break; // We'll loop back to re-enter
            }
            else {
                add_text(26, 52, "Please press Y or N", "Lred");
            }
        }

        add_text(24, 51, string(25, ' '), "Lred");
        add_text(26, 51, string(25, ' '), "Lred");
    }

    add_text(20, 44, string(35, ' '), "white");
    add_text(25, 44, string(37, ' '), "white");
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
    string style;
    Item start_item;
    while (key == '0') {
        key = _getch();
        switch (key) {
        case '1': {
            style = "Curious";
            start_item = teacup;
            break;
        }
        case '2': {
            style = "Brave";
            start_item = milk_tooth;
            break;
        }
        case '3': {
            style = "Timid";
            start_item = photo;
            break;
        }
        case '4': {
            style = "Unbothered";
            start_item = wax_finger;
            break;
        }
        case '5': {
            style = "Fiery";
            start_item = ticket;
            break;
        }
        case '6': {
            style = "Precise";
            start_item = notebook;
            break;
        }
        case '7': {
            style = "Thoughtful";
            start_item = tarot;
            break;
        }
        default: {
            key = '0';
            add_text(25, 50, "Just pick a bloody number", "Lred");
            move_cursor(30, 121);
        }
        }
    }
    add_text(25, 50, string(25, ' '), "white");

    add_text(18, 93, "ADVENTURE STYLE:", "pink");
    add_text(19, 93, style, "violet");
    add_text(22, 93, "STARTING ITEM:", "pink");
    add_text(23, 93, start_item.get_name(), "violet");
    player.add_to_inventory(start_item);

    add_text(6, 44, string(50, ' '), "white");

    for (int i = 0; i < 7; i++) {
        add_text(15 + (2 * i), 10, string(15, ' '), "white");
    }

    add_text(6, 48, "What is your biggest fear?", "pink");
    string input;
    move_cursor(20, 44);
    input = get_limited_input(35);
    add_text(6, 44, string(50, ' '), "white");
    add_text(20, 44, string(35, ' '), "white");

    add_text(26, 93, "PERSONALITY PROFILE:", "pink");
    add_text(27, 93, get_random_profile(), "violet");

    add_text(25, 45, "Press any key to start the game...", "Lred");

    move_cursor(30, 121);

}


void show_explore_screen(Player& player, Room*& current_room, string question, string error_message,
                            vector<string> option, vector<string>& prompt) {

    current_room = find_room_by_coords(room_list, player.get_location());

    system("CLS");

    // Break
    cout << col("violet") << " +" << col("Lblue") << string(37, '-') << col("violet")
        << "+" << col("Lblue") << string(41, '-') << col("violet")
        << "+" << col("Lblue") << string(37, '-') << col("violet") << "+\n";

    // Title
    cout << col("Lblue") << " |      " << col("pink") << "Name: " << col("violet")
        << setw(24) << left << player.get_name() << col("Lblue") << " |           " << col("pink")
        << " Health: " << health_colour(player.get_health()) << setw(3) << right << player.get_health() << "\x1B[0m"
        << col("green") << " / 100            " << col("Lblue") << "|      " << col("pink")
        << "Location: " << col("violet") << setw(21) << left << current_room->get_name()
        << col("Lblue") << "|\n";

    // Break
    cout << col("violet") << " +" << col("Lblue") << string(37, '-') << col("violet")
        << "+" << col("Lblue") << string(41, '-') << col("violet")
        << "+" << col("Lblue") << string(37, '-') << col("violet") << "+\n";

    // Area Description
    cout << col("Lblue") << " |" << string(117, ' ') << "|\n";
    cout << " |" << col("gold") << centre_text(current_room->get_description()[0], 117)
        << col("Lblue") << "|\n";
    cout << " |" << col("gold") << centre_text(current_room->get_description()[1], 117)
        << col("Lblue") << "|\n";
    cout << " |" << col("gold") << centre_text(current_room->get_description()[2], 117)
        << col("Lblue") << "|\n";
    cout << " |" << col("gold") << centre_text(current_room->get_description()[3], 117)
        << col("Lblue") << "|\n";
    cout << " |" << col("gold") << centre_text(current_room->get_description()[4], 117)
        << col("Lblue") << "|\n";
    cout << " |" << string(117, ' ') << "|\n";

    // Break
    cout << col("violet") << " +" << col("Lblue") << string(58, '-') << col("violet") << "+"
        << col("Lblue") << string(58, '-') << col("violet") << "+\n";

    // Boxes
    cout << col("Lblue") << " |" << string(58, ' ') << "|" << string(58, ' ') << "|\n";
    cout << " |     " << col("pink") << "Exits     :  " << col("white")  << pad_visual(current_room->room_direction_list(), 40)
        << col("Lblue") << "|" << col("violet") << centre_text(prompt[0], 58) << col("Lblue") << "|\n";
    cout << " |     " << col("pink") << "Items     :  " << col("white") << setw(40) << left
        << current_room->room_item_list() << col("Lblue") << "|" << col("violet") << centre_text(prompt[1], 58) << col("Lblue") << "|\n";
    cout << " |  " << col("pink") << "Curiosities  :  " << col("white") << setw(40) << left
        << current_room->room_interactable_list() << col("Lblue") << "|" << col("violet") << centre_text(prompt[2], 58) << col("Lblue") << "|\n";
    cout << " |" << string(58, ' ') << "|" << col("violet") << centre_text(prompt[3], 58) << col("Lblue") << "|\n";

    // Left break
    cout << col("violet") << " +" << col("Lblue") << string(58, '-') << col("violet") << "+"
        << col("violet") << centre_text(prompt[4], 58) << col("Lblue") << "|\n";

    // More boxes
    cout << " |" << col("pink") << centre_text(question, 58) << col("Lblue") << "|" << col("violet") << centre_text(prompt[5], 58) << col("Lblue") << "|\n";
    cout << " |" << string(58, ' ') << "|" << col("violet") << centre_text(prompt[6], 58) << col("Lblue") << "|\n";
    cout << " |   " << col("white") << setw(55) << left << option[0] << col("Lblue") << "|" << string(58, ' ') << "|\n";

    // Right break
    cout << " |   " << col("white") << setw(55) << left << option[1] << col("violet")
        << "+" << col("Lblue") << string(58, '-') << col("violet") << "+\n" << col("Lblue");
    cout << " |   " << col("white") << setw(55) << left << option[2]
        << col("Lblue") << "|" << string(58, ' ') << "|\n";
    cout << " |   " << col("white") << setw(55) << left << option[3]
        << col("Lblue") << "|" << string(58, ' ') << "|\n";
    cout << " |   " << col("white") << setw(55) << left << option[4] << col("Lblue") << "|"
        << col("Lred") << centre_text(error_message, 58) << col("Lblue") << "|\n";
    cout << " |   " << col("white") << setw(55) << left << option[5]
        << col("Lblue") << "|" << string(58, ' ') << "|\n";
    cout << " |" << string(58, ' ') << "|" << string(58, ' ') << "|\n";

    // Base line
    cout << col("violet") << " +" << col("Lblue") << string(58, '-') << col("violet") << "+"
        << col("Lblue") << string(58, '-') << col("violet") << "+\n\n";

    // Cursor input
    cout << col("white") << " > ";
}

void show_inventory_screen(Player& player, int& selected_item_index, vector<string>& inv_hint, string& question,
                            vector<string>& option, SortMode current_sort_mode, int& current_page, int& max_pages) {

    system("CLS");

    // Header border
    cout << col("violet") << " +" << col("Lblue");
    cout << string(117, '-') << col("violet") << "+\n";

    string sort_type = "S: Sort (";
    if (current_sort_mode == CHRONOLOGICAL) { sort_type += "CHRONOLOGICAL"; }
    if (current_sort_mode == ALPHABETICAL) { sort_type += "ALPHABETICAL"; }
    sort_type += ")";

    int inv_size = player.get_inventory().size();
    int total_pages = max(1, (inv_size + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE);
    string page_info = "Page " + to_string(current_page + 1) + " / " + to_string(total_pages);

    // Title line
    cout << col("Lblue") << " |     " << col("pink") << setw(30) << left << page_info << string(19, ' ')
        << "INVENTORY" << col("violet") << setw(49) << right << sort_type << col("Lblue") << "     |\n";

    // Divider
    cout << col("violet") << " +" << col("Lblue") << string(30, '-') << col("violet") << "+"
        << col("Lblue") << string(86, '-') << col("violet") << "+\n";

    // Column headers
    cout << col("Lblue") << " |     " << col("pink") << setw(25) << left << "Item" << col("Lblue")
        << "|  " << col("pink") << setw(84) << left << "Description" << col("Lblue") << "|\n";

    // Divider
    cout << col("violet") << " +" << col("Lblue") << string(30, '-') << col("violet") << "+"
        << col("Lblue") << string(86, '-') << col("violet") << "+\n";

    // Inventory listing
    vector<Item> displayed_inventory = player.get_inventory();

    if (current_sort_mode == ALPHABETICAL) {
        sort(displayed_inventory.begin(), displayed_inventory.end(),
            [](Item& a, Item& b) {
                return a.get_name() < b.get_name();
            });
    }

    max_pages = (displayed_inventory.size() - 1) / ITEMS_PER_PAGE;

    cout << col("Lblue") << " |" << string(30, ' ') << "|" << string(86, ' ') << "|\n";

    int start = current_page * ITEMS_PER_PAGE;
    int end = min(start + ITEMS_PER_PAGE, (int)displayed_inventory.size());

    for (int i = start; i < end; ++i) {
        Item item = displayed_inventory[i];
        string name = item.get_name();
        string desc = item.get_desc();

        cout << " |  ";
        if (i == selected_item_index) {
            cout << col("white") << ">";
        }
        else {
            cout << " ";
        }
        cout << "  " << col("violet") << setw(25) << left << name << col("Lblue") << "|  "
            << col("white") << setw(84) << left << desc << col("Lblue") << "|\n";
    }

    for (int i = 0; i < ((ITEMS_PER_PAGE - (end - start) + 1)); i++) {
        cout << " |" << string(30, ' ') << "|" << string(86, ' ') << "|\n";
    }

    // Divider
    cout << col("violet") << " +" << col("Lblue");
    cout << string(30, '-') << col("violet") << "+" << col("Lblue") << string(56, '-')
        << col("violet") << "+" << col("Lblue") << string(29, '-') << col("violet") << "+\n";

    cout << col("Lblue") << " |" << string(30, ' ') << "|" << string(56, ' ') << "|" << string(29, ' ') << "|\n";

    // Get selected item's lore
    vector<string> lore_lines(5, "");

    // Safety check — ensure selected index is valid
    if (!displayed_inventory.empty()) {
        if (selected_item_index >= displayed_inventory.size()) {
            selected_item_index = 0;
        }

        Item selected = displayed_inventory[selected_item_index];
        vector<string> item_lore = selected.get_lore();
        for (size_t i = 0; i < item_lore.size() && i < 5; ++i) {
            lore_lines[i] = item_lore[i];
        }
    }

    // Render the screen section
    cout << col("Lblue") << " | " << col("pink") << centre_text(question, 29) << col("Lblue") << "|" << col("violet")
        << centre_text(lore_lines[0], 56) << col("Lblue") << "|" << col("Lred") << centre_text(inv_hint[0], 29) << col("Lblue") << "|\n";
    cout << " |" << string(30, ' ') << "|" << col("violet") << centre_text(lore_lines[1], 56) << col("Lblue") << "|"
        << col("Lred") << centre_text(inv_hint[1], 29) << col("Lblue") << "|\n";
    cout << " |  " << col("white") << setw(28) << left << option[0] << col("Lblue") << "|" << col("violet") << centre_text(lore_lines[2], 56)
        << col("Lblue") << "|" << col("Lred") << centre_text(inv_hint[2], 29) << col("Lblue") << "|\n";
    cout << " |  " << col("white") << setw(28) << left << option[1] << col("Lblue") << "|" << col("violet") << centre_text(lore_lines[3], 56)
        << col("Lblue") << "|" << col("Lred") << centre_text(inv_hint[3], 29) << col("Lblue") << "|\n";
    cout << " |  " << col("white") << setw(28) << left << option[2] << col("Lblue") << "|" << col("violet") << centre_text(lore_lines[4], 56)
        << col("Lblue") << "|" << col("Lred") << centre_text(inv_hint[4], 29) << col("Lblue") << "|\n";
    cout << " |" << string(30, ' ') << "|" << string(56, ' ') << "|" << string(29, ' ') << "|\n";

    // Final bottom border
    cout << col("violet") << " +" << col("Lblue") << string(30, '-') << col("violet") << "+" << col("Lblue") << string(56, '-')
        << col("violet") << "+" << col("Lblue") << string(29, '-') << col("violet") << "+\n\n";

    // Input prompt
    cout << col("white") << " > ";
}