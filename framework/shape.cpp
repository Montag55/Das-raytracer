#include "shape.hpp"


Shape::Shape():
    name_{"default"},
    material_{},
    world_transformation_{glm::mat4x4 {1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1}},
    world_transformation_inv_{glm::mat4x4 {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1   
    }}{}
    //{std::cout<< "Shape constructed" << "\n";}
/*
Shape::Shape(std::string const& name, Material const& mtrl):
    name_{name},
    material_{mtrl},
    world_transformation_{glm::mat4x4 {1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1}},
    world_transformation_inv_{glm::mat4x4 {1, 0, 0, 0,
                                           0, 1, 0, 0,
                                           0, 0, 1, 0,
                                           0, 0, 0, 1
                                          }}
    {} 
    //{std::cout<< "Shape constructed" << "\n";}
*/
Shape::Shape(std::string const& name, std::shared_ptr<Material> mtrl):
    name_{name},
    material_{mtrl}/*,
    world_transformation_{glm::mat4x4 {1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1}},
    world_transformation_inv_{glm::mat4x4 {1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1}}*/
    {} 
    //{std::cout<< "Shape constructed" << "\n";}

Shape::~Shape(){}
//{std::cout<< "Shape destructed" << "\n";}


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


std::shared_ptr<Material> Shape::material() const
{
  return material_;
}
	
std::string const& Shape::name() const
{
  return name_;
}