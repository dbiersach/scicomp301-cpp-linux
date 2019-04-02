// HighDimensionHypersphere.cpp

#include "stdafx.h"

using namespace std;

const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
					   37, 41, 43, 47, 53, 59, 61, 67, 71 };

double Halton(int n, int p)
{
	double h = 0;
	double f = 1;
	for (int i = n; i > 0; i /= p)
	{
		f = f / p;
		h += f * (i % p);
	}
	return h;
}

int main()
{
	int iterations = int(1e7);
	for (int dimension{ 2 }; dimension < 13; ++dimension) {
		double count{};
		for (int i{}; i < iterations; ++i) {
			double distance = 0;
			for (int d{}; d < dimension; ++d) {
				double v = Halton(i, primes[d]);
				distance = distance + v * v;
				if (distance > 1.0)
					break;
			}
			if (distance <= 1.0)
				count++;
		}
		double volume = count / iterations * pow(2, dimension);
		cout << fixed << right << setw(2) << dimension << ", "
			<< setprecision(4) << volume
			<< endl;
	}

	return 0;
}

