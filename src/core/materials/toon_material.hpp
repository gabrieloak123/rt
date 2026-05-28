#ifndef TOON_MATERIAL_HPP
#define TOON_MATERIAL_HPP

#include "common.hpp"
#include "material.hpp"

namespace rt{
    class ToonMaterial : public Material {
        private:
            std::vector<RGBColor> color_map;
        public:
            ToonMaterial() : color_map() {};
            ToonMaterial(std::vector<RGBColor> color_map) : color_map(color_map) {};
            virtual std::vector<RGBColor> gm() const {return color_map;};
            virtual RGBColor kd() const override {return color_map[0];}
    };
}
#endif

