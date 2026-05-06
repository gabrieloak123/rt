#include "scenes.hpp"

namespace rt{
  
bool Scene::intersect(const Ray& ray, Surfel *isect) const{
  return aggregate ? aggregate->intersect(ray, isect) : false;
}
bool Scene::intersect_p(const Ray& ray) const {
    return aggregate ? aggregate->intersect_p(ray) : false;
}
}