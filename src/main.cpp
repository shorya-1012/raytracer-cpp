#include "color.h"
#include "vec3.h"

constexpr int image_widht = 256;
constexpr int image_height = 256;

int main(int argc, char *argv[]) {
  std::cout << "P3\n" << image_widht << " " << image_height << "\n255\n";
  for (int y = 0; y < image_height; y++) {
    // DEBUG
    std::clog << "Scan lines remaining : " << (image_height - y) << '\n'
              << std::flush;
    for (int x = 0; x < image_widht; x++) {
      auto pixel_color = Color(double(x) / (image_widht - 1),
                               double(y) / (image_height - 1), 0.0);
      write_color(std::cout, pixel_color);
    }
  }
  return 0;
}
