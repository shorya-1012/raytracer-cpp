#pragma once

#include "vec3.hpp"

class Ray {
private:
  Point3 _origin;
  Vec3 _direction;

public:
  Ray() {}
  Ray(const Point3 &origin, const Vec3 &dir)
      : _origin(origin), _direction(dir) {}

  const Point3 &origin() const { return _origin; }
  const Point3 &direction() const { return _direction; }

  const Point3 at(double t) const { return _origin + t * _direction; }
};
