#ifndef SDFLOADER_HPP
#define SDFLOADER_HPP
#include <string>
#include "scene.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "material.hpp"
#include <sstream>

class SDFLoader {
public:
    Scene load(std::string const& inpath);
    //static Material getMaterial(string name, std::vector<Material> data);
    //static LightPoint getLight(string name, std::vector<LightPoint> data);
    //static std::shared_ptr<RenderObject> const& getShape(string name, std::vector<std::shared_ptr<RenderObject>> data); 
};

#endif
