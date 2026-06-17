#ifndef DIRECTIONAL_LIGHTS_HPP
#define DIRECTIONAL_LIGHTS_HPP

#include "light.hpp"


namespace rt {
    class DirectionalLight : public Light {
        private:
            Vec3 direction;
            double world_radius;
        public:

            DirectionalLight(Vec3 direction, RGBColor intensity, RGBColor scale, double world_radius);
            RGBColor sample_Li( const Surfel& hit, Vec3* wi, VisibilityTester* vis  ) override;
    };
}

#endif
