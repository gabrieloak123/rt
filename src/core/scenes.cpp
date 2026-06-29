#include "scenes.hpp"

namespace rt{

Scene::Scene( const std::shared_ptr<AggregatePrimitive>& ag, const std::shared_ptr< Background >& bkg, const std::vector<std::shared_ptr<Light>>& lights)
             : lights(lights), background{bkg}, aggregate{ag} {}
bool Scene::intersect(const Ray& ray, Surfel *isect) const{
  return aggregate ? aggregate->intersect(ray, isect) : false;
}
bool Scene::intersect_p(const Ray& ray) const {
    return aggregate ? aggregate->intersect_p(ray) : false;
}
}