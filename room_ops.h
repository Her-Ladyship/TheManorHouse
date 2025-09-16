
#pragma once

#include <string>
#include <vector>

struct Coords;
class Player;
class Room;
class Game;

// Find a room by coordinates within a list.
Room* find_room_by_coords(const std::vector<Room>& rooms, Coords target);

// Handle the explore -> move prompt + state changes.
void change_room(Game& g);

// Initialise any doors that start locked.
void initialise_locked_doors();
