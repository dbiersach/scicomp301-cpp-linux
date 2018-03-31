// basel-series.cpp

#include "stdafx.h"

using namespace std;

int main()
{
    double sum;

    cout.imbue(std::locale(""));

    for (int limit{ 1000 }; limit <= 10000; limit += 1000) {
        sum = 0;
        for (int n{ 1 }; n < limit; ++n)
            sum += 1.0 / n;

        cout << "Sum of reciprocals of positive integers <= ";
        cout << setw(6) << limit << " = ";
        cout << setprecision(14) << sum << endl;
    }

    cout << endl << "Magic Number = "
         << sqrt(sum * 6) << endl;

    return 0;
}
