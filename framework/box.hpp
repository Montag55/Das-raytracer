#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"


class Box : public Shape
{
public:
	//constructors
	 Box();
	 Box(std::string const& name, Material const& mtrl, glm::vec3 const& min, glm::vec3 const& max );
	 Box(glm::vec3 const& min, glm::vec3 const& max);
	 Box(std::string const& name, Material* const& material, glm::vec3 const& min, glm::vec3 const& max );

	 //getter
	 glm::vec3 const& min() const;
	 glm::vec3 const& max() const;

	 //functions
	 float volume() const override;
	 float area() const override;

	 std::ostream& print(std::ostream& os) const override;

	 Hit intersect(Ray const& ray) const override;

private:
	glm::vec3 m_min;
	glm::vec3 m_max;
};


#endif