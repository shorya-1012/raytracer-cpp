#pragma once

#include "../hittable.hpp"

class Sphere : public Hittable {
private:
  Point3 center;
  double radius;

public:
  Sphere(Point3 center, double radius) : center(center), radius(radius) {}

  bool hit(const Ray &ray, double t_min, double t_max,
           HitRecord &rec) const override {
    Vec3 oc = center - ray.origin();
    double a = ray.direction().length_squared();
    double h = dot(ray.direction(), oc);
    double c = oc.length_squared() - radius * radius;

    double discriminant = h * h - a * c;
    if (discriminant < 0.0) {
      return false;
    }

    double discriminant_sqrt = std::sqrt(discriminant);

    double root = (h - discriminant_sqrt) / a;
    if (root <= t_min || root >= t_max) {
      root = (h + discriminant_sqrt) / a;
      if (root <= t_min || root >= t_max)
        return false;
    }

    rec.t = root;
    rec.p = ray.at(root);
    Vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(outward_normal, ray);

    return true;
  }
};
