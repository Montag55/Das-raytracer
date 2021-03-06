#include "sphere.hpp"
#include <catch.hpp>
#include <iostream>
#include <glm/vec3.hpp>
#include <cmath>
#include "hit.hpp"
#include <glm/glm.hpp>
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

/*
Sphere::Sphere(std::string const& name, Material const& mtrl, glm::vec3 const& ctr, float r):
	Shape{name, mtrl},
	m_center{ctr},
	m_radius{r}{}
	//{std::cout<< "Sphere constructed" << "\n";}
*/

Sphere::Sphere(std::string const& name, std::shared_ptr<Material> mtrl, glm::vec3 const& ctr, float r):
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

/*
//functions
float Sphere::volume() const
	{
		return 4.0f / 3.0f * (M_PI* m_radius * m_radius * m_radius);
	}

float Sphere::area() const
	{
		return 4.0f* M_PI * m_radius * m_radius;
	}
*/
Hit Sphere::intersect(Ray const& inray) const
	{
		Hit spherehit;
		Ray ray;
		if (transf())
    	{
        //Ray newray = transformRay(transformRay(world_transformation_inv(), ray));
        	ray =  transformRay(world_transformation_inv(), inray);
    	}
    	else
    		ray = inray;

    	ray.direction = glm::normalize(ray.direction);
		spherehit.m_hit = glm::intersectRaySphere(ray.origin, ray.direction,
			m_center, m_radius, spherehit.m_intersection, spherehit.m_normal);

		/*std::cout<< "Spherehit at: " <<spherehit.m_intersection.x  << ", "
	    << spherehit.m_intersection.y  << ", "<< spherehit.m_intersection.z << "\n";
	    */
        if (transf()){

            //spherehit.m_intersection = glm::vec3(world_transformation()* glm::vec4(spherehit.m_intersection, 1));
            spherehit.m_normal = glm::vec3(glm::mat3(world_transformation_inv_transp())* spherehit.m_normal);    
        }
        if (glm::distance(spherehit.m_intersection-0.001f*ray.direction, m_center) < m_radius){
        	spherehit.m_normal = -spherehit.m_normal;
        }

		if (spherehit.m_hit)
		{
			spherehit.m_distance = glm::distance(ray.origin, spherehit.m_intersection);
			spherehit.m_shape = this;
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