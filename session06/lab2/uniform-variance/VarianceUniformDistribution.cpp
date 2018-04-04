// VarianceUniformDistribution.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	seed_seq seed{ 2016 };
	default_random_engine generator{ seed };
	uniform_int_distribution<> distSetSize(1000000, 2000000);
	uniform_int_distribution<> distLimits(0, 1000);

	cout.imbue(std::locale(""));

	cout << right
		<< setw(5) << "Set #"
		<< setw(7) << "Lower"
		<< setw(7) << "Upper"
		<< setw(12) << "Set Size"
		<< setw(12) << "Mean"
		<< setw(13) << "Variance"
		<< setw(8) << "Magic"
		<< endl;

	for (int setNumber{ 1 }; setNumber <= 15; ++setNumber) {
		int setSize = distSetSize(generator);

		int lowerLimit = distLimits(generator);
		int upperLimit = 2 * lowerLimit + distLimits(generator);

		uniform_int_distribution<> distRange(lowerLimit, upperLimit);

		double sum{};
		for (int n{}; n < setSize;++n)
			sum += distRange(generator);
		double mean = sum / setSize;

		distRange.reset();

		sum = 0;
		for (int n{}; n < setSize;++n)
			sum += pow(distRange(generator) - mean, 2);
		double variance = sum / setSize;

		double magicNumber = 0;

		cout << right << fixed
			<< setw(5) << setNumber
			<< setw(7) << lowerLimit
			<< setw(7) << upperLimit
			<< setw(12) << setSize
			<< setw(12) << setprecision(3) << mean
			<< setw(13) << setprecision(3) << variance
			<< setw(8) << setprecision(0) << magicNumber
			<< endl;
	}

	return 0;
}

