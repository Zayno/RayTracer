#pragma once

#include <vector>

#include "HittableObject.h"

class HittableObjectList
{
public:
	HittableObjectList() = default;

	void Clear() { m_objects.clear(); }
	void Add(const HittableObject& NewHittableObj);

	bool Hit(const Ray& r, float t_min, float t_max, 
		HitRecord& HitRecordResult, ScatteringRecord& ScaatterignRecordResult);

	const std::vector<HittableObject>& Objects() const { return m_objects; }


	std::vector<HittableObject> m_objects;
};

