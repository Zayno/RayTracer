#pragma once

#include "Ray.h"

struct HitRecord
{
	bool IsValid = false;
	float t;
	point3 p;
	vec3 normal;
	bool front_face;

	void SetFaceNormal(const Ray& r, const vec3& outward_normal)
	{
		front_face = glm::dot(r.direction, outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

