#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include <map>
#include <string>
#include "shape.hpp"
#include "material.hpp"
#include "light.hpp"
#include "color.hpp"
#include "camera.hpp"
#include "composite.hpp"

struct Scene
{
		//Lichter
		std::vector <std::shared_ptr<Light>> m_lights;
		Color m_ambient;
		//Kontrast
		float m_A = 1.0f;
		float m_gamma = 0.99f;
		//Shapes
		std::shared_ptr<Composite> m_composite; 
		std::vector <std::shared_ptr<Shape>> m_shapes;
		//Materialien
		std::map<std::string, std::shared_ptr<Material>> m_materials;
		//Kamera
		Camera m_camera;
		//Antialias
		int m_antialiase = 0;
		//Reflection Depth
		unsigned int m_depth = 2;


};

#endif