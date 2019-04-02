// maze-draw.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

struct csv_reader : ctype<char> {
	csv_reader() : ctype<char>(get_table()) {}
	static ctype_base::mask const* get_table() {
		static vector<ctype_base::mask>
			rc(table_size, ctype_base::mask());
		rc[','] = ctype_base::space;
		rc['\n'] = ctype_base::space;
		rc[' '] = ctype_base::space;
		return &rc[0];
	}
};

int maze[10][10];

void LoadMaze()
{
	string line;
	stringstream ss;
	ss.imbue(locale(locale(), new csv_reader()));

	ifstream mazeFile("maze.csv");
	if (!mazeFile) {
		cout << "Missing maze.csv file!" << endl;
		exit(-1);
	}

	for (int r = 0; r < 10; r++) {
		getline(mazeFile, line);
		ss.str(line);
		for (int c = 0; c < 10; c++)
			ss >> maze[r][c];
		ss.clear();
	}

	mazeFile.close();
}

void SaveMaze()
{
	ofstream mazeFile("maze.dat", ios::binary);

	for (int r = 0; r < 10; r++)
		for (int c = 0; c < 10; c++)
			mazeFile.write((char*)&maze[r][c], sizeof(char));

	mazeFile.close();
}

void PrintMaze()
{
	// Print header rows
	cout << setw(6) << right << "  ";
	for (int c = 0; c < 10; c++)
		cout << setw(4) << right << c;
	cout << endl;
	cout << setw(6) << right << "  ";
	for (int c = 0; c < 10; c++)
		cout << setw(4) << right << " ===";
	cout << endl;

	// Print each row by col
	for (int r = 0; r < 10; r++) {
		cout << setw(4) << right << r << "||";
		for (int c = 0; c < 10; c++) {
			cout << setw(4) << right << maze[r][c];
		}
		cout << endl;
	}
	cout << endl;
}

void ValidateCell(int row, int col, int direction)
{
	int r2 = row;
	int c2 = col;

	if (direction == 1) {
		if (row == 0) return;
		else {
			r2--;
			if ((maze[r2][c2] & 4) == 4)
				return;
		}
	}

	if (direction == 2) {
		if (col == 9) return;
		else {
			c2++;
			if ((maze[r2][c2] & 8) == 8)
				return;
		}
	}

	if (direction == 4) {
		if (row == 9) return;
		else {
			r2++;
			if ((maze[r2][c2] & 1) == 1)
				return;

		}
	}

	if (direction == 8) {
		if (col == 0)
			return;
		else {
			c2--;
			if ((maze[r2][c2] & 2) == 2)
				return;
		}
	}

	cout << "Cells (" << row << "," << col << ") and"
		<< " (" << r2 << "," << c2 << ")"
		<< " do not agree in direction " << direction << endl;

	exit(-1);
}

void ValidateMaze()
{
	PrintMaze();

	// Ensure all cells have a value
	for (int r = 0; r < 10; ++r)
		for (int c = 0; c < 10; ++c)
			if (maze[r][c] == -99) {
				cout << "Cell (" << r << "," << c << ")"
					<< " is missing a value" << endl;
				exit(-1);
			}

	// Check outside walls of maze
	for (int i = 0; i < 10; i++) {
		if ((maze[0][i] & 1) != 1) {
			cout << "Cell (0," << i << ")"
				<< " is missing the north wall" << endl;
			exit(-1);
		}
		if ((maze[i][9] & 2) != 2) {
			cout << "Cell (" << i << ",9)"
				<< " is missing the west wall" << endl;
			exit(-1);
		}
		if ((maze[9][i] & 4) != 4) {
			cout << "Cell (9," << i << ")"
				<< " is missing the south wall" << endl;
			exit(-1);
		}
		if ((maze[i][0] & 8) != 8) {
			cout << "Cell (" << i << ",0)"
				<< " is missing the east wall" << endl;
			exit(-1);
		}
	}

	// Check all possible adjacent cells to every cell
	for (int r = 0; r < 10; ++r)
		for (int c = 0; c < 10; ++c) {
			int cell = maze[r][c];
			if ((cell & 1) == 1) ValidateCell(r, c, 1);
			if ((cell & 2) == 2) ValidateCell(r, c, 2);
			if ((cell & 4) == 4) ValidateCell(r, c, 4);
			if ((cell & 8) == 8) ValidateCell(r, c, 8);
		}

	cout << "Maze is valid!" << endl;
}

void draw(SimpleScreen& ss)
{
	// Draw maze (rows by cols)
	for (int r = 0; r < 10; r++) {
		double y0 = (9 - r) * 45;
		double y1 = (9 - r) * 45 + 45;
		for (int c = 0; c < 10; c++) {
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

int main()
{
	LoadMaze();
	ValidateMaze();
	SaveMaze();

	SimpleScreen ss(draw);
	ss.SetZoomFrame("white", 3);

	ss.SetWorldRect(-10, -10, 460, 460);

	ss.HandleEvents();

	return 0;
}

