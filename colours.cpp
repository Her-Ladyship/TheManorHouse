
#include "colours.h"

#include <tuple>
#include<algorithm>

std::vector<Colour> colours = {
    {"pink",     "\x1B[38;2;255;105;180m"},  // Hot pink
    {"violet",   "\x1B[38;2;238;130;238m"},  // Orchid/Violet
    {"Lblue",    "\x1B[38;2;173;216;230m"},  // Light blue
    {"Lred",     "\x1B[38;2;255;80;80m"},    // Light red (slightly dimmer than pure bright red)
    {"cyan",     "\x1B[38;2;0;255;255m"},    // Classic bright cyan
    {"green",    "\x1B[38;2;0;200;120m"},    // Muted mint green for softer tone
    {"orange",   "\x1B[38;2;255;165;0m"},    // Standard orange
    {"gold",     "\x1B[38;2;255;215;0m"},    // True gold
    {"white",    "\x1B[38;2;245;245;245m"},  // Softer white—not retina-burning pure white
    {"lavender", "\x1B[38;2;230;200;255m"},
    {"peach",    "\x1B[38;2;255;190;160m"},
    {"slate",    "\x1B[38;2;130;150;160m"},
    {"fog",      "\x1B[38;2;180;180;200m"},  // Hazy bluish grey, good for backgrounds or whispers
    {"dust",     "\x1B[38;2;200;190;170m"},  // Pale brown-grey, for age, books, bones, or faded furniture
    {"ash",      "\x1B[38;2;120;120;130m"},  // Soft charcoal grey, subtle but elegant
    {"crimson",  "\x1B[38;2;200;30;60m"},    // Deep blood red, great for ritual, drama, or secrets
    {"rust",     "\x1B[38;2;183;65;14m"},    // Aged orange-brown, good for decay or old brass
    {"amber",    "\x1B[38;2;255;191;0m"},    // Glowing warm yellow-orange, softer than gold
    {"steel",    "\x1B[38;2;100;120;140m"},  // Muted blue-grey, ideal for machines, knives, or indifference
    {"seafoam",  "\x1B[38;2;150;255;210m"},  // Dreamy green-blue, feels mystical and alive
    {"night",    "\x1B[38;2;30;30;60m"},     // Deep, deep indigo-blue. Near black. Great for shadows or finality.
    {"moss",     "\x1B[38;2;90;140;60m"},    // Damp, green-brown, for hidden corners or lurking things
    {"brass",    "\x1B[38;2;200;160;60m"},   // A dull golden tone—use for antique detail work
    {"rose",     "\x1B[38;2;255;170;200m"},  // Soft and feminine, but ghostly in context—perfect for corrupted innocence
    {"twilight", "\x1B[38;2;110;130;200m"},  // muted indigo-blue
    {"mist",     "\x1B[38;2;200;190;255m"},  // soft lavender haze
    {"ice",      "\x1B[38;2;180;240;255m"},  // pale icy cyan
    {"glint",    "\x1B[38;2;220;255;255m"},  // cool silvery shimmer
    {"abyss",    "\x1B[38;2;90;110;150m"},   // muted shadow blue
    {"frostbite","\x1B[38;2;100;130;180m"}   // a sharper blue, bordering eerie
};

void writing_reset() {
    std::cout << "\x1B[0m";
}

void colour(const std::string& colour_name) {
    writing_reset();
    for (const auto& colour : colours) {
        if (colour.name == colour_name) {
            std::cout << colour.code;
        }
    }
}

std::string col(const std::string& colour_name) {
    for (const auto& colour : colours) {
        if (colour.name == colour_name) {
            return colour.code;
        }
    }
    return "";
}

void bold_text(const std::string& colour_name) {
    writing_reset();
    std::string colour = col(colour_name);
    colour = "\x1B[1m" + colour;
    std::cout << colour;
}

void dim_text(const std::string& colour_name) {
    writing_reset();
    std::string colour = col(colour_name);
    colour = "\x1B[2m" + colour;
    std::cout << colour;
}

