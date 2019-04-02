// find-orf.cpp

#include "stdafx.h"

using namespace std;

string ReverseComplement(string seq)
{
    // Add your code here
}

vector<string> CreateReadingFrame(const string& seq, int offset)
{
    size_t i = abs(offset) - 1;
    vector<string> frame{};
    while (i < seq.length() - 2)
    {
        frame.push_back(seq.substr(i, 3));
        i += 3;
    }
    return move(frame);
}

bool FindCodon(const vector<string>& frame,
               const vector<string>& codons, size_t start, size_t& pos)
{
    pos = start;
    bool found = false;
    while (!found && pos < frame.size())
    {
        for (const string& codon : codons)
            if (frame.at(pos) == codon)
                found = true;
        if (!found)
            pos++;
    }
    return found;
}

void FindORF(const string& seq, int offset)
{
    vector<string> frame = CreateReadingFrame(seq, offset);

    size_t posStart{};
    if (!FindCodon(frame, { "ATG" }, 0, posStart))
        return;

    size_t posStop{};
    if (!FindCodon(frame, { "TAA","TAG","TGA" }, posStart + 1, posStop))
        return;

    if (posStart + 1 == posStop)
        return;

    cout << "Frame ";
    if (offset > 0) cout << "+";
    cout << offset << ": ";
    for (size_t i{ posStart }; i <= posStop; i++)
        cout << frame.at(i) << " ";
    cout << endl;
}

int main()
{
    string seq{ "CGCTACGTCTTACGCTGGAGCTCTCATGGATCGGTTCGGTAGGGCTCGATCACATCGCTAGCCAT" };
    cout << seq << endl << endl;

    string seqRevComp = ReverseComplement(seq);

    for (auto offset :
            {
                1,2,3,-1,-2,-3
            })
        if (offset > 0)
            FindORF(seq, offset);
        else
            FindORF(seqRevComp, offset);

    return 0;
}
