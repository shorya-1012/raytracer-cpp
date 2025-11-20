#include "utils/camera.hpp"
#include "utils/hittable_list.hpp"
#include "utils/material.hpp"
#include "utils/shapes/sphere.hpp"
#include "utils/vec3.hpp"
#include <GL/glut.h>
#include <iostream>
#include <memory>

constexpr int image_width = 1280;
constexpr double aspect_ratio = 16.0 / 9.0;

Camera *g_cam = nullptr;

void display_callback() {
  if (g_cam)
    g_cam->display();
}

std::shared_ptr<Material> create_material() {
  int choice;
  std::cout << "\nChoose material type:\n";
  std::cout << "1. Lambertian (Diffuse)\n";
  std::cout << "2. Metal\n";
  std::cout << "Enter choice: ";
  std::cin >> choice;

  double r, g, b;
  std::cout << "Enter color (r g b, values 0–1): ";
  std::cin >> r >> g >> b;

  if (choice == 2) {
    double fuzz;
    std::cout << "Enter fuzziness (0–1): ";
    std::cin >> fuzz;
    return std::make_shared<Metal>(Color(r, g, b), fuzz);
  }

  // Default to Lambertian
  return std::make_shared<Lambertian>(Color(r, g, b));
}

int main(int argc, char *argv[]) {
  int n;
  std::cout << "Enter number of spheres: ";
  std::cin >> n;

  HittableList world;

  // Ground sphere
  auto ground_material = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  world.push_back(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0,
                                           ground_material));

  for (int i = 0; i < n; ++i) {
    double x, y, z, radius;
    std::cout << "\nSphere " << i + 1 << ":\n";
    std::cout << "Enter position (x y z): ";
    std::cin >> x >> y >> z;
    std::cout << "Enter radius: ";
    std::cin >> radius;

    auto mat = create_material();
    world.push_back(std::make_shared<Sphere>(Point3(x, y, z), radius, mat));
  }

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
