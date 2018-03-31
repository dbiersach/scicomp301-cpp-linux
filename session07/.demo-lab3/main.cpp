#include "stdafx.h"

using namespace std;

int GCD(int a, int b)
{
	return b == 0 ? a : GCD(b, a % b);
}

int main()
{
	for (int n = 2; n <= 100; n = n + 1)
	{
		int totient = 0;

		for (int i = 1; i < n; i = i + 1)
		{
			if (GCD(n, i) == 1)
			{
				totient = totient + 1;
			}
		}

		if (n == totient + 1)
		{
			cout << n << endl;
		}
	}

    return 0;
}
