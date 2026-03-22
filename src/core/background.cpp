#include <fstream>
#include "background.hpp"

using std::ofstream;

const d width = 400;
const d height = 200;
const d max = 255;

BackgroundColor::BackgroundColor(const std::vector<RGBColor> &colors) {
  for (size_t i = 0; i < 4; i++) {
    m_corners[i] = colors[i];
  }
}

RGBColor BackgroundColor::linear_interpolation(const RGBColor &A,
                                               const RGBColor &B,
                                               double t) const {
  return RGBColor{
	static_cast<byte>((1 - t) * A.red + t * B.red),
	static_cast<byte>((1 - t) * A.green + t * B.green),
	static_cast<byte>((1 - t) * A.blue + t * B.blue)
  };
};

RGBColor BackgroundColor::sampleUV(real_type u, real_type v) const {
  const auto bottom_horizontal =
      linear_interpolation(m_corners[BOTTOM_LEFT], m_corners[BOTTOM_RIGHT], u);
  const auto top_horizontal =
      linear_interpolation(m_corners[TOP_LEFT], m_corners[TOP_RIGHT], u);

  const auto bilerp =
      linear_interpolation(top_horizontal, bottom_horizontal, v);

  return bilerp;
};

void BackgroundColor::dummy() {
  ofstream img("out.ppm");

  img << "P3" << "\n";
  img << width << " " << height << "\n";
  img << max << "\n";

  for (d y = 0; y < height; y++) {
    for (d x = 0; x < width; x++) {
      const real_type u = x / (width - 1);
      const real_type v = y / (height - 1);

      const RGBColor color = sampleUV(u, v);

      img << color.red << " " << color.green << " " << color.blue << "\n";
    }
  }
  img.close();
}
