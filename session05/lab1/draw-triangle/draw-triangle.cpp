// draw-triangle.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

int main()
{
    SimpleScreen ss;
    ss.SetWorldRect(-1, -1, 5, 5);
    ss.DrawAxes();

    PointSet ps;
    ps.add(0, 0);
    ps.add(4, 0);
    ps.add(4, 3);

    ss.DrawLines(&ps, "red", 1, true, true);

    ss.HandleEvents();

    return 0;
}

