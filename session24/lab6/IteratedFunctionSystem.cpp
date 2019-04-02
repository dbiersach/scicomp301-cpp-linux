// DrawSierpinskiTriangle.cpp

#include "stdafx.h"
#include "IteratedFunctionSystem.h"


IteratedFunctionSystem::IteratedFunctionSystem()
{
	transforms = new vector <Transform*>();
}

IteratedFunctionSystem::~IteratedFunctionSystem()
{
	for (Transform* t : *transforms)
		delete t;
	transforms->clear();
	delete transforms;
}

double IteratedFunctionSystem::Determinant(double matrix[3][3])
{
	double a = matrix[0][0];
	double b = matrix[0][1];
	double color = matrix[0][2];
	double d = matrix[1][0];
	double e = matrix[1][1];
	double f = matrix[1][2];
	double g = matrix[2][0];
	double h = matrix[2][1];
	double i = matrix[2][2];

	double det{ a * (e * i - f * h)
		- (b * (d * i - f * g))
		+ color * (d * h - e * g) };

	return det;
}

void IteratedFunctionSystem::Overlay(double matrix[3][3], double values[3], int col, double out[3][3])
{
	for (int i{}; i < 3; i++)
		for (int j{}; j < 3; j++)
			out[i][j] = matrix[i][j];
	for (int i = 0; i < 3; i++)
		out[i][col] = values[i];
}

void IteratedFunctionSystem::SetBaseFrame(double xMin, double yMin, double xMax, double yMax)
{
	affineWidth = xMax - xMin;
	affineHeight = yMax - yMin;
}

void IteratedFunctionSystem::AddMapping(double xLeft, double yLeft,
	double xRight, double yRight,
	double xTop, double yTop,
	string clr, double probability)
{
	cdf += probability;

	Transform* t = new Transform();
	t->x1 = xLeft; t->y1 = yLeft;
	t->x2 = xRight; t->y2 = yRight;
	t->x3 = xTop; t->y3 = yTop;
	t->clr = al_color_name(clr.c_str());
	t->probability = cdf;
	transforms->push_back(t);
}

void IteratedFunctionSystem::GenerateTransforms()
{
	double coeff[3][3];

	// Bottom left corner
	coeff[0][0] = 0; coeff[0][1] = 0;coeff[0][2] = 1;
	// Bottom right corner
	coeff[1][0] = affineWidth; coeff[1][1] = 0;coeff[1][2] = 1;
	// Top left corner
	coeff[2][0] = 0; coeff[2][1] = affineHeight;coeff[2][2] = 1;

	double d = Determinant(coeff);

	for (Transform* t : *transforms)
	{
		double xVec[3];
		xVec[0] = t->x1; xVec[1] = t->x2; xVec[2] = t->x3;

		double yVec[3];
		yVec[0] = t->y1; yVec[1] = t->y2; yVec[2] = t->y3;

		double matrix[3][3];

		Overlay(coeff, xVec, 0, matrix);
		t->m[0][0] = Determinant(matrix) / d;

		Overlay(coeff, xVec, 1, matrix);
		t->m[1][0] = Determinant(matrix) / d;

		Overlay(coeff, xVec, 2, matrix);
		t->m[2][0] = Determinant(matrix) / d;

		Overlay(coeff, yVec, 0, matrix);
		t->m[0][1] = Determinant(matrix) / d;

		Overlay(coeff, yVec, 1, matrix);
		t->m[1][1] = Determinant(matrix) / d;

		Overlay(coeff, yVec, 2, matrix);
		t->m[2][1] = Determinant(matrix) / d;

		t->m[0][2] = 0;
		t->m[1][2] = 0;
		t->m[2][2] = 1;
	}
}

void IteratedFunctionSystem::TransformPoint(double& x, double& y, ALLEGRO_COLOR &clr)
{
	double p = distribution(generator);

	// Find first transform with smaller probability
	size_t tn = 0;
	for (;tn < transforms->size()
		&& p > transforms->at(tn)->probability;++tn);

	Transform* t = transforms->at(tn);

	double xt = x * t->m[0][0] + y * t->m[1][0] + t->m[2][0];
	double yt = x * t->m[0][1] + y * t->m[1][1] + t->m[2][1];

	x = xt;
	y = yt;

	clr = t->clr;

}