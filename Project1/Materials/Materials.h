#pragma once
#include "../glm/gtc/quaternion.hpp"
#include "../HitRecord.h"
#include "../ScatteringRecord.h"
#include "../GCC_RNG.h"
class BaseMaterial
{
public:
	CRandom MyRandom;
	virtual ScatteringRecord Scatter(const Ray& r_in, const HitRecord& rec) = 0;

	vec3 GenerateRandomVectorInCone(vec3 axis, float maxAngle)
	{
		// Step 3: Generate random azimuth angle
		float azimuth = MyRandom.Random(2.0f * MY_PI);

		// Step 4: Generate random inclination angle
		float inclination = MyRandom.Random(DegToRad(maxAngle));

		// Step 5: Convert angles to Cartesian coordinates
		float x = sin(inclination) * cos(azimuth);
		float y = sin(inclination) * sin(azimuth);
		float z = cos(inclination);

		// Step 6: Create the resulting vector by combining coordinates with the axis
		//Vector3 coneVector = Quaternion.LookRotation(axis) * new Vector3(x, y, z);

		vec3 Up = { 0,1,0 };
		vec3 NewVec = { x,y,z };
		vec3 ConeVec = glm::quatLookAt(axis, Up) * NewVec;
		return ConeVec;
	}



};
