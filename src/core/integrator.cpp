#include "integrator.hpp"
#include "background.hpp"
#include "camera.hpp"
#include "common.hpp"
#include "paramset.hpp"
#include "scenes.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <limits>
#include <memory>
#include <optional>

std::optional<rt::RGBColor> RayCastIntegrator::Li(const Ray& ray, const rt::Scene& scene) const {

    rt::RGBColor L(0,0,0); // The radiance
    // Find closest ray intersection or return background radiance.
    rt::Surfel isect; // Intersection information.

    if (!scene.intersect(ray, &isect)) {
        return std::nullopt;
    }
    // Some form of determining the incoming radiance at the ray's origin.
    // Polymorphism in action.
    std::shared_ptr<rt::Material> fm{nullptr};
    
    fm = std::dynamic_pointer_cast<rt::FlatMaterial>( isect.primitive->get_material() );
    // Assign diffuse color to L.

    if(fm){
        L = fm->get_color();
    }
    else{
        L = rt::RGBColor(255, 0, 255);
    }
    return L;

}

std::optional<rt::RGBColor> NormalMapIntegrator::Li(const Ray& ray, const rt::Scene& scene) const {
    rt::RGBColor L(0, 0, 0);
    rt::Surfel isect;
    if(!scene.intersect(ray, &isect)){
        return std::nullopt;
    }

    std::shared_ptr<rt::Material> fm{nullptr};

    Vec3 temp = isect.n;
    temp += {1, 1, 1};
    temp /= 2;
    temp *= 255;

    fm = std::make_shared<rt::FlatMaterial>(rt::RGBColor(temp[0], temp[1], temp[2]));

    if(fm){
        L = fm->get_color();
    }
    else{
        L = rt::RGBColor(255, 0, 255);
    }

    return L;

}


void SamplerIntegrator::render(const rt::Scene& scene){
      // Perform objects initialization here.
  // -------------------------------------------------------------
  // The Film object holds the memory for the image.

  if(!camera){
    return;
  }
  preprocess(scene);
  
  auto w = camera->film->width();
  auto h = camera->film->height();

  // -------------------------------------------------------------
  // Traverse all pixels to shoot rays from.
  for (int j = 0; j < h; j++) {
    for (int i = 0; i < w; i++) {
        Ray ray = camera->generate_ray(i, j);
                // Determine the incoming light.
        auto temp_L =  Li( ray, scene );

        auto u = float(i) / float(w);
        auto v = 1.0f - float(j) / float(h);
        rt::RGBColor L = (temp_L.has_value()) ?  temp_L.value() : scene.background->sample(u, v);

        camera->film->add(rt::Pixel{static_cast<byte>(i), static_cast<byte>(j)}, L);
      }
  }
    // send image color buffer to the output file.
    camera->film->write_image();    
}