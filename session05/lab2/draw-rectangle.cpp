// draw-rectangle.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

int main()
{
	SimpleScreen ss;
	ss.SetWorldRect(-30, -30, 30, 30);
	ss.DrawAxes();

	PointSet ps;
	ps.add(0, 0);
	ps.add(5, 0);
	ps.add(5, 5);
	ps.add(0, 5);

	ss.DrawLines(&ps, "violet", 1, true, true);

	ss.HandleEvents();

	return 0;
}
