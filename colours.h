
#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Colour {
    std::string name;
    std::string code;
};

// Function declarations
void writing_reset();
void colour(const std::string& colour_name);
std::string col(const std::string& colour_name);

void bold_text(const std::string& colour_name);
void dim_text(const std::string& colour_name);
void italic_text(const std::string& colour_name);
void underline_text(const std::string& colour_name);
void blinking_text(const std::string& colour_name);
void inverse_text(const std::string& colour_name);
void strikethrough_text(const std::string& colour_name);

std::string health_colour(int num);
std::string apply_tinted_gradient(const std::string& line, int row_index);
std::string tint_house_char(char c);

// Declare colour list
extern std::vector<Colour> colours;
