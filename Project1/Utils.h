#pragma once

#define GLM_FORCE_SIMD_AVX2

#include "glm.hpp"
#include <random>
using namespace glm;

#include "GCC_RNG.h"
// Constants
constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float MY_PI = 3.1415926535897932385f;

// Utility Functions
inline float DegToRad(float degrees) { return degrees * MY_PI / 180.0f; }
#define LARGE_FLOAT 1000.0f
#define LARGE_FLOATMinus1 999.0f

template <typename T, qualifier Q> float polar(glm::vec<3, T, Q> vec)
{
	return MY_PI - vec.z / std::sqrt(glm::dot(vec, vec));
}

template <typename T, qualifier Q> float azimuth(glm::vec<3, T, Q> vec)
{
	return std::atan2(vec.x, vec.y);
}


using vec3 = glm::vec3;
using point3 = glm::vec3;
using color = glm::vec3;


