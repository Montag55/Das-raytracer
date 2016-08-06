#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include "hit.hpp"
class Renderer
{
public:
  Renderer(Scene const& scene, unsigned int width, unsigned int height, std::string const& ofile);

  void render();
  void write(Pixel const& p);
  Hit ohit(Ray const& ray) const;
  Color givacolor(Ray const& ray);

  inline std::vector<Color> const& colorbuffer() const
  {
    return m_colorbuffer;
  }

private:
  Scene m_scene;
  unsigned int m_width;
  unsigned int m_height;
  std::vector<Color> m_colorbuffer;
  std::string m_outfile;
  PpmWriter m_ppm;
};

#endif // #ifndef BUW_RENDERER_HPP
