#pragma once

#include "intervals.hpp"
#include "vec3.hpp"
#include <cmath>

using Color = Vec3;

inline double linear_to_gamma(double linear_comp) {
  if (linear_comp > 0)
    return std::sqrt(linear_comp);
  return 0;
}

inline void write_color(std::ostream &out, const Color &pixel_color) {
  // Translate the [0,1] component values to the byte range [0,255].
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // Apply gamma transform (gamma 2)
  r = linear_to_gamma(r);
  g = linear_to_gamma(g);
  b = linear_to_gamma(b);

  const Interval intensity(0.0, 0.999);
  int rbyte = int(256 * intensity.clamp(r));
  int gbyte = int(256 * intensity.clamp(g));
  int bbyte = int(256 * intensity.clamp(b));

  // Write out the pixel color components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
