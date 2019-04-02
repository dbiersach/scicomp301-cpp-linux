#include "stdafx.h"

using namespace std;

int main()
{
	int terms = 1000;

	int sum = 0;

	for (int n = 1; n <= terms; n = n + 1)
	{
		sum = sum + (int)pow(n, 2);
	}

	cout.imbue(locale(""));

	cout << "Sum of first " << terms
		<< " integers squared = " << sum
		<< endl;

    return 0;
}
