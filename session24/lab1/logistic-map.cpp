// logistic-map.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

const int iterations = 500;

seed_seq seed{ 2016 };
default_random_engine generator{ seed };
uniform_real_distribution<double> distribution(0, 1);

void draw(SimpleScreen& ss)
{
    double dx = (ss.worldXmax - ss.worldXmin) / ss.screenWidth;

    ss.LockDisplay();

    for (double x = ss.worldXmin; x < ss.worldXmax; x += dx) {
        double y = distribution(generator);

        // Initial iteration to reach strange attractor
        for (int i = 0; i < iterations; i++)
            y = x * y * (1 - y);

        // Iterate again but now plot the strange attractor
        for (int i = 0; i < iterations; i++) {
            y = x * y * (1 - y);
            ss.DrawPoint(x, y, "blue");
        }
    }

    ss.UnlockDisplay();
}

int main()
{
    SimpleScreen ss(draw);
    ss.SetWorldRect(2.5, 0, 4.0, 1);
    ss.HandleEvents();
    return 0;
}
