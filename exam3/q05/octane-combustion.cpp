// BalanceEquation.cpp

#include "stdafx.h"
using namespace std;

vector<vector<int>>* eqn;
vector<vector<int>>* stack;
ifstream* infile;

void OpenDataFile(string filename)
{
	infile = new ifstream(filename);

	// Ensure the file can be opened
	if (!infile->is_open()) {
		cout << "Error: Unable to open file "
			"\"" << filename << "\"" << endl;
		exit(-1);
	}
}

void LoadEquation()
{
	int constraints, unknowns;
	*infile >> constraints >> unknowns;

	eqn = new vector<vector<int>>(constraints);
	vector<int> constraint(unknowns);

	for (auto& e : *eqn) {
		for (auto& c : constraint)
			*infile >> c;
		e = constraint;
	}
}


void InitStack() {
	stack = new vector<vector<int>>();
	for (size_t i{}; i < eqn->front().size(); ++i)
		stack->push_back({ 1,eqn->back().at(i) + 1 });
}

bool IsSolution()
{
	for (size_t j{}; j < eqn->size() - 1; ++j) {
		int sum = 0;
		for (size_t i{}; i < stack->size(); ++i)
			sum += eqn->at(j).at(i) * stack->at(i).at(0);
		if (sum != 0)
			return false;
	}
	return true;
}

bool FindSolution()
{
	int stackLevel = 0;
	while (stackLevel >= 0) {
		while (stack->at(stackLevel).at(0)
			< stack->at(stackLevel).at(1))
		{
			if (stackLevel == (int)stack->size() - 1) break;
			stackLevel++;
			stack->at(stackLevel).at(0) = 1;
		}

		if (IsSolution())
			return true;

		stack->at(stackLevel).at(0)++;
		while (stack->at(stackLevel).at(0)
			== stack->at(stackLevel).at(1))
		{
			stackLevel--;
			if (stackLevel < 0) break;
			stack->at(stackLevel).at(0)++;
		}
	}
	return false;
}

void PrintUnknowns() {
	for (size_t i{}; i < stack->size(); ++i)
		cout << "x" << i << " = "
		<< stack->at(i).at(0) << endl;
}


int main(int argc, char *argv[])
{
	OpenDataFile("octane.txt");

	LoadEquation();

	InitStack();

	if (FindSolution())
		PrintUnknowns();

	return 0;
}

