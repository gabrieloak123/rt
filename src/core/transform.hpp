#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "camera.hpp"
namespace rt {

    class Transform {
        private:
            Mat4 t_matrix;     //< Transformation Matrix
            Mat4 t_matrix_inv; //< Inverse Transformation Matrix
        public:
            Transform() : t_matrix(), t_matrix_inv() {};
            Transform(const Mat4& t_matrix) : t_matrix(t_matrix), t_matrix_inv(t_matrix.inverse()) {};
            Transform(const Mat4& t_matrix, const Mat4& t_matrix_inv) : t_matrix(t_matrix), t_matrix_inv(t_matrix_inv) {};

            Transform inverse()   {return   Transform(t_matrix_inv, t_matrix);}
            Transform transpose() {return Transform(t_matrix.transpose(), t_matrix_inv.transpose());}

            Transform translate(const Vec3& delta);
            Transform rotate(const double& angle, const Vec3& delta);
            Transform scale(const Vec3& scales);
            Transform lookAt(const Vec3& look_from, const Vec3& vpn, const Vec3& vup);

            Mat4 getTMat()    const {return this->t_matrix;};
            Mat4 getTMatInv() const {return this->t_matrix_inv;};
    };

}; //< namespace rt


#endif