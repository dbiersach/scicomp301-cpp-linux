// mandelbrot-set.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

const int maxIterations = 500;
vector<ALLEGRO_COLOR> pallete(maxIterations + 1);

void InitPallete()
{
	seed_seq seed{ 22 };
	default_random_engine generator{ seed };
	uniform_int_distribution<> distribution(0, 255);

	for(auto& clr : pallete)
	{
		unsigned char red = distribution(generator);
		unsigned char green = distribution(generator);
		unsigned char blue = distribution(generator);
		clr = al_map_rgb(red, green, blue);
	}

	pallete.back() = al_color_name("black");
}

void draw(SimpleScreen& ss)
{
	double dx = (ss.worldXmax - ss.worldXmin) / ss.screenWidth;
	double dy = (ss.worldYmax - ss.worldYmin) / ss.screenHeight;

	ss.LockDisplay();

	for (double y = ss.worldYmin; y < ss.worldYmax; y += dy)
	{
		for (double x = ss.worldXmin; x < ss.worldXmax; x += dx)
		{
			double real = x;
			double realSquared = pow(real, 2);

			double imaginary = y;
			double imaginarySquared = pow(imaginary, 2);

			int iterations = 0;

			while ((iterations < maxIterations) &&
				(sqrt(realSquared + imaginarySquared) < 2.0))
			{
				double realNew = realSquared - imaginarySquared + x;
				double imaginaryNew = 2.0 * real * imaginary + y;

				real = realNew;
				realSquared = pow(real, 2);

				imaginary = imaginaryNew;
				imaginarySquared = pow(imaginary, 2);

				iterations++;
			}

			ss.DrawPoint(x, y, pallete.at(iterations));
		}
	}

	ss.UnlockDisplay();
}

int main()
{
	SimpleScreen ss(draw);
	ss.SetWorldRect(-2.2, -2.2, 1.0, 1.2);

	InitPallete();

	ss.HandleEvents();
	return 0;
}
