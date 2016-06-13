#include "box.hpp"
#include <glm/vec3.hpp>
#include <cmath>


Box::Box():
	m_min{-1.0},
	m_max{1.0}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
	m_max{max},
	m_min{min}
{}

glm::vec3 const& Box::min() const {
	return m_min;
}

glm::vec3 const& Box::max() const {
	return m_max;
}

float Box::volume() const {
	auto diff = m_max - m_min;
	return diff.x * diff.y * diff.z;
}

float Box::area() const {
	auto diff = m_max - m_min;
	return 2.0f*(diff.x*diff.y)+2.0f*(diff.y*diff.z)+2.0f*(diff.x*diff.z);
}