#pragma once


#include "Utils.h"

class Ray
{
public:
	constexpr Ray() = default;

	Ray(const point3 _origin, const vec3 _direction)
	{
		origin = _origin;
		direction = glm::normalize(_direction);
	}

	point3 origin{ 0, 0, 0 };
	vec3 direction{ 0, 0, 0 };

	constexpr point3 At(const float t) const 
	{ 
		return origin + direction * t; 
	}
};
