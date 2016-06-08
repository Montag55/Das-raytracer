#ifndef SPHERE_HPP
#define SHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape {
public:
	Sphere();
	glm::vec3 const& center() const;
	float radius() const;

private:
	float m_radius;
	glm::vec3 m_center;

};
#endif