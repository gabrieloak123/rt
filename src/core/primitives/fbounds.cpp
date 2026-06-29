#include "fbounds.hpp"
#include "primitive.hpp"
namespace rt{

    Bounds3f::Bounds3f(std::vector<std::shared_ptr<Primitive>> &prims) {
        std::numeric_limits<float>::infinity();

        Point3 p_min = Point3(std::numeric_limits<float>::infinity(),
                            std::numeric_limits<float>::infinity(),
                            std::numeric_limits<float>::infinity());
        Point3 p_max = Point3(-std::numeric_limits<float>::infinity(),
                            -std::numeric_limits<float>::infinity(),
                            -std::numeric_limits<float>::infinity());
        for (auto p : prims) {
        Bounds3f b;
        if (p->box(b)) {
            p_min = Point3(std::min(p_min.x(), b.pmin.x()),
                        std::min(p_min.y(), b.pmin.y()),
                        std::min(p_min.z(), b.pmin.z()));
            p_max = Point3(std::max(p_max.x(), b.pmax.x()),
                        std::max(p_max.y(), b.pmax.y()),
                        std::max(p_max.z(), b.pmax.z()));
        }
        }
        pmin = p_min;
        pmax = p_max;
  };

  Point3 Bounds3f::centroid() const { return (pmin + pmax) * 0.5; }

  void Bounds3f::print() {
    cout << "pmin: " << pmin << " | " << "pmax: " << pmax << "\n";
  }
  Bounds3f Bounds3f::merge(const Bounds3f &b) const {
    return Bounds3f(
        Point3(std::min(pmin.x(), b.pmin.x()), std::min(pmin.y(), b.pmin.y()),
               std::min(pmin.z(), b.pmin.z())),
        Point3(std::max(pmax.x(), b.pmax.x()), std::max(pmax.y(), b.pmax.y()),
               std::max(pmax.z(), b.pmax.z())));
  }

  Bounds3f Bounds3f::merge(const Point3 &p) const {
    return Bounds3f(Point3(
                              std::min(pmin.x(), p.x()),
                              std::min(pmin.y(), p.y()),
                              std::min(pmin.z(), p.z())),
                    Point3(
                              std::max(pmax.x(), p.x()),
                              std::max(pmax.y(), p.y()),
                              std::max(pmax.z(), p.z())));
  }

   bool Bounds3f::intersect_p(const Ray &ray, float &tmin, float &tmax) const {
    for (int a = 0; a < 3; ++a) {
      float invD = 1.0f / ray.getDirection()[a];
      float t0 = (pmin[a] - ray.getOrigin()[a]) * invD;
      float t1 = (pmax[a] - ray.getOrigin()[a]) * invD;
      if (invD < 0.0f) std::swap(t0, t1);
      tmin = ffmax(t0, tmin);
      tmax = ffmin(t1, tmax);
      if (tmax < tmin)
        return false;
    }
    return true;
  }
}