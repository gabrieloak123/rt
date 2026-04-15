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
	string outfile = "";
	string scene;
};

struct RGBColor {
  byte red;
  byte green;
  byte blue;

  RGBColor() : red(0), green(0), blue(0) {};
  RGBColor(byte red, byte green, byte blue) : red(red), green(green), blue(blue) {};

  RGBColor operator*(float t){
    return RGBColor( static_cast<byte>(t * red),
                     static_cast<byte>(t * green),
                     static_cast<byte>(t * blue)
    );
  };
  
  RGBColor operator+(const RGBColor& c){return RGBColor(red + c.red, green + c.green, blue + c.blue);};
  
  byte&    operator[](const size_t index){
    if(index == 0)return red;
    if(index == 1)return green;
    return blue;
  };

  byte operator[](const size_t index) const {
    if(index == 0)return red;
    if(index == 1)return green;
    return blue;
  };
};

// @author = Sam Altman's child
// ===
inline std::istream& operator>>(std::istream& is, rt::RGBColor& color) {
    return is >> color.red >> color.green >> color.blue;
}
inline std::ostream& operator<<(std::ostream& os, const rt::RGBColor& color) {
    return os << color.red << " " << color.green << " " << color.blue;
}
// ===

} // namespace rt

#endif //COMMON_HPP
