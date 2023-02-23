#pragma once
#include "hittable.hpp"
#include "sugaar.hpp"

namespace sugaar {
class Sphere : public Hittable {
 public:
  Sphere() {}
  Sphere(Vec3 c, double r, std::shared_ptr<Material> m)
      : m_Center(c), m_Radius(r), m_MaterialPtr(m) {}

  virtual bool hit(const Ray& r, double t_min, double t_max,
                   HitRecord& rec) const override;

 public:
  std::shared_ptr<Material> m_MaterialPtr;
  Vec3 m_Center;
  double m_Radius;
};

bool Sphere::hit(const Ray& r, double t_min, double t_max,
                 HitRecord& rec) const {
  Vec3 oc = r.origin() - m_Center;
  double a = r.direction().length_squared();
  double half_b = dot(oc, r.direction());
  double c = oc.length_squared() - m_Radius * m_Radius;
  double discriminant = half_b * half_b - a * c;

  if (discriminant < 0) return false;
  double sqrtd = sqrt(discriminant);

  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root) return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  rec.normal = (rec.p - m_Center) / m_Radius;

  Vec3 outward_normal = (rec.p - m_Center) / m_Radius;
  rec.set_face_normal(r, outward_normal);
  rec.material_ptr = m_MaterialPtr;

  return true;
}
}  // namespace sugaar