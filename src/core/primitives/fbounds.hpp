#ifndef FLOAT_BOUND_HPP
#define FLOAT_BOUND_HPP

#include "common.hpp"
#include "ray.hpp"
#include <limits>
#include <memory>

namespace rt {

class Primitive;

inline float ffmin(const float &a, const float &b) { return a < b ? a : b; }
inline float ffmax(const float &a, const float &b) { return a > b ? a : b; }

class Bounds3f {
private:
  Point3 pmin;
  Point3 pmax;

public:
  Bounds3f() {
    float inf = std::numeric_limits<float>::infinity();

    pmin = Point3(inf, inf, inf);
    pmax = Point3(-inf, -inf, -inf);
  }
  Bounds3f(const Point3 &p1, const Point3 &p2) {
    pmin = {std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y()),
            std::min(p1.z(), p2.z())};
    pmax = {std::max(p1.x(), p2.x()), std::max(p1.y(), p2.y()),
            std::max(p1.z(), p2.z())};
  };

  Bounds3f(std::vector<std::shared_ptr<Primitive>> &prims);

  // Getters
  const Point3 &min() const { return pmin; }
  const Point3 &max() const { return pmax; }

  void print();

  Point3 centroid() const;

  Bounds3f merge(const Bounds3f &b) const;

  Bounds3f merge(const Point3 &p) const;

  bool intersect_p(const Ray &ray, float &tmin, float &tmax) const;
};

}; // namespace rt

#endif
