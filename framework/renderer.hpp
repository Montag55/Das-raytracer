#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include "hit.hpp"
#include "ray.hpp"

class Renderer
{
public:
  Renderer(Scene const& scene, unsigned int width, unsigned int height, std::string const& ofile);

  void render();
  void write(Pixel const& p);

  Hit ohit(glm::mat4x4 const& trans_mat, Ray const& ray) const;
  Color raytrace(Ray const& ray, unsigned int depth);
  Color render_antialiase(Ray rayman, float antialiase_faktor, unsigned int depth);
  Color tonemap(Color tempcolor);
  void reflectedlight(Color & clr, Hit const& Hitze, Ray const& ray, unsigned int depth);
  void ambientlight(Color & clr, Color const& ka);
  void pointlight(Color & clr, std::shared_ptr<Light> const& light, Hit const& Hitze, Ray const& ray);
  void diffuselight(Color & clr, Hit const& Hitze, std::shared_ptr<Light> const& light,  Ray const& raylight);
  void specularlight(Color & clr, Hit const& Hitze, std::shared_ptr<Light> const& light,  Ray const& raylight, Ray const& ray);
  void refractedlight(Color & clr, Hit const& Hitze, Ray const& ray, unsigned int depth);
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
