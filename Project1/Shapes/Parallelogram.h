#pragma once

#include <array>
#include "Shapes.h"

#include "../Shapes/Plane.h"

class Parallelogram : public BaseShape
{
public:
	Parallelogram() = default;
	virtual ~Parallelogram() = default;

	explicit Parallelogram(std::array<point3, 3> points);

	Plane GetPlane() const { return m_plane; };

	std::array<point3, 4> Vertices() const;

	float FastHit(const Ray& r, const float t_min, const float t_max) override;
	HitRecord ComputeHitRecord(const Ray& r, const float t) override;
	HitRecord Hit(const Ray& r, const float t_min, const float t_max) override;
	AABB BoundingBox() override;


	Plane m_plane{};          // The origin of this plane lies on one vertex of the parallelogram
	std::array<vec3, 2> m_vertices{}; // Coordinates of two vertices w.r.t. the origin of the plane
};

