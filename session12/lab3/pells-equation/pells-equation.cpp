// pells-equation.cpp

#include "stdafx.h"

using namespace std;

void DisplayHeader();

int main()
{
    DisplayHeader();

    const uint64_t xMax = 70000;

    for (int n = 2; n <= 70; n++) {
        cout << setw(4) << n;
        bool foundSolution = false;
        uint64_t x = 1;
        while ((x <= xMax) && !foundSolution) {
            uint64_t xSqr = (uint64_t)x * x;
            uint64_t y = 1;
            uint64_t yMax = sqrt(xSqr / n);
            while ((y <= yMax) && !foundSolution) {
                uint64_t ySqr = (uint64_t)y * y;
                uint64_t lhs = xSqr - (uint64_t)n * ySqr;
                if (lhs == 1) {
                    cout << setw(8) << x
                         << setw(8) << y;
                    foundSolution = true;
                }
                y++;
            }
            x++;
        }
        if (!foundSolution)
            cout << setw(8) << "-"
                 << setw(8) << "-";
        cout << endl;
    }
    return 0;
}

void DisplayHeader()
{
    cout << setw(4) << "n"
         << setw(8) << "x"
         << setw(8) << "y"
         << endl;

    cout << setw(4) << "==="
         << setw(8) << "======"
         << setw(8) << "======"
         << endl;
}
