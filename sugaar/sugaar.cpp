#include "sugaar.hpp"
#include "math.hpp"

#define STB_IMAGE_IMPLMENTATION
#include "../stb/stb_image.h"

int main() {
	sugaar::Vector<3> vec(1, 2, 3);
	std::cout << vec.X() << "\n";
	return 0;
}
