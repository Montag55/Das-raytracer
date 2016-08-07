#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "scene.hpp"
#include <glm/vec3.hpp>
#include "color.hpp"
#include <string>



struct Light
{
	//constructoren im Struct?!

	Light():
		m_name{"default"},
		m_color {},
		m_point {0.0}
		{}


	Light(std::string const& name, Color const& clr, glm::vec3 const& pnt):
		m_name{name},
		m_color {clr},
		m_point {pnt}
		{}


	std::string m_name;
	glm::vec3 m_point;
	Color m_color;


	
};


#endif