// pachinko-normal.cpp

#include "stdafx.h"

using namespace std;

const int balls{ 1000 };
const int levels{ 10 };

seed_seq seed{ 2016 };
default_random_engine generator(seed);
uniform_int_distribution<int> distribution(0, 1);
double mean{};
double stddev{};

const int sigmas{ 4 };
vector<int> sigCountPachinko(sigmas);
vector<int> sigCountNormal(sigmas);

double chiSquared{};


int DropBall()
{
	int slot{};
	for (int level{}; level < levels; level++) {
		int step = distribution(generator);
		if (step == 0)
			slot--;
		else
			slot++;
	}
	slot = slot / 2;
	return slot;
}

void ResetPachinkoDistribution()
{
	generator.seed(seed);
	distribution.reset();
}

void CalcMeanPachinko()
{
	for (int ball{}; ball < balls; ball++)
		mean += DropBall();
	mean /= balls;
}

void CalcStdDevPachinko()
{
	double variance{};
	for (int ball{}; ball < balls; ball++)
		variance += pow(DropBall() - mean, 2);
	stddev = sqrt(variance / balls);
}

void CountBallsPerSigma()
{
	sigCountNormal[0] = 0.6826 * balls;
	sigCountNormal[1] = 0.2718 * balls;
	sigCountNormal[2] = 0.0430 * balls;
	sigCountNormal[3] = 0.0026 * balls;

	for (int ball{}; ball < balls; ball++) {
		int slot = DropBall();
		int sigma = abs(mean + slot) / stddev;
		if (sigma < sigCountPachinko.size())
			sigCountPachinko.at(sigma)++;
	}

	for (int s{}; s < sigmas; s++)
		chiSquared += (pow(
			sigCountNormal[s] -
			sigCountPachinko[s], 2)
			/ sigCountNormal.at(s));
}



void DisplayBallsPerSigma()
{
	cout.imbue(locale(""));

	cout << " Balls: " << balls << endl
		<< "Levels: " << levels << endl
		<< endl;

	cout << setw(8) << "Sigma"
		<< setw(10) << "Pachinko"
		<< setw(10) << "Normal"
		<< endl;


	for (size_t s{}; s < sigmas; s++) {
		cout << setw(8) << s + 1
			<< setw(10) << sigCountPachinko.at(s)
			<< setw(10) << sigCountNormal.at(s)
			<< endl;
	}

	cout << endl << fixed << setprecision(3)
		<< "Chi-Squared: " << chiSquared
		<< endl << endl;
}

int main()
{
	CalcMeanPachinko();

	ResetPachinkoDistribution();

	CalcStdDevPachinko();

	ResetPachinkoDistribution();

	CountBallsPerSigma();

	DisplayBallsPerSigma();

	return 0;
}
