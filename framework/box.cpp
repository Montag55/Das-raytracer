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
    std::cout<< "huhu boxhit\n";

    if (transf())
    {
        ray =  transformRay(world_transformation_inv(), ray);
        std::cout << "transformed Ray direction:  x:" << ray.direction.x << "\ny: "<< ray.direction.z << "\nz: "<< ray.direction.z << "\n";
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
        
        //boxhit.m_intersection = glm::vec3{tmin*ray.direction.x, tmin*ray.direction.y, tmin*ray.direction.z};
        boxhit.m_intersection = glm::vec3{tmin*ray.direction.x + ray.origin.x, tmin*ray.direction.y + ray.origin.y, tmin*ray.direction.z + ray.origin.z};
        boxhit.m_hit = true;
        boxhit.m_shape = this;
        boxhit.m_distance = glm::length(boxhit.m_intersection-ray.origin);
         

        std::cout<< "Boxhit min, box min: " << boxhit.m_intersection.x<< "   "<<m_min.x<< "\n";
        

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
        //std::cout<< "Boxhit normal: " << boxhit.m_normal.x<< "   "<< boxhit.m_hit<< "\n";
        
        if (transf()){
            boxhit.m_intersection= glm::vec3(world_transformation()* glm::vec4(boxhit.m_intersection, 1));
            
            boxhit.m_normal= glm::normalize(glm::vec3(glm::mat3(world_transformation_inv_transp())* boxhit.m_normal));
        }
    }    
   

          //   std::cout<< "Boxhit normal danach: " << boxhit.m_normal.x<< "   "<< boxhit.m_hit<< "\n";;

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