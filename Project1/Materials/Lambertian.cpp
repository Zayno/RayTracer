#include "../Materials/Lambertian.h"
#include "../glm/gtc/epsilon.hpp"
#include "../glm/gtc/random.hpp"




ScatteringRecord Lambertian::Scatter(const Ray& r_in, const HitRecord& rec)
{
	//vec3 scatter_direction = rec.normal + sphericalRand(1.0f);
	vec3 scatter_direction = rec.normal + GenerateRandomVectorInCone(rec.normal, 90.0f);

	// Catch degenerate scatter direction
	if (glm::any(glm::epsilonEqual(scatter_direction, vec3{ 0, 0, 0 }, std::numeric_limits<float>::epsilon())))
		scatter_direction = rec.normal;

	return ScatteringRecord{ true, m_albedo, Ray{rec.p, scatter_direction} };
}
