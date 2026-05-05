#include "scenes.hpp"
#include "paramset.hpp"
#include "ssmath/vec3.hpp"
#include <memory>

namespace rt {

    
void PrimitiveList::add(std::shared_ptr<Primitive> object) {
    primitives.push_back(object);
}

bool PrimitiveList::intersect(const Ray& ray, Surfel* isect) const {
    Surfel temp_isect;
    bool hit_anything = false;
    for (const auto& object : primitives) {
        if (object->intersect(ray, &temp_isect)) {
            hit_anything = true;
            if (isect) {
                *isect = temp_isect;
            }
        }
    }
    return hit_anything;
}

bool PrimitiveList::intersect_p(const Ray& ray) const  {
    for (const auto& object : primitives) {
        if (object->intersect_p(ray)) {
            return true;
        }
    }
    return false;
}


Sphere::Sphere(Point3 center, float radius,std::shared_ptr<Material> mat)
    : center(center), radius(radius) {
      this->material = mat;
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
  
  double n = (hB > 0) ? -hB - sqr : -hB + sqr; // to avoid precision lost

  double t0 = n / A;
  double t1 = C / n;

  if (t0 > t1) {
	  std::swap(t0, t1);
  }

  if (t0 < r.getTMin() || t0 > r.getTMax()) {
      t0 = t1;
      if (t0 < r.getTMin() || t0 > r.getTMax()) {
          return false; 
      }
  }

  if (sf) {
    sf->time = t0;
    sf->p = r(t0);
    sf->n = (sf->p - center) / radius;
    sf->wo = -r.getDirection();
    sf->primitive = this;
  }
  r.setTMax(t0);

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


bool rt::Scene::intersect(const Ray& ray, Surfel *isect) const{
  if(aggregate){
    return aggregate->intersect(ray, isect);
  }
  return false; 
}
bool rt::Scene::intersect_p(const Ray& ray) const {
    if (aggregate) {
        return aggregate->intersect_p(ray);
    }
    return false;
}