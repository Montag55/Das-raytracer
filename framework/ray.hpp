#include <glm/vec3.hpp>

struct Ray{
	Ray();
	Ray(glm::vec3 const& orig, glm::vec3 const& dir):
		origin{orig},
		direction{dir}
	{}
	
	glm::vec3 origin;
	glm::vec3 direction;
};