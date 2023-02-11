#include "sugaar.hpp"
#include "math.hpp"
#include "image.hpp"
#include "ray.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "camera.hpp"

constexpr std::uint32_t width = 1280;
constexpr std::uint32_t height = 720;

using namespace sugaar;

Vec4 ray_color(const Ray& r, const Hittable& world, int depth) {
	HitRecord rec;

	if (depth <= 0) return Vec4(0, 0, 0, 0);

	if (world.hit(r, 0.001, infinity, rec)) {
		Ray scatttered;
		Vec4 attenuation;

		if (rec.material_ptr->scatter(r, rec, attenuation, scatttered))
			return attenuation * ray_color(scatttered, world, depth - 1);

		return Vec4(0, 0, 0, 0);
	}

	Vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.Y() + 1.0);
	return (1.0 - t) * Vec4(1.0, 1.0, 1.0, 1.0) + t * Vec4(0.3, 0.4, 0.5, 1.0);
}

int main() {
	Camera cam((double)width/(double)height, 2.0, 1.0);
	const int samples_per_pixel = 50;
	const int max_depth = 5;

	Image img(width, height);

	HittableList world;
	
	auto material_ground = std::make_shared<Lambertian>(Vec4(0.8, 0.8, 0.0, 1.0));
	auto material_center = std::make_shared<Lambertian>(Vec4(0.7, 0.3, 0.3, 1.0));
	auto material_left = std::make_shared<Metal>(Vec4(0.8, 0.8, 0.8, 1.0), 0.3);
	auto material_right = std::make_shared<Metal>(Vec4(0.8, 0.6, 0.2, 1.0), 1.0);

	world.add(std::make_shared<Sphere>(Vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<Sphere>(Vec3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<Sphere>(Vec3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<Sphere>(Vec3(1.0, 0.0, -1.0), 0.5, material_right));


	for (int y = 0; y < height; y++) {
		std::cout << "Rendering line " << y << "\n";
		for (int x = 0; x < width; x++) {	
			Vec4 pixel_color(0, 0, 0, 0);
			for (int s = 0; s < samples_per_pixel; s++) {
				auto u = (double(x) + random_double()) / ((double)(width - 1));
				auto v = (double(y) + random_double()) / ((double)(height - 1));
				Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			pixel_color[0] = sqrt(pixel_color[0] / (double)samples_per_pixel);
			pixel_color[1] = sqrt(pixel_color[1] / (double)samples_per_pixel);
			pixel_color[2] = sqrt(pixel_color[2] / (double)samples_per_pixel);
			pixel_color[3] = sqrt(pixel_color[3] / (double)samples_per_pixel);
			img.set(x, y, pixel_color);
		}
	}

	img.save("sugaar.png");

	return 0;
}
