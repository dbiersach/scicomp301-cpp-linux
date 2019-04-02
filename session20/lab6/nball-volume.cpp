// nball-volume.cpp

#include "stdafx.h"

using namespace std;

// Euler's Gamma kernel
inline double f(double x, double n)
{
	return pow(x,n-1) * exp(-x);
}

// Find Gamma using Simpson's integration
double gamma(double n)
{
	double a{ 0 };
	double b{ 1e3 };
	int intervals = 1e5;

	double dx{ (b - a) / intervals };
	double sum{ f(a,n) + f(b,n) };
	a += dx;
	for (int i{ 1 }; i < intervals; ++i, a += dx)
		sum += f(a, n)*(2 * (i % 2 + 1));
	return (dx / 3)*sum;
}

// Find volume of unit ball
// See https://en.wikipedia.org/wiki/N-sphere
double v(double x)
{
	double halfx = x / 2.0;
	return pow(M_PI, halfx) / gamma(halfx + 1);
}

// This returns the x and y values for the maximum value of a function
// when both the analytic & numerical first derivative are unavailable.
// Note: This only works for concave down (negative second derivative) functions
tuple<double, double> find_max(double x1, double x2, double epsilon)
{
	double max = numeric_limits<double>::min();
	while (true)
	{
		double dx = (x2 - x1) / 97;
		double y1 = v(x1);
		double y2 = v(x1 + dx);
		while (y1 < y2)
		{
			x1 = x1 + dx;
			y1 = v(x1);
			y2 = v(x1 + dx);
		}
		if (abs(max - y1) < epsilon)
			break;
		x1 = x1 - dx;
		x2 = x1 + dx;
		max = v(x1);
	}
	return tuple<double, double>(x1, v((x1 + x2) / 2));
}

int main()
{
	cout << "Unit Hypersphere" << endl
		<< "Dim  Volume" << endl << fixed;

	for (double x{ 1 }; x <= 10; x += 1)
		cout << setw(2) << setprecision(0) << x << " = "
		<< setprecision(6) << v(x) << endl;

	tuple<double, double> max = find_max(1, 10, 1e-8);

	cout << "Max Volume = " << get<1>(max) << endl
		<< "Dimension = " << get<0>(max) << endl;

	return 0;
}

