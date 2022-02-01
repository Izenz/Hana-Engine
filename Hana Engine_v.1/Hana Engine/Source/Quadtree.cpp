#include "Quadtree.h"

Quadtree::Quadtree()
{
	boundary = new QT_Rectangle(0, 0, 0, 0);
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

Quadtree::Quadtree(const QT_Rectangle& _boundary, unsigned capacity)
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
	QT_Rectangle nw_Boundary(float2(0, 0), boundary->width, boundary->height);
	NW = new Quadtree(nw_Boundary, capacity);	// Top left

	QT_Rectangle sw_Boundary(float2(0, boundary->height), boundary->width, boundary->height);
	SW = new Quadtree(sw_Boundary, capacity);	// Bottom left

	QT_Rectangle ne_Boundary(float2(boundary->width, 0), boundary->width, boundary->height);
	NE = new Quadtree(ne_Boundary, capacity);	// Top right

	QT_Rectangle se_Boundary(float2(boundary->width, boundary->height), boundary->width, boundary->height);
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


void Quadtree::GetObjectsInRange(const QT_Rectangle& Range, std::list<AABB*>& found_objects)
{
	if (!boundary->Intersects(Range)) {
		return;
	}
	else {
		for (AABB* entity : entities_contained) {
			if (Range.Contains(entity)) {
				found_objects.push_back(entity);
			}
		}

		if (divided) {
			NW->GetObjectsInRange(Range, found_objects);
			SW->GetObjectsInRange(Range, found_objects);
			NE->GetObjectsInRange(Range, found_objects);
			SE->GetObjectsInRange(Range, found_objects);
		}
	}
}
