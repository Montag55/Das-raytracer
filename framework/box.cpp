#include "box.hpp"
#include <glm/vec3.hpp>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <catch.hpp>


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
/*
Box::Box(std::string const& name, Material const& mtrl, glm::vec3 const& min, glm::vec3 const& max )
    : Shape{name, mtrl},
    m_min{min},
    m_max{max}
    {} 
*/
Box::Box(std::string const& name, std::shared_ptr<Material> mtrl, glm::vec3 const& min, glm::vec3 const& max )
    : Shape{name, mtrl},
    m_min{min},
	m_max{max}
	{} 
/*
Box::Box(std::string const& name, Material* const& material, glm::vec3 const& min, glm::vec3 const& max )
    : Shape{name, material},
    m_min{min},
    m_max{max}
    {}
*/

//getter
glm::vec3 const& Box::min() const 
	{return m_min;}

glm::vec3 const& Box::max() const 
	{return m_max;}



/*//functions
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
*/

Hit Box::intersect(Ray ray) const
{

    Hit boxhit;

    if (transf())
    {
        ray = transformRay(world_transformation_inv(), ray);
    }

    double t1 = (m_min.x - ray.origin.x)*ray.inv_direction.x;
    double t2 = (m_max.x - ray.origin.x)*ray.inv_direction.x;
    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);

    t1 = (m_min.y - ray.origin.y)*ray.inv_direction.y;
    t2 = (m_max.y - ray.origin.y)*ray.inv_direction.y;
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));

    t1 = (m_min.z - ray.origin.z)*ray.inv_direction.z;
    t2 = (m_max.z - ray.origin.z)*ray.inv_direction.z;
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));



    if (tmax > std::max(0.0, tmin))
    {   
        boxhit.m_hit = true;
        boxhit.m_distance = glm::length(boxhit.m_intersection-ray.origin);

        boxhit.m_shape = this;
        boxhit.m_intersection = glm::vec3{tmin*ray.direction.x, tmin*ray.direction.y, tmin*ray.direction.z};

        

        if((boxhit.m_intersection.x) == Approx(m_min.x))
            {
                boxhit.m_normal = glm::vec3{-1, 0, 0};
            }

        else if((boxhit.m_intersection.x) == Approx(m_max.x))
            {
                boxhit.m_normal = glm::vec3{1, 0, 0};
            }

        else if((boxhit.m_intersection.y) == Approx(m_min.y))
            {
                boxhit.m_normal = glm::vec3{0, -1, 0};
            }

        else if((boxhit.m_intersection.y) == Approx(m_max.y))
            {
                boxhit.m_normal = glm::vec3{0, 1, 0};
            }

        else if((boxhit.m_intersection.z) == Approx(m_min.z))
            {
                boxhit.m_normal = glm::vec3{0, 0, -1};
            }

        else if((boxhit.m_intersection.z) == Approx(m_max.z))
            {
                boxhit.m_normal = glm::vec3{0, 0, 1};
            }
    } 
    return boxhit;
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