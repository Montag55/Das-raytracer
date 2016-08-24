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
        0, 0, 0, 1}},
    world_transformation_inv_transp_{glm::mat4x4 {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1}}
    {}
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
                                           0, 0, 0, 1}}
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

//####################################################################
bool const& Shape::transf() const{
  return m_transf;
}

glm::mat4x4 const& Shape::world_transformation() const{
  return world_transformation_;
}

glm::mat4x4 const& Shape::world_transformation_inv() const{
  return world_transformation_inv_;
}

glm::mat4x4 const& Shape::world_transformation_inv_transp() const{
  return world_transformation_inv_transp_;
}
//####################################################################


void Shape::scale(glm::vec3 const& vec)
  {   
    world_transformation_ = glm::scale(glm::mat4(), vec) * world_transformation_;
    world_transformation_inv_ = glm::scale(glm::mat4(), 1.0f /vec) * world_transformation_inv_;
    world_transformation_inv_transp_ = glm::transpose(glm::mat4(world_transformation_inv_));
    m_transf=true;
  }

void Shape::rotate(float angle, glm::vec3 const& vec)
    {
      angle = angle* 0.017453292519943f; //grad in rad
      world_transformation_ = glm::rotate(glm::mat4(), angle, vec) * world_transformation_;
      world_transformation_inv_ = glm::rotate(glm::mat4(), -angle, vec) * world_transformation_inv_;
      world_transformation_inv_transp_ = glm::transpose(glm::mat4(world_transformation_inv_));
      m_transf=true;
    }

void Shape::translate(glm::vec3 const& vec)
    {
      world_transformation_ = glm::translate(glm::mat4(), vec) * world_transformation_; //Erstellt aus dem Vec3 eine Matrix und multipliziert diese mit der aktuellen World Matrize
      world_transformation_inv_ = glm::translate(glm::mat4(), -vec) * world_transformation_inv_;
      world_transformation_inv_transp_ = glm::transpose(glm::mat4(world_transformation_inv_));
      m_transf=true;
    }
