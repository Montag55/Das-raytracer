#define _USE_MATH_DEFINES
#include <cmath>
#include "camera.hpp"

Camera::Camera():
m_pos{glm::vec3{ 0, 0, 0 }},
m_dir{glm::vec3{ 0, 0, 1 }},
m_up{glm::vec3{ 0, 1, 0 }},
m_fov_x{45.0},
m_name{"Default Camera"} {}

Camera::Camera(
    glm::vec3 const& position, glm::vec3 const& dir, glm::vec3 const& up,
    double fov_x, std::string const& name
):
m_pos{position},
m_dir{dir},
m_up{up},
m_fov_x{fov_x},
m_name{name} {}

Camera::Camera(Camera const& cam) :
m_pos{ cam.m_pos },
m_dir{ cam.m_dir },
m_up{ cam.m_up },
m_fov_x{ cam.m_fov_x },
m_name{cam.m_name} {}

Camera::~Camera() {}

/**
 * @brief  Creates a ray that has the camera position as origin. The direction
 * are determined by the passed arguments and the focal distance.
 */
 /*
Ray Camera::camera_ray(double x_coord, double y_coord) const {
    return {
        m_pos,
        glm::vec3{ x_coord, y_coord, -focal_distance() }
    };
}

Camera& Camera::operator=(Camera const& tmp_cam) {
    if (this == &tmp_cam) {
        return *this;
    }

    m_pos = tmp_cam.m_pos;
    m_dir = tmp_cam.m_dir;
    m_up = tmp_cam.m_up;

    m_fov_x = tmp_cam.m_fov_x;
    m_name = tmp_cam.m_name;

    return *this;
}




std::ostream& operator<<(std::ostream& os, Camera const& cam) {
    os << cam.m_name << " / " <<  "px (fov: " << cam.m_fov_x << "°)";
    return os;
}
*/