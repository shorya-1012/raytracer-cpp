#pragma once

// common header files
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

// constants
constexpr double infinty = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// util functions
inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}
