// 2DCircleAreaPRNG.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

void draw(SimpleScreen& ss)
{
	ss.DrawAxes();
	ss.DrawCircle(0, 0, 1, "green", 2);

	seed_seq seed{ 2017 };
	default_random_engine generator{ seed };
	uniform_real_distribution<double> distribution{ 0, 1 };

	const int iterations = 100000;
	int count{};

	ss.LockDisplay();

	for (int i{};i < iterations;++i) {
		double x = distribution(generator) * 2.0 - 1.0;
		double y = distribution(generator) * 2.0 - 1.0;
		if (x*x + y*y <= 1.0) {
			ss.DrawPoint(x, y, "red");
			count++;
		}
		else
			ss.DrawPoint(x, y, "blue");
	}

	ss.UnlockDisplay();

	double area = (double)count / iterations * 4.0;
	double err = (M_PI - area) / M_PI * 100;

	cout << "2D Circle Area PRNG" << endl
		<< "Iterations = " << iterations << endl
		<< "Est. Area  = " << area << endl
		<< "Act. Area  = " << M_PI << endl
		<< "Abs. % Err = " << abs(err) << endl;

}


int main()
{
	cout.imbue(locale(""));

	SimpleScreen ss(draw);
	ss.SetZoomFrame("white", 3);

	ss.SetWorldRect(-1.2, -1.2, 1.2, 1.2);

	ss.HandleEvents();

	return 0;
}

