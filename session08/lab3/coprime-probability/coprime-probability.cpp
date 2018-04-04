// coprime-probability.cpp

#include "stdafx.h"

using namespace std;

int GCD(int a, int b)
{
    return b == 0 ? a : GCD(b, a % b);
}

int main()
{
    seed_seq seed{ 2016 };
    default_random_engine generator{ seed };
    uniform_int_distribution<int> distribution(1, 100000);

    double maxIterations{ 1000000 };
    double coprimePairs{};

    for (double i{}; i < maxIterations; ++i) {
        int a = distribution(generator);
        int b = distribution(generator);
        if (GCD(a, b) == 1)
            coprimePairs++;
    }

    double coprimeProbability = coprimePairs / maxIterations;

    cout << "Probability two random integers are coprime = "
         << setprecision(14) << coprimeProbability << endl;

    cout << endl << "Hidden constant = "
         << sqrt(6 / coprimeProbability) << endl;

    return 0;
}
