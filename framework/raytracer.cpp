#include "raytracer.hpp"
#include <string>
#include <iostream>
#include "sdfloader.hpp"


//Constructor
Raytracer::Raytracer(std::string const& inpath, unsigned int width, unsigned int height, std::string const& outpath):
m_inpath {inpath},
m_width {width},
m_height {height},
m_outpath {outpath}
{}

void Raytracer::render(){
	bool i = true;
	Scene scene;
	while (i){
		scene = SDFLoader::load("../scene.txt");
		i = false;																				//	Gedanke: EINE Scene laden bis 
	}                                                 	//	keine Textdatei mehr im Ordner
 																											//	Idee: Material Filename + index
	
} 
