#include "sugaar.hpp"
#include "math.hpp"
#include "image.hpp"
#include "ray.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

constexpr std::uint32_t width = 1280;
constexpr std::uint32_t height = 720;

using namespace sugaar;

Vec4 ray_color(const Ray& r, const Hittable& world) {
	HitRecord rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * Vec4((rec.normal + Vec3(1, 1, 1)), 2.0);
	}
	Vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.Y() + 1.0);
	return (1.0 - t) * Vec4(1.0, 1.0, 1.0, 1.0) + t * Vec4(0.3, 0.4, 0.5, 1.0);
}

int main() {
	const auto aspect_ratio = double(width) / double(height);
	
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = Vec3(0, 0, 0);
	auto horizontal = Vec3(viewport_width, 0, 0);
	auto vertical = Vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);

	Image img(width, height);

	HittableList world;
	world.add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
	world.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			auto u = double(x) / double(width - 1);
			auto v = double(y) / double(height - 1);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Vec4 color = ray_color(r, world);
			img.set(x, y, color);
		}
	}

	img.save("sugaar.png");

	return 0;
}
