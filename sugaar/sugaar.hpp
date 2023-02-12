#pragma once

/* C++ headers */
#include <iostream>
#include <vector>
#include <array>
#include <memory>
#include <limits>

/* C headers */
#include <cmath>

#include "math.hpp"

namespace sugaar {
	const double infinity = std::numeric_limits<double>::infinity();
	const double pi = 3.141592653589793115998;
	const double e = 2.718281828459045090796;


	constexpr std::uint32_t width = 1920;
	constexpr std::uint32_t height = 1080;
	constexpr double aspect_ratio = ((double)width / (double)height);

}