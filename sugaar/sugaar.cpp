#include "sugaar.hpp"
#include "math.hpp"
#include "image.hpp"
#include "ray.hpp"

constexpr std::uint32_t width = 1280;
constexpr std::uint32_t height = 720;

using namespace sugaar;

double hit_sphere(const Vec3& center, double radius, const Ray& r) {
	Vec3 oc = r.origin() - center;
	double a = r.direction().length_squared();
	double half_b = dot(oc, r.direction());
	double c = oc.length_squared() - radius * radius;
	double discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return -1;
	else return (-half_b - sqrt(discriminant)) / a;
}

Vec4 ray_color(const Ray& r) {
	const Vec3 center(0, 0, -1);
	double t = hit_sphere(center, 0.5, r);
	if (t > 0.0) {
		Vec3 N = unit_vector(r.at(t) - center);
		Vec4 color = 0.5 * Vec4(N.X() + 1, N.Y() + 1, N.Z() + 1, 2.0);
		return color;
	}
	Vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.Y() + 1.0);
	return (1.0 - t) * Vec4(1.0, 1.0, 1.0, 1.0) + t * Vec4(0.5, 0.7, 1.0, 1.0);
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

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			auto u = double(x) / double(width - 1);
			auto v = double(y) / double(height - 1);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			Vec4 color = ray_color(r);
			img.set(x, y, color);
		}
	}

	img.save("sugaar.png");

	return 0;
}
