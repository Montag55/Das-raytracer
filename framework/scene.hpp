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

struct Scene
{
	std::shared_ptr<Shape> shapes;
	std::vector<Light*> lights;
	Color ambient;
	Camera camera;
	std::map<std::string, Material*> materials;
	//std::shared_ptr<Composite> composite;
};

#endif