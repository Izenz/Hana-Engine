#include "Quadtree.h"

Quadtree::Quadtree()
{
	boundary = new Rectangle(0, 0, 0, 0);
	capacity = 0;
	divided = false;
}

Quadtree::~Quadtree()
{
	delete boundary;

	if (divided) {
		delete NW;
		delete NE;
		delete SW;
		delete SE;
	}
}

Quadtree::Quadtree(const Rectangle& _boundary, unsigned capacity)
{
	boundary->origin = _boundary.origin;
	boundary->width = _boundary.width;
	boundary->height = _boundary.height;
}

void Quadtree::Init()
{

}

void Quadtree::Update()
{

}

void Quadtree::Insert(AABB& entity)
{
	if (!DoesBoundaryContain(entity)) {
		return;
	}

	if (entities_contained.size() < capacity) {
		entities_contained.push_back(&entity);
	}
	else {
		if (!divided)	Subdivide();

		NW->Insert(entity);
		SW->Insert(entity);
		NE->Insert(entity);
		SE->Insert(entity);
	}

}

void Quadtree::Subdivide()
{
	Rectangle nw_Boundary(float2(0, 0), boundary->width, boundary->height);
	NW = new Quadtree(nw_Boundary, capacity);	// Top left

	Rectangle sw_Boundary(float2(0, boundary->height), boundary->width, boundary->height);
	SW = new Quadtree(sw_Boundary, capacity);	// Bottom left

	Rectangle ne_Boundary(float2(boundary->width, 0), boundary->width, boundary->height);
	NE = new Quadtree(ne_Boundary, capacity);	// Top right

	Rectangle se_Boundary(float2(boundary->width, boundary->height), boundary->width, boundary->height);
	SE = new Quadtree(se_Boundary, capacity);	// Bottom right

	divided = true;
}

bool Quadtree::DoesBoundaryContain(const AABB& entity) const
{
	// TODO: Edge cases????
	bool within_width = entity.CenterPoint().x <= boundary->width && entity.CenterPoint().x >= boundary->origin.x;
	bool within_height = entity.CenterPoint().y <= boundary->height && entity.CenterPoint().y >= boundary->origin.y;

	return within_height && within_width;
}
