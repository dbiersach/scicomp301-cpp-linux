// reverse-string.cpp

#include "stdafx.h"

using namespace std;

string ReverseString(string a)
{
    string b;

    // Implement your algorithm here


    return b;
}

int main()
{
    string s = "Forever Young";
    string r = ReverseString(s);

    cout << "Original string = "
         << s << endl;

    cout << "Reversed string = "
         << r << endl;

    reverse(s.begin(),s.end());

    cout << "  STL reverse() = "
         << s << endl;

    return 0;
}
