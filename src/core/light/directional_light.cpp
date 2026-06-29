#include "directional_light.hpp"

namespace rt {

    DirectionalLight::DirectionalLight(Vec3 direction, RGBColor intensity, RGBColor scale, double world_radius)
     :
    Light(intensity, scale), direction(direction), world_radius(world_radius) {flag = light_flag_e::directional;};

    RGBColor DirectionalLight::sample_Li(const Surfel& hit, Vec3* wi, VisibilityTester* vis ){
        *wi = -direction;
        wi->mk_unit_vec();

        Surfel lpos;

        // lpos.p = hit.p + (*wi) * world_radius;

        *vis = VisibilityTester(hit, *wi);

        return intensity * scale ;
    }

};