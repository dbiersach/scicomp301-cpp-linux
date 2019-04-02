// random-straws.cpp

#include "stdafx.h"

using namespace std;

seed_seq seed{ 2016 };
default_random_engine generator{ seed };
uniform_real_distribution<double> distribution(0.0, 1.0);


int main()
{
    double maxIterations = 10000000;
    double totalStraws = 0;

    cout.imbue(locale(""));
    cout << fixed << setprecision(0);
    cout << "Performing " << maxIterations
         << " experiments.." << endl;

    for (double iteration = 0; iteration < maxIterations; iteration++) {
        // Insert your code here

    }
    double meanStrawsPerUnitLength = totalStraws / maxIterations;

    cout << setprecision(6) << endl
         << "Mean straws per iteration: "
         << meanStrawsPerUnitLength << endl;

    cout << "Base of natural logarithm: "
         << exp(1) << endl;

    return 0;
}
