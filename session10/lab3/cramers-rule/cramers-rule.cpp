// cramers-rule.cpp

#include "stdafx.h"

using namespace std;

double Determinant(double matrix[3][3])
{
	double a = matrix[0][0];
	double b = matrix[0][1];
	double c = matrix[0][2];
	double d = matrix[1][0];
	double e = matrix[1][1];
	double f = matrix[1][2];
	double g = matrix[2][0];
	double h = matrix[2][1];
	double i = matrix[2][2];

	double det = a * (e * i - f * h)
		- (b * (d * i - f * g))
		+ c * (d * h - e * g);

	return det;
}

void OverlayValues(double coeffMatrix[3][3], double valueVector[3],
	int col, double newMatrix[3][3])
{
	// Copy existing coeffMatrix to newMatrix
	for (int i{}; i < 3; ++i)
		for (int j{}; j < 3; ++j)
			newMatrix[i][j] = coeffMatrix[i][j];

	// Overlay the valueVector on the specified column
	for (int i{}; i < 3; ++i)
		newMatrix[i][col] = valueVector[i];
}

void DisplayEquations(double coeffMatrix[3][3], double valueVector[3])
{
	for (int i{}; i < 3; ++i) {
		if (coeffMatrix[i][0] != 0) {
			if (coeffMatrix[i][0] < 0)
				cout << "-";
			if (abs(coeffMatrix[i][0]) != 1)
				cout << abs(coeffMatrix[i][0]);
			cout << "x ";
		}
		if (coeffMatrix[i][1] != 0) {
			if (coeffMatrix[i][1] < 0)
				cout << "-";
			else
				cout << "+ ";
			if (abs(coeffMatrix[i][1]) != 1)
				cout << abs(coeffMatrix[i][1]);
			cout << "y ";
		}
		if (coeffMatrix[i][2] != 0) {
			if (coeffMatrix[i][2] < 0)
				cout << "-";
			else
				cout << "+ ";
			if (abs(coeffMatrix[i][2]) != 1)
				cout << abs(coeffMatrix[i][2]);
			cout << "z ";
		}
		cout << "= " << valueVector[i] << endl;
	}
	cout << endl;
}

int main()
{
	double coeffMatrix[3][3]
	{ { 4,5,-2 },
	{ 7,-1,2 },
	{ 3,1,4 } };

	double valueVector[3]{ -14,42,28 };

	DisplayEquations(coeffMatrix, valueVector);

	double detCoeff = Determinant(coeffMatrix);

	if (detCoeff == 0) {
		cout << "This system is linearly dependent"
			 << "and not uniquely solveable!"
			<< endl;
	}
	else {

		double mX[3][3];
		OverlayValues(coeffMatrix, valueVector, 0, mX);
		double detX = Determinant(mX);

		double mY[3][3];
		OverlayValues(coeffMatrix, valueVector, 1, mY);
		double detY = Determinant(mY);

		double mZ[3][3];
		OverlayValues(coeffMatrix, valueVector, 2, mZ);
		double detZ = Determinant(mZ);

		cout << "DetCoeff = " << detCoeff << endl;
		cout << endl;

		cout << "DetX = " << detX << endl;
		cout << "DetY = " << detY << endl;
		cout << "DetZ = " << detZ << endl;
		cout << endl;

		cout << "X = " << detX / detCoeff << endl;
		cout << "Y = " << detY / detCoeff << endl;
		cout << "Z = " << detZ / detCoeff << endl;
	}

	return 0;
}
