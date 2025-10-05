#pragma once

#include "intervals.hpp"
#include "ray.hpp"

struct HitRecord {
  Point3 p;
  Vec3 normal;
  double t;
  bool front_face;

  void set_face_normal(const Vec3 &outward_normal, const Ray &ray) {
    bool front_face = dot(ray.direction(), outward_normal) < 0.0;
    this->normal = front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual ~Hittable() = default;

  virtual bool hit(const Ray &ray, Interval ray_t, HitRecord &rec) const = 0;
};
