// 3DSphereVolumeQRNG.cpp

#include "stdafx.h"
#include "SimpleScreen.h"
#include "Niederreiter2.h"

using namespace std;

void draw(SimpleScreen& ss) {
	// Set the radius of the sphere
	double radius = 1.0;

	// Calculate the angle deltas
	double intervals = 37;
	double deltaPhi = M_PI / intervals;         // Latitudes
	double deltaTheta = 2 * M_PI / intervals;   // Longitudes

	// Step phi around a half-circle to set each vertex "Y" coordinate
	for (double phi = 0; phi < M_PI; phi += deltaPhi)
	{
		PointSet3D* vertices = new PointSet3D();
		vertices->add(0, radius * cos(phi), 0);
		vertices->add(0, radius * cos(phi), 0);
		vertices->add(0, radius * cos(phi + deltaPhi), 0);
		vertices->add(0, radius * cos(phi + deltaPhi), 0);

		// Calculate radius of each line of latitude
		double rA = radius * sin(phi);
		double rB = radius * sin(phi + deltaPhi);

		// Step theta around a full circle to set each vertex "X" and "Z" coordinate
		for (double theta = 0; theta < M_PI * 2; theta += deltaTheta)
		{
			vertices->at(0)->x = rA * sin(theta);
			vertices->at(0)->z = -rA * cos(theta);

			vertices->at(1)->x = rA * sin(theta + deltaTheta);
			vertices->at(1)->z = -rA * cos(theta + deltaTheta);

			vertices->at(2)->x = rB * sin(theta + deltaTheta);
			vertices->at(2)->z = -rB * cos(theta + deltaTheta);

			vertices->at(3)->x = rB * sin(theta);
			vertices->at(3)->z = -rB * cos(theta);

			// At the North pole (phi == 0) vertex 0 and 1 are the same points,
			// so we use a different vertex number ordering to designate a
			// more meaningful surface normal for those particular facets
			Facet* f = (phi > 0) ? new Facet(vertices, { 0, 1, 2, 3 })
				: new Facet(vertices, { 2, 3, 0, 1 });

			ss.DrawFacet(f, al_color_name("black"), al_color_name("darkgreen"), 1, false, false, 0);
		}
	}

	Niederreiter2 qrng;
	double r[3];
	int seed{};

	const int iterations = 10000;
	int count{};

	ss.LockDisplay();

	for (int i{};i < iterations;++i) {
		qrng.Next(3, &seed, r);

		double x = r[0] * -2.0 - 1.0;
		double y = r[1] * -2.0 - 1.0;
		double z = r[2] * -2.0 - 1.0;
		if (x*x + y*y + z*z <= 1.0) {
			ss.DrawPoint3D(x, y, z, "red");
			count++;
		}
		else
			ss.DrawPoint3D(x, y, z, "blue");
	}

	ss.UnlockDisplay();

	double estVol = (double)count / iterations * 8;
	double actVol = 4.0 / 3.0 * M_PI;
	double err = (actVol - estVol) / actVol * 100;

	cout << "3D Sphere Volume QRNG" << endl
		<< "Iterations = " << iterations << endl
		<< "Est. Volume  = " << estVol << endl
		<< "Act. Volume  = " << actVol << endl
		<< "Abs. % Error = " << abs(err) << endl << endl;
}

int main()
{
	cout.imbue(locale(""));

	SimpleScreen ss(draw);
	ss.SetZoomFrame("white", 3);

	ss.SetWorldRect(-1.25, -1.25, 1.25, 1.25);

	ss.SetProjection(29, 0.225);

	ss.SetCameraLocation(0.3, 0.6, 1.2);

	ss.HandleEvents();

	return 0;
}

