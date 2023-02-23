#pragma once
#include "math.hpp"

namespace sugaar {
class Ray {
 public:
  Ray() {}
  Ray(const Vec3& origin, const Vec3& direction)
      : m_Origin(origin), m_Direction(direction) {}

  Vec3 origin() const { return m_Origin; }
  Vec3 direction() const { return m_Direction; }

  Vec3 at(double t) const { return m_Origin + t * m_Direction; }

 private:
  Vec3 m_Origin;
  Vec3 m_Direction;
};
}  // namespace sugaar