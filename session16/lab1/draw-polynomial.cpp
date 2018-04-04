// draw-polynomial.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

void draw(SimpleScreen& ss)
{
	ss.DrawAxes();

	double x= ss.worldXmin ;
	const double dx = ss.worldWidth / 97;

	PointSet ps;
	while (x <= ss.worldXmax) {
		double y = (x + 9) * (x + 4)
			* (x + 1) * (x - 5) * (x - 11);
		ps.add(x, y);
		x += dx;
	}

	ss.DrawLines(&ps, "green", 2, false);
}

int main()
{
	SimpleScreen ss(draw);
	ss.SetWorldRect(-10, -20000, 12, 31000);
	ss.HandleEvents();
	return 0;
}
