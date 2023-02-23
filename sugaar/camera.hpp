#pragma once
#include "math.hpp"
#include "ray.hpp"

namespace sugaar {
class Camera {
public:
  Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect,
         double aperture, double focus_dist) {
    auto h = tan(vfov / 2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect * viewport_height;

    auto w = unit_vector(lookfrom - lookat);
    auto u = unit_vector(cross(vup, w));
    auto v = cross(w, u);

    auto focal_length = 1.0;

    m_Origin = lookfrom;
    m_Horizontal = focus_dist * viewport_width * u;
    m_Vertical = focus_dist * viewport_height * v;
    m_LowerLeftCorner = m_Origin - m_Horizontal / 2 - m_Vertical / 2 - focus_dist * w;

    m_LensRadius = aperture / 2;
  }
  Ray get_ray(double s, double t) const {
    const Vec2 temp = Vec2::random_in_unit_sphere();
    Vec3 rd = m_LensRadius * Vec3(temp.X(), temp.Y(), 0.0);
    Vec3 offset = m_U * rd.X() + m_V * rd.Y();
    return Ray(m_Origin + offset, m_LowerLeftCorner + s * m_Horizontal +
                                    t * m_Vertical - m_Origin - offset);
  }

private:
  Vec3 m_Origin;
  Vec3 m_LowerLeftCorner;
  Vec3 m_Horizontal, m_Vertical;
  Vec3 m_U, m_V, m_W;
  double m_LensRadius;
};

} // namespace sugaar