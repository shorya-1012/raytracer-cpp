#include "vec3.h"

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

  Point3 at(double t) { return _origin + t * _direction; }
};

//
// w   = 16
// h   =  9
// h = w * 9 / 16
