#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "common.hpp"
#include "light.hpp"

namespace rt {
class SpotLight : public Light {
  using Degrees = double;

private:
  Vec3 spot_axis;
  Degrees cutoff_angle;
  Degrees falloff_angle;
  int world_radius;

public:
  SpotLight(Vec3 axis, Degrees cutoff, Degrees falloff, int world_radius,
            RGBColor intensity, RGBColor scale)
      : Light(intensity, scale), spot_axis(axis), cutoff_angle(cutoff),
        falloff_angle(falloff), world_radius(world_radius) {
    flag = light_flag_e::spot;
  };
  RGBColor sample_Li(const Surfel &hit, Vec3 *wi) override;
};
} // namespace rt

#endif
