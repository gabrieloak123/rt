#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "film.hpp"

enum CameraType_e {
	ORTHOGRAPHIC = 0,
};

namespace rt {

class Camera {
public:
	Camera();
	~Camera() = default;

	Film film() { return m_film; };
private:
	CameraType_e m_type;
	Film m_film;
};

} // namespace rt
#endif //CAMERA_HPP
