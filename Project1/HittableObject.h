#pragma once

#include "Materials/Materials.h"
#include "Shapes/Shapes.h"

#include "Ray.h"


class HittableObject
{

public:
	HittableObject(BaseShape* pShape, BaseMaterial* pMat)
	{
		m_pShape = pShape;
		m_pMaterial = pMat;

	}

	virtual ~HittableObject() = default;

	BaseShape* m_pShape;
	BaseMaterial* m_pMaterial;
};

