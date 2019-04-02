// AdjMatrix.cpp

#include "stdafx.h"
#include "AdjMatrix.h"

using namespace std;

AdjMatrix::AdjMatrix()
{
	for (int r = 0; r < 100; r++) {
		for (int c = 0; c < 100; c++) {
			ai[r][c] = false;
			af[r][c] = false;
		}
	}
}

AdjMatrix::~AdjMatrix()
{
}

void AdjMatrix::Link(int r, int c, int r2, int c2)
{
	int cell1 = r * 10 + c;
	int cell2 = r2 * 10 + c2;
	ai[cell1][cell2] = true;
	ai[cell2][cell1] = true;
}

void AdjMatrix::Init(int maze[10][10])
{
	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			if (r == c)
				Link(r, c, r, c);
			if ((maze[r][c] & 1) != 1)
				Link(r, c, r - 1, c);
			if ((maze[r][c] & 2) != 2)
				Link(r, c, r, c + 1);
			if ((maze[r][c] & 4) != 4)
				Link(r, c, r + 1, c);
			if ((maze[r][c] & 8) != 8)
				Link(r, c, r, c - 1);
		}
	}
	for (int r = 0; r < 100; r++)
		for (int c = 0; c < 100; c++)
			af[r][c] = ai[r][c];
}


void AdjMatrix::Step()
{
	bool temp[100][100];

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			bool linked = false;
			for (int k = 0; k < 100; k++) {
				if (ai[i][k] && af[k][j]) {
					linked = true;
					break;
				}
			}
			temp[i][j] = linked;
		}
	}

	for (int r = 0; r < 100; r++)
		for (int c = 0; c < 100; c++)
			af[r][c] = temp[r][c];
}

int AdjMatrix::MinSteps()
{
	int minSteps = 0;
	while (!af[0][99])	{
		Step();
		minSteps++;
	}
	return minSteps + 1;
}