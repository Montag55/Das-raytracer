#include "sphere.hpp"
#include <catch.hpp>
#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>
#include "hit.hpp"
#define _USE_MATH_DEFINES



//Constructors
Sphere::Sphere():
	Shape{},
    m_center{0.0},
    m_radius{1.0f}{}
        //{std::cout<< "Sphere constructed" << "\n";}
    
    
Sphere::Sphere(glm::vec3 const& ctr, float r):
	Shape{},
	m_center{ctr},
	m_radius{r} {
	    //{std::cout<< "Sphere constructed" << "\n";}
	}


Sphere::Sphere(std::string const& name, Material const& mtrl, glm::vec3 const& ctr, float r):
	Shape{name, mtrl},
	m_center{ctr},
	m_radius{r}{}
	//{std::cout<< "Sphere constructed" << "\n";}


Sphere::Sphere(std::string const& name, Material* const& mtrl, glm::vec3 const& ctr, float r):
	Shape{name, mtrl},
	m_center{ctr},
	m_radius{r}{}
	//{std::cout<< "Sphere constructed" << "\n";}

Sphere::~Sphere(){
	//{std::cout<< "Sphere destructed" << "\n";}
}


//getter
glm::vec3 const& Sphere::center() const 
	{return m_center;}

float Sphere::radius() const 
	{return m_radius;}


//functions
float Sphere::volume() const
	{
		return 4.0f / 3.0f * (M_PI* m_radius * m_radius * m_radius);
	}

float Sphere::area() const
	{
		return 4.0f* M_PI * m_radius * m_radius;
	}

Hit Sphere::intersect(Ray const& ray) const
	{
		Hit spherehit;

		spherehit.m_hit = glm::intersectRaySphere(ray.origin, ray.direction,
			m_center, m_radius, spherehit.m_intersection, spherehit.m_normal);

		std::cout<< "Spherehit at: " <<spherehit.m_intersection.x  << ", "
	   << spherehit.m_intersection.y  << ", "<< spherehit.m_intersection.z << "\n";
		if (spherehit.m_hit)
		{
			spherehit.m_distance = glm::distance(ray.origin, spherehit.m_intersection);
			spherehit.m_shape = std::make_shared<Sphere> (*this);
		}
			
		return spherehit;
	}


std::ostream& Sphere::print(std::ostream& os) const
{
	Shape::print(os);
	os << "Radius:  " << m_radius << "\n"
	   << "Center:   ("
	   << m_center.x << ", "
	   << m_center.y << ", "
	   << m_center.z << ")" << "\n";

	return os;
}