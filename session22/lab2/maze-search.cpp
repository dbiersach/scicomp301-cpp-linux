// maze-search.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

int maze[10][10];
bool crumbs[10][10];
int visitCount[10][10];

vector<string> visitColors =
{ "blue","green","red","orange","purple","yellow","cyan" };

vector<tuple<int, int, int>> stack;

bool foundExit = false;
int totalSteps = 0;


void ResetVisitCount()
{
	for (int r = 0; r < 10; r++)
		for (int c = 0; c < 10; c++)
			visitCount[r][c] = 0;
}

void LoadMaze()
{
	ifstream mazeFile("maze.dat", ios::binary);
	if (!mazeFile) {
		cout << "Missing maze.dat file!" << endl;
		exit(-1);
	}

	for (int r = 0; r < 10; r++) {
		for (int c = 0; c < 10; c++) {
			mazeFile.read((char*)&maze[r][c], sizeof(char));
			crumbs[r][c] = false;
		}
	}

	mazeFile.close();
}

void DrawMaze(SimpleScreen& ss)
{
	// Draw maze (rows by cols)
	for (size_t r{ 0 }; r < 10; ++r) {
		double y0 = (9 - r) * 45;
		double y1 = (9 - r) * 45 + 45;
		for (size_t c{}; c < 10; ++c) {
			double x0 = c * 45;
			double x1 = c * 45 + 45;

			Point2D v0(x0, y0);	// Lower-left vertex
			Point2D v1(x1, y0);	// Lower-right vertex
			Point2D v2(x1, y1);	// Upper-right vertex
			Point2D v3(x0, y1);	// Upper-left vertex

			// Draw entrance cell
			if (r == 0 && c == 0)
				ss.DrawRectangle("tan", v0.x, v0.y, 45, 45, 1, true);
			// Draw exit cell
			if (r == 9 && c == 9)
				ss.DrawRectangle("orange", v0.x, v0.y, 45, 45, 1, true);

			// Draw cell corner circles
			ss.DrawCircle(v0.x, v0.y, 2, "black", 5);
			ss.DrawCircle(v1.x, v1.y, 2, "black", 5);
			ss.DrawCircle(v2.x, v2.y, 2, "black", 5);
			ss.DrawCircle(v3.x, v3.y, 2, "black", 5);

			int cell = maze[r][c];
			// Draw north wall if required
			if ((cell & 1) == 1)
				ss.DrawLine(v2, v3, "black", 3);
			// Draw west wall if required
			if ((cell & 2) == 2)
				ss.DrawLine(v1, v2, "black", 3);
			// Draw south wall if required
			if ((cell & 4) == 4)
				ss.DrawLine(v0, v1, "black", 3);
			// Draw east wall if required
			if ((cell & 8) == 8)
				ss.DrawLine(v0, v3, "black", 3);
		}
	}
}

void DrawVisitCount(SimpleScreen &ss)
{
	for (int r = 0; r < 10; r++) {
		double y0 = (9 - r) * 45;
		double y1 = (9 - r) * 45 + 45;
		for (size_t c{}; c < 10; ++c) {
			double x0 = c * 45;
			double x1 = c * 45 + 45;
			Point2D v0(x0 + 15, y0 + 15);
			Point2D v1(x1 - 15, y0 + 15);
			Point2D v2(x1 - 15, y1 - 15);
			Point2D v3(x0 + 15, y1 - 15);
			size_t count = visitCount[r][c];
			if (count > 0) {
				if (count > visitColors.size())
					count = visitColors.size();
				ss.DrawRectangle(visitColors.at(count - 1),
					v0.x, v0.y, 15, 15, 1, true);
			}
		}
	}
}


void draw(SimpleScreen& ss)
{
	DrawVisitCount(ss);
}

bool TryStep()
{
	bool moved = false;

	int r = get<0>(stack.back());
	int c = get<1>(stack.back());
	int r2 = r;
	int c2 = c;

	int dir = get<2>(stack.back());
	if (dir == 1) r2--;
	if (dir == 2) c2++;
	if (dir == 4) r2++;
	if (dir == 8) c2--;

	get<2>(stack.back()) *= 2;

	if (((maze[r][c] & dir) != dir) &&
		(!crumbs[r2][c2]))
	{
		tuple<int, int, int> cell(r2, c2, 1);
		stack.push_back(cell);
		moved = true;
	}

	if (dir == 16 && !moved) {
		crumbs[r][c] = false;
		stack.pop_back();
		r2 = get<0>(stack.back());
		c2 = get<1>(stack.back());
		moved = true;
	}

	if (moved) {
		crumbs[r2][c2] = true;
		visitCount[r2][c2]++;
		totalSteps++;
		if (r2 == 9 && c2 == 9)
			foundExit = true;
		return true;
	}

	return false;
}

void Navigate(SimpleScreen& ss, bool singleStep)
{
	while (!foundExit) {
		while (!TryStep());
		if (foundExit) {
			cout << "Exit found!" << endl
				<< "Total steps = " << totalSteps << endl
				<< "Path steps = " << stack.size() - 1 << endl;
			ResetVisitCount();
			for (auto s : stack)
				visitCount[get<0>(s)][get<1>(s)] = 1;
			ss.Clear();
			DrawMaze(ss);
		}
		ss.Redraw();
		if (singleStep) break;
	}
}

void eventHandler(SimpleScreen& ss, ALLEGRO_EVENT& ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_S)
			Navigate(ss, true);
		if (ev.keyboard.keycode == ALLEGRO_KEY_F)
			Navigate(ss, false);
	}
}

int main()
{
	LoadMaze();
	ResetVisitCount();

	tuple<int, int, int> entrance(0, 0, 1);
	stack.push_back(entrance);
	crumbs[0][0] = true;
	visitCount[0][0] = 1;

	SimpleScreen ss(draw, eventHandler);
	ss.SetZoomFrame("white", 3);
	ss.SetWorldRect(-10, -10, 460, 460);

	DrawMaze(ss);

	ss.HandleEvents();

	return 0;
}

