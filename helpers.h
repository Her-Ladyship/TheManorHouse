
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
void press_any_key();
bool yes_no_check(const string& prompt);
string centre_text(string input, int width);
int numbers_error_check(int lower_bounds, int higher_bounds, GameState& game_state, string& error_message);
void load_main_question(string& question, vector<string>& option);
