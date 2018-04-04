// hero-abilities.cpp

#include "stdafx.h"

using namespace std;

seed_seq seed{ 2016 };
default_random_engine generator{ seed };
uniform_int_distribution<> distribution1d20(3, 18);
uniform_int_distribution<> distribution1d6(1, 6);

double CalcMean1d20(double totalRolls)
{
    double sum{};
    for (double rollNumber{}; rollNumber <= totalRolls; ++rollNumber) {
        int roll = distribution1d20(generator);
        sum = sum + roll;
    }
    double mean = sum / totalRolls;
    return mean;
}

double CalcStdDev1d20(double totalRolls, double mean)
{
    double sum{};
    for (double rollNumber{}; rollNumber <= totalRolls; ++rollNumber) {
        // Insert the correct code here

    }
    double variance = sum / totalRolls;
    double stdDev = sqrt(variance);
    return stdDev;
}

double CalcMean3d6(double totalRolls)
{
    double sum{};
    for (double rollNumber{}; rollNumber <= totalRolls; ++rollNumber) {
        int roll = distribution1d6(generator)
                   + distribution1d6(generator)
                   + distribution1d6(generator);
        sum = sum + roll;
    }
    double mean = sum / totalRolls;
    return mean;
}

double CalcStdDev3d6(double totalRolls, double mean)
{
    double sum{};
    for (double rollNumber{}; rollNumber <= totalRolls; ++rollNumber) {
        int roll = distribution1d6(generator)
                   + distribution1d6(generator)
                   + distribution1d6(generator);
        sum = sum + pow(roll - mean, 2);
    }
    double variance = sum / totalRolls;
    double stdDev = sqrt(variance);
    return stdDev;
}

int main()
{
    double totalRolls = 1000000;

    cout.imbue(std::locale(""));

    cout << "Total number of dice rolls: "
         << setprecision(0) << fixed << totalRolls
         << endl << endl;

    double mean1d20 = CalcMean1d20(totalRolls);
    double mean3d6 = CalcMean3d6(totalRolls);

    distribution1d20.reset();
    distribution1d6.reset();

    double stdDev1d20 = CalcStdDev1d20(totalRolls, mean1d20);
    double stdDev3d6 = CalcStdDev3d6(totalRolls, mean3d6);

    cout << "Mean ability (1d20): "
         << fixed << setprecision(2) << mean1d20
         << endl;

    cout << "Mean ability (3d6) : "
         << fixed << setprecision(2) << mean3d6
         << endl << endl;

    cout << "Standard deviation ability (1d20): "
         << fixed << setprecision(2) << stdDev1d20
         << endl;

    cout << "Standard deviation ability (3d6) : "
         << fixed << setprecision(2) << stdDev3d6
         << endl << endl;

    return 0;
}
