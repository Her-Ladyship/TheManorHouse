
#pragma once

#include <string>

#include "helpers.h"   // for Coords

// Canonical directions used in navigation prompts.
enum class Direction { North, South, East, West, None };

// Map the menu key the player pressed to a direction.
// 1:N, 2:S, 3:E, 4:W, anything else -> None.
inline Direction direction_from_key(char key) {
    switch (key) {
    case '1': return Direction::North;
    case '2': return Direction::South;
    case '3': return Direction::East;
    case '4': return Direction::West;
    default:  return Direction::None;
    }
}

// Convert a Direction to the user-facing string we already use.
inline std::string to_string(Direction d) {
    switch (d) {
    case Direction::North: return "North";
    case Direction::South: return "South";
    case Direction::East:  return "East";
    case Direction::West:  return "West";
    default:               return "";
    }
}

// Pure helper: return a *new* Coords moved one step in the given direction.
inline Coords moved(Coords c, Direction d) {
    switch (d) {
    case Direction::North: c.y += 1; break;
    case Direction::South: c.y -= 1; break;
    case Direction::East:  c.x += 1; break;
    case Direction::West:  c.x -= 1; break;
    default: break;
    }
    return c;
}