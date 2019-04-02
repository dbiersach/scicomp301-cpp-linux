// freq-ciphertext.cpp

#include "stdafx.h"

using namespace std;

int main()
{
    // Open file at the end so the "get" position will be file size
    ifstream ifs("Encrypted.txt", ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    // Allocate a vector big enough to hold all the file bytes
    vector<uint8_t> fileBytes(pos);

    // Read in the file from the beginning straight into the vector
    ifs.seekg(0, ios::beg);
    ifs.read((char*)(fileBytes.data()), pos);

    // Create a new CERN ROOT app
    string title = "Frequency Analysis";
    TApplication* theApp = new TApplication(title.c_str(), nullptr, nullptr);

    TCanvas* c1 = new TCanvas(title.c_str());
    c1->SetTitle(title.c_str());

    // Create a ROOT one dimensional histogram of integers
    TH1I* h1 = new TH1I(nullptr, title.c_str(), 256, 0, 257);
    h1->SetStats(kFALSE);

    TAxis* ya = h1->GetYaxis();
    ya->SetTitle("Count");
    ya->CenterTitle();

    TAxis* xa = h1->GetXaxis();
    xa->SetTitle("ASCII Value");
    xa->CenterTitle();
    xa->SetTickSize(0);

    // Fill the histogram using the bytes in the file
    for (auto item : fileBytes)
        h1->Fill((int)item);

    h1->SetBinContent(243, 0);

    // Label any bin with the ASCII value
    // if the bin count is > 6% of the file size,
    // as these would be noteworthy occurrences
    for (int i{}; i < xa->GetNbins(); ++i)
        if (h1->GetBinContent(i) > fileBytes.size() * 0.06)
            xa->SetBinLabel(i, to_string(i).c_str());

    h1->Draw();

    theApp->Run();
    return 0;
}
