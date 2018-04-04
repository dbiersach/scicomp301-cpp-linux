// Tile.cpp

#include "stdafx.h"
#include "Tile.h"

using namespace std;

Tile::Tile(int id, int north, int east, int south, int west)
{
    Id = id;
    Rotation = 0;
    Placed = false;

    // Rotation = 0, no turn = original orientation
    Bindings[0][0] = north;
    Bindings[0][1] = east;
    Bindings[0][2] = south;
    Bindings[0][3] = west;

    // Rotation = 1, one quarter turn counterclockwise
    Bindings[1][0] = east;
    Bindings[1][1] = south;
    Bindings[1][2] = west;
    Bindings[1][3] = north;

    // Rotation = 2, two quarter turns counterclockwise
    Bindings[2][0] = south;
    Bindings[2][1] = west;
    Bindings[2][2] = north;
    Bindings[2][3] = east;

    // Rotation = 3, three quarter turns counterclockwise
    Bindings[3][0] = west;
    Bindings[3][1] = north;
    Bindings[3][2] = east;
    Bindings[3][3] = south;
}
