#pragma once
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

#include "math.hpp"

namespace sugaar {
class Image {
 public:
  Image(std::uint32_t w, std::uint32_t h)
      : m_Width(w), m_Height(h), pixels(w * h) {}

  Vector<4> get(std::uint32_t x, std::uint32_t y) const {
    return pixels[y * m_Width + x];
  }
  Vector<4>& get(std::uint32_t x, std::uint32_t y) {
    return pixels[y * m_Width + x];
  }
  void set(std::uint32_t x, std::uint32_t y, const Vector<4>& data) {
    std::lock_guard<std::mutex> lock(m);
    get(x, y) = data;
  }

  void save(std::string path);

 private:
  std::uint32_t m_Width, m_Height;
  std::vector<Vector<4>> pixels;

  std::mutex m;
};

}  // namespace sugaar