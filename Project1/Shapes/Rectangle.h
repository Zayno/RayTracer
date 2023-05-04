#pragma once

#include "../Shapes/Parallelogram.h"

class Rectangle : public Parallelogram 
{
public:
  Rectangle() : Parallelogram() {}
  explicit Rectangle(std::array<point3, 3> points);
};
