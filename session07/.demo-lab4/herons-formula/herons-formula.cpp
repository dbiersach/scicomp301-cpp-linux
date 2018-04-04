// herons-formula.cpp

#include "stdafx.h"

using namespace std;

seed_seq seed{ 2016 };
default_random_engine generator{ seed };
uniform_int_distribution<> distribution(1, 100);

bool IsValidTriangle(int a, int b, int c)
{
    bool test1 = ((a+b)>=c);
    bool test2 = ((a+c)>=b);
    bool test3 = ((b+c)>=a);
    return (test1 && test2 && test3);
}

int main()
{
    for(int i=1; i<=10; i++)
    {
        int a = distribution(generator);
        int b = distribution(generator);
        int c = distribution(generator);

        while(IsValidTriangle(a,b,c) == false)
        {
            a = distribution(generator);
            b = distribution(generator);
            c = distribution(generator);
        }

        double s = (double)(a+b+c)/2.0;
        double area = sqrt(s*(s-a)*(s-b)*(s-c));

        cout << "Triangle # " << i << endl;
        cout << "\tSides: "
             << a << ", "
             << b << ", "
             << c << endl;
        cout << "\tArea = " << area << endl;

    }
    return 0;
}
