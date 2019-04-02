// Tile.h

#pragma once

using namespace std;

class Tile
{
public:
    Tile(int id, int north, int east, int south, int west);
    int Id;
    int Rotation;
    bool Placed;
    int Bindings[4][4];
};


