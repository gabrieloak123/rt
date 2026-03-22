#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstdint>
#include <string>
#include <iostream>

using byte = uint16_t;

using std::cout;
using std::endl;
using std::string;

struct RGBColor {
  byte red;
  byte green;
  byte blue;
};

// Corner indexes.
enum Corners_e {
  TOP_LEFT = 0,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT,
};

#endif //COMMON_HPP
