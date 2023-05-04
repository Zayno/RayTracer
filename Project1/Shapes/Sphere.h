#pragma once

#include "Shapes.h"
#include "AABB.h"

class Sphere : public BaseShape
{
public:
	Sphere() = default;
	Sphere(point3 center, float radius) : m_center{ center }, m_radius{ radius }, m_sqRadius{ m_radius * m_radius } 
	{
		m_BoundingBox.m_a = { m_center - vec3(m_radius, m_radius, m_radius) };
		m_BoundingBox.m_b = { m_center + vec3(m_radius, m_radius, m_radius) };
	}

	float FastHit(const Ray& r, const float t_min, const float t_max) override;
	HitRecord ComputeHitRecord(const Ray& r, const float t)override;
	HitRecord Hit(const Ray& r, const float t_min, const float t_max)override;
	AABB BoundingBox() override;

public:
	point3 m_center{ 0, 0, 0 };
	float m_radius{ 0 };
	float m_sqRadius{ 0 };
	AABB m_BoundingBox;
};
