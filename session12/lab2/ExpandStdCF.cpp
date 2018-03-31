// ExpandStdCF.cpp

#include "stdafx.h"

using namespace std;

int main()
{
	int maxTerms = 20;

	vector<int> cf;

	vector<double> h(maxTerms + 2);
	vector<double> k(maxTerms + 2);

	if (cf.size() == 0) {
		cout << "Error - Missing cf data!";
		return -1;
	}

	h.at(0) = 0; k.at(0) = 1;
	h.at(1) = 1; k.at(1) = 0;

	cout << "Using " << maxTerms << " terms, ";
	cout << "the continued fraction expansion is:" << endl;
	cout << setw(5) << "a";
	cout << right << setw(15) << "h";
	cout << right << setw(15) << "k";
	cout << setw(20) << "convergent" << endl;



	for (int n{ 2 }; n < maxTerms + 2; ++n) {
		double a = cf.at(n - 2);

		h.at(n) = a * h.at(n - 1) + h.at(n - 2);
		k.at(n) = a * k.at(n - 1) + k.at(n - 2);

		double convergent = h.at(n) / k.at(n);

		cout << setprecision(0) << right
			<< setw(5) << a << setw(15) << h[n] << setw(15) << k[n]
			<< setprecision(14) << fixed << setw(20) << convergent << endl;
	}

	return 0;
}
