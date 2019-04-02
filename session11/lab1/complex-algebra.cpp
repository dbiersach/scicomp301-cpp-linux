// complex-algebra.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	complex<double> z1(-5.9, -7.5);
	complex<double> z2(sqrt(2), M_PI);

	cout << "z1 = " << z1 << endl
		<< "z2 = " << z2 << endl << endl;

	cout << "z1 + z2 = "
		<< z1 + z2 << endl;

	cout << "z1 - z2 = "
		<< z1 - z2 << endl;

	cout << "z1 * z2 = "
		<< z1 * z2 << endl;

	cout << "z1 / z2 = "
		<< z1 / z2 << endl;

	cout << endl << "z1^2 = "
		<< pow(z1, 2) << endl << endl;

	return 0;
}

