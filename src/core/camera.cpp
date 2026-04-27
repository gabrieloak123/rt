#include "camera.hpp"

namespace rt {

Camera::Camera(CameraType_e type, Point3 &look_from, const Vec3 look_at,
               const Vec3 vup, Vec3 vpn, double l, double r, double b, double t,
               int nx, int ny, double focal_dist)
    : m_type(type), m_origin(look_from), m_focal_distance(focal_dist) {

  Vec3 gaze{look_at -
            look_from}; //< Create and calculate the main projection direction
  m_gaze_dir = gaze;
  m_gaze_dir.mk_unit_vec();

  Vec3 w{vpn}; //< Create the W axis aligned with vpn.
  w.mk_unit_vec();

  Vec3 u = cross(vup, w); //< Create the U axis perpendicular to the vup and W.
  u.mk_unit_vec();

  Vec3 v = cross(w, u); //< Create the V axis perpendicular to W and U .
  v.mk_unit_vec();

  m_camera_to_world =
      Mat4( //< Creates the transformation matrix responsible for the linear
            // transformation from camera to image.
          u[0], v[0], w[0], look_from[0], u[1], v[1], w[1], look_from[1], u[2],
          v[2], w[2], look_from[2], 0.0, 0.0, 0.0, 1.0);

  double width{r - l}, height{t - b}; //< Screen limits

  m_raster_to_screen =
      Mat4( //< Creates the transformation matrix responsible for the linear
            // transformation from raster to sceen.
          width / nx, 0.0, 0.0, l + width / (2.0 * nx), 0.0, height / ny, 0.0,
          b + height / (2.0 * ny), 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

Ray Camera::generate_ray(int i, int j) {
  Point4 p_raster(static_cast<double>(i), static_cast<double>(j), 0.0,
                  1.0); //< Pixel (i, j)
  Point4 p_camera{m_raster_to_screen *
                  p_raster}; //< Maps the pixel to the screen window in the
                             // camera's coordinate sys.

  switch (m_type) {
  case CameraType_e::ORTHOGRAPHIC: //< Case Ortographic
  {
    Point4 origin4d{m_camera_to_world *
                    p_camera}; //< Origin starts from the projection plane
                               // transformed to world space.
    return Ray(
        Point3(origin4d[0], origin4d[1], origin4d[2]),
        m_gaze_dir); //< Return a ray who travel parallel to the gaze direction
  }

  default: //< Case Perspective
  {
    p_camera[2] = m_focal_distance; //< Push the target point on the screen to
                                    // world space.
    Point4 target4d{m_camera_to_world *
                    p_camera}; //< Convert the target point to world space.
    Point3 target_world(target4d[0], target4d[1], target4d[2]);
    Vec3 direction{target_world -
                   m_origin}; //< Create a vector based on the difference
                              // between the two points.
    direction.mk_unit_vec();

    return Ray(
        m_origin,
        direction); //< Return a ray who shoot from the origin to the direction.
  }
  }
}

std::unique_ptr<Camera> create_camera(const ParamSet &camera,
                                      const ParamSet &look_at) {
#ifdef DEBUG
  std::cout << ">>> Inside create_camera()\n";
#endif

  //==[1] Retrieve lookat tag.
  auto lookfrom{look_at.retrieve<Vec3>("look_from", Vec3(0, 0, 0))};
  auto lookat{look_at.retrieve<Vec3>("look_at", Vec3(0, 0, -1))};
  auto up{look_at.retrieve<Vec3>("up", Vec3(0, 1, 0))};

  //==[2] Retrieve camera type.
  std::unordered_map<string, Camera::CameraType_e> camera_type_opts{
      {"orthographic", Camera::CameraType_e::ORTHOGRAPHIC},
      {"perspective", Camera::CameraType_e::PERSPECTIVE},
  };

  auto camera_type{
      camera_type_opts[camera.retrieve<string>("type", "orthographic")]};

  //==[3] Retrieve orthographic data.
  if (camera_type == Camera::CameraType_e::ORTHOGRAPHIC) {

    auto screen_window = camera.retrieve<Point4>("screen_window");

#ifdef DEBUG
    std::cout << "================================================\n";
    std::cout << ">>> create_camera() - orthographic camera parameters are:\n";
    std::cout << "    - look_at: " << lookat << "\n";
    std::cout << "    - look_from: " << lookfrom << "\n";
    std::cout << "    - up: " << up << "\n";
    std::cout << "    - screen_window: " << screen_window << "\n";
    std::cout << "================================================\n";
#endif

	// TODO: instanciate
    return std::make_unique<Camera>(dimensions.first, dimensions.second, filename,
                                  film_type, img_type, apply_gamma_correction);
  }
  //==[4] Retrieve perspective data.

    auto fovy = camera.retrieve<double>("fovy", 1.0);

#ifdef DEBUG
    std::cout << "================================================\n";
    std::cout << ">>> create_camera() - perspective camera parameters are:\n";
    std::cout << "    - look_at: " << lookat << "\n";
    std::cout << "    - look_from: " << lookfrom << "\n";
    std::cout << "    - up: " << up << "\n";
    std::cout << "    - fovy: " << fovy << "\n";
    std::cout << "================================================\n";
#endif

	// TODO: instanciate
    return std::make_unique<Camera>(dimensions.first, dimensions.second, filename,
                                  film_type, img_type, apply_gamma_correction);
}
}; // namespace rt
