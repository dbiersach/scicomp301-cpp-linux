// simpsons-rule.cpp

#include "stdafx.h"
using namespace std;

const double a{-10};
const double b{12};
const int intervals = 1e6;

inline double f(double x)
{
    return (x+9)*(x+4)*(x+1)*(x-5)*(x-11);
}

double lefthand(double a, double b)
{
    const double dx{(b-a)/intervals};
    double sum{};
    while(a<=b)
    {
        sum+=f(a);
        a+=dx;
    }
    return sum*dx;
}

double simpsons(double a, double b)
{
    const double dx{(b-a)/intervals};
    double sum{f(a)+f(b)};
    a+=dx;
    for(int i{1}; i<intervals; ++i,a+=dx)
        sum+=f(a)*(2*(i%2+1));
    return (dx/3)*sum;
}

int main()
{
    cout.imbue(locale(""));

    cout << "Integrating "
         << "x^5 - 2x^4 - 120x^3 + 22x^2 + 2199x +1980"
         << endl << " over [" << a << ", " << b << "]"
         << " using " << intervals << " intervals:"
         << endl << endl;

    double i1{-306482./15};
    cout << "Analytic (Exact): "
         << fixed << setprecision(14)
         << i1 << endl << endl;

    double i2{lefthand(a,b)};
    cout << "Left-hand Rule  : "
         << fixed << setprecision(14)
         << i2 << endl
         << scientific << setprecision(4)
         << "% Error = " << (i2-i1)/i1
         << endl << endl;

    double i3{simpsons(a,b)};
    cout << "Simpson's Rule  : "
         << fixed << setprecision(14)
         << i3 << endl
         << scientific << setprecision(4)
         << "% Error = " << (i3-i1)/i1
         << endl << endl;

    return 0;
}
