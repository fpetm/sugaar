#include "image.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>

#include "sugaar.hpp"

void sugaar::Image::save(std::string path) {
  char* data = new char[m_Width * m_Height * 4];
  for (std::uint32_t y = 0; y < m_Height; y++) {
    for (std::uint32_t x = 0; x < m_Width; x++) {
      data[(y * width + x) * 4 + 0] = static_cast<char>(get(x, y).X() * 255.9);
      data[(y * width + x) * 4 + 1] = static_cast<char>(get(x, y).Y() * 255.9);
      data[(y * width + x) * 4 + 2] = static_cast<char>(get(x, y).Z() * 255.9);
      data[(y * width + x) * 4 + 3] = static_cast<char>(get(x, y).W() * 255.9);
    }
  }
  stbi_flip_vertically_on_write(1);
  stbi_write_png(path.c_str(), m_Width, m_Height, 4, data,
                 sizeof(char) * 4 * m_Width);
  delete[] data;
}
