#pragma once

#include "Materials.h"

class Metal : public BaseMaterial
{
  friend bool operator==(const Metal &lhs, const Metal &rhs);

public:
  explicit Metal(const color &albedo, const float fuzzyness)
      : m_albedo(albedo), m_fuzzyness{fuzzyness < 1.0f ? fuzzyness : 1.0f} {}

  ScatteringRecord Scatter(const Ray &r_in, const HitRecord &rec) override;

  color m_albedo;
  float m_fuzzyness{1.0f};
};

inline bool operator==(const Metal &lhs, const Metal &rhs) 
{
  return (lhs.m_albedo == rhs.m_albedo) && (lhs.m_fuzzyness && rhs.m_fuzzyness);
}

