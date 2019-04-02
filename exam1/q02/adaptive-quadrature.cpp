// adaptive-quadrature.cpp

#include "stdafx.h"

using namespace std;

// This is the function we are integrating
double f(double x)
{
	return 5 * pow(x, 3) - 9 * pow(x, 2) + 11;
}

// This is the exact analytic integral of our function
double F(double x)
{
	return 5 * pow(x, 4) / 4 - 3 * pow(x, 3) + 11 * x;
}


double midpointFixed(double a, double b)
{
	double n = 1e6;
	double dx = (b - a) / n;
	double area = 0;
	for (double x = a; x < b; x += dx) {
		// Use the midpoint rule
		area += f(x + dx / 2) * dx;
	}
	return area;
}

double midpointAdpative(double a, double b)
{
	double maxSlope = 1e-3;
	double dx = 1;
	double area = 0;
	double x = a;
	while (x < b) {
		double f1 = f(x);
		double f2 = f(x + dx);
		// Implement your code here
	}
	return area;
}

int main()
{
	double a = 0;
	double b = 10;

	double areaActual = F(b) - F(a);
	cout << "Integral using analytic calculus = \t\t"
		<< fixed << setprecision(15)
		<< areaActual << endl;

	double areaFixed = midpointFixed(a, b);
	cout << "Integral using fixed width midpoint rule =\t"
		<< fixed << setprecision(15)
		<< areaFixed << endl;

	double areaAdaptive = midpointAdpative(a, b);
	cout << "Integral using adaptive width midpoint rule =\t"
		<< fixed << setprecision(15)
		<< areaAdaptive	<< endl << endl;

	cout << "% Relative Error Fixed =\t"
		<< fixed << setprecision(15)
		<< abs((areaActual - areaFixed) / areaActual) * 100
		<< endl;

	cout << "% Relative Error Adaptive =\t"
		<< fixed << setprecision(15)
		<< abs((areaActual - areaAdaptive)) / areaActual * 100
		<< endl << endl;

	return 0;
}

