// vector-addition.cpp

#include "stdafx.h"

using namespace std;

template <typename T>
void DisplayVector(string name, vector<T> vec)
{
	cout << "Vector " << name << " = {";
	for (size_t i{}; i < vec.size() - 1; i++)
		cout << vec.at(i) << ", ";
	cout << vec.back() << "}" << endl << endl;
}

template <typename T>
vector<T> AddVectors(vector<T> vec1, vector<T> vec2)
{
	vector<T> vec3(vec1.size());
    // Implement your code here
	return vec3;
}


int main()
{
	vector<int> a{ -2, 3, 6, 113, 49, 0, 123 };
	vector<int> b{ 18, 13, 990, 2, -55, -9, 14 };

	DisplayVector("a", a);
	DisplayVector("b", b);
	DisplayVector("c", AddVectors(a, b));

	return 0;
}

