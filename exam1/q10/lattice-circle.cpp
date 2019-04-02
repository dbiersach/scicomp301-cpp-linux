// lattice-circle.cpp

#include "stdafx.h"

using namespace std;

int LatticePoints(const int radius)
{
    int numPoints = 0;

    // Implement your code here

    return numPoints;

}

int main()
{
    cout.imbue(locale(""));

    for (int radius{ 1000 }; radius <= 10000; radius += 1000)
    {
        cout << "Radius = " << fixed << setw(6) << radius
             << "  Act Points = "
             << setw(12) << LatticePoints(radius)
             << "  Est Points = " << setprecision(0)
             << setw(12) << round(M_PI * radius * radius + 2 * sqrt(2 * M_PI * radius))
             << endl;
    }

    return 0;
}

