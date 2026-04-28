
#ifndef SCENES_HPP
#define SCENES_HPP

#include "common.hpp"
#include "paramset.hpp"
#include "ray.hpp"
#include <memory>

using Mat4 = mat4<double>;
using Point2 = std::pair<double, double>;
using Point3 = vec3<double>;
using Point4 = vec4<double>;
using Vec3 = vec3<double>;

class Primitive; 
struct Material;

struct Surfel{
	public:
		Surfel( const Point3&p,const Vec3&n, const Vec3&wo, float time,
			const Point2& uv, const Primitive *pri )
			: p{p}, n{n}, wo{wo}, time{time}, uv{uv}, primitive{pri}
            {/* empty */};
            
        Surfel() = default;

		Point3 p;        //!< Contact point.
		Vec3 n;       //!< The surface normal.
		Vec3 wo;      //!< Outgoing direction of light, which is -ray.
		double time;
        Point2 uv;     //!< Parametric coordinate (u,v) of the hit surface.
		const Primitive *primitive=nullptr; //!< Pointer to the primitive.
};



struct Material {    
    Material(rt::RGBColor color, std::string type) : color(color), type(type) {};
    Material(Material& mat) : color(mat.color), type(mat.type) {};
    rt::RGBColor color;
    std::string type;
};

class Primitive {
    protected:
        std::shared_ptr<Material> material;
    public:
        virtual ~Primitive() = default;
        virtual bool intersect(const Ray& r, Surfel *sf) const = 0;
        virtual bool intersect_p(const Ray& r) const = 0;
        virtual const std::shared_ptr<Material> get_material() const {return material;}

};


class Sphere : public Primitive {
    private:
        Point3 center{};
        double radius{0};
    public:
        Sphere(Point3 center, float radius, Material& mat);
        bool intersect(const Ray& r, Surfel *sf) const;
        bool intersect_p(const Ray& r)const;
    
};


class Scene {

};

#endif