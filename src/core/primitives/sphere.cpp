#include "sphere.hpp"
#include "common.hpp"
#include "fbounds.hpp"

namespace rt{

bool Sphere::intersect(const Ray &r, float *t_hit, Surfel *sf) const {

  auto newr = (*world_to_obj)(r);
  Point3 oc = newr.getOrigin() - center;
  Vec3 v = newr.getDirection();

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

  if (t0 < newr.getTMin() || t0 > newr.getTMax()) {
      t0 = t1;
      if (t0 < newr.getTMin() || t0 > newr.getTMax()) {
          return false; 
      }
  }

  if(t_hit) *t_hit = t0;

  if (sf) {
    sf->time = t0;
    sf->p = newr(t0);
    sf->n = (sf->p - center) / radius;

    if (flips_normal) sf->n = -sf->n;
    
    sf->wo = -newr.getDirection();

    *sf = (*obj_to_world)(*sf);
  }

  return true;
}

bool Sphere::box(Bounds3f &box) const {
	Vec3 r_vec =Vec3(radius, radius, radius);
  auto tempc = (*world_to_obj)(center);
	box = Bounds3f(tempc - r_vec, tempc + r_vec);
  box = (*obj_to_world)(box);
	return true;
};

bool Sphere::intersect_p(const Ray &r) const {
  auto newr = (*world_to_obj)(r);
  Point3 oc = newr.getOrigin() - center;
  Vec3 v = newr.getDirection();

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

  if (t0 >= newr.getTMin() && t0 <= newr.getTMax())
    return true;

  if (t1 >= newr.getTMin() && t1 <= newr.getTMax())
    return true;

  return false;
}


}
