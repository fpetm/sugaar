#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <mutex>
#include "math.hpp"

namespace sugaar {
	class Image {
	public:
		Image(std::uint32_t w, std::uint32_t h) : width(w), height(h), pixels(w*h) {  }

		Vector<4> get(std::uint32_t x, std::uint32_t y) const { return pixels[y * width + x]; }
		Vector<4>& get(std::uint32_t x, std::uint32_t y) { return pixels[y * width + x]; }
		void set(std::uint32_t x, std::uint32_t y, const Vector<4> &data) { 
			std::lock_guard<std::mutex> lock(m);
			get(x,y) = data; 
		}

		void save(std::string path);
		
	private:
		std::uint32_t width, height;
		std::vector<Vector<4>> pixels;
		
		std::mutex m;
	};

	


}