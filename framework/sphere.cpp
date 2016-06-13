#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <cmath>


Sphere::Sphere() :
	m_center{0.0},
	m_radius{1.0f}
{}

Sphere::Sphere(glm::vec3 const& center, float radius) :
		m_radius{radius},
		m_center{center}
	{}

glm::vec3 const& Sphere::center() const {
	return m_center;
}

float Sphere::radius() const {
	return m_radius;
}

float Sphere::volume() const {
	return 4.0f/3.0f * m_radius * m_radius * m_radius * M_PI;
}

float Sphere::area() const {
	return 4.0f * M_PI * m_radius * m_radius;
}

