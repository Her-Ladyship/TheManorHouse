
#include "helpers.h"
#include "colours.h"

#include <regex>
#include <algorithm>
#include <conio.h>
#include <random>

bool yes_no_check(const string& prompt) {
    string input;
    char choice;

    while (true) {
        cout << prompt;
        cin >> ws;
        getline(cin, input);

        if (input.empty()) {
            cout << "Invalid input. Please enter 'Y' or 'N'.\n";
            continue;
        }

        choice = toupper(input[0]);

        if (choice == 'Y' || choice == 'N') {
            cout << endl;
            return (choice == 'Y');
        }

        cout << "Invalid input. Please enter 'Y' or 'N'.\n";
    }
}

string centre_text(string input, int width) {
    if (input.length() > width) {
        input = input.substr(0, width);
    }

    int pad_left = (width - input.length()) / 2;
    int pad_right = width - input.length() - pad_left;

    return string(pad_left, ' ') + input + string(pad_right, ' ');
}

int numbers_error_check(int lower_bounds, int higher_bounds, GameState& game_state, string& error_message) {
    int user_choice;
    cin >> user_choice;

    if (cin.fail() || user_choice < lower_bounds || user_choice > higher_bounds) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (game_state == EXPLORE) {
            error_message = "Invalid input. Enter a number between " + to_string(lower_bounds) + " and " + to_string(higher_bounds) + ".";
        }
        else if (game_state == INVENTORY) {
            error_message = "DON'T DO THAT. " + to_string(lower_bounds) + " TO " + to_string(higher_bounds) + ".";
        }
        return -1;
    }

    error_message = ""; // Clear error if success
    return user_choice;
}

void load_main_question(string& question, vector<string>& option) {
    question = "What do you want to do?";

    option[0] = "1. Leave Room";
    option[1] = "2. Interact with Curiosity";
    option[2] = "3. Take Item";
    option[3] = "4. Check Inventory";
    option[4] = "";
    option[5] = "Q. Quit";
}

void load_inv_main_question(string& question, vector<string>& option) {
    question = "What would you like to do?";
    option = { "1. Use an item","2. Combine items","3. Return to exploration","","","" };
}

string to_lower(const string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

string capitalise_words(const string& input) {
    string result = input;
    bool capitalise_next = true;

    for (char& ch : result) {
        if (isspace(ch)) {
            capitalise_next = true;
        }
        else if (capitalise_next && isalpha(ch)) {
            ch = toupper(ch);
            capitalise_next = false;
        }
        else {
            ch = tolower(ch);
        }
    }

    return result;
}

string strip_ansi_codes(const string& input) {
    return regex_replace(input, regex("\x1B\\[[0-9;]*m"), "");
}

string pad_visual(const string& styled, int width) {
    int len = strip_ansi_codes(styled).length();
    return styled + string(max(0, width - len), ' ');
}

void move_cursor(int row, int col) {
    cout << "\x1B[" << row << ";" << col << "H";
}

string get_limited_input(int max_len) {
    string result;
    char ch;
    while (true) {
        ch = _getch();

        if (ch == '\r') break; // Enter key
        if (ch == '\b' && !result.empty()) {
            result.pop_back();
            cout << "\b \b"; // Erase last char visually
        }
        else if ((isalpha(ch) || ch == ' ' || ch == '-' || ch == '\'') && result.length() < max_len) {
            result += ch;
            cout << col("violet") << ch; // Echo with style
        }
    }
    return result;
}

void add_text(int row, int column, const string& message, string colour) {
    move_cursor(row, column);
    cout << col(colour) << message;
}

string get_random_profile() {
    static vector<string> profiles = {
        "Overthinker", "Late Bloomer", "Mild Disappointment", "Unwitting Pawn",
        "Habitual Escapist", "Unremarkable Soul", "Chronic Observer",
        "Second Choice", "Misplaced Hope", "Burdened Romantic"
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, profiles.size() - 1);

    return profiles[dist(gen)];
}
