// raytracer.hpp
// Tohrbe GREAT

#ifndef BUW_RAYTRACER_HPP
#define BUW_RAYTRACER_HPP

//#include  <dirent.h>
#include <string>
#include "scene.hpp"

class Raytracer{
public: 
	//Custom-Constructor
	Raytracer(std::string const& inpath, unsigned int width, unsigned int height, std::string const& outpath) ; 
	
	//~Box()override;
	void render();
private:
  std::string m_in;
  unsigned int m_width;
  unsigned int m_height;
  std::string m_out;




};

#endif // BUW_BOX_HPP