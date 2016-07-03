#include "shape.hpp"


Shape::Shape():
    name_{"default"},
    material_{} 
    {std::cout<< "Shape constructed" << "\n";}

Shape::Shape(std::string const& name, Material const& clr):
    name_{name},
    material_{clr} 
    {std::cout<< "Shape constructed" << "\n";}

Shape::~Shape()
{std::cout<< "Shape destructed" << "\n";}


std::ostream& Shape::print(std::ostream& os) const
{
	os 	<< "Name:   " << name_ << "\n"
		<< "Material:  " << material_ << "\n";

	return os;
}

std::ostream& operator <<(std::ostream& os, Shape const& s)
{
	return s.print(os);
}


Material const& Shape::material() const
{
  return material_;
}
	
std::string const& Shape::name() const
{
  return name_;
}