#pragma once

#include <array>
#include "Shapes.h"

class Plane : public BaseShape
{
public:
	Plane() = default;
	Plane(const point3& point, const float polar, const float azimuth);
	Plane(const point3& point, glm::vec3 normal);
	explicit Plane(std::array<point3, 3> points);

	inline float Polar() const { return m_polar; }
	inline float Azimuth() const { return m_azimuth; }
	glm::vec3 Normal() const { return m_normal; }

	point3 Origin() const { return m_point; }

	float FastHit(const Ray& r, const float t_min, const float t_max) override;
	HitRecord ComputeHitRecord(const Ray& r, const float t) override;
	HitRecord Hit(const Ray& r, const float t_min, const float t_max) override;
	AABB BoundingBox() override 
	{ 
		AABB Result;
		Result.IsValid = false;
		return Result;
	};


	point3 m_point{};
	glm::vec3 m_normal{};
	float m_polar{};
	float m_azimuth{};

};

