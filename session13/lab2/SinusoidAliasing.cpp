// SinusoidAliasing.cpp

#include "stdafx.h"

using namespace std;

const double b = 210;
const int n = 420;

vector<double> x(n + 1);
vector<double> y(n + 1);

void InitData()
{
	double dx = b / n;

	for (int i = 0;i <= n;i++) {
		x.at(i) = i * dx;
		y.at(i) =
			sin(4 * M_PI * x.at(i)) *
			sin(6 * M_PI * x.at(i)) *
			sin(10 * M_PI * x.at(i))*
			sin(14 * M_PI * x.at(i));

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
	string title = "y=UNKNOWN ("
		+ to_string(n) + " samples)";
	mg->SetTitle(title.c_str());
	gStyle->SetTitleFontSize(0.03f);

	mg->SetMinimum(-1.);
	mg->SetMaximum(1.);

	TGraph* g = new TGraph(n + 1, &x.at(0), &y.at(0));
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

