#pragma once

#include "color.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class Material {
public:
  virtual ~Material() = default;

  virtual bool scatter(const Ray &r_in, const HitRecord hit_rec,
                       Color &attenuation, Ray &scattered) const {
    return false;
  }
};

class Lambertian : public Material {
  Color albedo;

public:
  Lambertian(const Color &albedo) : albedo(albedo) {}
  bool scatter(const Ray &r_in, const HitRecord hit_rec, Color &attenuation,
               Ray &scattered) const override {
    Vec3 scatter_dir = hit_rec.normal + random_unit_vector();
    if (scatter_dir.is_near_zero()) {
      scatter_dir = hit_rec.normal;
    }
    scattered = Ray(hit_rec.p, scatter_dir);
    attenuation = albedo;
    return true;
  }
};

class Metal : public Material {
  Color albedo;

public:
  Metal(const Color &albedo) : albedo(albedo) {}

  bool scatter(const Ray &r_in, const HitRecord hit_rec, Color &attenuation,
               Ray &scattered) const override {
    Vec3 reflected = reflect(r_in.direction(), hit_rec.normal);
    scattered = Ray(hit_rec.p, reflected);
    attenuation = albedo;
    return true;
  }
};
