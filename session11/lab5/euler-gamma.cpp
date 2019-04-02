// euler-gamma.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

PointSet psFactorial;
PointSet psGamma;

inline double f(double x, double n)
{
    // Euler's Gamma Function
    return 0 * pow(x,n-1) * exp(-x);
}

double simpsons(double n)
{
    double a{0};
    double b{1e3};
    int intervals = 1e5;

    double dx{(b-a)/intervals};
    double sum{f(a,n)+f(b,n)};
    a+=dx;
    for(int i{1}; i<intervals; ++i,a+=dx)
        sum+=f(a,n)*(2*(i%2+1));
    return (dx/3)*sum;
}

int factorial(int n)
{
    return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

void draw(SimpleScreen& ss)
{
    ss.DrawLines(&psFactorial, "green", 2, false);
    ss.DrawLines(&psGamma, "red", 2, false);
}

int main()
{
    const int max_n = 4;

    for(int n{}; n<=max_n; n++)
        psFactorial.add(n,factorial(n));

    for(double n = 0; n <= max_n + 0.1; n += 0.1)
        psGamma.add(n,simpsons(n + 1));

    SimpleScreen ss(draw);
    ss.SetWorldRect(0, -1, max_n, factorial(max_n));
    ss.DrawAxes();
    ss.HandleEvents();

    return 0;
}
