// 4DHypersphereContentQRNG.cpp

#include "stdafx.h"

using namespace std;

const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
37, 41, 43, 47, 53, 59, 61, 67, 71 };

double Halton(int n, int p)
{
	double h = 0;
	double f = 1;
	for (int i = n; i > 0; i /= p) {
		f = f / p;
		h += f * (i % p);
	}
	return h;
}

int main()
{
	int iterations = int(1e7);

	double count = 0;

	for (int i = 0; i < iterations; i++) {
		double x = Halton(i, primes[0]);
		double y = Halton(i, primes[1]);
		double z = Halton(i, primes[2]);

		double distance = x * x + y * y + z * z;

		if (distance <= 1.0)
			count++;
	}

	double volume = count / iterations * 8;

	cout << fixed << setprecision(4)
		<< volume << endl;

	return 0;
}



