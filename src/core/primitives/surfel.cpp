#include "surfel.hpp"
#include "primitive.hpp"

namespace rt{
    Surfel::Surfel(const Point3 &p, const Vec3 &n, const Vec3 &wo, float time,
         const Point2 &uv, const Primitive *pri)
      : p{p}, n{n}, wo{wo}, time{time}, uv{uv}, primitive{pri} { /* empty */ };
}