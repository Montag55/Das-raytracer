#ifndef RAY_HPP
#define RAY_HPP
#include <glm/vec3.hpp>

struct Ray
{

	Ray():
		origin{0.0},
		direction{0.0}
		{}

	Ray(glm::vec3 const& orig, glm::vec3 const& dir):
		origin{orig},
		direction{dir}
		{}


	glm::vec3 origin;
	glm::vec3 direction;
};

#endif