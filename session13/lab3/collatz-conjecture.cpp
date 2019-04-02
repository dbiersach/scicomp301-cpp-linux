// collatz-conjecture.cpp

#include "stdafx.h"

using namespace std;

int CalcStopTime(uint64_t n)
{
	int stopTime = 0;

	// TODO:  Insert your code here

	return stopTime;
}

int main()
{
	const uint64_t limit = (int)1e6;
	string title = "Collatz Conjecture (n #LT " + to_string(limit) + ")";
	TApplication* theApp = new TApplication(title.c_str(), nullptr, nullptr);

	TCanvas* c1 = new TCanvas(title.c_str());
	c1->SetTitle(title.c_str());

	TH1I* h1 = new TH1I(nullptr, title.c_str(), 500, 0, 501);
	h1->SetStats(kFALSE);

	TAxis* ya = h1->GetYaxis();
	ya->SetTitle("Count");
	ya->CenterTitle();

	TAxis* xa = h1->GetXaxis();
	xa->SetTitle("Stopping Time");
	xa->CenterTitle();
	xa->SetTickSize(0);

	// Fill the histogram
	for (uint64_t n{ 1 }; n < limit; n++)
		h1->Fill((int)CalcStopTime(n));

	h1->SetFillColor(kBlue);
	h1->Draw("B");

	theApp->Run();
	return 0;
}
