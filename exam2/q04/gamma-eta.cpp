// gamma-eta.cpp

#include "stdafx.h"

using namespace std;

double Eta(double s)
{
	double eta = 1;
	for (int n{ 2 }; n <= 1e5; n++)
	{
		double term = 1. / pow(n, s);
		eta += (n % 2) == 0 ? -term : term;
	}
	return eta;
}

inline double f(double x, double s)
{
    // Add your code here
}

double Simpsons(double s)
{
	double a{ 0 };
	double b{ 1e3 };
	int intervals = 1e5;

	double dx{ (b - a) / intervals };
	double sum{ f(a,s) + f(b,s) };
	a += dx;
	for (int i{ 1 }; i < intervals; ++i, a += dx)
		sum += f(a, s)*(2 * (i % 2 + 1));
	return (dx / 3)*sum;
}

int main()
{
	double s = 6;

	double gamma = Simpsons(s) / Eta(s);

	cout << gamma << endl;

	return 0;
}
