// complex-factorization.cpp

#include "stdafx.h"

using namespace std;

vector<int> primes;

void GeneratePrimes(int count)
{
    primes.push_back(2);
    int n = 3;
    while (primes.size() < count) {
        if (n % 2 == 1) {
            bool isPrime = true;
            for (size_t p{}; p < primes.size(); p++)
                if (n % primes.at(p) == 0) {
                    isPrime = false;
                    break;
                }
            if (isPrime)
                primes.push_back(n);
        }
        n += 2;
    }
    primes.erase(primes.begin());
}

void FindSumOfSquares()
{
    for (int p : primes) {
        for (int a = 1; a <= sqrt(p); a++) {
            double b = sqrt(p - a*a);
            if (floor(b) == b) {
                cout << p << " = "
                     << "(" << a << " + " << b << "i)"
                     << "(" << a << " - " << b << "i)"
                     << endl;
                break;
            }
        }
    }
}

int main()
{
    GeneratePrimes(25);

    FindSumOfSquares();

    return 0;
}

