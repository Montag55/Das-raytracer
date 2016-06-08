#include "box.hpp"
#include <glm/vec3.hpp>


Box::Box():
	m_min{-1.0},
	m_max{1.0}
{}

glm::vec3 const& Box::min() const {
	return m_min;
}

glm::vec3 const& Box::max() const {
	return m_max;
}