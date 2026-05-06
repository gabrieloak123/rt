#include "directional_light.hpp"

namespace rt {

    RGBColor DirectionalLight::sample_Li(const Surfel& hit, Vec3* wi  ){
        *wi = -direction;
        wi->mk_unit_vec();

        return intensity * scale ;
    }

};