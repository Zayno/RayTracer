#pragma once

#include "../HitRecord.h"
#include "../Utils.h"

class AABB
{
public:
	AABB() = default;
	AABB(point3 a, point3 b) : m_a{ a }, m_b{ b } {}

	point3 A() const { return m_a; }
	point3 B() const { return m_b; }

	float FastHit(const Ray& r, const float t_min, const float t_max) const;
	bool IsValid = false;

	point3 m_a;
	point3 m_b;
};

