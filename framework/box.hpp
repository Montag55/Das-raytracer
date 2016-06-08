#ifndef BOX_HPP
#define BOX_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
public:
	Box();
	glm::vec3 const& min() const;
	glm::vec3 const& max() const;

private:
	glm::vec3 m_max;
	glm::vec3 m_min;
};
#endif