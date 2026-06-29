#ifndef SURFEL_HPP
#define SURFEL_HPP

#include "api.hpp"
#include <ssmath/ssmath.hpp>

namespace rt{
struct Surfel {
public:
  
  Surfel(const Point3 &p, const Vec3 &n, const Vec3 &wo, float time,
         const Point2 &uv, const Primitive *pri);

  Surfel(const Surfel& s) = default;
  Surfel() = default;

  Point3 p; //!< Contact point.
  Vec3 n;   //!< The surface normal.
  Vec3 wo;  //!< Outgoing direction of light, which is -ray.
  double time;
  Point2 uv; //!< Parametric coordinate (u,v) of the hit surface.
  const Primitive *primitive = nullptr; //!< Pointer to the primitive.
};
}
#endif