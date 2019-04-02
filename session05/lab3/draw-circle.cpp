// draw-circle.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

void draw(SimpleScreen& ss) {
	ss.DrawAxes();

	double radius{ 3 };

	int intervals{ 97 };

	double deltaTheta{ 2.0 * M_PI / intervals };

	PointSet psCircle;

	for (int i{}; i < intervals; ++i) {
		double theta = deltaTheta * i;
		double x = radius * cos(theta);
		double y = radius * sin(theta);
		psCircle.add(x, y);
	}

	ss.DrawLines(&psCircle, "green", 2);
}

int main()
{
	SimpleScreen ss(draw);
	ss.SetWorldRect(-5, -5, 5, 5);
	ss.HandleEvents();
	return 0;
}
