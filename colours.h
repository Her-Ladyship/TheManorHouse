
#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Colour {
    string name;
    string code;
};

// Function declarations
void writing_reset();
void colour(const string& colour_name);
string col(const string& colour_name);

void bold_text(const string& colour_name);
void dim_text(const string& colour_name);
void italic_text(const string& colour_name);
void underline_text(const string& colour_name);
void blinking_text(const string& colour_name);
void inverse_text(const string& colour_name);
void strikethrough_text(const string& colour_name);

string health_colour(int num);

// Declare colour list
extern vector<Colour> colours;