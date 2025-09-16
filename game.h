
#pragma once

#include <string>
#include <vector>

#include "helpers.h"
#include "player.h"
#include "room.h"
#include "ui_constants.h"

struct Game {
    // previous globals
    GameState game_state = GameState::TITLE;
    SortMode current_sort_mode = SortMode::CHRONOLOGICAL;
    bool game_over = false;

    int selected_item_index = 0;
    int current_page = 0;
    int max_pages = 0;

    std::string error_message, question;
    std::vector<std::string> option = make_blank_options();
    std::vector<std::string> inv_hint = make_blank_inv_hints();
    std::vector<std::string> prompt = make_blank_prompt();

    Player player;
    Room* current_room = nullptr; // matches previous behaviour
};
