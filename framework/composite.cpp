#include "composite.hpp"
#include <cmath>
#include <catch.hpp>
#include <algorithm>



Composite::Composite():
	m_name("default-comp"),
	m_shapes() {}

Composite::Composite(std::string name ):
	m_name(name),
	m_shapes() {}

Composite::~Composite() {}

/*
void Composite::add(std::shared_ptr<Shape> shape) const
{
	m_shapes.push_back(shape);
}
*/

Hit Composite::intersect(Ray ray) const
{
	Hit hit;
	Hit temphit;
	for( auto &i : m_shapes)
	{
		std::cout<< "get back too da choppa!" << "\n";
	  temphit= i->intersect(ray);
	  if(temphit.m_distance<hit.m_distance)
	  {
	    hit = temphit;
	  }
	} 
	return hit;
}

void Composite::add(shape_pointer const& shape)
{
    m_shapes.push_back(shape);
} 

void Composite::set_name(std::string const name)
{   
    std::cout<< "setname" << "\n";
    std::cout<< name << "\n";
    m_name = name;
 
    
} 