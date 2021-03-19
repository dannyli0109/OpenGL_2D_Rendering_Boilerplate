#pragma once
class AABB
{
public:
	AABB() = default;
	AABB(float minX, float maxX, float minY, float maxY);
	bool IsOverlapping(AABB other);

	float minX, maxX, minY, maxY;
};

