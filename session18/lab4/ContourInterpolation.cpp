// ContourInterpolation.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

double p = 2.0;

const int oceanSize = 390;
const int intervals = 30;
const double delta = oceanSize / intervals;

const int numSamples = 220;
Point3D samples[numSamples];

const int gridHeight = -80;

PointSet3D vSamples, vGrid;
PointSet3D vOceanAct, vOceanEst;

FacetSet fSamples, fGrid;
FacetSet fOceanAct, fOceanActFlip;
FacetSet fOceanEst, fOceanEstFlip;

enum DrawMode { SAMPLES, ACTUAL, ESTIMATED };
DrawMode mode = SAMPLES;

double GetActHeight(double x, double z)
{
	return ((30 * sin(0.025 * x) * cos(0.025 * z)) +
		(50 * cos(0.025 * sqrt(x * x + z * z))));
}

double GetEstHeight(double x, double z)
{
	double sumWeight = 0;
	double sumHeightWeight = 0;

	for (size_t n{}; n < numSamples; ++n) {
		double distance = sqrt(pow(x - samples[n].x, 2)
			+ pow(z - samples[n].z, 2));

		if (distance == 0) return samples[n].y;

		double weight = 1 / pow(distance, p);

		sumWeight += weight;
		sumHeightWeight += samples[n].y * weight;
	}

	double height = sumHeightWeight / sumWeight;

	return height;
}

void CalcEstimatedSurface()
{
	vOceanEst.clear();
	fOceanEst.clear();
	fOceanEstFlip.clear();
	for (int iz{ intervals - 1 };iz >= 0;--iz) {
		for (int ix{}; ix < intervals;++ix) {
			double x = ix * delta;
			double z = -iz * delta;
			// Create Estimated Ocean facet at this interval
			size_t v0 = vOceanEst.add(x, GetEstHeight(x, z - delta), z - delta);
			size_t v1 = vOceanEst.add(x, GetEstHeight(x, z), z);
			size_t v2 = vOceanEst.add(x + delta, GetEstHeight(x + delta, z), z);
			size_t v3 = vOceanEst.add(x + delta, GetEstHeight(x + delta, z - delta), z - delta);
			fOceanEst.add(&vOceanEst, { v0,v1,v2,v3 });
			fOceanEstFlip.add(&vOceanEst, { v0,v3,v2,v1 });
		}
	}
}

double CalcRMSD()
{
	double rmsd = 0;
	double sumErrors = 0;
	for (int iz{ intervals - 1 };iz >= 0;--iz) {
		for (int ix{}; ix < intervals;++ix) {
			double x = ix * delta;
			double z = -iz * delta;
			double act = GetActHeight(x, z);
			double est = GetEstHeight(x, z);
			sumErrors += 0;
		}
	}
	rmsd = 0;
	return rmsd;
}


void InitSamples()
{
	seed_seq seed{ 2017 };
	default_random_engine prng{ seed };
	uniform_int_distribution<int> dist{ 0, oceanSize };

	// Generate random sample points
	for (size_t i{};i < numSamples;++i) {
		samples[i].x = dist(prng);
		samples[i].z = -dist(prng);
		samples[i].y = GetActHeight(samples[i].x, samples[i].z);
	}

	// Create a small marker at each sample point (a horizontal facet)
	for (size_t i{};i < numSamples;++i)
	{
		size_t v0 = vSamples.add(samples[i].x, samples[i].y, samples[i].z + 2);
		size_t v1 = vSamples.add(samples[i].x + 2, samples[i].y, samples[i].z);
		size_t v2 = vSamples.add(samples[i].x, samples[i].y, samples[i].z - 2);
		size_t v3 = vSamples.add(samples[i].x - 2, samples[i].y, samples[i].z);
		fSamples.add(&vSamples, { v0,v1,v2,v3 });
	}
}

