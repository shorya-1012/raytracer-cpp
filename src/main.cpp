#include "utils/color.h"
#include "utils/ray.h"
#include "utils/vec3.h"

constexpr int image_width = 400;
const double aspect_ratio = 16.0 / 9.0;

Color color_ray(const Ray &ray) {
  Vec3 unit_direction = unit_vector(ray.direction());
  double a = 0.5 * (unit_direction.y() + 1.0);
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
  Vec3 pixel_delta_v = viewport_v / image_width;

  Point3 viewport_upper_left =
      camera_center - Vec3(0, 0, focal_len) - viewport_u / 2 - viewport_v / 2;

  Point3 pixel_00 = viewport_upper_left + 0.5 * (pixel_delta_v + pixel_delta_u);

  std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
  for (int y = 0; y < image_height; y++) {
    // DEBUG
    std::clog << "Scan lines remaining : " << (image_height - y) << '\n'
              << std::flush;
    for (int x = 0; x < image_width; x++) {
      Point3 pixel_center =
          pixel_00 + (x * pixel_delta_u) + (y * pixel_delta_v);
      Ray ray(camera_center, pixel_center);
      write_color(std::cout, color_ray(ray));
    }
  }
  return 0;
}
