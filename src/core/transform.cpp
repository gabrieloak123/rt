#include "transform.hpp"
#include "ssmath/vec2.hpp"
#include <cmath>

namespace rt{

    Transform Transform::translate(const Vec3& delta)
    {
        Mat4 m(   1, 0, 0, delta.x(),
                  0, 1, 0, delta.y(),
                  0, 0, 1, delta.y(),
                  0, 0, 0, 1);

        Mat4 minv(1, 0, 0, -delta.x(),
                  0, 1, 0, -delta.y(),
                  0, 0, 1, -delta.z(),
                  0, 0, 0, 1);

        return Transform(m, minv);
    }

    Transform Transform::rotate(const double& angle, const Vec3& delta)
    {
        double c = std::cos((M_PI / 180.0) * angle);
        double s = std::sin((M_PI / 180.0) * angle);
        double c1 = 1 - c;

        Vec3 k = unit_vec(delta);
        double kx = k.x();
        double ky = k.y();
        double kz = k.z(); 

        Mat4 m(   c + c1 * kx * kx, c1 * kx * ky - s * kz, c1 * kx * kz + s * ky, 0, 
                  c1 * kx * ky + s * kz, c1 * ky * ky, c1 * ky * kz - s * kx, 0,
                  c1 * kx * kz - s * ky, c1 * ky * kz + s * kx, c + c1 * kz * kz, 0,
                  0, 0, 0, 1);

        Mat4 minv = m.transpose();

        return Transform(m, minv);
    }

    Transform Transform::scale(const Vec3& scales)
    {
        Mat4 m(   scales.x(), 0, 0, 0,
                  0, scales.y(), 0, 0,
                  0, 0, scales.z(), 0,
                  0, 0, 0, 1);

        Mat4 minv(1/scales.x(), 0, 0, 0,
                  0, 1/scales.y(), 0, 0,
                  0, 0, 1/scales.z(), 0,
                  0, 0, 0, 1);

        return Transform(m, minv);
    }

    Transform Transform::lookAt(const Vec3& look_from, const Vec3& look_at, const Vec3& vup){

    }

} //< namespace rt