#include "../Materials/Metal.h"
#include "../glm/gtc/epsilon.hpp"
#include "../glm/gtc/random.hpp"



ScatteringRecord Metal::Scatter(const Ray& r_in, const HitRecord& rec)
{
	ScatteringRecord empty_result{};
	empty_result.IsValid = false;

	//vec3 new_direction = glm::reflect(r_in.direction, rec.normal) + m_fuzzyness * sphericalRand(1.0f);
	vec3 new_direction = glm::reflect(r_in.direction, rec.normal) + m_fuzzyness * GenerateRandomVectorInCone(rec.normal, 90.0f);

	if (glm::dot(new_direction, rec.normal) > 0)
	{
		return ScatteringRecord{ true, m_albedo, Ray{rec.p, new_direction} };
	}

	return empty_result;
}
