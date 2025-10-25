#include "utils/camera.hpp"
#include "utils/hittable_list.hpp"
#include "utils/material.hpp"
#include "utils/shapes/sphere.hpp"
#include "utils/vec3.hpp"
#include <memory>

constexpr int image_width = 400;
constexpr double aspect_ratio = 16.0 / 9.0;

Camera *g_cam = nullptr;

void display_callback() {
  if (g_cam)
    g_cam->display();
}

int main(int argc, char *argv[]) {

  auto ground_material = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto center_material = std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
  auto left_material = std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
  auto right_material = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

  HittableList world;
  world.push_back(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0,
                                           ground_material));
  world.push_back(
      std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, center_material));
  world.push_back(
      std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, left_material));
  world.push_back(
      std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, right_material));

  Camera camera(image_width, aspect_ratio, 10);
  camera.render(world);
  g_cam = &camera;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(camera.image_width, camera.image_height);
  glutCreateWindow("Ray Tracer Output");

  glutDisplayFunc(display_callback);
  glutMainLoop();

  return 0;
}
