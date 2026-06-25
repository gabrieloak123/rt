#include "transform.hpp"
#include <cmath>
#include "common.hpp"
#include "ray.hpp"
#include "fbounds.hpp"
#include "surfel.hpp"


namespace rt{

    inline double gamma(int n) {
        double epsilon = std::numeric_limits<double>::epsilon() * 0.5;
        return (n * epsilon) / (1.0 - n * epsilon);
    }   

    Transform::Transform() : t_matrix(), t_matrix_inv() {};
    Transform::Transform(const Mat4& t_matrix) : t_matrix(t_matrix), t_matrix_inv(t_matrix.inverse()) {};
    Transform::Transform(const Mat4& t_matrix, const Mat4& t_matrix_inv) : t_matrix(t_matrix), t_matrix_inv(t_matrix_inv) {};

    Transform Transform::inverse()   const {return   Transform(t_matrix_inv, t_matrix);}
    Transform Transform::transpose() const {return Transform(t_matrix.transpose(), t_matrix_inv.transpose());}

    void Transform::operator=(const Transform& t){
        t_matrix = t.getTMat();
        t_matrix_inv = t.getTMatInv();
    }
    Point4 Transform::operator()(const Point4& p, bool isNormal) const {
        if(!isNormal)
            return t_matrix * p;
        return t_matrix_inv.transpose() * p;
    }
    Point3 Transform::operator()(const Point3& p, const bool& isVector, const bool& isNormal, Vec3* err) const{
        if(!isVector)
            {
            Point3 result = (t_matrix * Vec4(p, 1)).xyz();

            if(err) 
            {
                double xErr = (std::abs(t_matrix(0, 0) * p.x()) + std::abs(t_matrix(0, 1) * p.y()) + std::abs(t_matrix(0, 2) * p.z()) + std::abs(t_matrix(0, 3)));
                double yErr = (std::abs(t_matrix(1, 0) * p.x()) + std::abs(t_matrix(1, 1) * p.y()) + std::abs(t_matrix(1, 2) * p.z()) + std::abs(t_matrix(1, 3)));
                double zErr = (std::abs(t_matrix(2, 0) * p.x()) + std::abs(t_matrix(2, 1) * p.y()) + std::abs(t_matrix(2, 2) * p.z()) + std::abs(t_matrix(2, 3)));
                *err = Vec3(xErr, yErr, zErr) * gamma(3);
            }
            
            return result;
        }
        if(!isNormal) return (t_matrix * Vec4(p, 0)).xyz();
        return (t_matrix_inv.transpose() * Vec4(p, 0)).xyz();
    }
    
    Ray Transform::operator()(const Ray& r) const {
        Vec3 err;
        Point3 o = (*this)(r.getOrigin(), false, false, &err);
        Vec3 d = (*this)(r.getDirection(), true, false);  
        double lengthSqr = d.sqr_length();
        double tMin = r.getTMin();
        double tMax = r.getTMax();

        if (lengthSqr > 0) {
            Vec3 absD = {std::abs(d[0]), std::abs(d[1]), std::abs(d[2])};
            double dt = dot(absD, err) / lengthSqr;
            o += d * dt;
            tMax -= dt;
        }

        return Ray(o, d, tMin, tMax);
    }
    Bounds3f Transform::operator()(const Bounds3f& b) const {
        const Transform &M = *this;
        Bounds3f ret(b);    

        ret.merge(M(Point3(b.max().x(), b.min().y(), b.min().z())));
        ret.merge(M(Point3(b.min().x(), b.max().y(), b.min().z())));
        ret.merge(M(Point3(b.min().x(), b.min().y(), b.max().z())));
        ret.merge(M(Point3(b.min().x(), b.max().y(), b.max().z())));
        ret.merge(M(Point3(b.max().x(), b.max().y(), b.min().z())));
        ret.merge(M(Point3(b.max().x(), b.min().y(), b.max().z())));
        ret.merge(M(Point3(b.max().x(), b.max().y(), b.max().z())));
        
        return ret;
    }

    Surfel Transform::operator()(const Surfel& s) const{
        auto temp = s;
        temp.n = (*this)(s.n, true, true);
        temp.p = (*this)(s.p, false, false);
        temp.wo= (*this)(s.wo, true, false);

        temp.n.mk_unit_vec();
        temp.wo.mk_unit_vec();

        return temp;
    }

    Transform Transform::operator()(const Transform& t) const {
        return Transform(t_matrix * t.getTMat(),t.getTMatInv() * t_matrix_inv);
    }
    Transform Transform::operator*(const Transform& t) const {
        return Transform(t_matrix * t.getTMat(),t.getTMatInv() * t_matrix_inv);
    }

    Transform Transform::translate(const Vec3& delta)
    {
        Mat4 m(   1, 0, 0, delta.x(),
                  0, 1, 0, delta.y(),
                  0, 0, 1, delta.z(),
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

        Mat4 m(   c + c1 * kx * kx,      c1 * kx * ky - s * kz, c1 * kx * kz + s * ky, 0, 
                  c1 * kx * ky + s * kz, c + c1 * ky * ky,      c1 * ky * kz - s * kx, 0,
                  c1 * kx * kz - s * ky, c1 * ky * kz + s * kx, c + c1 * kz * kz,      0,
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

        Vec3 w{look_from - look_at}; //< Create the W axis aligned with vpn.
        w.mk_unit_vec();

        Vec3 u = -cross(vup, w); //< Create the U axis perpendicular to the vup and W.
        u.mk_unit_vec();

        Vec3 v = cross(w, u); //< Create the V axis perpendicular to W and U .
        v.mk_unit_vec();

        Mat4 m_camera_to_world( //< Creates the transformation matrix responsible for the linear
                                //< transformation from camera to image.
                u[0], v[0], w[0], look_from[0], 
                u[1], v[1], w[1], look_from[1], 
                u[2], v[2], w[2], look_from[2], 
                0.0, 0.0, 0.0,            1.0);

        Mat4 m_camera_to_world_inv = m_camera_to_world.inverse();

        return Transform(m_camera_to_world, m_camera_to_world_inv);
    }

} //< namespace rt