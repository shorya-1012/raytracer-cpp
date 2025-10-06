#include "utils/camera.hpp"
#include "utils/hittable_list.hpp"
#include "utils/shapes/sphere.hpp"
#include "utils/vec3.hpp"
#include <memory>

constexpr int image_width = 400;
constexpr double aspect_ratio = 16.0 / 9.0;

int main(int argc, char *argv[]) {
  HittableList world;
  world.push_back(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5));
  world.push_back(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100));

  Camera camera(image_width, aspect_ratio, 10);

  camera.render(world);

  return 0;
}
