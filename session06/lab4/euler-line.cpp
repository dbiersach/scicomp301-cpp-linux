// euler-line.cpp

#include "stdafx.h"
#include "SimpleScreen.h"

using namespace std;

seed_seq seed{ 2016 };
default_random_engine gen{ seed };
uniform_int_distribution<int> dist(0, 20);

Point2D v1, v2, v3;

void CreateTriangle()
{
    v1.x = -30 + dist(gen);
    v1.y = -30 + dist(gen);

    v2.x = 10 + dist(gen);
    v2.y = -10 + dist(gen);

    v3.x = -10 + dist(gen);
    v3.y = 10 + dist(gen);
}

void draw(SimpleScreen& ss)
{
    // Connect the three vertices
    PointSet ps;
    ps.add(&v1);
    ps.add(&v2);
    ps.add(&v3);
    ss.DrawLines(&ps, "black", 2, true);

    // Calculate the slope of each side
    double slope12 = (v2.y - v1.y) / (v2.x - v1.x);
    double slope13 = (v3.y - v1.y) / (v3.x - v1.x);
    double slope23 = (v3.y - v2.y) / (v3.x - v2.x);

    // Calculate perpendicular slopes of each side
    slope12 = -1 / slope12;
    slope13 = -1 / slope13;
    slope23 = -1 / slope23;

    // Calculate the centroid
    Point2D centroid((v1.x + v2.x + v3.x) / 3,
                     (v1.y + v2.y + v3.y) / 3);

    // Connect vertices to centroid
    ss.DrawLine(v1, centroid, "orange", 3);
    ss.DrawLine(v2, centroid, "orange", 3);
    ss.DrawLine(v3, centroid, "orange", 3);

    // Calculate side bisector points
    Point2D bis12((v1.x + v2.x) / 2, (v1.y + v2.y) / 2);
    Point2D bis13((v1.x + v3.x) / 2, (v1.y + v3.y) / 2);
    Point2D bis23((v2.x + v3.x) / 2, (v2.y + v3.y) / 2);

    // Calculate y-intercept of each perpendicular side bisector
    double yint12 = bis12.y - slope12*bis12.x;
    double yint13 = bis13.y - slope13*bis13.x;
    double yint23 = bis23.y - slope23*bis23.x;

    // Calculate the circumcenter
    double ccx = (yint13 - yint12) / (slope12 - slope13);
    double ccy = slope12*ccx + yint12;
    Point2D cc(ccx, ccy);

    // Connect the side bisectors to the circumcenter
    ss.DrawLine(bis12, cc, "green", 3);
    ss.DrawLine(bis13, cc, "green", 3);
    ss.DrawLine(bis23, cc, "green", 3);

    // Calculate the point-slope of the Euler line
    // connecting the centroid with the circumcenter
    double slope_el = (centroid.y - cc.y) / (centroid.x - cc.x);
    double yint_el = cc.y - slope_el*cc.x;

    // Draw the Euler line
    Point2D el1(-30, -30 * slope_el + yint_el);
    Point2D el2(30, 30 * slope_el + yint_el);
    ss.DrawLine(el1, el2, "red", 4);
}

void eventHandler(SimpleScreen& ss, ALLEGRO_EVENT& ev)
{
    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
        if (ev.keyboard.keycode == ALLEGRO_KEY_N) {
            CreateTriangle();
            ss.Clear();
            ss.Redraw();
        }
    }
}

int main()
{
    SimpleScreen ss(draw, eventHandler);

    ss.SetWorldRect(-30, -30, 30, 30);

    CreateTriangle();

    ss.HandleEvents();

    return 0;
}

