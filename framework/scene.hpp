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
		float m_A = 0.9f;
		float m_gamma = 0.5f;
		//Shapes
		std::shared_ptr<Composite> m_composite; 
		std::vector <std::shared_ptr<Shape>> m_shapes;
		//Materialien
		std::map<std::string, std::shared_ptr<Material>> m_materials;
		//Kamera
		Camera m_camera;


};

#endif