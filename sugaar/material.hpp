#pragma once
#include "ray.hpp"

namespace sugaar {
	struct HitRecord;

	class Material {
	public:
		virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec4& attenuation, Ray& scattered) const = 0;
	};

	class Lambertian : public Material {
	public:
		Lambertian(const Vec4& a) : albedo(a) {}
		virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec4& attenuation, Ray& scattered) const override {
			auto scatter_direction = rec.normal + Vec3::random_unit_vector();
			if (scatter_direction.near_zero())
				scatter_direction = rec.normal;
			scattered = Ray(rec.p, scatter_direction);
			attenuation = albedo;
			return true;
		}
	private:
		Vec4 albedo;
	};

	class Metal : public Material {
	public:
		Metal(const Vec4& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

		virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec4& attenuation, Ray& scattered) const override {
			Vec3 reflected = reflect<3>(unit_vector(r_in.direction()), rec.normal);
			scattered = Ray(rec.p, reflected + fuzz * Vec3::random_in_unit_sphere());
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		}
	private:
		Vec4 albedo;
		double fuzz;
	};
}