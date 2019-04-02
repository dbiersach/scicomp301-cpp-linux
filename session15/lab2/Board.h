// Board.h

#pragma once

#include "Tile.h"

using namespace std;

class Board
{
public:
    Board();
    ~Board();

    void Print();
    bool IsMatch(Tile* tileA, int positionB, int bindingSite);
    bool CanPlaceTile(Tile* tile, int position);
    void Solve(int position);

    Tile* tiles[9];
    Tile* positions[9];
};



