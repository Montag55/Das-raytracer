#ifndef HIT_HPP
#define HIT_HPP
#include "shape.hpp"
#include <memory>


class Shape;

struct Hit
{

	Hit();

	Hit(bool hit, double distance, glm::vec3 const& intersection,
        glm::vec3 const& normal, std::shared_ptr<Shape> shape);

	//Copyconstructor fehlt noch


    bool m_hit;
    double m_distance;
    glm::vec3 m_intersection;
    glm::vec3 m_normal;
    std::shared_ptr<Shape> m_shape;
};

#endif