
#include "colours.h"

vector<Colour> colours = {
    {"pink", "\x1B[38;2;255;105;180m"},
    {"lime", "\x1B[38;2;0;255;0m"},
    {"Lblue", "\x1B[38;2;173;216;230m"},
    {"violet", "\x1B[38;2;238;130;238m"},
    {"red", "\x1B[31m"},
    {"green", "\x1B[32m"},
    {"blue", "\x1B[34m"},
    {"yellow", "\x1B[33m"},
    {"cyan", "\x1B[36m"},
    {"magenta", "\x1B[35m"},
    {"white", "\x1B[37m"},
    {"Lred", "\x1B[91m"},
    {"bright_green", "\x1B[92m"},
    {"bright_yellow", "\x1B[93m"},
    {"bright_blue", "\x1B[94m"},
    {"bright_cyan", "\x1B[96m"},
    {"bright_magenta", "\x1B[95m"},
    {"bright_white", "\x1B[97m"},
    {"indigo", "\x1B[38;2;75;0;130m"},
    {"orange", "\x1B[38;2;255;165;0m"},
    {"teal", "\x1B[38;2;0;128;128m"},
    {"gold", "\x1B[38;2;255;215;0m"}
};

void writing_reset() {
    cout << "\x1B[0m";
}

void colour(const string& colour_name) {
    writing_reset();
    for (const auto& colour : colours) {
        if (colour.name == colour_name) {
            cout << colour.code;
        }
    }
}

string col(const string& colour_name) {
    for (const auto& colour : colours) {
        if (colour.name == colour_name) {
            return colour.code;
        }
    }
    return "";
}

void bold_text(const string& colour_name) {
    writing_reset();
    string colour = col(colour_name);
    colour = "\x1B[1m" + colour;
    cout << colour;
}

void dim_text(const string& colour_name) {
    writing_reset();
    string colour = col(colour_name);
    colour = "\x1B[2m" + colour;
    cout << colour;
}

void italic_text(const string& colour_name) {
    writing_reset();
    string colour = col(colour_name);
    colour = "\x1B[3m" + colour;
    cout << colour;
}

void underline_text(const string& colour_name) {
    writing_reset();
    string colour = col(colour_name);
    colour = "\x1B[4m" + colour;
    cout << colour;
}

void blinking_text(const string& colour_name) {
    writing_reset();
    string colour = col(colour_name);
    colour = "\x1B[5m" + colour;
    cout << colour;
}

void inverse_text(const string& colour_name) {
    writing_reset();
    string colour = col(colour_name);
    colour = "\x1B[7m" + colour;
    cout << colour;
}

void strikethrough_text(const string& colour_name) {
    writing_reset();
    string colour = col(colour_name);
    colour = "\x1B[9m" + colour;
    cout << colour;
}

string health_colour(int num) {
    string colour;
    if (num > 69) { colour = col("green"); }
    else if (num > 39 && num < 70) { colour = col("orange"); }
    else { colour = col("Lred"); }

    if (num < 21) { colour = "\x1B[5m" + colour; }

    return colour;
}