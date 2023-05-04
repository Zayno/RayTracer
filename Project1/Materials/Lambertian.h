#pragma once

#include "Materials.h"

class Lambertian :public BaseMaterial
{
  friend bool operator==(const Lambertian &lhs, const Lambertian &rhs);

public:
  explicit Lambertian(const color &albedo) : m_albedo(albedo) {}

  ScatteringRecord Scatter(const Ray &r_in, const HitRecord &rec) override;

  color m_albedo;
};

inline bool operator==(const Lambertian &lhs, const Lambertian &rhs) { return lhs.m_albedo == rhs.m_albedo; }

