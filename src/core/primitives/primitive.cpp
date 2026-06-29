#include "primitive.hpp"
#include "bvh_accel.hpp"
#include "error.hpp"
#include "shape.hpp"

namespace rt {

  PrimitiveList::PrimitiveList(std::vector<std::shared_ptr<Primitive>> prim)
      : primitives(prim) {}

  GeometricPrimitive::GeometricPrimitive(std::shared_ptr<Shape> shape,
                     std::shared_ptr<Material> material)
      : shape(shape), material(material) {};

const std::shared_ptr<Material> AggregatePrimitive::get_material() const {
  WARNING("AggregatePrimitive must not have a material");
  return nullptr;
}

void PrimitiveList::add(const std::shared_ptr<Primitive> &object) {
  primitives.push_back(object);
}


bool PrimitiveList::intersect(const Ray &ray, Surfel *isect) const {
  Surfel temp_isect;
  bool hit_anything = false;
  for (const auto &object : primitives) {
    if (object->intersect(ray, &temp_isect)) {
      hit_anything = true;
      if (isect) {
        *isect = temp_isect;
      }
    }
  }
  return hit_anything;
}

bool PrimitiveList::intersect_p(const Ray &ray) const {
  for (const auto &object : primitives) {
    if (object->intersect_p(ray)) {
      return true;
    }
  }
  return false;
}

bool GeometricPrimitive::intersect(const Ray &r, Surfel *sf) const {
  float t_hit;
  if (shape->intersect(r, &t_hit, sf)) {
    r.setTMax(t_hit);
    if (sf) {
      sf->primitive = this;
    }
    return true;
  }
  return false;
}

bool GeometricPrimitive::intersect_p(const Ray &r) const {
  return shape->intersect_p(r);
}

bool GeometricPrimitive::box(Bounds3f &box) const { return shape->box(box);};

void GeometricPrimitive::set_material(const std::shared_ptr<Material> &m) { material = m; };
} // namespace rt
