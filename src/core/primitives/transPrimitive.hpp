#ifndef TRANSFORMED_PRIMITIVE_HPP
#define TRANSFORMED_PRIMITIVE_HPP

#include "primitive.hpp"

namespace rt {
    class TransformedPrimitive : public Primitive
    {
        private:
            std::shared_ptr<Primitive> primitive;
            std::shared_ptr<Transform> obj_to_world;
            std::shared_ptr<Transform> world_to_obj;          
        public:
            TransformedPrimitive(
                         const std::shared_ptr<Primitive>& prim, 
                         const std::shared_ptr<Transform>& o2w, 
                         const std::shared_ptr<Transform>& w2o);

            bool intersect(const Ray &r, Surfel *sf) const override;
            bool intersect_p(const Ray &r) const override;
            bool box(Bounds3f &box) const override ;
            const std::shared_ptr<Material> get_material() const override;
    };
};


#endif //< TRANSFORMED_PRIMITIVE_HPP