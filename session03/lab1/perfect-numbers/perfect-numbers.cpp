// perfect-numbers.cpp

#include "stdafx.h"

using namespace std;

int main()
{
    for (int n{ 2 }; n < 10000; ++n) {
        int sumOfFactors{ 1 };

        // Insert your code here

        if (sumOfFactors == n)
            cout << n << " is a perfect number"
                 << endl;
    }
    return 0;
}
