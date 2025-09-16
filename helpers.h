
#pragma once

#include <iostream>
#include <string>
#include <vector>

// STRUCTS + ENUMS
struct Coords {
    int x;
    int y;
};

enum class GameState { TITLE, NAME_ENTRY, EXPLORE, INVENTORY, COMBAT, TESTING };
enum class SortMode { CHRONOLOGICAL, ALPHABETICAL };

// FUNCTION PROTOTYPES
bool yes_no_check(const std::string& prompt);
std::string centre_text(std::string input, int width);
int numbers_error_check(int lower_bounds, int higher_bounds, GameState& game_state, std::string& error_message);
void load_main_question(std::string& question, std::vector<std::string>& option);
void load_inv_main_question(std::string& question, std::vector<std::string>& option);
std::string to_lower(const std::string& input);
std::string capitalise_words(const std::string& input);
std::string strip_ansi_codes(const std::string& input);
std::string pad_visual(const std::string& styled, int width);
void move_cursor(int row, int col);
std::string get_limited_input(int max_len);
void add_text(int row, int column, const std::string& message, std::string colour);
std::string get_random_profile();
