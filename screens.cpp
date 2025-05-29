
#include "screens.h"

const int ITEMS_PER_PAGE = 11;

void show_title_screen() {

    system("CLS");

    // Border
    cout << col("cyan") << " +" << col("Lblue") << string(117, '-') << col("cyan") << "+\n" << col("Lblue");
    cout << " |" << string(117, ' ') << "|\n";

    // 'The'
    cout << " |" << string(5, ' ') << col("violet") << "...     ..      .." << string(60, ' ') << col("pink") << "~~~888~~~ 888"
        << string(21, ' ') << col("Lblue") << "|\n";
    cout << " |   " << col("violet") << "x*8888x.:*8888: -\"888:" << string(61, ' ') << col("pink") << "888    888-~88e  e88~~8e"
        << string(7, ' ') << col("Lblue") << "|\n";
    cout << " |  " << col("violet") << "X   48888X `8888H  8888" << string(61, ' ') << col("pink") << "888    888  888 d888  88b"
        << string(6, ' ') << col("Lblue") << "|\n";
    cout << " | " << col("violet") << "X8x.  8888X  8888X  !888>" << string(60, ' ') << col("pink") << "888    888  888 8888__888"
        << string(6, ' ') << col("Lblue") << "|\n";
    cout << " | " << col("violet") << "X8888 X8888  88888   \"*8%-       u        u.    u.          u.      .u    ."
        << string(10, ' ') << col("pink") << "888    888  888 Y888    ," << col("Lblue") << "      |\n";
    cout << " | " << col("violet") << "'*888!X8888> X8888  xH8>      us888u.   x@88k u@88c.  ...ue888b   .d88B :@8c"
        << string(9, ' ') << col("pink") << "888    888  888  \"88___/ " << string(6, ' ') << col("Lblue") << "|\n";

    // 'Manor' ======
    cout << " |   " << col("violet") << "`?8 `8888  X888X X888>   .@88 \"8888\" ^\"8888\"\"8888\"  888R Y888r =\"8888f8888r"
        << string(39, ' ') << col("Lblue") << "|\n";
    cout << " |   " << col("violet") << "-^  '888\"  X888  8888>   9888  9888    8888  888R   888R I888>   4888>'88\""
        << string(40, ' ') << col("Lblue") << "|\n";
    cout << " |    " << col("violet") << "dx '88~x. !88~  8888>   9888  9888    8888  888R   888R I888>   4888> '"
        << string(42, ' ') << col("Lblue") << "|\n";
    cout << " |  " << col("violet") << ".8888Xf.888x:!    X888X.: 9888  9888    8888  888R   888R I888>   4888>"
        << string(44, ' ') << col("Lblue") << "|\n";
    cout << " | " << col("violet") << ":\"\"888\":~\"888\"     `888*\"  9888  9888    8888  888R  u8888cJ888   .d888L .+"
        << string(41, ' ') << col("Lblue") << "|\n";
    cout << " |     " << col("violet") << "\"~'    \"~        \"\"    \"888*\"\"888\"  \"*88*\" 8888\"  \"*888*P\"    ^\"8888*\""
        << string(42, ' ') << col("Lblue") << "|\n";
    cout << " |" << col("violet") << string(29, ' ') << "^Y\"   ^Y'      \"\"   'Y\"      'Y\"         \"Y\""
        << string(44, ' ') << col("Lblue") << "|\n";
    cout << " |  " << col("violet") << string(93, ' ') << ".x+=:." << string(16, ' ') << col("Lblue") << "|\n";
    cout << " | " << col("violet") << string(51, ' ') << ".xHL" << string(38, ' ') << "z`    ^%"
        << string(15, ' ') << col("Lblue") << "|\n";

    // 'House'
    cout << " |     " << col("violet") << string(44, ' ') << ". - `8888hxxx~         u.       x.    .         .   <k"
        << string(14, ' ') << col("Lblue") << "|\n";
    cout << " |" << string(46, ' ') << col("violet") << ".H8X  `%888*\"       ...ue888b   .@88k  z88u      .@8Ned8\"      .u"
        << string(6, ' ') << col("Lblue") << "|\n";
    cout << " |" << string(46, ' ') << col("violet") << "888X     ..x..      888R Y888r ~\"8888 ^8888    .@^%8888\"    ud8888."
        << col("Lblue") << "    |\n";
    cout << " |" << string(45, ' ') << col("violet") << "'8888k .x8888888x    888R I888>   8888  888R   x88:  `)8b. :888'8888."
        << col("Lblue") << "   |\n";
    cout << " |" << string(46, ' ') << col("violet") << "?8888X    \"88888X   888R I888>   8888  888R   8888N=*8888 d888 '88%\""
        << col("Lblue") << "   |\n";
    cout << " |" << string(47, ' ') << col("violet") << "?8888X    '88888>  888R I888>   8888  888R    %8\"    R88 8888.+\""
        << col("Lblue") << "      |\n";
    cout << " |" << string(44, ' ') << col("violet") << "H8H %8888     `8888> u8888cJ888    8888 ,888B .   @8Wou 9%  8888L"
        << string(8, ' ') << col("Lblue") << "|\n";
    cout << " |" << string(43, ' ') << col("violet") << "'888> 888\"      8888   \"*888*P\"    \"8888Y 8888\"  .888888P`   '8888c. .+"
        << col("Lblue") << "   |\n";
    cout << " |" << string(45, ' ') << col("violet") << "\"8` .8\" ..     88*      'Y\"        `Y\"   'YP    `   ^\"F      \"88888%"
        << col("Lblue") << "    |\n";
    cout << " |" << string(48, ' ') << col("violet") << "`  x8888h. d*\"                                              \"YP'"
        << col("Lblue") << "     |\n";
    cout << " |" << string(52, ' ') << col("violet") << "\"\"*888%~" << string(57, ' ') << col("Lblue") << "|\n";

    // Border
    cout << " |" << string(117, ' ') << "|\n";
    cout << col("cyan") << " +" << col("Lblue") << string(117, '-') << col("cyan") << "+" << col("Lblue");


    system("pause>nul");
}

