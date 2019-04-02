// stdcf-biersach.cpp

#include "stdafx.h"

using namespace std;

string EncodeCF(double x)
{
    const int maxTerms = 7;
    string cf{to_string(int(x)) + "," };
    x = x - int(x);
    for (int terms = 1; terms < maxTerms; terms++)
    {
        cf += to_string((int)(1 / x));
        if (terms < maxTerms - 1) cf += ",";
        x = 1 / x - (int)(1 / x);
    }
    return move(cf);
}

int main()
{
    for (int n{ 1 }; n < 10; n++)
    {
        double x = (1+sqrt(5))/2;
        cout << EncodeCF(x) << endl;
    }

    return 0;
}
