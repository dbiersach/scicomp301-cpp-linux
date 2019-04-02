// lcm-gcd.cpp

#include "stdafx.h"

using namespace std;

int GCD(uint64_t a, uint64_t b)
{
    return b == 0 ? a : GCD(b, a % b);
}

int LCM(uint64_t a, uint64_t b)
{
    // Implement your code here
}

int main()
{
    uint64_t a = 447618;
    uint64_t b = 2011835;

    cout.imbue(locale(""));
    cout << "LCM of " << a
         << " and " << b << " is "
         << LCM(a, b) << endl;

    return 0;
}