void show_explore_screen(Player& player, Room*& current_room, string question, string error_message,
                            vector<string> option, vector<string>& prompt) {

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
    cout << " |     " << col("pink") << "Exits     :  " << col("white")  << pad_visual(current_room->room_direction_list(), 40)
        << col("Lblue") << "|" << col("violet") << centre_text(prompt[0], 58) << col("Lblue") << "|\n";
    cout << " |     " << col("pink") << "Items     :  " << col("white") << setw(40) << left
        << current_room->room_item_list() << col("Lblue") << "|" << col("violet") << centre_text(prompt[1], 58) << col("Lblue") << "|\n";
    cout << " |  " << col("pink") << "Curiosities  :  " << col("white") << setw(40) << left
        << current_room->room_interactable_list() << col("Lblue") << "|" << col("violet") << centre_text(prompt[2], 58) << col("Lblue") << "|\n";
    cout << " |" << string(58, ' ') << "|" << col("violet") << centre_text(prompt[3], 58) << col("Lblue") << "|\n";

    // Left break
    cout << col("cyan") << " +" << col("Lblue") << string(58, '-') << col("cyan") << "+"
        << col("violet") << centre_text(prompt[4], 58) << col("Lblue") << "|\n";

    // More boxes
    cout << " |" << col("pink") << centre_text(question, 58) << col("Lblue") << "|" << col("violet") << centre_text(prompt[5], 58) << col("Lblue") << "|\n";
    cout << " |" << string(58, ' ') << "|" << col("violet") << centre_text(prompt[6], 58) << col("Lblue") << "|\n";
    cout << " |   " << col("white") << setw(55) << left << option[0] << col("Lblue") << "|" << string(58, ' ') << "|\n";

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

    int inv_size = player.get_inventory().size();
    int total_pages = max(1, (inv_size + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE);
    string page_info = "Page " + to_string(current_page + 1) + " / " + to_string(total_pages);

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