#include "AABB.h"

AABB::AABB(float minX, float maxX, float minY, float maxY)
{
	this->minX = minX;
	this->maxX = maxX;
	this->minY = minY;
	this->maxY = maxY;
}

bool AABB::IsOverlapping(AABB other)
{
	return (minX < other.maxX) && (maxX > other.minX) && (minY < other.maxY) && (maxY > other.minY);
}
