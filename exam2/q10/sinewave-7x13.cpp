// sinewave-7x13.cpp

#include "stdafx.h"

using namespace std;

const double b = 20;
const int n = 640;

vector<double> x(n + 1);
vector<double> y(n + 1);

void InitData()
{
	double dx = b / n;

	for (int i = 0;i <= n;i++) {
		x.at(i) = i * dx;
		y.at(i) = sin(4.0 / 5.0 * M_PI * x.at(i));
	}
}

int main()
{
	InitData();

	TApplication* theApp = new
		TApplication(nullptr, nullptr, nullptr);

	TCanvas* c = new TCanvas(
		(string().append("Sinusoid Aliasing (")
		.append(to_string(n))
		.append(" samples)")).c_str());

	TMultiGraph* mg = new TMultiGraph();
	string title = "y=sin(#frac{4#pi}{5}x) ("
		+ to_string(n) + " samples)";
	mg->SetTitle(title.c_str());
	gStyle->SetTitleFontSize(0.03f);

	mg->SetMinimum(-1.);
	mg->SetMaximum(1.);

	TGraph* g = new TGraph(n + 1, &x[0], &y[0]);
	g->SetLineColor(kBlue);
	g->SetMarkerColor(kRed);
	g->SetMarkerStyle(kFullDotLarge);

	mg->Add(g);
	mg->Draw("ALP");

	mg->GetXaxis()->SetTitle("x");
	mg->GetYaxis()->SetTitle("y");

	gPad->Modified();

	theApp->Run();

	delete g;
	delete mg;
	delete c;
	delete theApp;
}

