// goldbach-conjecture.cpp

#include "stdafx.h"

using namespace std;

vector<int> GeneratePrimes(size_t numPrimes)
{
    vector<int> primes;

    primes.push_back(2);

    int n = 3;
    while (primes.size() < numPrimes)
    {
        int r = 0;
        for (int p : primes)
        {
            r = n % p;
            if (r == 0) break;
        }
        if (r > 0)
            primes.push_back(n);
        n = n + 2;
    }

    return primes;
}

int main()
{
    vector<int> primes = GeneratePrimes(50);

    // Remove the first (only even) prime which is 2
    primes.erase(primes.begin());

    cout << "For primes " << primes.front()
         << " to " << primes.back()
         << ": " << endl;

    vector<bool> goldbachNumbers(primes.back() * 2 + 1);

    // Pair up each prime with itself, and then to each successive prime.
    // Sum these two numbers, and use this sum as an index into a boolean
    // vector that records if a sum has occurred at least once
    for (size_t i{0}; i < primes.size(); i++)
        for (size_t j{i}; j < primes.size(); j++)
            goldbachNumbers.at(primes.at(i) + primes.at(j)) = true;

    // Verify all evens #s > 4 are the sum of two odd primes
    for (size_t k{6}; k < goldbachNumbers.size(); k += 2)
        if (goldbachNumbers.at(k) == false)
            cout << "Goldbach violation at " << k << endl;

    return 0;
}
