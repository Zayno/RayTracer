#include <random>

#include "../Materials/Dielectric.h"

extern color white;
extern color azure;

// rng stuff
static std::mt19937 m_rnGenerator{};
static std::uniform_real_distribution<float> m_unifDistribution{ 0.0f, 1.0f };


ScatteringRecord Dielectric::Scatter(const Ray& r_in, const HitRecord& rec)
{
	const float refraction_ratio = rec.front_face ? m_invRefractionIndex : m_refractionIndex;

	const float cos_theta = -1.0f * glm::dot(r_in.direction, rec.normal);
	const float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);

	bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
	if (cannot_refract || Reflectance(cos_theta, refraction_ratio) > m_unifDistribution(m_rnGenerator)) 
	{
		return ScatteringRecord{ true, white, Ray{rec.p, glm::reflect(r_in.direction, rec.normal)} };
	}
	else 
	{
		return ScatteringRecord{ true, white, Ray{rec.p, glm::refract(r_in.direction, rec.normal, refraction_ratio)} };
	}
}
