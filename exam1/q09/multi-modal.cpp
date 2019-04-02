// multi-modal.cpp

#include "stdafx.h"

using namespace std;

vector<int> FindModes(vector<int> data)
{
    // Prepare return vector
    vector<int> modes;

    // Implement your code here

    return modes;
}

int main()
{
    // Prepare data vector
    vector<int> data {7,1,2,3,7,4,5,6,7,1,2,1,1,9,7,10,2,2};

    cout << "The modes of the data are: " << endl;
    for (auto& n : FindModes(data))
        cout << n << endl;

    return 0;
}

