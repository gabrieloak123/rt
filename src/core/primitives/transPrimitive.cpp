#include "transPrimitive.hpp"
#include <memory>


namespace rt {

    TransformedPrimitive::TransformedPrimitive(
                         const std::shared_ptr<Primitive>& prim, 
                         const std::shared_ptr<Transform>& o2w, 
                         const std::shared_ptr<Transform>& w2o)
        : primitive(prim), obj_to_world(o2w), world_to_obj(w2o) {}
    
    bool TransformedPrimitive::box(Bounds3f &box) const
    {
        if (!primitive->box(box)) {
        return false;
    }
        box = (*obj_to_world)(box); 
        return true;
    }

    const std::shared_ptr<Material> TransformedPrimitive::get_material() const 
    {
        return primitive->get_material();
    }
    
    bool TransformedPrimitive::intersect(const Ray &r, Surfel *sf) const
    {
        Ray ray = (*world_to_obj)(r);
        
        if(!primitive->intersect(ray, sf))
            return false;

        r.setTMax(ray.getTMax());
        
        if(sf)
            *sf = (*obj_to_world)(*sf);

        return true;
    }
    bool TransformedPrimitive::intersect_p(const Ray &r) const
    {
        return primitive->intersect_p((*world_to_obj)(r));
    }

    

};