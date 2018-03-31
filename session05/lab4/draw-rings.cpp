// draw-rings.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

void draw(SimpleScreen& ss)
{
    double radius{ 5 };
    int width{ 15 };

    // You must determine proper offsets
    double ringOffsetFullX{};
    double ringOffsetHalfX{};
    double ringOffsetY{};

    ss.DrawCircle(0, 0, radius, "black", width);
    ss.DrawCircle(-ringOffsetFullX, 0, radius, "blue", width);
    ss.DrawCircle(ringOffsetFullX, 0, radius, "red", width);
    ss.DrawCircle(-ringOffsetHalfX, -ringOffsetY, radius, "yellow", width);
    ss.DrawCircle(ringOffsetHalfX, -ringOffsetY, radius, "green", width);
}

int main()
{
    SimpleScreen ss(draw);
    ss.SetWorldRect(-20, -20, 20, 20);
    ss.HandleEvents();
    return 0;
}
