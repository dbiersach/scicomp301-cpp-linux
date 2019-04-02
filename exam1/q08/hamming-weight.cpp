// hamming-weight.cpp

#include "stdafx.h"
#include <bitset>

using namespace std;


int PopCount(int n)
{
    int onebits = 0;
    // Insert your code here
    return onebits;
}

int main()
{
    int n = 95601;

    cout << "The Hamming weight of " << n
         << " in base 2 is " << PopCount(n)
         << endl << endl;

    bitset<17> b(n);

    cout << n << " in base 10 is "
         << b.to_string() << " in base 2" << endl;
    cout << "Therefore the popcount is " << b.count()
         << endl << endl;

    return 0;
}

