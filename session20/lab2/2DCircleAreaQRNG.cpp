// 2DCircleAreaQRNG.cpp

#include "stdafx.h"
#include "SimpleScreen.h"
#include "Niederreiter2.h"

using namespace std;

void draw(SimpleScreen& ss)
{
	ss.DrawAxes();
	ss.DrawCircle(0, 0, 1, "green", 2);

	Niederreiter2 qrng;
	double r[2];
	int seed{};

	const int iterations = 10000;
	int count{};

	ss.LockDisplay();

	for (int i{};i < iterations;++i) {
		qrng.Next(2, &seed, r);

		double x = r[0] * -2.0 - 1.0;
		double y = r[1] * -2.0 - 1.0;
		if (x*x + y*y <= 1.0) {
			ss.DrawPoint(x, y, "red");
			count++;
		}
		else
			ss.DrawPoint(x, y, "blue");
	}

	ss.UnlockDisplay();

	double estArea = (double)count / iterations * 4;
	double actArea = M_PI;
	double err = (actArea - estArea) / actArea * 100;

	cout << "2D Circle Area QRNG" << endl
		<< "Iterations = " << iterations << endl
		<< "Est. Area  = " << estArea << endl
		<< "Act. Area  = " << actArea << endl
		<< "Abs. % Err = " << abs(err) << endl << endl;

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

