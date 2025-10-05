#include "utils/common.hpp"
#include "utils/hittable.hpp"
#include "utils/hittable_list.hpp"
#include "utils/shapes/sphere.hpp"
#include "utils/vec3.hpp"
#include <memory>

constexpr int image_width = 1080;
constexpr double aspect_ratio = 16.0 / 9.0;

Color ray_color(const Ray &r, const Hittable &world) {
  HitRecord rec;
  if (world.hit(r, 0, infinty, rec)) {
    return 0.5 * (rec.normal + Color(1, 1, 1));
  }

  Vec3 unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}

int main(int argc, char *argv[]) {
  int image_height = (double)image_width / aspect_ratio;
  // ensure image height is atleast 1
  image_height = image_height < 1 ? 1 : image_height;

  int focal_len = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * (double)image_width / (double)image_height;

  Point3 camera_center(0.0, 0.0, 0.0);

  Vec3 viewport_u(viewport_width, 0, 0);
  Vec3 viewport_v(0, -viewport_height, 0);

  Vec3 pixel_delta_u = viewport_u / image_width;
  Vec3 pixel_delta_v = viewport_v / image_height;

  Point3 viewport_upper_left =
      camera_center - Vec3(0, 0, focal_len) - viewport_u / 2 - viewport_v / 2;
  Point3 pixel_00 = viewport_upper_left + 0.5 * (pixel_delta_v + pixel_delta_u);

  HittableList world;
  world.push_back(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.push_back(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int y = 0; y < image_height; y++) {
    // DEBUG
    std::clog << "Scan lines remaining : " << (image_height - y) << '\n'
              << std::flush;
    for (int x = 0; x < image_width; x++) {
      Point3 pixel_center =
          pixel_00 + (x * pixel_delta_u) + (y * pixel_delta_v);
      Ray ray(camera_center, pixel_center);

      Color pixel_color = ray_color(ray, world);
      write_color(std::cout, pixel_color);
    }
  }
  return 0;
}
