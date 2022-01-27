#pragma once
#include "MathGeoLib.h"
#include <vector>

#include "Globals.h"

typedef struct RECT	 {
	float2 origin;				// origin 
	unsigned width, height;

	RECT(const float2& _origin, unsigned _width, unsigned _height) {
		origin = _origin;
		width = _width;
		height = _height;
	}

	RECT(int _x, int _y, unsigned _width, unsigned _height) {
		origin.x = _x;
		origin.y = _y;
		width = _width;
		height = _height;
	}
} Rectangle;

class Quadtree
{

public:

	Quadtree();
	Quadtree(const Rectangle& _boundary, unsigned capacity);
	~Quadtree();

	void Init();
	void Update();

	void Insert(AABB& entity);
	void Subdivide();
	bool DoesBoundaryContain(const AABB&) const;
private:
	Rectangle* boundary;
	unsigned capacity;
	std::vector<AABB*> entities_contained;

	bool divided;
	Quadtree* NW;
	Quadtree* NE;
	Quadtree* SW;
	Quadtree* SE;
};

