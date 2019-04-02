// euler-identity.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	complex<double> z(0, M_PI);

	complex<double> ez(1, 0);

	uint64_t fact = 1;

	for (int p = 1;p < 21;p = p + 1)
	{
		ez = ez + pow(z, p) / complex<double>(fact, 0);
		fact = fact * (p + 1);
	}

	cout << fixed << setprecision(5)
        << "e^" << z << " = " << ez
		<< endl << endl;

	return 0;
}
