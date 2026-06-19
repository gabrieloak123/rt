#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "common.hpp"

namespace rt {
    
    class Bounds3f;
    class Surfel;
    class Ray;

    class Transform {
        private:
            Mat4 t_matrix;     //< Transformation Matrix
            Mat4 t_matrix_inv; //< Inverse Transformation Matrix
        public:
            Transform();
            Transform(const Mat4& t_matrix);
            Transform(const Mat4& t_matrix, const Mat4& t_matrix_inv);
            Transform(const Transform&) = default;

            Transform inverse()   const;
            Transform transpose() const;

            Transform translate(const Vec3& delta);
            Transform rotate(const double& angle, const Vec3& delta);
            Transform scale(const Vec3& scales);
            Transform lookAt(const Vec3& look_from, const Vec3& vpn, const Vec3& vup);

            void operator=(const Transform& t);
            Point4 operator()(const Point4& p, bool isNormal=false) const;
            Point3 operator()(const Point3& p, const bool& isNormal=false, Vec3* = nullptr) const;
            Ray operator()(const Ray& p) const;
            Bounds3f operator()(const Bounds3f& b) const;
            Surfel operator()(const Surfel& s) const;
            Transform operator()(const Transform& t) const;

            Mat4 getTMat()    const {return this->t_matrix;};
            Mat3 getTMat3()   const {return Mat3
                                    (t_matrix(0, 0), t_matrix(0, 1), t_matrix(0, 2),
                                     t_matrix(1, 0), t_matrix(1, 1), t_matrix(1, 2),
                                     t_matrix(2, 0), t_matrix(2, 1), t_matrix(2, 2));}
            Mat4 getTMatInv() const {return this->t_matrix_inv;};
    };

}; //< namespace rt


#endif