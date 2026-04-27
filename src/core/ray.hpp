#ifndef RAY_HPP
#define RAY_HPP

#include "ssmath/ssmath.hpp"

#include <cmath>

using Point3 = vec3<double>;
using Vector3 = vec3<double>;

class Ray {
    private:

    Point3 origin{};
    Vector3 direction{};

    mutable double t_min{}, t_max{};    
    

    public:

        Ray() : t_min(0.0), t_max(INFINITY){};

        Ray( Point3 o, Vector3 dir, double t_min = 0.0, double t_max = INFINITY) : origin(o), direction(dir), t_min(t_min), t_max(t_max) {};

        void normalize(){direction.mk_unit_vec();};
        
        void setOrigin(Point3 o){this->origin = o;};
        void setDirection(Vector3 dir){this->direction = dir;};
        void setTmin(double t_min)const{this->t_min = t_min;}
        void setTMax(double t_max)const{this->t_max = t_max;}
        
        Point3 getOrigin()const{return this->origin;};
        Vector3 getDirection()const{return this->direction;};
        double getTMin()const{return this->t_min;}
        double getTMax()const{return this->t_max;}

        constexpr Point3 operator()(double t) const {return origin + direction * t;}
    };



#endif