#ifndef SHAPE_HPP
#define SHAPE_HPP
#define GLM_FORCE_RADIANS
#include "material.hpp"
#include <ostream>
#include "ray.hpp"
#include "hit.hpp"
#include <glm/mat4x4.hpp>
#include <memory>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"




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
	std::string const& name() const;
	//###############################################################
	bool const& transf() const;
	glm::mat4x4 const& world_transformation() const;
	glm::mat4x4 const& world_transformation_inv() const;
	/*
	virtual float area() const = 0;
	virtual float volume() const = 0;
	*/




	//Funktionen
	virtual std::ostream& print(std::ostream& os) const;
	virtual Hit intersect(Ray ray) const = 0;
	virtual void scale(glm::vec3 const& vec);
	virtual void rotate(float angle, glm::vec3 const& vec);
	virtual void translate(glm::vec3 const& vec);



private:
	std::string name_;
	std::shared_ptr<Material> material_;
	glm::mat4x4 world_transformation_;
	glm::mat4x4 world_transformation_inv_;
	bool m_transf;


};

//dingsoperator
std::ostream& operator <<(std::ostream& os, Shape const& s);


#endif