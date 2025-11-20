#pragma once

#include "color.hpp"
#include "common.hpp"
#include "hittable.hpp"
#include "material.hpp"
#include "vec3.hpp"
#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>

class Camera {
public:
  int image_width;
  int image_height;
  double aspect_ratio;
  int samples_per_pixel;
  int max_recursion_depth;
  std::vector<unsigned char> framebuffer;

  Camera(int width, double aspect_ratio, int samples_per_pixel)
      : image_width(width), aspect_ratio(aspect_ratio),
        samples_per_pixel(samples_per_pixel), max_recursion_depth(50) {}

  void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (size_t y = 0; y < image_height; y++) {
      for (size_t x = 0; x < image_width; x++) {
        size_t index = (y * image_width + x) * 3;
        float r = framebuffer[index + 0] / 255.0f;
        float g = framebuffer[index + 1] / 255.0f;
        float b = framebuffer[index + 2] / 255.0f;

        glColor3f(r, g, b);
        float gl_x = (float)x / (image_width / 2.0f) - 1.0f;
        float gl_y = 1.0f - (float)y / (image_height / 2.0f);
        glVertex2f(gl_x, gl_y);
      }
    }
    glEnd();
    glFlush();
  }

  void render(const Hittable &world) {
    init();

    framebuffer.resize(image_width * image_height * 3);

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int y = 0; y < image_height; y++) {
      // DEBUG
      std::clog << "Scan lines remaining : " << (image_height - y) << '\n'
                << std::flush;
      for (int x = 0; x < image_width; x++) {
        Color pixel_color(0.0, 0.0, 0.0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          Ray r = get_ray(x, y);
          pixel_color += ray_color(r, world, max_recursion_depth);
        }
        size_t index = (y * image_width + x) * 3;

        write_to_framebuffer(framebuffer, pixel_sample_scale * pixel_color,
                             index);
      }
    }
  }

private:
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

  Color ray_color(const Ray &r, const Hittable &world, int curr_depth) {
    // Limit recursion
    if (curr_depth <= 0)
      return Color(0, 0, 0);

    HitRecord rec;
    if (world.hit(r, Interval(0.001, infinty), rec)) {
      Ray scattered;
      Color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered)) {
        return attenuation * ray_color(scattered, world, curr_depth - 1);
      }
      return Color(0, 0, 0);
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
