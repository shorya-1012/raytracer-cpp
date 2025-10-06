#pragma once

#include "color.hpp"
#include "common.hpp"
#include "hittable.hpp"
// #include <cam>

class Camera {
public:
  int image_width;
  double aspect_ratio;
  int samples_per_pixel;

  Camera(int width, double aspect_ratio, int samples_per_pixel)
      : image_width(width), aspect_ratio(aspect_ratio),
        samples_per_pixel(samples_per_pixel) {}

  void render(const Hittable &world) {
    init();

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int y = 0; y < image_height; y++) {
      // DEBUG
      std::clog << "Scan lines remaining : " << (image_height - y) << '\n'
                << std::flush;
      for (int x = 0; x < image_width; x++) {
        Color pixel_color(0.0, 0.0, 0.0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          Ray r = get_ray(x, y);
          pixel_color += ray_color(r, world);
        }
        write_color(std::cout, pixel_sample_scale * pixel_color);
      }
    }
  }

private:
  int image_height;
  Point3 camera_center;
  Point3 pixel_00;
  Point3 pixel_delta_u;
  Point3 pixel_delta_v;
  double pixel_sample_scale;

  void init() {
    image_height = (double)image_width / aspect_ratio;
    // ensure image height is atleast 1
    image_height = image_height < 1 ? 1 : image_height;

    camera_center = Point3(0.0, 0.0, 0.0);

    pixel_sample_scale = 1.0 / samples_per_pixel;

    // calculate viewport dimensions
    int focal_len = 1.0;
    double viewport_height = 2.0;
    double viewport_width =
        viewport_height * (double)image_width / (double)image_height;

    Vec3 viewport_u(viewport_width, 0, 0);
    Vec3 viewport_v(0, -viewport_height, 0);

    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    Point3 viewport_upper_left =
        camera_center - Vec3(0, 0, focal_len) - viewport_u / 2 - viewport_v / 2;
    pixel_00 = viewport_upper_left + 0.5 * (pixel_delta_v + pixel_delta_u);
  }

  Color ray_color(const Ray &r, const Hittable &world) {
    HitRecord rec;
    if (world.hit(r, Interval(0, infinty), rec)) {
      return 0.5 * (rec.normal + Color(1, 1, 1));
    }

    Vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
  }

  Ray get_ray(int x, int y) const {
    Vec3 offset = sample_square();
    auto pixel_sample = pixel_00 + ((x + offset.x()) * pixel_delta_u) +
                        ((y + offset.y()) * pixel_delta_v);

    Vec3 ray_origin = camera_center;
    Vec3 ray_dir = pixel_sample - ray_origin;

    return Ray(ray_origin, ray_dir);
  }

  Vec3 sample_square() const {
    return Vec3(random_double() - 0.5, random_double() - 0.5, 0.0);
  }
};
