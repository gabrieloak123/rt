#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <array>
#include <vector>

#include "common.hpp"

using d = double;
using real_type = double;

using std::array;

enum BackgroundType_e {
	COLORS = 0,
};

class BackgroundColor {
public:
  // Ctro receives a list of four colors, for each corner.
  BackgroundColor(const std::vector<RGBColor> &colors);
  // Dtro
  ~BackgroundColor();

  void dummy();

private:
  // Each corner has a color associated with.
  array<RGBColor, 4> m_corners;
  BackgroundType_e m_type;
  //mapping?


  // Return the linearly interpolated color in [A;B], based on the parameter
  RGBColor linear_interpolation(const RGBColor &A, const RGBColor &B, double t) const;
  // Sample and returns a color, based on the raster coordinate.
  RGBColor sampleUV(real_type u, real_type v) const;
};

#endif //BACKGROUND_HPP
