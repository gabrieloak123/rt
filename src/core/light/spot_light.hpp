#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "common.hpp"
#include "light.hpp"

namespace rt {
class SpotLight : public Light {
  using Degrees = double;

private:
  Point3 spot_pos;
  Vec3 spot_axis;
  Vec3 attenuation;
  Degrees cutoff_angle;
  Degrees falloff_angle;
  int world_radius;
  
public:

  double att{1};
  

  SpotLight(Point3 pos, Vec3 axis, Degrees cutoff, Degrees falloff, int world_radius,
            RGBColor intensity, RGBColor scale, Vec3 attenuation);
  RGBColor sample_Li(const Surfel &hit, Vec3 *wi, VisibilityTester* vis) override;
};
} // namespace rt

#endif
