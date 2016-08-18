#include "hit.hpp"
#include <cmath> // INFINITY


Hit::Hit():
	m_hit{ false },
	m_distance{ INFINITY },
	m_intersection{ glm::vec3{ INFINITY, INFINITY, INFINITY } },
	m_normal{ glm::vec3{ INFINITY, INFINITY, INFINITY } },
	m_shape{ nullptr } {}



Hit::Hit(bool hit, double distance, glm::vec3 const& intersection,
        glm::vec3 const& normal,  Shape* const shape):
	m_hit{hit},
	m_distance{distance},
	m_intersection{intersection},
	m_normal{normal},
	m_shape{shape} {}

 //Custom 2
Hit::Hit(Hit const& tmp_hit) :
	m_hit{ tmp_hit.m_hit },
	m_distance{ tmp_hit.m_distance },
	m_intersection{ tmp_hit.m_intersection },
	m_normal{ tmp_hit.m_normal },
	m_shape{ tmp_hit.m_shape } {std::cout<<"Huhu\n";}

//FUNKTIOENNE----------------------------------------------------------------
Hit& Hit::operator=(Hit const& tmp_hit) 
{
    if (this == &tmp_hit) {
        return *this;
    }

    m_hit = tmp_hit.m_hit;
    m_distance = tmp_hit.m_distance;
    m_intersection = tmp_hit.m_intersection;
    m_normal = tmp_hit.m_normal;
    m_shape = tmp_hit.m_shape;

    return *this;
}
