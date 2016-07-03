#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "material.hpp"
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

class Sphere : public Shape
{
public:
	//constructors
	 Sphere();
	 Sphere(glm::vec3 const& ctr, float r);
	 Sphere(std::string const& name, Material const& mtrl, glm::vec3 const& ctr, float r);

	 ~Sphere();
	 //getter
	 glm::vec3 const& center() const;
	 float radius() const;

	 //functions
	 float volume() const override;
	 float area() const override;

	 std::ostream& print(std::ostream& os) const override;

	 bool intersect(Ray const& ray, float& t) const override;


private:
	float m_radius;
	glm::vec3 m_center;
};

#endif