
#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// STRUCTS + ENUMS
struct Coords {
    int x;
    int y;
};

enum GameState {
    TITLE,
    EXPLORE,
    INVENTORY,
    COMBAT
};

enum SortMode { CHRONOLOGICAL, ALPHABETICAL };

// FUNCTION PROTOTYPES
bool yes_no_check(const string& prompt);
string centre_text(string input, int width);
int numbers_error_check(int lower_bounds, int higher_bounds, GameState& game_state, string& error_message);
void load_main_question(string& question, vector<string>& option);
void load_inv_main_question(string& question, vector<string>& option);
string to_lower(const string& input);
string capitalise_words(const string& input);
string strip_ansi_codes(const string& input);
string pad_visual(const string& styled, int width);