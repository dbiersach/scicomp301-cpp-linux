// AdjMatrix.h

#pragma once

class AdjMatrix
{
public:
	AdjMatrix();
	~AdjMatrix();

	void Init(int maze[10][10]);
	int MinSteps();

private:
	bool ai[100][100];
	bool af[100][100];

	void Link(int r, int c, int r2, int c2);
	void Step();
};

