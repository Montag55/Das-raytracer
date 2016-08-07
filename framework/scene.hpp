#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>
#include <map>
#include <string>
#include "shape.hpp"
#include "material.hpp"
#include "light.hpp"
#include "color.hpp"
//#include "camera.hpp"

struct Scene
{
	//OptionalHit intersect(Ray const&) const;
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;
	Color ambient;
	//Camera camera;
	std::map<std::string, Material*> materials;

};

#endif