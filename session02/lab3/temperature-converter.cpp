// temperature-converter.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	cout.imbue(std::locale(""));
	cout << fixed << setprecision(2);

	for (double degF{ -44 }; degF <= 216; degF += 4) {

		double degC = 0;

		cout << setw(7) << right << degF << " F = "
			<< setw(7) << right << degC << " C"
			<< endl;
	}

	return 0;
}

