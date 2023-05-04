#pragma once

#include "../HitRecord.h"
#include "../Utils.h"
#include "../Shapes/AABB.h"


class BaseShape
{
public:

	virtual float FastHit(const Ray& r, const float t_min, const float t_max) = 0;
	virtual HitRecord ComputeHitRecord(const Ray& r, const float t) = 0;
	virtual HitRecord Hit(const Ray& r, const float t_min, const float t_max) = 0;
	virtual AABB BoundingBox() = 0;


};

