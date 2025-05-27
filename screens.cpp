
#include "screens.h"

const int ITEMS_PER_PAGE = 11;

void show_explore_screen(Player& player, Room*& current_room, string question, string error_message, vector<string> option) {

    current_room = find_room_by_coords(room_list, player.get_location());

    system("CLS");

    // Break
    cout << col("cyan") << " +" << col("Lblue") << string(37, '-') << col("cyan")
        << "+" << col("Lblue") << string(41, '-') << col("cyan")
        << "+" << col("Lblue") << string(37, '-') << col("cyan") << "+\n";

    // Title
    cout << col("Lblue") << " |      " << col("pink") << "Name: " << col("violet")
        << setw(24) << left << player.get_name() << col("Lblue") << " |           " << col("pink")
        << " Health: " << health_colour(player.get_health()) << setw(3) << right << player.get_health() << "\x1B[0m"
        << col("green") << " / 100            " << col("Lblue") << "|      " << col("pink")
        << "Location: " << col("violet") << setw(21) << left << current_room->get_name()
        << col("Lblue") << "|\n";

    // Break
    cout << col("cyan") << " +" << col("Lblue") << string(37, '-') << col("cyan")
        << "+" << col("Lblue") << string(41, '-') << col("cyan")
        << "+" << col("Lblue") << string(37, '-') << col("cyan") << "+\n";

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
    cout << col("cyan") << " +" << col("Lblue") << string(58, '-') << col("cyan") << "+"
        << col("Lblue") << string(58, '-') << col("cyan") << "+\n";

    // Boxes
    cout << col("Lblue") << " |" << string(58, ' ') << "|" << string(58, ' ') << "|\n";
    cout << " |     " << col("pink") << "Exits     :  " << col("white") << setw(40) << left
        << room_direction_list(current_room) << col("Lblue") << "|" << string(58, ' ') << "|\n";
    cout << " |     " << col("pink") << "Items     :  " << col("white") << setw(40) << left
        << room_item_list(current_room) << col("Lblue") << "|                 " << col("violet")
        << "THIS PART CAN SHOW THE                   " << col("Lblue") << "|\n";
    cout << " |  " << col("pink") << "Curiosities  :  " << col("white") << setw(40) << left
        << room_interactable_list(current_room) << col("Lblue") << "|                  "
        << col("violet") << "SYSTEM RESPONSE FROM                    " << col("Lblue") << "|\n";
    cout << " |" << string(58, ' ') << "|                     " << col("violet")
        << "LAST USER INPUT                      " << col("Lblue") << "|\n";

    // Left break
    cout << col("cyan") << " +" << col("Lblue") << string(58, '-') << col("cyan") << "+"
        << string(58, ' ') << col("Lblue") << "|\n";

    // More boxes
    cout << " |" << col("pink") << centre_text(question, 58)
        << col("Lblue") << "|" << string(58, ' ') << "|\n";
    cout << " |" << string(58, ' ') << "|" << string(58, ' ') << "|\n";
    cout << " |   " << col("white") << setw(55) << left << option[0]
        << col("Lblue") << "|" << string(58, ' ') << "|\n";

    // Right break
    cout << " |   " << col("white") << setw(55) << left << option[1] << col("cyan")
        << "+" << col("Lblue") << string(58, '-') << col("cyan") << "+\n" << col("Lblue");
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
    cout << col("cyan") << " +" << col("Lblue") << string(58, '-') << col("cyan") << "+"
        << col("Lblue") << string(58, '-') << col("cyan") << "+\n\n";

    // Cursor input
    cout << col("white") << " > ";
}

void show_inventory_screen(Player& player, int& selected_item_index, vector<string>& inv_hint, string& question,
                            vector<string>& option, SortMode current_sort_mode, int& current_page, int& max_pages) {

    system("CLS");

    // Header border
    cout << col("cyan") << " +" << col("Lblue");
    cout << string(117, '-') << col("cyan") << "+\n";

    string sort_type = "S: Sort (";
    if (current_sort_mode == CHRONOLOGICAL) { sort_type += "CHRONOLOGICAL"; }
    if (current_sort_mode == ALPHABETICAL) { sort_type += "ALPHABETICAL"; }
    sort_type += ")";

    string page_info = "Page " + to_string(current_page + 1) + " / "
        + to_string((player.get_inventory().size() - 1) / ITEMS_PER_PAGE + 1);

    // Title line
    cout << col("Lblue") << " |     " << col("pink") << setw(30) << left << page_info << string(19, ' ')
        << "INVENTORY" << col("violet") << setw(49) << right << sort_type << col("Lblue") << "     |\n";

    // Divider
    cout << col("cyan") << " +" << col("Lblue") << string(30, '-') << col("cyan") << "+"
        << col("Lblue") << string(86, '-') << col("cyan") << "+\n";

    // Column headers
    cout << col("Lblue") << " |     " << col("pink") << setw(25) << left << "Item" << col("Lblue")
        << "|  " << col("pink") << setw(84) << left << "Description" << col("Lblue") << "|\n";

    // Divider
    cout << col("cyan") << " +" << col("Lblue") << string(30, '-') << col("cyan") << "+"
        << col("Lblue") << string(86, '-') << col("cyan") << "+\n";

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
    cout << col("cyan") << " +" << col("Lblue");
    cout << string(30, '-') << col("cyan") << "+" << col("Lblue") << string(56, '-')
        << col("cyan") << "+" << col("Lblue") << string(29, '-') << col("cyan") << "+\n";

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
    cout << col("cyan") << " +" << col("Lblue") << string(30, '-') << col("cyan") << "+" << col("Lblue") << string(56, '-')
        << col("cyan") << "+" << col("Lblue") << string(29, '-') << col("cyan") << "+\n\n";

    // Input prompt
    cout << col("white") << " > ";
}