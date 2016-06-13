#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape {
public:
	Sphere();
	Sphere(glm::vec3 const& center, float radius);

	glm::vec3 const& center() const;
	float radius() const;

	float volume() const override;
	float area() const override;

private:
	float m_radius;
	glm::vec3 m_center;

};
#endif