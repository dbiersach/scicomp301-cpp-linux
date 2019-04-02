// draw-curves.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

void CalcPolarCurve(PointSet& ps,
	double loops, double radius)
{
	int intervals{ 997 };

	double deltaTheta{ 2.0 * M_PI / intervals };

	for (int i{}; i <= intervals; i++){
		double theta{ i * deltaTheta };
		double r{ radius * sin(loops * theta) };
		double x{ r * cos(theta) };
		double y{ r * sin(theta) };
		ps.add(x, y);
	}
}

void draw(SimpleScreen& ss) {
	PointSet ps1, ps2;
	CalcPolarCurve(ps1, 8, 15);
	CalcPolarCurve(ps2, 4, 10);

	ss.DrawLines(&ps1, "green", 3, false, false, 1);
	ss.DrawLines(&ps2, "red", 3, false, false, 1);
}

int main()
{
	SimpleScreen ss(draw);
	ss.SetWorldRect(-20, -20, 20, 20);
	ss.HandleEvents();
	return 0;
}
