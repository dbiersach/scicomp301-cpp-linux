// ScrambleSquaresSolver.cpp

#include "stdafx.h"
#include "Tile.h"
#include "Board.h"

using namespace std;

int main()
{
    Board* board = new Board();
    board->Solve(0);
    delete board;
    return 0;
}
