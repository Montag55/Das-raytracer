#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP
#include <string>
#include "scene.hpp"

class Raytracer
{
public:
  Raytracer(std::string const& inpath, unsigned int width, unsigned int height, std::string const& outpath);

  void render();

private:
  std::string m_inpath;
  unsigned int  m_width;
  unsigned int m_height;	
  std::string m_outpath;

};

#endif
