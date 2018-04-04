// bigint-sqrt.cpp

#include "stdafx.h"

using namespace std;

vector<int> five{ 5 };

vector<int>* getDigits(const string& s)
{
	size_t len = s.size();
	vector<int>* digits = new vector<int>(len);
	for (size_t i{}; i < len;++i)
		digits->at(i) = s.at(len - i - 1) - '0';
	return digits;
}

string makeString(const vector<int>* digits)
{
	string s{};
	for (size_t i{ digits->size() }; i > 0;--i)
		s += digits->at(i - 1) + '0';
	while (s.size() > 1 && s.at(0) == '0')
		s.erase(0, 1);
	return s;
}

void rippleCarry(vector<int>* digits)
{
	for (size_t i{};i < digits->size() - 1;++i) {
		if (digits->at(i) > 9) {
			digits->at(i + 1) +=
				(digits->at(i) - (digits->at(i) % 10)) / 10;
			digits->at(i) = digits->at(i) % 10;
		}
	}
	while (digits->at(digits->size() - 1) == 0) {
		digits->erase(digits->end() - 1);
	}
}

vector<int>* add(vector<int>* x, vector<int>* y)
{
	if (x->size() > y->size())
		swap(x, y);
	vector<int>* z = new vector<int>(y->size() + 1);
	for (size_t i{}; i < y->size();++i)
		z->at(i) = (i < x->size()) ?
		x->at(i) + y->at(i) : y->at(i);
	rippleCarry(z);
	return z;
}

vector<int>* multiply(vector<int>* x, vector<int>* y)
{
	if (x->size() > y->size())
		swap(x, y);
	vector<int>* z = new vector<int>(
		x->size() + y->size());
	for (size_t i{}; i < y->size();++i)
		for (size_t j{}; j < x->size();++j)
			z->at(i + j) += (y->at(i) * x->at(j));
	rippleCarry(z);
	return z;
}

vector<int>* average(vector<int>* x, vector<int>* y)
{
	vector<int>* z = multiply(&five, add(x, y));
	z->erase(z->begin());
	return z;
}

bool isEqual(vector<int>* a, vector<int>* b)
{
	if (a->size() != b->size())
		return false;
	for (size_t i{}; i < a->size();++i)
		if (a->at(i) != b->at(i))
			return false;
	return true;
}

bool isGreater(vector<int>* a, vector<int>* b)
{
	if (a->size() > b->size())
		return true;
	if (a->size() < b->size())
		return false;
	for (size_t i{ a->size() }; i > 0;--i)
		if (a->at(i - 1) > b->at(i - 1))
			return true;
		else if (a->at(i - 1) < b->at(i - 1))
			return false;
	return false;
}

string intSqrt(vector<int>* x)
{
	vector<int>* lowEnd = new vector<int>{ 0 };
	vector<int>* highEnd = x;

	vector<int>* lastEstimate = new vector<int>{ 0 };

	vector<int>* estimate = average(lowEnd, highEnd);

	while (!isEqual(lastEstimate, estimate))
	{
		vector<int>* estimateSquared = multiply(estimate, estimate);
		if (isGreater(estimateSquared, x))
			highEnd = estimate;
		else
			lowEnd = estimate;

		lastEstimate = estimate;
		estimate = average(lowEnd, highEnd);
		delete estimateSquared;
	}

	string s = makeString(estimate);
	delete estimate;
	delete highEnd;
	delete lowEnd;

	return s;
}


int main()
{
	seed_seq seed{ 2016 };
	default_random_engine generator{ seed };
	uniform_int_distribution<int> distribution(0, 9);

	string s = "1";
	for (int i{}; i < 99;++i)
		s += distribution(generator) + '0';

	cout << "The Integer Square Root of "
		<< endl << endl
		<< s << endl << endl
		<< "is" << endl << endl;

	cout << intSqrt(getDigits(s))
		<< endl << endl;

	return 0;
}
