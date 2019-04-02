// sum-multiples.cpp

#include "stdafx.h"

using namespace std;


int main()
{
	int termsMax = 1900;
	int sum = 0;

    // Implement your code here

	cout.imbue(locale(""));

	cout << "The sum of all natural numbers less than "	<< termsMax << endl
		<< "that are fully divisible by both 7 and 11 is " << sum << endl << endl;

    return 0;
}

