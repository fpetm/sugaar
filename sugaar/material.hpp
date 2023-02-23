#pragma once
#include "ray.hpp"

namespace sugaar {
struct HitRecord;

class Material {
 public:
  virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec4& attenuation,
                       Ray& scattered) const = 0;
};

class Lambertian : public Material {
 public:
  Lambertian(const Vec4& a) : m_Albedo(a) {}
  virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec4& attenuation,
                       Ray& scattered) const override {
    auto scatter_direction = rec.normal + Vec3::random_unit_vector();
    if (scatter_direction.near_zero()) scatter_direction = rec.normal;
    scattered = Ray(rec.p, scatter_direction);
    attenuation = m_Albedo;
    return true;
  }

 private:
  Vec4 m_Albedo;
};

class Metal : public Material {
 public:
  Metal(const Vec4& a, double f) : m_Albedo(a), m_Fuzz(f < 1 ? f : 1) {}

  virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec4& attenuation,
                       Ray& scattered) const override {
    Vec3 reflected = reflect<3>(unit_vector(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, reflected + m_Fuzz * Vec3::random_in_unit_sphere());
    attenuation = m_Albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

 private:
  Vec4 m_Albedo;
  double m_Fuzz;
};

class Dielectric : public Material {
 public:
  Dielectric(double index_of_refraction) : m_IR(index_of_refraction) {}

  virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec4& attenuation,
                       Ray& scattered) const override {
    attenuation = Vec4(1.0, 1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1 / m_IR) : m_IR;
    Vec3 unit_direction = unit_vector(r_in.direction());

    double cos_theta = std::min(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract ||
        reflectance(cos_theta, refraction_ratio) > random_double())
      direction = reflect(unit_direction, rec.normal);
    else
      direction = refract(unit_direction, rec.normal, refraction_ratio);

    scattered = Ray(rec.p, direction);
    return true;
  }

 private:
  double m_IR;

 private:
  static double reflectance(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
  }
};
}  // namespace sugaar