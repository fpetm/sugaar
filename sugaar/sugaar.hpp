#pragma once

/* C++ headers */
#include <array>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

/* C headers */
#include <cmath>


namespace sugaar {

const double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.141592653589793115998;
constexpr double e = 2.718281828459045090796;

constexpr std::uint32_t width = 190;
constexpr std::uint32_t height = 108;
constexpr double aspect_ratio =
    (static_cast<double>(width) / static_cast<double>(height));

typedef std::uint64_t u64;
typedef std::uint32_t u32;

}  // namespace sugaar