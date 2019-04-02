// GenerateStdCF.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	double x = (1 + sqrt(5)) / 2;

	int maxTerms = 20;

	cout << "To " << maxTerms << " terms, "
		<< "the standard continued fraction for "
		<< setprecision(14) << x << " is:\n" << endl
		<< "{" << (int)(x) << ", ";

	x = x - int(x);

	for (int terms = 1;terms < maxTerms;terms++)
	{
		cout << (int)(1 / x);
		if (terms < maxTerms - 1) cout << ", ";
		x = 1 / x - (int)(1 / x);
	}

	cout << "}" << endl << endl;

	return 0;
}


