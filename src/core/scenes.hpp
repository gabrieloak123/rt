
#ifndef SCENES_HPP
#define SCENES_HPP

#include "background.hpp"
#include "common.hpp"
#include "paramset.hpp"
#include "ray.hpp"
#include <memory>

using Mat4 = mat4<double>;
using Point2 = std::pair<double, double>;
using Point3 = vec3<double>;
using Point4 = vec4<double>;
using Vec3 = vec3<double>;

namespace rt {

class Primitive;
class Material;

struct Surfel {
public:
  Surfel(const Point3 &p, const Vec3 &n, const Vec3 &wo, float time,
         const Point2 &uv, const Primitive *pri)
      : p{p}, n{n}, wo{wo}, time{time}, uv{uv}, primitive{pri} { /* empty */ };

  Surfel() = default;

  Point3 p; //!< Contact point.
  Vec3 n;   //!< The surface normal.
  Vec3 wo;  //!< Outgoing direction of light, which is -ray.
  double time;
  Point2 uv; //!< Parametric coordinate (u,v) of the hit surface.
  const Primitive *primitive = nullptr; //!< Pointer to the primitive.
};
class Material {
  public:
  virtual ~Material() = default;
  virtual rt::RGBColor get_color() const = 0;
};
class FlatMaterial : public Material{
  public:
  FlatMaterial(rt::RGBColor color) : color(color){};
  FlatMaterial(Material &mat);

  rt::RGBColor color;
  rt::RGBColor get_color() const override {return color;}
};

class Primitive {
protected:
  std::shared_ptr<Material> material;

public:
  virtual ~Primitive() = default;
  virtual bool intersect(const Ray &r, Surfel *sf) const = 0;
  virtual bool intersect_p(const Ray &r) const = 0;
  virtual const std::shared_ptr<Material> get_material() const {
    return material;
  }
};

class PrimitiveList : public Primitive {
  private:
    std::vector<std::shared_ptr<Primitive>> primitives;
  public:
    void add(std::shared_ptr<Primitive> primitive);
    bool intersect(const Ray& ray, Surfel* isect) const override;
    bool intersect_p(const Ray &ray) const override;
    
};

class Sphere : public Primitive {
private:
  Point3 center{};
  double radius{0};

public:
  Sphere(Point3 center, float radius,std::shared_ptr<Material> mat);
  bool intersect(const Ray &r, Surfel *sf) const;
  bool intersect_p(const Ray &r) const;
};

class Scene {
    //=== Public data
    public:
        //std::vector<shared_ptr<Light>> lights; // list of lights
        std::shared_ptr< Background > background; // The background object.
    private:
        std::shared_ptr<Primitive> aggregate; // The scene graph of objects, acceleration structure.

    //=== Public interface
    public:
        Scene( std::shared_ptr<Primitive> ag, std::shared_ptr< Background > bkg)
             : background{bkg}, aggregate{ag}
        {}
        /// Determines the intersection info; return true if there is an intersection.
        bool intersect( const Ray& r, Surfel *isect ) const;
        
        /*! A faster version that only determines whether there is an intersection or not;
         * it doesn't calculate the intersection info.
         */
        bool intersect_p( const Ray& r ) const;
};

} // namespace rt
#endif
