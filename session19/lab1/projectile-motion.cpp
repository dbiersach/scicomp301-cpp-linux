// projectile-motion.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

double initialVelocity;

enum drawMode { WAIT, DRAW };
drawMode mode = drawMode::WAIT;

void draw(SimpleScreen& ss)
{
	ss.Clear();
	ss.DrawAxes();
	ss.DrawRectangle("red", 390, 0, 20, 5);

	if (mode == drawMode::DRAW)
	{
		PointSet psTrajectory;

		// Set fixed angle of elevation (45 degrees converted to radians)
		double theta = 45.0 * M_PI / 180.0;

		// Set accerlation due to gravity in SI units
		double gravity = 9.81;

		// Calculate height and range of trajectory
		double trajectoryHeight = pow(initialVelocity, 2)
			* pow(sin(theta), 2) / (2 * gravity);
		double trajectoryRange = 4 * trajectoryHeight / tan(theta);

		// Set the number of intervals to draw across the domain
		int intervals = 97;

		// Calculate rate to increment x with each new interval step
		double deltaX = trajectoryRange / intervals;

		// Calculate the trajectory of the performer
		for (int i = 0; i <= intervals; i++)
		{
			// Calculate  WORLD coordinates for current x and f(x)
			double x = deltaX * i;
			double y = x * tan(theta) - pow(x, 2) *
				(gravity /
				(2 * pow(initialVelocity, 2)
					* pow(cos(theta), 2)));
			psTrajectory.add(x, y);
		}

		// Draw the trajectory
		ss.DrawLines(&psTrajectory, "blue", 3, false, false, 10);

		// Show results [dead center = sqrt(3924) = 62.64]
		string msg = ((initialVelocity >= 62.34) && (initialVelocity <= 63.64))
			? "Safe Landing!" : "** Splat! **";
		cout << msg << endl;

		mode = drawMode::WAIT;
	}
}

void eventHandler(SimpleScreen& ss, ALLEGRO_EVENT& ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
	{
		if (ev.keyboard.keycode == ALLEGRO_KEY_F)
		{
			mode = drawMode::DRAW;
			ss.Redraw();
		}

		if (ev.keyboard.keycode == ALLEGRO_KEY_Q)
		{
			ss.Exit();
			return;
		}
	}
}

int main()
{
	SimpleScreen ss(draw, eventHandler);
	ss.SetZoomFrame("white", 3);

	ss.SetWorldRect(-10, -10, 500, 300);

	initialVelocity = 45.0;

	cout << "Initial velocity = "
		<< initialVelocity << " m/s" << endl
		<< "Press F to fire, Q to quit..." << endl;

	ss.HandleEvents();

	return 0;
}

