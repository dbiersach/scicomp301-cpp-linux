// IteratedFunctionSystem.h

#pragma once

#include "stdafx.h"

using namespace std;


struct Transform
{
	double x1, y1, x2, y2, x3, y3;
	double m[3][3];
	ALLEGRO_COLOR clr;
	double probability;
};

class IteratedFunctionSystem
{
public:
	IteratedFunctionSystem();
	~IteratedFunctionSystem();
	void SetBaseFrame(double xMin, double yMin, double xMax, double yMax);
	void AddMapping(double xLeft, double yLeft,
		double xRight, double yRight,
		double xTop, double yTop,
		string clr, double);
	void GenerateTransforms();
	void TransformPoint(double& x, double& y, ALLEGRO_COLOR &clr);

private:
	double Determinant(double matrix[3][3]);
	void Overlay(double matrix[3][3], double values[3], int col, double out[3][3]);

	vector<Transform*>* transforms = nullptr;

	double affineWidth;
	double affineHeight;
	double cdf;

	seed_seq seed{ 8 };
	default_random_engine generator{ seed };
	uniform_real_distribution<double> distribution{ 0, 1 };

};

