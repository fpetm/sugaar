#include "sugaar.hpp"
#include "math.hpp"
#include "image.hpp"

int main() {
	
	sugaar::Image *img = new sugaar::Image(1000, 1000);
	for (int x = 0; x < 1000; x++) {
		for (int y = 0; y < 1000; y++) {
			double r = double(x) / 999;
			double g = double(y) / 999;
			double b = 0.25;
			double a = 1.0;
			img->set(x, y, sugaar::Vector<4>(r, g, b, a));
		}
	}
	img->save("test.png");
	return 0;
}
