// riemann-hypothesis.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

const int max_terms = 1e5;

PointSet psEta;
PointSet psZeta;

complex<double> Eta(complex<double> s)
{
    complex<double> eta = 1;
    for (int n{ 2 }; n <= max_terms; n++)
    {
        complex<double> term = 1. / pow(n, s);
        eta += (n % 2) == 0 ? -term : term;
    }
    return eta;
}

complex<double> Zeta(complex<double> s)
{
    return Eta(s) / (1. - pow(2, 1. - s));
}

void draw(SimpleScreen& ss)
{
    ss.DrawLines(&psEta, "blue", 2, false);
    ss.DrawLines(&psZeta, "red", 2, false);
    ss.DrawAxes();
}

int main()
{
    double x_min = -1.0, x_max = 27.0;
    double y_min = -0.5, y_max = 4.0;

    SimpleScreen ss(draw);
    ss.SetWorldRect(x_min, y_min, x_max, y_max);

    double dx = ss.worldWidth / ss.screenWidth;

    for(double x{0}; x < x_max; x += dx)
    {
        complex<double> s(0.5, x);
        psEta.add(x,abs(Eta(s)));
        psZeta.add(x,abs(Zeta(s)));
    }

    ss.HandleEvents();

    return 0;
}
