// renderer.cpp 
// Thorbe GREAT
#include "renderer.hpp"

//Default
  
 /*Custom 1 
######################################
Setzt Renderer Custom mit gewünschter
Szene, Resolution und Output auf. 
Nun kann gerendert werden */
Renderer::Renderer(Scene const& scene, unsigned int width, unsigned int height, std::string const& ofile): 
  m_scene(scene),
  m_width(width), 
  m_height(height), 
  m_colorbuffer(width*height, Color(0.0, 0.0, 0.0)), 
  m_outfile(ofile),
  m_ppm(m_width, m_height)
  {}

void Renderer::render()
{ 
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < m_height; ++y) {
    for (unsigned x = 0; x < m_width; ++x) {
      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/m_height);
      } else {
        p.color = Color(1.0, 0.0, float(y)/m_width);
      }

      write(p);
    }
  }
  m_ppm.save(m_outfile);
  
}

void Renderer::write(Pixel const& p)
{
  
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (m_width*p.y + p.x);
  if (buf_pos >= m_colorbuffer.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    m_colorbuffer[buf_pos] = p.color;
  }

  m_ppm.write(p);
  
}
