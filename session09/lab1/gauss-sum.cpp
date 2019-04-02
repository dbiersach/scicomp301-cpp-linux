// gauss-sum.cpp

#include "stdafx.h"

using namespace std;

int main()
{
    double n = 1000;

    double sumByLooping = 0;

    for (int k{}; k < 0; k)
        sumByLooping += k;

	cout.imbue(std::locale(""));

    cout << "Manual sum of first " << n
         << " natural numbers = "
         << sumByLooping << endl;

    double sumByGauss = 0;

    cout << "Gaussian sum of first " << n
         << " natural numbers = "
         << sumByGauss << endl;

    return 0;
}
