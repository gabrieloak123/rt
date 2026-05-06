#include "integrator.hpp"

namespace rt{
class NormalMapIntegrator : public SamplerIntegrator {
    public:
        NormalMapIntegrator(std::shared_ptr<rt::Camera> cam) : SamplerIntegrator(cam) {}
        std::optional<rt::RGBColor> Li(const Ray& ray, const rt::Scene& scene) const override;
};
}