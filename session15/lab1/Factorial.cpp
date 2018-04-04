// Factorial.cpp

#include "stdafx.h"

using namespace std;

int IterativeFactorial(int n)
{
    int x = n;
    while (n > 1) {
        n = n-1;
        x = x * n;
    }
    return x;
}

int RecursiveFactorial(int n)
{
    if (n==0)
        return 1;
    else
        return n * RecursiveFactorial(n-1);
}

int main()
{
    int x = 5;

    cout << "Iterative Factorial of "
         << x << "! = "
         << IterativeFactorial(x) << endl;

    cout << "Recursive Factorial of "
         << x << "! = "
         << RecursiveFactorial(x) << endl;

    return 0;
}
