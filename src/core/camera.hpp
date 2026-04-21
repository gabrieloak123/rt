#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ssmath/ssmath.hpp"
#include "ray.hpp"

using Mat4 = mat4<double>;
using Point3 = vec3<double>;
using Point4 = vec4<double>;
using Vec3 = vec3<double>;


/**
 * @brief Supported camera projection types.
 */
enum CameraType_e {
	ORTHOGRAPHIC = 0,
	PERSPECTIVE
};

namespace rt {

/**
 * @class Camera
 * @brief Manages the projection of the 3D scene onto the 2D image plane.
 * @details This class calculates and stores the transformation matrices (Camera-to-World and Raster-to-Screen)
 * 			to generate rays in an optimized manner during rendering. It natively supports oblique projections 
 * 			by parameterizing the View Plane Normal (VPN).
 */
class Camera {
public:

	/**
     * @brief Camera constructor. Pre-computes all transformation matrices.
     * @param type The projection type (ORTHOGRAPHIC or PERSPECTIVE).
     * @param look_from The camera's position in world space.
     * @param look_at The target point in space the camera is aiming at.
     * @param vup The View-Up vector (defines which direction is "up").
     * @param vpn The View Plane Normal vector (defines the tilt of the projection plane, useful for oblique projections).
     * @param l Left boundary of the projection window.
     * @param r Right boundary of the projection window.
     * @param b Bottom boundary of the projection window.
     * @param t Top boundary of the projection window.
     * @param nx Horizontal resolution of the final image in pixels.
     * @param ny Vertical resolution of the final image in pixels.
     * @param focal_dist Focal distance (distance from the camera to the projection plane). Relevant for perspective.
     */
	Camera(CameraType_e type, Point3& look_from, const Vec3 look_at, const Vec3 vup,  Vec3 vpn, 
		   double l, double r, double b, double t, int nx, int ny, double focal_dist = 1.0);
	

	~Camera() = default;
	
	/**
      * @brief Generates a ray starting from the camera and passing through the specified pixel.
      * @param i The x-coordinate (column) of the pixel in the raster.
      * @param j The y-coordinate (row) of the pixel in the raster.
      * @return Ray The mathematical ray configured with its origin and direction in world space.
      */
	Ray generate_ray(int i, int j);

private:
	CameraType_e m_type;	   		 //< Stores the current projection type.

	Mat4 m_camera_to_world; 	     //< Matrix that transforms from camera space to world space.
	Mat4 m_raster_to_screen; //< Matrix that transforms from pixel coordinates to the camera screen.
	Point3 m_origin;				 //< Camera position.
	Vec3 m_gaze_dir;				 //< Gaze direction.
	double m_focal_distance;		 //< Focal distance used in perspective projection.
	
};

} // namespace rt
#endif //CAMERA_HPP
