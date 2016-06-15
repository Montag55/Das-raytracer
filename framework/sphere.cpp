#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <cmath>



Sphere::Sphere() :
	Sphere::Shape{},
	m_radius{1.0f},
	m_center{0.0}
{}

Sphere::Sphere(float radius, glm::vec3 const& center) :
	Sphere::Shape{},
	m_radius{radius},
	m_center{center}
{}

Sphere::Sphere(glm::vec3 const& center, float radius, Color const& color,  std::string const& name) :
	Sphere::Shape{name, color},
	m_radius{radius},
	m_center{center}
{}

std::ostream& Sphere::print(std::ostream& os) const{
	Shape::print(os);
	os << "Radius " << m_radius << "\n" << "Center " << m_center.x << m_center.y << m_center.z << "\n";
	return os;
}

std::ostream& operator <<(std::ostream& os, Sphere const& s){
	return s.print(os);
}


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

bool Sphere::intersect(Ray const& ray, float& dis) const{
	return glm::intersectRaySphere(ray.origin, ray.direction , m_center, m_radius * m_radius, dis);
}
