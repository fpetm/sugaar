#include "sugaar.hpp"

#include <chrono>
#include <thread>

#include "camera.hpp"
#include "hittable_list.hpp"
#include "image.hpp"
#include "material.hpp"
#include "math.hpp"
#include "ray.hpp"
#include "sphere.hpp"

using namespace sugaar;

HittableList random_scene() {
  HittableList world;

  auto ground_material = std::make_shared<Lambertian>(Vec4(0.5, 0.5, 0.5, 1.0));
  world.add(std::make_shared<Sphere>(Vec3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      const auto choose_mat = random_double();
      Vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - Vec3(4, 0.2, 0)).length() > 0.9) {
        std::shared_ptr<Material> sphere_material;

        if (choose_mat < 0.8) {
          Vec4 albedo(Vec3::random() * Vec3::random(), 1.0);
          sphere_material = std::make_shared<Lambertian>(albedo);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          Vec4 albedo(Vec3::random(0.5, 1), 1.0);
          auto fuzz = random_double(0, 0.5);
          sphere_material = std::make_shared<Metal>(albedo, fuzz);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<Dielectric>(1.5);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<Dielectric>(1.5);
  world.add(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<Lambertian>(Vec4(0.4, 0.2, 0.1, 1.0));
  world.add(std::make_shared<Sphere>(Vec3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<Metal>(Vec4(0.7, 0.6, 0.5, 1.0), 0.0);
  world.add(std::make_shared<Sphere>(Vec3(4, 1, 0), 1.0, material3));

  return world;
}

inline Vec4 adjust_color(Vec4 color, int samples_per_pixel = 1,
                         double gamma = 2.0) {
  Vec4 c;
  c[0] = pow(color[0] / samples_per_pixel, 1 / gamma);
  c[1] = pow(color[1] / samples_per_pixel, 1 / gamma);
  c[2] = pow(color[2] / samples_per_pixel, 1 / gamma);
  c[3] = pow(color[3] / samples_per_pixel, 1 / gamma);
  return c;
}

Vec4 ray_color(const Ray &r, const Hittable &world, int depth) {
  HitRecord rec;

  if (depth <= 0) return Vec4{0, 0, 0, 0};

  if (world.hit(r, 0.001, infinity, rec)) {
    Ray scattered;
    Vec4 attenuation;

    if (rec.material_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);

    return Vec4{0, 0, 0, 0};
  }

  Vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.Y() + 1.0);
  return (1.0 - t) * Vec4(1.0, 1.0, 1.0, 1.0) + t * Vec4(0.3, 0.4, 0.5, 1.0);
}

int main() {
  constexpr int samples_per_pixel = 256;
  constexpr int max_depth = 64;

  Image img(width, height);

  HittableList world = random_scene();

  const Vec3 lookfrom(13, 2, 3);
  const Vec3 lookat(0, 0, 0);
  const Vec3 vup(0, 1, 0);
  const auto dist_to_focus = 10.0;
  const double aperture = 0.1;
  const Camera cam(lookfrom, lookat, vup, pi / 9, aspect_ratio, aperture,
             dist_to_focus);

  const auto start = std::chrono::high_resolution_clock::now();

  std::array<std::thread, height> threads;
  for (int y = 0; y < height; y++) {
    threads[y] =
        std::thread([&img, &cam, &world, y, max_depth, samples_per_pixel]() {
          for (int x = 0; x < width; x++) {
            Vec4 pixel_color(0, 0, 0, 0);
            for (int s = 0; s < samples_per_pixel; s++) {
              auto u = (double(x) + random_double()) / ((double)(width - 1));
              auto v = (double(y) + random_double()) / ((double)(height - 1));
              Ray r = cam.get_ray(u, v);
              pixel_color += ray_color(r, world, max_depth);
            }
            img.set(x, y, adjust_color(pixel_color, samples_per_pixel));
          }
        });
  }

  for (int y = 0; y < height; y++) {
    threads[y].join();
  }

  const auto end = std::chrono::high_resolution_clock::now();

  img.save("sugaar.png");

  const auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Finished rendering a " << width << "x" << height << " ("
            << samples_per_pixel << " samples per pixel) image in "
            << duration.count() / 1000.0 << " seconds.\n"
            << std::endl;

  return 0;
}
