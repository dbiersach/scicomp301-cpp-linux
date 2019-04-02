// SimpleScreen.h

#pragma once

#include "stdafx.h"

using std::string;
using std::vector;



// Point 2D
class Point2D
{
public:
	Point2D();
	Point2D(double x, double y);
	~Point2D();
	double x, y;
};

// Point 3D
class Point3D
{
public:
	Point3D();
	Point3D(double x, double y, double z);
	~Point3D();
	double x, y, z;
};

// Rectangle
class Rectangle
{
public:
	Rectangle();
	Rectangle(double xMin, double yMin, double xMax, double yMax);
	~Rectangle();
	void Resize(double width, double height);
	double xMin, yMin, xMax, yMax;
};

// UnitVector
class UnitVector
{
public:
	UnitVector();
	UnitVector(Point3D* tail, Point3D* tip);
	~UnitVector();
	void normalize();
	UnitVector* crossProduct(UnitVector* other);
	double dotProduct(UnitVector* other);
private:
	double x, y, z;
};


// PointSet
class PointSet
{
public:
	PointSet();
	~PointSet();
	Point2D* at(size_t i);
	void clear();
	void add(double x, double y);
	void add(Point2D* pt);
	size_t size();
private:
	vector<Point2D*>* points;
};

// PointSet3D
class PointSet3D
{
public:
	PointSet3D();
	~PointSet3D();
	Point3D* at(size_t i);
	void clear();
	void add(double x, double y, double z);
	void add(Point3D* p3d);
	size_t size();
private:
	vector<Point3D*>* points;
};

// Facet
class Facet
{
public:
	Facet();
	Facet(PointSet3D* allVertices, vector<size_t> vertexNumbers);
	~Facet();
	Point3D* at(size_t i);
	PointSet3D* all();
	void clear();
	size_t size();
	Point3D* center();
	UnitVector* surfaceNormal();
private:
	PointSet3D* points;
};

// FacetSet
class FacetSet
{
public:
	FacetSet();
	~FacetSet();
	Facet* at(size_t i);
	PointSet3D* vertices(size_t facetNumber);
	void add(PointSet3D* allVertices, vector<size_t> vertexNumbers);
	void clear();
	size_t size();
private:
	vector<Facet*>* facets;
};

// SimpleScreen
class SimpleScreen
{
public:
	SimpleScreen(void(*draw)(SimpleScreen& ss) = nullptr,
		void(*eventHandler)(SimpleScreen& ss, ALLEGRO_EVENT& ev)= nullptr);

	~SimpleScreen();

	void SetWorldRect(double xMin, double yMin,
		double xMax, double yMax);

	void GetWorldRect();

	void SetProjection(double degrees = 45, double correction = 1);

	void SetCameraLocation(double x, double y, double z);

	void SetZoomFrame(string clr, double width = 2);

	void LockDisplay();

	void UnlockDisplay();

	void Clear();

	void Update();

	void Redraw();

	void Exit();

	void HandleEvents();

	bool Contains(double x, double y);

	void DrawAxes(string clr = "black", float width = 1);

	void DrawLine(Point2D &a, Point2D &b,
		string clr = "black", float width = 1);

	void DrawLines(PointSet* ps, string clr, float width = 1,
		bool close = true, bool fill = false, long delay = 0);

	void DrawLines(FacetSet* facets, string clr, float width = 1,
		bool fill = false, long delay = 0);

	void DrawLines(Facet* f, ALLEGRO_COLOR clr, float width,
		bool fill = false, long delay = 0);

	void DrawFacet(Facet* f, ALLEGRO_COLOR clrMin, ALLEGRO_COLOR clrMax,
		float width, bool culled = false, bool shaded = false, long delay = 0);

	void DrawRectangle(string clr, double xMin, double yMin,
		double width, double height, int borderWidth = 3, bool fill = false);

	void DrawCircle(double centerX, double centerY,
		double radius, string clr, int width);

	void DrawPoint(double x, double y, string clr);

	void DrawPoint(double x, double y, ALLEGRO_COLOR& clr);

	void DrawPoint3D(double x, double y, double z, string clr);

	void DrawPoint3D(double x, double y, double z, ALLEGRO_COLOR& clr);


	const int screenWidth = 501;
	const int screenHeight = 501;

	double worldXmin, worldYmin;
	double worldXmax, worldYmax;
	double worldWidth, worldHeight;


private:
	void CalcScreenPoints(PointSet* ps);
	void CalcScreenPoints3D(PointSet3D* ps3d);

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* event_queue;

	void(*draw)(SimpleScreen& ss);
	void(*eventHandler)(SimpleScreen& ss, ALLEGRO_EVENT& ev);
	ALLEGRO_LOCKED_REGION *lr = nullptr;

	double scaleX, scaleY;

	vector<Rectangle> worldRects;

	bool exit;
	bool redraw;

	ALLEGRO_COLOR zoomFrameClr;
	double zoomFrameBorderWidth;

	vector<Point2D*>* points;

	double obliqueAngle;
	double obliqueCos;
	double obliqueSin;
	double aspectCorrection;

	Point3D* cameraLocation;


};
