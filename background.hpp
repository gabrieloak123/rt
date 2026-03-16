#include <array>
#include <cstdint>
#include <vector>

using b = uint16_t;
using d = double;
using real_type = double;

namespace rt {

struct RGBColor {
  b red;
  b green;
  b blue;
};

class BackgroundColor {
public:
  // Ctro receives a list of four colors, for each corner.
  BackgroundColor(const std::vector<RGBColor> &colors);
  // Dtro
  ~BackgroundColor();

  // Each corner has a color associated with.
  std::array<RGBColor, 4> corners;

  // Corner indexes.
  enum Corners_e {
    TOP_LEFT = 0,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
  };

  void dummy();

private:
  // Return the linearly interpolated color in [A;B], based on the parameter
  RGBColor linear_interpolation(const RGBColor &A, const RGBColor &B, double t) const;
  // Sample and returns a color, based on the raster coordinate.
  RGBColor sampleUV(real_type u, real_type v) const;
};
} // namespace rt
