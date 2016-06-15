#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "color.hpp"

class Box : public Shape {
public:
	Box();
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(std::string const& name, Color const& color, glm::vec3 const& min, glm::vec3 const& max);
	
	std::ostream& print(std::ostream& os) const override;

	glm::vec3 const& min() const;
	glm::vec3 const& max() const;

	float volume() const override;
	float area() const override;



private:
	glm::vec3 m_min;
	glm::vec3 m_max;
};

std::ostream& operator<<(std::ostream& os, Box const& b);

#endif