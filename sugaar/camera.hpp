#pragma once
#include "math.hpp"
#include "ray.hpp"

namespace sugaar {
	class Camera {
	public:
		Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect_ratio) {
			auto h = tan(vfov / 2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = aspect_ratio * viewport_height;
			
			auto w = unit_vector(lookfrom - lookat);
			auto u = unit_vector(cross(vup, w));
			auto v = cross(w, u);

			auto focal_length = 1.0;

			origin = lookfrom;
			horizontal = viewport_width * u;
			vertical = viewport_height *v;
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
		}
		Ray get_ray(double u, double v) const {
			return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
		}
	private:
		Vec3 origin;
		Vec3 lower_left_corner;
		Vec3 horizontal, vertical;
	};

}