// primalityrace.cpp

#include "stdafx.h"

using namespace std;
using namespace chrono;

seed_seq seed{ 2016 };
default_random_engine generator{ seed };
uniform_int_distribution<int> distribution(100000, 999999);

int CountPrimes(unique_ptr<vector<int>> const &samples)
{
    int numPrimes{};
    for (const auto &sample : *samples) {
        if (sample % 2 != 0) {
            bool isPrime = true;
            int n{ 2 };
            while (n < sample) {
                if (sample % n == 0) {
                    isPrime = false;
                    break;
                }
                n++;
            }
            if (isPrime)
                numPrimes++;
        }
    }
    return numPrimes;
}

int main()
{
    const auto samples{ make_unique<vector<int>>(100000) };

    for (auto &sample : *samples)
        sample = distribution(generator);

    cout.imbue(std::locale(""));
    cout << "Counting primes in vector of "
         << samples->size() << " random integers..."
         << endl;

    auto startTime = system_clock::now();

    int numPrimes = CountPrimes(samples);

    auto stopTime = system_clock::now();

    auto totalTime = duration_cast<milliseconds>(stopTime - startTime);

    cout << "Number of Primes: " << numPrimes << endl;
    cout << "Total run time (ms): " << totalTime.count() << endl;

    return 0;
}