void InitStaticSurfaces()
{
	// Create surface facets starting from the back of the world
	for (int iz{ intervals - 1 };iz >= 0;--iz) {
		for (int ix{}; ix < intervals;++ix) {
			double x = ix * delta;
			double z = -iz * delta;

			// Create Reference Grid facet at this interval
			size_t v0 = vGrid.add(x, gridHeight, z - delta);
			size_t v1 = vGrid.add(x, gridHeight, z);
			size_t v2 = vGrid.add(x + delta, gridHeight, z);
			size_t v3 = vGrid.add(x + delta, gridHeight, z - delta);
			fGrid.add(&vGrid, { v0,v1,v2,v3 });

			// Create Actual Ocean facet at this interval
			v0 = vOceanAct.add(x, GetActHeight(x, z - delta), z - delta);
			v1 = vOceanAct.add(x, GetActHeight(x, z), z);
			v2 = vOceanAct.add(x + delta, GetActHeight(x + delta, z), z);
			v3 = vOceanAct.add(x + delta, GetActHeight(x + delta, z - delta), z - delta);
			fOceanAct.add(&vOceanAct, { v0,v1,v2,v3 });
			fOceanActFlip.add(&vOceanAct, { v0,v3,v2,v1 });
		}
	}
}


void draw(SimpleScreen& ss)
{
	ALLEGRO_COLOR clrGrid = al_color_name("black");
	ALLEGRO_COLOR clrSample = al_color_name("red");
	ALLEGRO_COLOR clrOceanAct = al_color_name("blue");
	ALLEGRO_COLOR clrOceanEst = al_color_name("green");

	ss.Clear();
	if (mode == SAMPLES)
		ss.SetWindowTitle("Contour Interpolation - Sample Data");

	// Draw reference grid
	for (size_t f{}; f < fGrid.size();++f) {
		ss.DrawLines(fGrid.at(f), ss.screenColor, 1, true);
		ss.DrawLines(fGrid.at(f), clrGrid);
	}

	// Draw actual surface
	if (mode == ACTUAL) {
		ss.SetWindowTitle("Contour Interpolation - Actual Surface");
		for (size_t f{}; f < fOceanAct.size();++f) {
			ss.DrawLines(fOceanAct.at(f), ss.screenColor, 1, true);
			ss.DrawLines(fOceanActFlip.at(f), ss.screenColor, 1, true);
			ss.DrawLines(fOceanAct.at(f), clrOceanAct);
		}
	}

	// Draw estimated surface
	if (mode == ESTIMATED) {
		ss.SetWindowTitle("Contour Interpolation - Estimated Surface");
		for (size_t f{}; f < fOceanAct.size();++f) {
			ss.DrawLines(fOceanEst.at(f), ss.screenColor, 1, true);
			ss.DrawLines(fOceanEstFlip.at(f), ss.screenColor, 1, true);
			ss.DrawLines(fOceanEst.at(f), clrOceanEst);
		}
	}

	// Draw all sample markers (facets)
	ss.DrawLines(&fSamples, clrSample, 0, true);
}

void eventHandler(SimpleScreen& ss, ALLEGRO_EVENT& ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
		if (ev.keyboard.keycode == ALLEGRO_KEY_A)
			mode = ACTUAL;
		if (ev.keyboard.keycode == ALLEGRO_KEY_E)
			mode = ESTIMATED;
		if (ev.keyboard.keycode == ALLEGRO_KEY_S)
			mode = SAMPLES;
		if (ev.keyboard.keycode == ALLEGRO_KEY_MINUS) {
			p -= 0.1;
			mode = ESTIMATED;
		}
		if (ev.keyboard.keycode == ALLEGRO_KEY_EQUALS) {
			p += 0.1;
			mode = ESTIMATED;
		}
		if (mode == ESTIMATED) {
			CalcEstimatedSurface();
			cout << "p = " << fixed << setprecision(2) << p << ", RMSD = "
				<< right << setw(7) << setprecision(4) << CalcRMSD() << endl;
		}
		ss.Redraw();
	}
}

int main()
{
	InitSamples();
	InitStaticSurfaces();

	SimpleScreen ss(draw, eventHandler);

	ss.SetWorldRect(-10, -100, 501, 411);
	ss.SetProjection(29, 0.225);

	cout << "Press S to see only sample data" << endl
		<< "Press A to see actual ocean floor" << endl
		<< "Press E to see estimated ocean floor" << endl
		<< "Press - to reduce p by 0.1" << endl
		<< "Press + to increase p by 0.1" << endl;

	ss.HandleEvents();

	return 0;
}

