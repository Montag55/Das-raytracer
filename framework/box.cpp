#include "box.hpp"
#include <glm/vec3.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>


//Constructors
Box::Box() :
    Shape{},
    m_min{0.0},
    m_max{0.0}
    {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
	Shape{},
	m_min{min},
	m_max{max}
	{}

Box::Box(std::string const& name, Material const& mtrl, glm::vec3 const& min, glm::vec3 const& max )
    : Shape{name, mtrl},
    m_min{min},
	m_max{max}
	{}

//getter
glm::vec3 const& Box::min() const 
	{return m_min;}

glm::vec3 const& Box::max() const 
	{return m_max;}


//functions
float Box::volume() const
	{
		auto diff = m_max - m_min;
		return diff.x * diff.y * diff.z;
	}

float Box::area() const
{ 	
	auto diff = m_max - m_min;

	return 2*(diff.y*diff.z + diff.x*diff.z + diff.x*diff.y); 
}

bool Box::intersect(Ray const& ray, float& t) const
{
	float tmin = (m_min.x - ray.origin.x) / ray.direction.x; 
    float tmax = (m_max.x - ray.origin.x) / ray.direction.x; 
 
    if (tmin > tmax) std::swap(tmin, tmax); 
 
    float tymin = (m_min.y - ray.origin.y) / ray.direction.y; 
    float tymax = (m_max.y - ray.origin.y) / ray.direction.y; 
 
    if (tymin > tymax) std::swap(tymin, tymax); 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        return false; 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = (m_min.z - ray.origin.z) / ray.direction.z; 
    float tzmax = (m_max.z - ray.origin.z) / ray.direction.z; 
 
    if (tzmin > tzmax) std::swap(tzmin, tzmax); 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        return false; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    return true; 
}

std::ostream& Box::print(std::ostream& os) const
{
	Shape::print(os);
	os << "Min:   ("
	   << m_min.x << ", "
	   << m_min.y << ", "
	   << m_min.z << ")" << "\n" 
	   << "Max:   ("
	   << m_max.x << ", "
	   << m_max.y << ", "
	   << m_max.z << ")" << "\n";

	return os;
}