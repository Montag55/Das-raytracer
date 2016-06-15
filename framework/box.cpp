#include "box.hpp"
#include <glm/vec3.hpp>
#include <cmath>


Box::Box():
	Box::Shape{},
	m_min{-1.0},
	m_max{1.0}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
	Box::Shape{},
	m_min{min},
	m_max{max}
{}

Box::Box(std::string const& name, Color const& color, glm::vec3 const& min, glm::vec3 const& max):
	Box::Shape{name, color},
	m_min{min},
	m_max{max}
{}

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	os << "Min " << m_min.x << m_min.y << m_min.z<< "\n" << "Max " << m_max.x << m_max.y << m_max.z<< "\n"; 
	return os;
}

std::ostream& operator <<(std::ostream& os, Box const& b){
	return b.print(os);
}

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