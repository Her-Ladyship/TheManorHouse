
#include "helpers.h"
#include "colours.h"

#include <regex>
#include <algorithm>
#include <conio.h>
#include <random>
#include <limits>   // NEW: for std::numeric_limits
#include <cctype>   // NEW: for std::toupper / std::tolower / std::isspace / std::isalpha


bool yes_no_check(const std::string& prompt) {
    std::string input;
    char choice;

    while (true) {
        std::cout << prompt;
        std::cin >> std::ws;
        std::getline(std::cin, input);

        if (input.empty()) {
            std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
            continue;
        }

        choice = static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));

        if (choice == 'Y' || choice == 'N') {
            std::cout << std::endl;
            return (choice == 'Y');
        }

        std::cout << "Invalid input. Please enter 'Y' or 'N'.\n";
    }
}

std::string centre_text(std::string input, int width) {
    if (static_cast<int>(input.length()) > width) {
        input = input.substr(0, width);
    }
    int pad_left = (width - static_cast<int>(input.length())) / 2;
    int pad_right = width - static_cast<int>(input.length()) - pad_left;
    return std::string(pad_left, ' ') + input + std::string(pad_right, ' ');
}

int numbers_error_check(int lower_bounds, int higher_bounds, GameState& game_state, std::string& error_message) {
    int user_choice;
    std::cin >> user_choice;

    if (std::cin.fail() || user_choice < lower_bounds || user_choice > higher_bounds) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (game_state == GameState::EXPLORE) {
            error_message = "Invalid input. Enter a number between " +
                std::to_string(lower_bounds) + " and " + std::to_string(higher_bounds) + ".";
        }
        else if (game_state == GameState::INVENTORY) {
            error_message = "DON'T DO THAT. " + std::to_string(lower_bounds) + " TO " + std::to_string(higher_bounds) + ".";
        }
        return -1;
    }

    error_message = "";
    return user_choice;
}

void load_main_question(std::string& question, std::vector<std::string>& option) {
    question = "What do you want to do?";
    option[0] = "1. Leave Room";
    option[1] = "2. Interact with Curiosity";
    option[2] = "3. Take Item";
    option[3] = "4. Check Inventory";
    option[4] = "";
    option[5] = "Q. Quit";
}

void load_inv_main_question(std::string& question, std::vector<std::string>& option) {
    question = "What would you like to do?";
    option = { "1. Use an item","2. Combine items","3. Return to exploration","","","" };
}

void load_combat_lines(std::vector<std::string>& combat_lines) {
    combat_lines = { "", "WHAT WILL YOU DO?", "",
                      "1. Strike",
                      "2. Throw",
                      "3. Guard",
                      "4. Use Item",
                      "5. Flee",
                      "" };
}

std::string to_lower(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return result;
}

std::string capitalise_words(const std::string& input) {
    std::string result = input;
    bool capitalise_next = true;

    for (char& ch : result) {
        unsigned char uch = static_cast<unsigned char>(ch);
        if (std::isspace(uch)) {
            capitalise_next = true;
        }
        else if (capitalise_next && std::isalpha(uch)) {
            ch = static_cast<char>(std::toupper(uch));
            capitalise_next = false;
        }
        else {
            ch = static_cast<char>(std::tolower(uch));
        }
    }
    return result;
}

std::string strip_ansi_codes(const std::string& input) {
    return std::regex_replace(input, std::regex("\x1B\\[[0-9;]*m"), "");
}

std::string pad_visual(const std::string& styled, int width) {
    int len = static_cast<int>(strip_ansi_codes(styled).length());
    return styled + std::string(std::max(0, width - len), ' ');
}

void move_cursor(int row, int col) {
    std::cout << "\x1B[" << row << ";" << col << "H";
}

std::string get_limited_input(int max_len) {
    std::string result;
    char ch;
    while (true) {
        ch = _getch();

        if (ch == '\r') break; // Enter
        if (ch == '\b' && !result.empty()) {
            result.pop_back();
            std::cout << "\b \b";
        }
        else if ((std::isalpha(static_cast<unsigned char>(ch)) || ch == ' ' || ch == '-' || ch == '\'')
            && static_cast<int>(result.length()) < max_len) {
            result += ch;
            std::cout << col("violet") << ch; // echo with style
        }
    }
    return result;
}

void add_text(int row, int column, const std::string& message, std::string colour) {
    move_cursor(row, column);
    std::cout << col(colour) << message;
}

std::string get_random_profile() {
    static std::vector<std::string> profiles = {
        "Overthinker", "Late Bloomer", "Mild Disappointment", "Unwitting Pawn",
        "Habitual Escapist", "Unremarkable Soul", "Chronic Observer",
        "Second Choice", "Misplaced Hope", "Burdened Romantic"
    };

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(profiles.size()) - 1);

    return profiles[dist(gen)];
}