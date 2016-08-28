#ifndef CAMERA_HPP
#define CAMERA_HPP
#define GLM_FORCE_RADIANS

#include <glm/vec3.hpp>
#include <string>
#include "ray.hpp"

#include "glm/detail/type_vec.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Camera {
    //Konstruktoren
    Camera();
    Camera(double fov_x, std::string const& name);

    //amera(Camera const& cam);
    //Destruktor
    ~Camera();


    //Transformationen
    void translate(glm::vec3 const& transl);
    void rotate(float angle, glm::vec3 const& axis);
    // + getter
     glm::mat4 GetTransformation() const {
        return transformation;
    }
    
    glm::mat4 GetTransformation_inv() const {
        return transformation_inv;
    }


    /*Ray camera_ray(double x_coord, double y_coord) const;
    Camera& operator=(Camera const& tmp_cam);
    friend std::ostream& operator<<(std::ostream& os, Camera const& cam);
*/  glm::mat4 transformation, transformation_inv;
    double m_fov_x;
    std::string m_name;
};

#endif