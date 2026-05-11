#include "ambient_light.hpp"
#include "common.hpp"

namespace rt{

    RGBColor AmbientLight::sample_Li( const Surfel& hit, Vec3* wi  ){
        *wi = {0, 0, 0};
        return intensity * scale;
    }

}