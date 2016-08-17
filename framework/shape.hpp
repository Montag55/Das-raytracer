#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "material.hpp"
#include <ostream>
#include "ray.hpp"
#include "hit.hpp"
#include <glm/mat4x4.hpp>
#include <memory>



struct Hit; // forward declaration for intersect.
//NOCHMAL ANSCHAUEN

class Shape
{
public:
	//constr./Destr
	Shape();
	Shape(std::string const& name, Material const& mtrl);
	Shape(std::string const& name, std::shared_ptr<Material> mtrl);
	virtual ~Shape();

	//getter
	std::shared_ptr<Material> material() const;
  	void scale(glm::vec3 const& vec);
	std::string const& name() const;

	virtual float area() const = 0;
	virtual float volume() const = 0;

	virtual std::ostream& print(std::ostream& os) const;

	virtual Hit intersect(Ray const& ray) const = 0;
	
private:
	std::string name_;
	std::shared_ptr<Material> material_;
	glm::mat4x4 world_transformation_;
	glm::mat4x4 world_transformation_inv_;


};

//dingsoperator
std::ostream& operator <<(std::ostream& os, Shape const& s);


#endif