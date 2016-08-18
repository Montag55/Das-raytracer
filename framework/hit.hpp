#ifndef HIT_HPP
#define HIT_HPP
#include "shape.hpp"
#include <memory>


class Shape;

struct Hit
{
    //KONSTRUTOREN----------------------------------------------------------------
    Hit();
    Hit(bool hit, double distance, glm::vec3 const& intersection,
        glm::vec3 const& normal, Shape* const shape);
    Hit(Hit const& tmp_hit);
    //FUNKTIONEN------------------------------------------------------------------
    Hit& operator=(Hit const& tmp_hit);
	//Copyconstructor fehlt noch
	//unsigned distence? nicht verkacken bitte


    bool m_hit;
    double m_distance;
    glm::vec3 m_intersection;
    glm::vec3 m_normal;
    Shape* m_shape;
};

#endif