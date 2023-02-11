#pragma once
#include "sugaar.hpp"

#include "hittable.hpp"

namespace sugaar {
	class Sphere : public Hittable {
	public:
		Sphere() {}
		Sphere(Vec3 c, double r, std::shared_ptr<Material> m) : center(c), radius(r), material_ptr(m) {}

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	public:
		std::shared_ptr<Material> material_ptr;
		Vec3 center;
		double radius;
	};

	bool Sphere::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const  {
		Vec3 oc = r.origin() - center;
		double a = r.direction().length_squared();
		double half_b = dot(oc, r.direction());
		double c = oc.length_squared() - radius * radius;
		double discriminant = half_b * half_b - a * c;

		if (discriminant < 0) return false;
		double sqrtd = sqrt(discriminant);

		auto root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root) {
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
				return false;
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		rec.normal = (rec.p - center) / radius;

		Vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);
		rec.material_ptr = material_ptr;

		return true;
	}
}