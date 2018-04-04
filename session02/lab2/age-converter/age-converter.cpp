// age-converter.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	double ageInYears = 0;

	double ageInSeconds =
		ageInYears * 1;

	cout.imbue(std::locale(""));
	cout << fixed << setprecision(2);

	cout << "Age (years) = "
		<< ageInYears << endl;

	cout << "Age (secs) = ";

    return 0;
}

