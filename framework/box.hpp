#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "material.hpp"
#include "ray.hpp"

class Box : public Shape
{
public:
	//constructors
	 Box();
	 Box(std::string const& name, Material const& mtrl, glm::vec3 const& min, glm::vec3 const& max );
	 Box(glm::vec3 const& min, glm::vec3 const& max);

	 //getter
	 glm::vec3 const& min() const;
	 glm::vec3 const& max() const;

	 //functions
	 float volume() const override;
	 float area() const override;

	 std::ostream& print(std::ostream& os) const override;

	 bool intersect(Ray const& ray, float& t) const override;

private:
	glm::vec3 m_min;
	glm::vec3 m_max;
};


#endif