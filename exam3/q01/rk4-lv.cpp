// rk4-lv.cpp

#include "stdafx.h"

using namespace std;

// Runge-Kutta method for two coupled 1st order differential equations
void runge_kutta(double &x1, double &x2, double &t, const double dt,
                 double(*fx1)(double, double, double),
                 double(*fx2)(double, double, double))
{
    double dx1 = fx1(x1, x2, t);
    double dy1 = fx2(x1, x2, t);

    double dx2 = fx1(x1 + (dt / 2.0) * dx1, x2 + (dt / 2.0) * dy1, t);
    double dy2 = fx2(x1 + (dt / 2.0) * dx1, x2 + (dt / 2.0) * dy1, t);

    double dx3 = fx1(x1 + (dt / 2.0) * dx2, x2 + (dt / 2.0) * dy2, t);
    double dy3 = fx2(x1 + (dt / 2.0) * dx2, x2 + (dt / 2.0) * dy2, t);

    double dx4 = fx1(x1 + dt * dx3, x2 + dt * dy3, t);
    double dy4 = fx2(x1 + dt * dx3, x2 + dt * dy3, t);

    x1 += dt * (dx1 + 2.0 * dx2 + 2.0 * dx3 + dx4) / 6.0;
    x2 += dt * (dy1 + 2.0 * dy2 + 2.0 * dy3 + dy4) / 6.0;
    t += dt;
}

// Lotka-Volterra {Prey} dx/dt
double d_prey(double x, double y, double t)
{
    return 0;
}

// Lotka-Volterra {Predator} dy/dt
double d_predator(double x, double y, double t)
{
    return 0;
}

int main()
{
    // Initial time
    double t = 0.0;

    // Initial prey population %
    double x = 0.0;

    // Initial predator population %
    double y = 0.0;

    // Stop time (dimensionless)
    double t_stop = 20.0;

    // Number of time steps
    const int steps = 250;

    // Time step (delta time)
    const double dt = t_stop / steps;

    double time[steps];
    double prey[steps];
    double predator[steps];

    time[0] = t;
    prey[0] = x;
    predator[0] = y;

    // Use Runge-Kutta for coupled differential equations
    for (int step{ 1 }; step < steps; ++step)
    {
        runge_kutta(x, y, t, dt, d_prey, d_predator);
        time[step] = t;
        prey[step] = x;
        predator[step] = y;
    }

    // Graph the curve using CERN's ROOT libraries
    string title = "Lotka-Volterra using RK4";
    TApplication* theApp =
        new TApplication(title.c_str(), nullptr, nullptr);

    TCanvas* c1 = new TCanvas(title.c_str());
    c1->SetTitle(title.c_str());

    TMultiGraph* mg1 = new TMultiGraph();
    mg1->SetTitle((title + ";time;population").c_str());

    TGraph* g1 = new TGraph(steps, time, prey);
    //g1->SetTitle((title + ";time;count").c_str());
    g1->SetMarkerColor(kBlue);
    g1->SetLineColor(kBlue);
    g1->SetLineWidth(3);
    mg1->Add(g1);

    TGraph* g2 = new TGraph(steps, time, predator);
    //g2->SetTitle((title + ";time;count").c_str());
    g2->SetMarkerColor(kRed);
    g2->SetLineColor(kRed);
    g2->SetLineWidth(3);
    mg1->Add(g2);

    mg1->Draw("AL");
    TLegend* leg1 = new TLegend(0.8, 0.85, 0.9, 0.9);
    leg1->AddEntry(g1, "prey", "l");
    leg1->AddEntry(g2, "predator", "l");
    leg1->Draw();

    theApp->Run();

    delete g1;
    delete g2;
    delete mg1;
    delete c1;
    delete theApp;

    return 0;
}


