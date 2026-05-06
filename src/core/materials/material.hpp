#include "common.hpp"

/*

*/
#ifndef MATERIAL_HPP
#define MATERIAL_HPP
namespace rt{
    class Material {
        public:
            virtual ~Material() = default;
            virtual rt::RGBColor get_color() const = 0;
    };
}      //< namespace rt
#endif //< MATERIAL_HPP


#ifndef FLAT_MATERIAL_HPP
#define FLAT_MATERIAL_HPP

namespace rt{
    class FlatMaterial : public Material{
        public:
            FlatMaterial(rt::RGBColor color) : color(color){};
            FlatMaterial(Material &mat);

            rt::RGBColor color;
            rt::RGBColor get_color() const override {return color;}
    };
}       //< namespace rt
#endif  //< FLAT_MATERIAL_HPP