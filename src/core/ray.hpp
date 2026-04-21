#ifndef RAY_HPP
#define RAY_HPP

#include "ssmath/ssmath.hpp"

#include <cmath>

using Point3 = vec3<double>;
using Vector3 = vec3<double>;

class Ray {
    private:

    Point3 position{};
    Vector3 direction{};

    mutable double t_min{}, t_max{};    

    constexpr Point3 operator()(double t) const {return position + direction * t;}
    

    public:

        Ray() : t_min(0.0), t_max(INFINITY){};

        Ray( Point3 pos, Vector3 dir, double t_min = 0.0, double t_max = INFINITY) : position(pos), direction(dir), t_min(t_min), t_max(t_max) {};

        void normalize(){direction.mk_unit_vec();};
        
        void setPosition(Point3 pos){this->position = pos;};
        void setDirection(Vector3 dir){this->direction = dir;};
        
        Point3 getPosition(){return this->position;};
        Vector3 getDirection(){return this->direction;};


};



#endif