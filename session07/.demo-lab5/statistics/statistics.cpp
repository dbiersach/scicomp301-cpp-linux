// statistics.cpp

#include "stdafx.h"

using namespace std;

int main()
{
    seed_seq seed{ 2016 };
    default_random_engine generator{ seed };
    uniform_int_distribution<> distribution(0, 100);

    vector<int> samples(10);

    cout << "Samples: ";
    for(auto& sample : samples)
    {
        sample = distribution(generator);
        cout << sample << " ";
    }
    cout << endl;

    double sum = 0;
    for(auto sample: samples)
        sum += sample;
    double mean = sum / samples.size();
    cout << "Mean = " << mean << endl;

    sort(samples.begin(), samples.end());

    int middle = samples.size() / 2;
    double median = samples.at(middle);
    if (samples.size() % 2 == 0)
        median = (median + samples.at(middle - 1)) / 2;
    cout << "Median = " << median << endl;

    vector<int> occurances(101, 0);
    for (auto s : samples)
        occurances.at(s)++;

    int maxOccurance =
        *max_element(
            occurances.begin(), occurances.end());

    cout << "Mode(s) = ";
    for (size_t i{}; i < occurances.size(); i++)
        if (occurances.at(i) == maxOccurance)
            cout << i << " ";
    cout << endl;

    double sumSqr = 0;
    for(auto sample: samples)
        sumSqr += pow(sample - mean,2);
    double variance = sumSqr / samples.size();
    cout << "Population Variance = " << variance << endl;

    double stdDev = sqrt(variance);
    cout << "Population Std Dev = " << stdDev << endl;

    return 0;
}

