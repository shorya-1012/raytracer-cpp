#pragma once

#include "hittable.hpp"
#include <memory>
#include <vector>

class HittableList : public Hittable {
public:
  std::vector<std::shared_ptr<Hittable>> objects;

  HittableList() {}
  HittableList(std::shared_ptr<Hittable> object) { push_back(object); }

  void push_back(std::shared_ptr<Hittable> object) {
    objects.push_back(object);
  }
  void clear() { objects.clear(); }

  virtual bool hit(const Ray &ray, double t_min, double t_max,
                   HitRecord &rec) const override {
    bool hit_anything = false;
    HitRecord temp_rec;
    double closest = t_max;

    for (const auto &object : objects) {
      if (object->hit(ray, t_min, closest, temp_rec)) {
        hit_anything = true;
        closest = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  }
};
