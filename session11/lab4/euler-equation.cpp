// euler-equation.cpp

#include "stdafx.h"

using namespace std;

void epow(double x)
{
	complex<double> z(0, x);

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
}

int main()
{
    epow(0);                // Theta = PI * 0
    epow(M_PI / 2.);        // Theta = PI * 1/2
    epow(M_PI);             // Theta = PI * 1
    epow(3. * M_PI / 2.);   // Theta = PI * 3/2

	return 0;
}
