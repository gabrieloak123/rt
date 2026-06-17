#include "ray.hpp"

namespace rt{

    Ray::Ray(const Point3& o, const Vector3& dir, double t_min, double t_max)
      : origin(o), direction(dir), t_min(t_min), t_max(t_max) {};

};