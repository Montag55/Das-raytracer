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

Box::Box(std::string const& name, Material* const& mtrl, glm::vec3 const& min, glm::vec3 const& max )
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

Hit Box::intersect(Ray const& ray) const
{

    Hit boxhit;
    
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
        boxhit.m_distance = sqrt(tmin*tmin*(
                                ray.direction.x*ray.direction.x +
                                ray.direction.y*ray.direction.y +
                                ray.direction.z*ray.direction.z));

        boxhit.m_shape = std::make_shared<Box> (*this);
        boxhit.m_intersection = glm::vec3{tmin*ray.direction.x, tmin*ray.direction.y, tmin*ray.direction.z};
    }

    /* Alte!

	float txmin = (m_min.x - ray.origin.x) / ray.direction.x; 
    float txmax = (m_max.x - ray.origin.x) / ray.direction.x; 
 
    if (txmin > txmax) std::swap(txmin, txmax); 
    float tmin = txmin;
    float tmax = txmax;
 
    float tymin = (m_min.y - ray.origin.y) / ray.direction.y; 
    float tymax = (m_max.y - ray.origin.y) / ray.direction.y; 
 
    if (tymin > tymax) std::swap(tymin, tymax); 
 
    if ((tmin > tymax) || (tymin > tmax)) 
        boxhit.m_hit = false; 
 
    if (tymin > tmin) 
        tmin = tymin; 
 
    if (tymax < tmax) 
        tmax = tymax; 
 
    float tzmin = (m_min.z - ray.origin.z) / ray.direction.z; 
    float tzmax = (m_max.z - ray.origin.z) / ray.direction.z; 
 
    if (tzmin > tzmax) std::swap(tzmin, tzmax); 
 
    if ((tmin > tzmax) || (tzmin > tmax)) 
        boxhit.m_hit = false; 
 
    if (tzmin > tmin) 
        tmin = tzmin; 
 
    if (tzmax < tmax) 
        tmax = tzmax; 
 
    boxhit.m_hit = true;
   
    
    if (boxhit.m_hit)
    {
        boxhit.m_distance = sqrt((txmin-ray.origin.x)*(txmin-ray.origin.x)+
                                (tymin-ray.origin.y)*(tymin-ray.origin.y)+
                                (tzmin-ray.origin.z)*(tzmin-ray.origin.z)
                                );

        boxhit.m_shape = std::make_shared<Box> (*this);
        boxhit.m_intersection = glm::vec3{tmin*ray.m_dir.x, tmin*ray.m_dir.y, tmin*ray.m_dir.z};
    }

    //nur zum pushen hinzugefügt
    */

    



    /*
    if (tmax > std::max(0.0, tmin)) {
        boxhit.m_distance = 
        );

        boxhit.m_intersection = glm::vec3{
            tmin*ray.m_dir.x, tmin*ray.m_dir.y, tmin*ray.m_dir.z
            };
        boxhit.m_normal = normal(boxhit.m_intersection);
        boxhit.m_shape = std::make_shared<Box>(*this);
        boxhit.m_hit = true;
    }
    */

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