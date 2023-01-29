#include "image.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

void sugaar::Image::save(std::string path) {
	char* data = (char*)malloc(width * height * 4);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			data[(y * width + x) * 4 + 0] = (char)(get(x, y).X() * 255.999);
			data[(y * width + x) * 4 + 1] = (char)(get(x, y).Y() * 255.999);
			data[(y * width + x) * 4 + 2] = (char)(get(x, y).Z() * 255.999);
			data[(y * width + x) * 4 + 3] = (char)(get(x, y).W() * 255.999);
		}
	}
	stbi_flip_vertically_on_write(1);
	stbi_write_png(path.c_str(), width, height, 4, data, sizeof(char) * 4 * width);
	free(data);
}