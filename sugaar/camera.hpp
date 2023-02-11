#pragma once
#include "math.hpp"
#include "ray.hpp"

namespace sugaar {
	class Camera {
	public:
		Camera(double aspect_ratio, double viewport_height, double focal_length) {
			auto viewport_width = aspect_ratio * viewport_height;

			origin = Vec3(0, 0, 0);
			horizontal = Vec3(viewport_width, 0, 0);
			vertical = Vec3(0, viewport_height, 0);
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - Vec3(0, 0, focal_length);
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