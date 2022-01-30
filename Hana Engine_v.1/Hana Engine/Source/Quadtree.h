#pragma once
#include "MathGeoLib.h"
#include <vector>
#include <list>

#include "Globals.h"

typedef struct RECTANG	 {
	float2 origin;				// origin is located on the TOP LEFT corner.
	unsigned width, height;

	RECTANG(const float2& _origin, unsigned _width, unsigned _height) {
		origin = _origin;
		width = _width;
		height = _height;
	}

	RECTANG(int _x, int _y, unsigned _width, unsigned _height) {
		origin.x = _x;
		origin.y = _y;
		width = _width;
		height = _height;
	}

	bool Contains(const AABB* entity) const {
		return true;
	}

	bool Intersects(const RECTANG& Rect) const {
		// If any of these is TRUE they are NOT overlapping
		bool width_check = this->origin.x > (Rect.origin.x + Rect.width) || (this->origin.x + this->width) < Rect.origin.x;
		bool height_check = this->origin.y > (Rect.origin.y + Rect.height) || (this->origin.y + this->height) < Rect.origin.y;

		return !(width_check || height_check);
	}

} QT_Rectangle;

class Quadtree
{

public:

	Quadtree();
	Quadtree(const QT_Rectangle& _boundary, unsigned capacity);
	~Quadtree();

	void Init();
	void Update();

	void Insert(AABB& entity);
	void Subdivide();
	bool DoesBoundaryContain(const AABB&) const;
	void GetObjectsInRange(const QT_Rectangle& Range, std::list<AABB*>& found_objects);

private:
	QT_Rectangle* boundary;
	unsigned capacity;
	std::vector<AABB*> entities_contained;

	bool divided;
	Quadtree* NW;
	Quadtree* NE;
	Quadtree* SW;
	Quadtree* SE;
};

