#pragma once

// common header files
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

#include "ray.hpp"
#include "vec3.hpp"

// constants
constexpr double infinty = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// util functions
inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  static std::uniform_real_distribution<double> dist(0.0, 1.0);
  static std::mt19937 generator;
  return dist(generator);
}

inline double random_double(double min, double max) {
  return min + (max - min) * random_double();
}
