#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <string>
#include "ray.hpp"

struct Camera {
    Camera();
    Camera(glm::vec3 const& position, glm::vec3 const& dir, glm::vec3 const& up,
             double fov_x, std::string const& name);

    Camera(Camera const& cam);
    ~Camera();

    /*Ray camera_ray(double x_coord, double y_coord) const;
    Camera& operator=(Camera const& tmp_cam);
    friend std::ostream& operator<<(std::ostream& os, Camera const& cam);
*/
    glm::vec3 m_pos, m_dir, m_up;
    double m_fov_x;
    std::string m_name;
};

#endif