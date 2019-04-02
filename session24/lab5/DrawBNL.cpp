// DrawBNL.cpp

#include "stdafx.h"
#include "SimpleScreen.h"
#include "IteratedFunctionSystem.h"

using namespace std;

IteratedFunctionSystem* ifs = nullptr;
const int iterations = 500000;


void draw(SimpleScreen& ss) {
	ss.LockDisplay();
	double x, y;
	ALLEGRO_COLOR clr;
	for (int i{}; i < iterations; i++) {
		ifs->TransformPoint(x, y, clr);
		ss.DrawPoint(x, y, clr);
	}
	ss.UnlockDisplay();
}

int main()
{
	SimpleScreen ss(draw);
	ss.SetZoomFrame("white", 3);

	ss.SetWorldRect(0, 0, 17, 7);

	ifs = new IteratedFunctionSystem();

	ifs->SetBaseFrame(0, 0, 17, 7);

	double p = 1. / 29;

	// B
	ifs->AddMapping(0, 6, 2, 6, 0, 7, "lightblue", p);     // 01
	ifs->AddMapping(2, 6, 4, 6, 2, 7, "blue", p);          // 02
	ifs->AddMapping(1, 4, 1, 6, 0, 4, "blue", p);          // 03
	ifs->AddMapping(4, 6, 4, 4, 5, 6, "blue", p);          // 04
	ifs->AddMapping(0, 3, 2, 3, 0, 4, "blue", p);          // 05
	ifs->AddMapping(4, 4, 2, 4, 4, 3, "red", p);           // 06
	ifs->AddMapping(1, 1, 1, 3, 0, 1, "pink", p);          // 07
	ifs->AddMapping(4, 3, 4, 1, 5, 3, "blue", p);          // 08
	ifs->AddMapping(0, 0, 2, 0, 0, 1, "blue", p);          // 09
	ifs->AddMapping(4, 1, 2, 1, 4, 0, "sienna", p);        // 10

	// N
	ifs->AddMapping(6, 6, 7, 6, 6, 7, "blue", p);          // 11
	ifs->AddMapping(10, 6, 11, 6, 10, 7, "papayawhip", p); // 12
	ifs->AddMapping(6, 5, 8, 5, 6, 6, "chartreuse", p);    // 13
	ifs->AddMapping(11, 4, 11, 6, 10, 4, "blue", p);       // 14
	ifs->AddMapping(7, 3, 7, 5, 6, 3, "blue", p);          // 15
	ifs->AddMapping(8, 4, 9, 4, 8, 5, "blue", p);          // 16
	ifs->AddMapping(7, 1, 7, 3, 6, 1, "orange", p);        // 17
	ifs->AddMapping(9, 2, 9, 4, 8, 2, "blue", p);          // 18
	ifs->AddMapping(10, 4, 10, 2, 11, 4, "maroon", p);     // 19
	ifs->AddMapping(6, 0, 7, 0, 6, 1, "blue", p);          // 20
	ifs->AddMapping(9, 1, 11, 1, 9, 2, "blue", p);         // 21
	ifs->AddMapping(10, 0, 11, 0, 10, 1, "yellow", p);     // 22

	// L
	ifs->AddMapping(13, 5, 13, 7, 12, 5, "green", p);      // 23
	ifs->AddMapping(12, 4, 13, 4, 12, 5, "blue", p);       // 24
	ifs->AddMapping(12, 4, 12, 2, 13, 4, "blue", p);       // 25
	ifs->AddMapping(13, 1, 13, 2, 12, 1, "white", p);      // 26
	ifs->AddMapping(12, 0, 14, 0, 12, 1, "blue", p);       // 27
	ifs->AddMapping(15, 0, 15, 1, 14, 0, "blue", p);       // 28
	ifs->AddMapping(15, 0, 17, 0, 15, 1, "purple", p);     // 29

	ifs->GenerateTransforms();

	ss.HandleEvents();

	delete ifs;

	return 0;
}

