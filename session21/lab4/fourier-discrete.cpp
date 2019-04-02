// fourier-discrete.cpp

#include "stdafx.h"

using namespace std;

vector<double> xOrd;
vector<double> xAct;
vector<double> yAct;
vector<double> xRad;
vector<double> fCos;
vector<double> fSin;
vector<double> yEst;
vector<double> yPower;

struct csv_reader : ctype<char> {
	csv_reader() : ctype<char>(get_table()) {}
	static ctype_base::mask const* get_table() {
		static vector<ctype_base::mask> rc(table_size, ctype_base::mask());
		rc[','] = ctype_base::space;
		rc['\n'] = ctype_base::space;
		rc[' '] = ctype_base::space;
		return &rc[0];
	}
};

void LoadSamples(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "Error: missing samples filename";
		exit(-1);
	}

	string filename{ argv[1] };
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "Error: Unable to open file "
			"\"" << filename << "\"" << endl;
		exit(-1);
	}

	double x, y;
	string line;
	stringstream ss;

	ss.imbue(locale(locale(), new csv_reader()));
	while (getline(infile, line)) {
		ss.str(line);
		ss >> x >> y;
		ss.clear();
		xAct.push_back(x);
		yAct.push_back(y);
		xOrd.push_back(xAct.size() - 1);
	}

	infile.close();
}

void ScaleDomain()
{
	double delta = (2 * M_PI) / xAct.size();
	for (size_t i{}; i < xAct.size(); ++i)
		xRad.push_back(delta * i);
}

void CalcDFT()
{
	const size_t sample_count{ yAct.size() };
	const size_t term_count{ sample_count / 2 };

	for (size_t term{ 0 }; term < term_count; ++term) {
		double fcos{ 0 }, fsin{ 0 };
		for (size_t i{ 0 }; i < sample_count; ++i) {
			double xs = xRad.at(i);
			double ys = yAct.at(i);
			fcos += cos(term * xs) * ys;
			fsin += sin(term * xs) * ys;
		}
		fcos /= sample_count;
		fsin /= sample_count;
		if (term > 0) {
			fcos *= 2;
			fsin *= 2;
		}
		fCos.push_back(fcos);
		fSin.push_back(fsin);
	}
}

void CalcIDFT()
{
	size_t sample_count{ yAct.size() };
	size_t term_count{ fCos.size() };

	for (size_t i{}; i < sample_count; ++i) {
		double xs = xRad.at(i);
		double yt{};
		for (size_t term{}; term < term_count; ++term) {
			yt += fCos.at(term) * cos(term * xs);
			yt += fSin.at(term) * sin(term * xs);
		}
		yEst.push_back(yt);
	}
}

void CalcPowerSpectrum()
{
	size_t term_count{ fCos.size() };
	for (size_t term{}; term < term_count; ++term)
		yPower.push_back(sqrt(pow(fCos.at(term), 2) + pow(fSin.at(term), 2)));
}

void PlotTransforms()
{
	TApplication* theApp = new TApplication(nullptr, nullptr, nullptr);

	string c1Title{ "Samples" };
	TCanvas* c1 = new TCanvas(c1Title.c_str());
	c1->SetTitle(c1Title.c_str());
	TMultiGraph* mg1 = new TMultiGraph();
	mg1->SetTitle(c1Title.c_str());
	TGraph* g1 = new TGraph(xAct.size(), &xAct[0], &yAct[0]);
	g1->SetLineColor(kBlue);
	g1->SetLineWidth(2);
	mg1->Add(g1);
	TGraph* g2 = new TGraph(xAct.size(), &xAct[0], &yEst[0]);
	g2->SetLineColor(kRed);
	g2->SetLineWidth(2);
	mg1->Add(g2);
	mg1->Draw("AL");
	TLegend* leg1 = new TLegend(0.8, 0.85, 0.9, 0.9);
	leg1->AddEntry(g1, "Actual","l");
	leg1->AddEntry(g2, "Reconstructed","l");
	leg1->Draw();

	string c2Title{ "Discrete Fourier Transform" };
	TCanvas* c2 = new TCanvas(c2Title.c_str());
	c2->SetTitle(c2Title.c_str());
	TMultiGraph* mg2 = new TMultiGraph();
	mg2->SetTitle(c2Title.c_str());
	TGraph* g3 = new TGraph(fCos.size(), &xOrd[0], &fCos[0]);
	g3->SetFillColor(kBlue);
	mg2->Add(g3);
	TGraph* g4 = new TGraph(fSin.size(), &xOrd[0], &fSin[0]);
	g4->SetFillColor(kRed);
	mg2->Add(g4);
	mg2->Draw("AB");
	TLegend* leg2 = new TLegend(0.85, 0.85, 0.9, 0.9);
	leg2->AddEntry(g3, "fCos", "f");
	leg2->AddEntry(g4, "fSin", "f");
	leg2->Draw();
	mg2->GetXaxis()->SetLimits(0, fCos.size());
	gPad->Modified();

	string c3Title{ "Power Spectrum" };
	TCanvas* c3 = new TCanvas(c3Title.c_str());
	c3->SetTitle(c3Title.c_str());
	TMultiGraph* mg3 = new TMultiGraph();
	mg3->SetTitle(c3Title.c_str());
	TGraph* g5 = new TGraph(yPower.size(), &xOrd[0], &yPower[0]);
	g5->SetFillColor(kGreen);
	mg3->Add(g5);
	mg3->Draw("AB");
	mg3->GetXaxis()->SetLimits(0, fCos.size());
	gPad->Modified();

	theApp->Run();

	delete g1;
	delete g2;
	delete g3;
	delete g4;
	delete g5;
	delete mg1;
	delete mg2;
	delete mg3;
	delete c1;
	delete c2;
	delete c3;
	delete leg1;
	delete leg2;

	delete theApp;
}


int main(int argc, char *argv[])
{
	LoadSamples(argc, argv);

	ScaleDomain();

	CalcDFT();

	CalcIDFT();

	CalcPowerSpectrum();

	PlotTransforms();

	return 0;
}
















