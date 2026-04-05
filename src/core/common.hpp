#ifndef COMMON_HPP
#define COMMON_HPP

#include <array>
#include <optional>
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

using byte = uint16_t;

using std::cout;
using std::endl;

using std::array;
using std::vector;
using std::string;

// Corner indexes.
enum Corners_e {
  TOP_LEFT = 0,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
};

namespace rt {

struct Pixel {
	u_int16_t x;
	u_int16_t y;
};

struct RunningOptions {
	std::optional<array<Pixel,2>> crop_region;
	bool quick{false};
	string outfile;
	string scene;
};

struct RGBColor {
  byte red;
  byte green;
  byte blue;
};

} // namespace rt

#endif //COMMON_HPP
