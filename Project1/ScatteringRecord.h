#pragma once

#include "Ray.h"
#include "Utils.h"


struct ScatteringRecord
{
	bool IsValid = false;
	color attenuation{ 0, 0, 0 };
	Ray ray{};
};

