#pragma once

#include "../HitRecord.h"
#include "../ScatteringRecord.h"


class BaseMaterial
{
public:

	virtual ScatteringRecord Scatter(const Ray& r_in, const HitRecord& rec) = 0;


};

