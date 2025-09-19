
#pragma once
#include <string>
#include <vector>

constexpr int PROMPT_LINES = 7;
constexpr int OPTION_SLOTS = 6;
constexpr int INV_HINT_LINES = 5;
constexpr int COMBAT_LINES = 10;

// Handy helpers for blanking UI regions.
inline std::vector<std::string> make_blank_prompt() { return std::vector<std::string>(PROMPT_LINES, ""); }
inline std::vector<std::string> make_blank_options() { return std::vector<std::string>(OPTION_SLOTS, ""); }
inline std::vector<std::string> make_blank_inv_hints() { return std::vector<std::string>(INV_HINT_LINES, ""); }
inline std::vector<std::string> make_blank_combat_lines() { return std::vector<std::string>(COMBAT_LINES, ""); }
