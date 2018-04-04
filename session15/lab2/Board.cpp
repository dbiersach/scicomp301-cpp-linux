// Board.cpp

#include "stdafx.h"
#include "Board.h"

using namespace std;

Board::Board()
{
    tiles[0] = new Tile(0, 128, 4, 2, 8);
    tiles[1] = new Tile(1, 64, 32, 2, 8);
    tiles[2] = new Tile(2, 128, 4, 32, 2);
    tiles[3] = new Tile(3, 2, 32, 4, 128);
    tiles[4] = new Tile(4, 16, 8, 64, 1);
    tiles[5] = new Tile(5, 128, 8, 16, 1);
    tiles[6] = new Tile(6, 128, 4, 16, 2);
    tiles[7] = new Tile(7, 128, 64, 2, 16);
    tiles[8] = new Tile(8, 1, 4, 16, 32);

    for(int i=0; i<9; i++)
        positions[i] = nullptr;
}

Board::~Board()
{
    for (int i=0; i<9; i++)
        delete tiles[i];
}

void Board::Print()
{
    for(int i=0; i<9; i+=3) {
        cout << "(" << positions[i]->Id << " r "
             << positions[i]->Rotation << ")   ";
        cout << "(" << positions[i+1]->Id << " r "
             << positions[i+1]->Rotation << ")   ";
        cout << "(" << positions[i+2]->Id << " r "
             << positions[i+2]->Rotation << ")" << endl;
    }
    cout << endl;
}

bool Board::IsMatch(Tile* tileA, int positionB, int bindingSite)
{
    Tile* tileB = positions[positionB];
    if (tileB == nullptr) return true;
    int sum = 0;
    switch(bindingSite) {
    case 0:  // North binding
        sum = tileA->Bindings[tileA->Rotation][0] + tileB->Bindings[tileB->Rotation][2];
        break;
    case 1: // East binding
        sum = tileA->Bindings[tileA->Rotation][1] + tileB->Bindings[tileB->Rotation][3];
        break;
    case 2: // South binding
        sum = tileA->Bindings[tileA->Rotation][2] + tileB->Bindings[tileB->Rotation][0];
        break;
    case 3: // West binding
        sum = tileA->Bindings[tileA->Rotation][3] + tileB->Bindings[tileB->Rotation][1];
        break;
    }
    return ((sum == 3) || (sum == 12) || (sum == 48) || (sum == 192));
}

bool Board::CanPlaceTile(Tile* tile, int position)
{
    switch (position) {
    case 0:
        if (!IsMatch(tile, 1, 1)) return false;
        if (!IsMatch(tile, 3, 2)) return false;
        break;
    case 1:
        if (!IsMatch(tile, 2, 1)) return false;
        if (!IsMatch(tile, 4, 2)) return false;
        if (!IsMatch(tile, 0, 3)) return false;
        break;
    case 2:
        if (!IsMatch(tile, 5, 2)) return false;
        if (!IsMatch(tile, 1, 3)) return false;
        break;
    case 3:
        if (!IsMatch(tile, 0, 0)) return false;
        if (!IsMatch(tile, 4, 1)) return false;
        if (!IsMatch(tile, 3, 2)) return false;
        break;
    case 4:
        if (!IsMatch(tile, 1, 0)) return false;
        if (!IsMatch(tile, 5, 1)) return false;
        if (!IsMatch(tile, 7, 2)) return false;
        if (!IsMatch(tile, 3, 3)) return false;
        break;
    case 5:
        if (!IsMatch(tile, 2, 0)) return false;
        if (!IsMatch(tile, 8, 2)) return false;
        if (!IsMatch(tile, 4, 3)) return false;
        break;
    case 6:
        if (!IsMatch(tile, 3, 0)) return false;
        if (!IsMatch(tile, 7, 1)) return false;
        break;
    case 7:
        if (!IsMatch(tile, 4, 0)) return false;
        if (!IsMatch(tile, 8, 1)) return false;
        if (!IsMatch(tile, 6, 3)) return false;
        break;
    case 8:
        if (!IsMatch(tile, 5, 0)) return false;
        if (!IsMatch(tile, 7, 3)) return false;
        break;
    }
    return true;
}

void Board::Solve(int position)
{
    for (int tileNum = 0; tileNum < 9; tileNum++) {
        Tile* tile = tiles[tileNum];
        if (!tile->Placed) {
            for (tile->Rotation = 0; tile->Rotation < 4; tile->Rotation++) {
                if (CanPlaceTile(tile, position)) {
                    tile->Placed = true;
                    positions[position] = tile;
                    if (position == 8)
                        Print();
                    else
                        Solve(position + 1);
                    positions[position] = nullptr;
                    tile->Placed = false;
                }
            }
        }
    }
}
