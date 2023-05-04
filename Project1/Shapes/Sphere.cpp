#include "AABB.h"
#include "../Shapes/Sphere.h"



float Sphere::FastHit(const Ray& r, const float t_min, const float t_max) 
{
	vec3 oc = r.origin - m_center;

	// In the following computations we solve a quadratic equation in the usual way
	// However the 2nd order coefficient "a" is the length of the ray direction, which
	// is 1 by construction. If the following computations don't look right, it's because
	// "a" is optimized away :)
	// I'll leave the original version commented out...

	// const float a = glm::dot(r.direction, r.direction); // 1 by construction!
	float half_b = glm::dot(oc, r.direction);
	// const float c = glm::dot(oc, oc) - m_radius * m_radius;

	// const float discriminant = half_b * half_b - a * c;
	float discriminant = half_b * half_b - glm::dot(oc, oc) + m_sqRadius;
	if (discriminant < 0)
		return LARGE_FLOAT;

	float sqrtd = std::sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	float root = -half_b - sqrtd;
	if (root < t_min || t_max < root) 
	{
		root = -half_b + sqrtd;
		if (root < t_min || t_max < root)
			return LARGE_FLOAT;
	}

	return root;
}

HitRecord Sphere::ComputeHitRecord(const Ray& r, const float t) 
{
	HitRecord result{};
	result.t = t;
	result.p = r.At(result.t);
	vec3 outward_normal = glm::normalize(result.p - m_center);

	// NOTE: I really don't like this, the book author is using negative radius to artificially invert all normals of the
	// sphere, so he can model hollow spheres...
	outward_normal *= sign(m_radius);

	result.SetFaceNormal(r, outward_normal);
	result.IsValid = true;
	return result;
}

HitRecord Sphere::Hit(const Ray& r, const float t_min, const float t_max) 
{
	float t = FastHit(r, t_min, t_max);
	if ( t < LARGE_FLOATMinus1)
	{
		return ComputeHitRecord(r, t);
	}
	else 
	{
		HitRecord result{};
		result.IsValid = false;
		return result;
	}
}

AABB Sphere::BoundingBox() 
{
	return m_BoundingBox;
}
