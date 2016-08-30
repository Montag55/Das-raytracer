#define _USE_MATH_DEFINES
#include <cmath>
#include "camera.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>


Camera::Camera():
transformation(glm::mat4()),
transformation_inv(glm::mat4()),
m_fov_x{45.0},
m_name{"Default Camera"} {}

Camera::Camera(double fov_x, std::string const& name):
transformation(glm::mat4()),
transformation_inv(glm::mat4()),
m_fov_x{fov_x},
m_name{name} {}

void Camera::translate(glm::vec3 const& transl) {
    std::cout << "translating: ("<< transl.x<<","<<transl.y<<","<<transl.z<<")"<<std::endl;
    transformation = transformation * glm::translate(glm::mat4(), transl);
    transformation_inv = transformation_inv *glm::translate(glm::mat4(), -transl);

    //std::cout<<glm::to_string(transformation)<<std::endl;
}

void Camera::rotate(float angle, glm::vec3 const& axis) {
   transformation = transformation * glm::rotate(glm::mat4(), angle, axis) ;
   transformation_inv = transformation_inv * glm::rotate(glm::mat4(), -angle, axis);
}

Ray Camera::calculate_eye_ray(int x,int y, float distance)
{   
    Ray rayman;
    rayman.origin = glm::vec3(transformation_inv*glm::vec4(0, 0, 0, 1));
    rayman.direction = glm::vec3(transformation_inv *
                                (glm::vec4(x, y, distance, 0)));

    //std::cout << "Ursprung:     " << rayman.origin.x<<"\n" << rayman.origin.y<<"\n" << rayman.origin.z<<"\n";
//std::cout << "Richtung:     " << rayman.direction.x<<"\n" << rayman.direction.y<<"\n" << rayman.direction.z<<"\n";

    return rayman;
}

Camera::~Camera() {}

/*
Camera::Camera(Camera const& cam) :
m_pos{ cam.m_pos },
m_dir{ cam.m_dir },
m_up{ cam.m_up },
m_fov_x{ cam.m_fov_x },
m_name{cam.m_name} {}
*/

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