#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "common.hpp"
#include "ray.hpp"
#include "surfel.hpp"
#include "fbounds.hpp"
#include "transform.hpp"
#include <memory>

namespace rt{
class Shape {
public:
  bool flips_normal;

  std::shared_ptr<Transform> obj_to_world;
  std::shared_ptr<Transform> world_to_obj;

  Shape(bool flip, const std::shared_ptr<Transform>& obj_to_world, const std::shared_ptr<Transform>& world_to_obj)
   : flips_normal(flip), obj_to_world(obj_to_world), world_to_obj(world_to_obj) {};
  
  virtual bool box(Bounds3f &box) const = 0;
  virtual bool intersect(const Ray &r, float *t_hit, Surfel *sf) const = 0;
  virtual bool intersect_p(const Ray &r) const = 0;
};

} // namespace rt
#endif //< SHAPE_HPP