void italic_text(const std::string& colour_name) {
    writing_reset();
    std::string colour = col(colour_name);
    colour = "\x1B[3m" + colour;
    std::cout << colour;
}

void underline_text(const std::string& colour_name) {
    writing_reset();
    std::string colour = col(colour_name);
    colour = "\x1B[4m" + colour;
    std::cout << colour;
}

void blinking_text(const std::string& colour_name) {
    writing_reset();
    std::string colour = col(colour_name);
    colour = "\x1B[5m" + colour;
    std::cout << colour;
}

void inverse_text(const std::string& colour_name) {
    writing_reset();
    std::string colour = col(colour_name);
    colour = "\x1B[7m" + colour;
    std::cout << colour;
}

void strikethrough_text(const std::string& colour_name) {
    writing_reset();
    std::string colour = col(colour_name);
    colour = "\x1B[9m" + colour;
    std::cout << colour;
}

std::string health_colour(int num) {
    std::string colour;
    if (num > 69) { colour = col("green"); }
    else if (num > 39 && num < 70) { colour = col("orange"); }
    else { colour = col("Lred"); }

    if (num < 21) { colour = "\x1B[5m" + colour; }

    return colour;
}

std::string apply_tinted_gradient(const std::string& line, int row_index) {
    // Define base RGB colours for each letter in MANOR
    std::vector<std::tuple<int, int, int>> base_colours = {
        {255, 191, 0},   // amber
        {200, 160, 60},  // brass
        {200, 160, 60},  // brass
        {160, 120, 30},  // dark_gold
        {160, 120, 30}   // dark_gold
    };

    // Brightness multiplier fade from top to bottom
    std::vector<float> fade = {
        0.40f, 0.46f, 0.52f,
        0.58f, 0.64f, 0.70f,
        0.76f, 0.82f, 0.88f,
        0.92f, 0.96f, 1.0f
    };

    // Slice positions (widths of each MANOR letter)
    int slice1 = 26, slice2 = 12, slice3 = 14, slice4 = 12;

    auto tint = [](int r, int g, int b, float factor) {
        r = std::min(255, int(r * factor));
        g = std::min(255, int(g * factor));
        b = std::min(255, int(b * factor));
        return "\x1B[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    };

    float brightness = fade[row_index];
    std::string result;

    result += tint(std::get<0>(base_colours[0]), std::get<1>(base_colours[0]), std::get<2>(base_colours[0]), brightness) +
              line.substr(0, slice1);
    result += tint(std::get<0>(base_colours[1]), std::get<1>(base_colours[1]), std::get<2>(base_colours[1]), brightness) +
              line.substr(slice1, slice2);
    result += tint(std::get<0>(base_colours[2]), std::get<1>(base_colours[2]), std::get<2>(base_colours[2]), brightness) +
              line.substr(slice1 + slice2, slice3);
    result += tint(std::get<0>(base_colours[3]), std::get<1>(base_colours[3]), std::get<2>(base_colours[3]), brightness) +
              line.substr(slice1 + slice2 + slice3, slice4);
    result += tint(std::get<0>(base_colours[4]), std::get<1>(base_colours[4]), std::get<2>(base_colours[4]), brightness) +
              line.substr(slice1 + slice2 + slice3 + slice4);

    return result;
}

std::string tint_house_char(char c) {
    switch (c) {
    case '%': case '*': case 'R': return col("crimson") + c;
    case '8': case 'd': return col("ice") + c;
    case 'b': case 'X': case 'N': return col("twilight") + c;
    case 'r': case 'I': case 'k': case 'H': case 'Y': case 'P': case ')': return col("frostbite") + c;
    case '~': case '\'': case '.': return col("mist") + c;
    case '@': case '+': case '=': return col("steel") + c;
    case 'o': case 'z': case 'w': return col("fog") + c;
    case 'x': case '<': return col("abyss") + c;
    case 'a': return "\x1B[5m" + col("pink") + c + "\x1B[0m";
    case ' ': return " ";
    default: return col("violet") + c;
    }
}
