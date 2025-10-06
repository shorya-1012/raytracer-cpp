#pragma once

#include "intervals.hpp"
#include "vec3.hpp"

using Color = Vec3;

inline void write_color(std::ostream &out, const Color &pixel_color) {
  // Translate the [0,1] component values to the byte range [0,255].
  const Interval intensity(0.0, 0.999);
  int rbyte = int(256 * intensity.clamp(pixel_color.x()));
  int gbyte = int(256 * intensity.clamp(pixel_color.y()));
  int bbyte = int(256 * intensity.clamp(pixel_color.z()));

  // Write out the pixel color components.
  out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
