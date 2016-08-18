#include "composite.hpp"
#include <cmath>
#include <catch.hpp>
#include <algorithm>



Composite::Composite():
	m_name("default-comp"),
	m_shapes() {}

Composite::Composite(std::string const& name ):
	m_name(name),
	m_shapes() {}

Composite::~Composite() {}

/*
void Composite::add(std::shared_ptr<Shape> shape) const
{
	m_shapes.push_back(shape);
}
*/

Hit Composite::intersect(Ray const& ray) const
{
	Hit hit;
	Hit temphit;
	for( auto &i : m_shapes)
	{
	  temphit= i->intersect(ray);
	  if(temphit.m_distance<hit.m_distance)
	  {
	    hit = temphit;
	  }
	} 
	return hit;
}
