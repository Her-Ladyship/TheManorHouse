
#pragma once
#include <string>
#include <vector>

// Forward declarations instead of including heavy headers here
class Player;
class Room;
class Game;

bool logic_take_item(Game& g, const std::string& cleaned_input);
bool logic_interact(Game& g, const std::string& lower_input);
Room* find_adjacent_room_by_direction(Room* from, const std::string& dir);
bool flee_through_any_unlocked_exit(Game& g);
bool gate_enemy_locked_room_on_entry(Game& g, Room* target);