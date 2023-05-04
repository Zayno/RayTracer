#pragma once

#include "Materials.h"


class Dielectric : public BaseMaterial
{
  friend bool operator==(const Dielectric &lhs, const Dielectric &rhs);

public:
  explicit Dielectric(const float refractionIndex)
      : m_refractionIndex(refractionIndex), m_invRefractionIndex(1.0f / m_refractionIndex) {}

  ScatteringRecord Scatter(const Ray &r_in, const HitRecord &rec) override;

  float m_refractionIndex;
  float m_invRefractionIndex;

  static float Reflectance(const float cosine, const float refractionIndex) 
  {
    // Use Schlick's approximation for reflectance.
    float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * std::pow((1.0f - cosine), 5.0f);
  }
};

inline bool operator==(const Dielectric &lhs, const Dielectric &rhs) 
{
  return lhs.m_invRefractionIndex == rhs.m_refractionIndex;
}

