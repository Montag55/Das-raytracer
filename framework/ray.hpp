#ifndef RAY_HPP
#define RAY_HPP
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/detail/func_matrix.hpp>

struct Ray
{

	Ray():
		origin{0.0},
		direction{0.0}
		{}

	Ray(glm::vec3 const& orig, glm::vec3 const& dir):
		origin{orig},
		direction{dir},
		inv_direction{glm::vec3{1.0/dir.x, 1.0/dir.y, 1.0/dir.z}}
		{}
    //###################################################################
	friend Ray transformRay(glm::mat4x4 const& trans_mat1, glm::mat4x4 const& trans_mat2, glm::mat4x4 const& trans_mat3, Ray const& ray)
	{	
		glm::mat4x4 trans_mat_inv1 = glm::inverse(trans_mat1);
		glm::mat4x4 trans_mat_inv2 = glm::inverse(trans_mat2);
		glm::mat4x4 trans_mat_inv3 = glm::inverse(trans_mat3);
 		Ray newray;
		glm::vec3 origin(trans_mat_inv1* trans_mat_inv2* trans_mat_inv3* glm::vec4(ray.origin, 1));
		glm::vec3 direction(trans_mat_inv2 * trans_mat_inv3 * glm::vec4(ray.direction, 1));
		glm::vec3 inv_direction(trans_mat_inv2 * trans_mat_inv3 * glm::vec4(ray.inv_direction, 1));

		newray.origin = origin;
		newray.direction = direction;
		newray.inv_direction = inv_direction;
		return newray;
	}
	//##################################################################

	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 inv_direction;
};

#endif