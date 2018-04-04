#include "stdafx.h"

using namespace std;

vector<int> samples;

void InitSamples()
{
	seed_seq seed{ 2016 };
	default_random_engine generator{ seed };
	uniform_int_distribution<> distribution(1, 100);

	for (int i = 0; i < 100; i++)
	{
		int rnd = distribution(generator);
		samples.push_back(rnd);
	}
}

void DisplaySamples()
{
	for (auto sample : samples)
	{
		cout << sample << " ";
	}
	cout << endl << endl;
}

void BubbleSortSamples()
{
	bool allSorted = false;
	while (allSorted == false)
	{
		bool swapNeeded = false;
		for (size_t i{}; i < samples.size() - 1; ++i)
		{
			if (samples.at(i) > samples.at(i + 1))
			{
				swap(samples.at(i), samples.at(i + 1));
				swapNeeded = true;
			}
		}
		if (swapNeeded == false)
		{
			allSorted = true;
		}
	}
}


int main()
{
	InitSamples();

	DisplaySamples();

	BubbleSortSamples();

	DisplaySamples();

    return 0;
}
