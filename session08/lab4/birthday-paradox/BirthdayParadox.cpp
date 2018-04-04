// BirthdayParadox.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	seed_seq seed{ 2016 };
	default_random_engine generator{ seed };
	uniform_int_distribution<int> distribution(0, 364);

	for (int students = 2; students <= 80; students++)
	{
		int totalIterations = 10000;
		int matchCount = 0;

		vector<int>* birthdays = new vector<int>(students, 0);

		for (int iteration = 0; iteration < totalIterations; iteration++) {
			// Initialize the birthdays array with a random day between 0 and 364
			for (int i = 0; i < birthdays->size(); i++)
				birthdays->at(i) = distribution(generator);

			// Compare birthdays of each person to the remaining people
			// Note:  Only loop until the first match is found
			bool foundMatch = false;
			// TODO:  Insert your code here

			if (foundMatch)
				matchCount++;
		}

		delete birthdays;

		cout << "Probability of matching birthdays among "
			<< setw(2) << students << " people = "
			<< fixed << setprecision(4) << (double)matchCount / totalIterations
			<< endl;
	}

	return 0;
}

