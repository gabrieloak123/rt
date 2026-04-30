#include "scenes.hpp"
#include "paramset.hpp"
#include "ssmath/vec3.hpp"
#include <memory>

namespace rt {

Sphere::Sphere(Point3 center, float radius, Material &mat)
    : center(center), radius(radius) {
  material = std::shared_ptr<Material>(new Material(mat));
}

bool Sphere::intersect(const Ray &r, Surfel *sf) const {
  Point3 oc = r.getOrigin() - center;
  Vec3 v = r.getDirection();

  double A = dot(v, v);
  double hB = dot(oc, v);
  double C = dot(oc, oc) - radius * radius;

  double delta = hB * hB - A * C;

  if (delta < 0)
    return false;

  double sqr = std::sqrt(delta);
  double root = (-hB - sqr) / A;

  if (root < r.getTMin() || root > r.getTMax()) {
    root = (-hB + sqr) / A;
    if (root < r.getTMin() || root > r.getTMax()) {
      return false;
    }
  }

  if (sf) {
    sf->time = root;
    sf->p = r(root);
    sf->n = (sf->p - center) / radius;
    sf->wo = -r.getDirection();
    sf->primitive = this;
  }
  r.setTMax(root);

  return true;
}

bool Sphere::intersect_p(const Ray &r) const {
  Point3 oc = r.getOrigin() - center;
  Vec3 v = r.getDirection();

  double A = dot(v, v);
  double hB = dot(oc, v);
  double C = dot(oc, oc) - radius * radius;

  double delta = hB * hB - A * C;

  if (delta < 0)
    return false;

  double sqr = std::sqrt(delta);

  double n = (hB > 0) ? -hB - sqr : -hB + sqr; // to avoid precision lost

  double t0 = n / A;
  double t1 = C / n;

  if (t0 > t1) {
	  std::swap(t0, t1);
  }

  if (t0 >= r.getTMin() && t0 <= r.getTMax())
    return true;

  if (t1 >= r.getTMin() && t1 <= r.getTMax())
    return true;

  return false;
}

} // namespace rt
