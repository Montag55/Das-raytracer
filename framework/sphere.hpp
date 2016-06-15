#ifndef SPHERE_HPP
#define SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"
#include "color.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <ray.hpp>

class Sphere : public Shape {
public:
	Sphere();
	Sphere(float radius, glm::vec3 const& center);
	Sphere(glm::vec3 const& center, float radius, Color const& color, std::string const& name);
	~Sphere(){
		std::cout << "Dies wurde Deconstruuuuuuuktet!" << "\n";
	}

	std::ostream& print(std::ostream& os) const override;

	glm::vec3 const& center() const;
	float radius() const;

	float volume() const override;
	float area() const override;

	bool intersect(Ray const& ray, float& dis) const;

private:
	float m_radius;
	glm::vec3 m_center;
};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif