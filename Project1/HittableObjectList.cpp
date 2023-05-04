#include "HittableObjectList.h"

void HittableObjectList::Add(const HittableObject& NewHittableObj)
{
	m_objects.push_back(NewHittableObj);
}

bool HittableObjectList::Hit(const Ray& r, float t_min, float t_max,
	HitRecord& HitRecordResult, ScatteringRecord& ScaatterignRecordResult)
{

	float closest_t = t_max;
	const HittableObject* closest_obj = nullptr;

	for (auto& object : m_objects)
	{
		float temp_t = object.m_pShape->FastHit(r, t_min, closest_t);

		if (temp_t < closest_t)
		{
			closest_obj = &object;
			closest_t = temp_t;
		}
	}

	if (!closest_obj)
	{
		return false;
	}
	else
	{
		HitRecordResult = closest_obj->m_pShape->ComputeHitRecord(r, closest_t);
		ScaatterignRecordResult = closest_obj->m_pMaterial->Scatter(r, HitRecordResult);

		return true;


	}
}
