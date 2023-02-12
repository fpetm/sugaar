#pragma once
#include "math.hpp"
#include "ray.hpp"

namespace sugaar {
	class Camera {
	public:
		Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist) {
			auto h = tan(vfov / 2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = aspect_ratio * viewport_height;
			
			auto w = unit_vector(lookfrom - lookat);
			auto u = unit_vector(cross(vup, w));
			auto v = cross(w, u);

			auto focal_length = 1.0;

			origin = lookfrom;
			horizontal = focus_dist * viewport_width * u;
			vertical = focus_dist * viewport_height *v;
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist * w;

			lens_radius = aperture / 2;
		}
		Ray get_ray(double s, double t) const {
			const Vec2 temp = Vec2::random_in_unit_sphere();
			Vec3 rd = lens_radius * Vec3(temp.X(), temp.Y(), 0.0);
			Vec3 offset = u * rd.X() + v * rd.Y();
			return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
		}
	private:
		Vec3 origin;
		Vec3 lower_left_corner;
		Vec3 horizontal, vertical;
		Vec3 u, v, w;
		double lens_radius;
	};

}