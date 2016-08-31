#include "renderer.hpp"
#include <glm/glm.hpp>
#include "glm/ext.hpp"


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
  float distance = (-float(m_width))  / (2*tan(0.5*m_scene.m_camera.m_fov_x *M_PI / 180)); //krasser trigonometrischer kack zur Bestimmung der Bilddistanz // minus für neg. z Achse
  float samplePosY = (-float(m_height)/2); 
  //std::cout << "Distanz:     " << distance<<"\n";

  for (unsigned y = 0; y < m_height; ++y) {     //Horizontal
    float samplePosX = (-float(m_width)/2);
    for (unsigned x = 0; x < m_width; ++x) {  //Vertikal
      
      Pixel p(x,y);
      

      Ray rayman = m_scene.m_camera.calculate_eye_ray(samplePosX, samplePosY, distance);
      Color tempcolor;

      if (m_scene.m_antialiase>0) //antialiasing
      {
        tempcolor = render_antialiase(rayman, m_scene.m_antialiase, 4);
      }
      else{
        tempcolor = raytrace(rayman, 4);
      }

      p.color = tonemap(tempcolor); // tonemapping

      write(p);

      samplePosX++;
     
    }
    samplePosY++;
  }
  m_ppm.save(m_outfile);
}


void Renderer::write(Pixel const& p)
{
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

Color Renderer::raytrace(Ray const& ray, unsigned int depth)
  {

    Hit Hitze =m_scene.m_composite->intersect(ray); 
     
    if(Hitze.m_hit==true) //Treffer?
    {  
      Color clr;
  
      ambientlight(clr,Hitze.m_shape->material()->ka);      //AMBIENT
            
      //Überprüfe nun alle direkten Lichtwege
      for(auto& light : m_scene.m_lights) 
      {
        pointlight(clr, light, Hitze, ray);                      //DIFFUSE & SPECULAR 
      }

      if (depth>0)
      {
        reflectedlight(clr, Hitze,ray, depth);              //REFLECTION
      }
                                                                //REFRACTION?
    return clr;   
    }
  return m_scene.m_ambient; //Schuß ins nirgendswo!
  } 



/*Hier werden die schönsten aller Lichter berechnet!*/
void Renderer::ambientlight(Color & clr, Color const& ka)
{
  clr+=(m_scene.m_ambient)*(ka);  //+=I_a*k_a
}

void Renderer::pointlight(Color & clr, std::shared_ptr<Light> const& light, Hit const& Hitze, Ray const& ray)
{
        //glm::vec3 transformed_light_direction = glm::normalize(glm::vec3(Hitze.m_shape->world_transformation_inv()*
          //                                   (glm::vec4 (light->m_point, 1)-glm::vec4(Hitze.m_intersection,1))));
      
        glm::vec3 direct=glm::normalize(light->m_point-Hitze.m_intersection);

        Ray raylight
        {
          Hitze.m_intersection+(direct*0.001f), //nicht selbst Treffen
          direct
        };       

        int distance= glm::length(Hitze.m_intersection-light->m_point);
        Hit LightHitze = m_scene.m_composite->intersect(raylight);
        
        if (LightHitze.m_distance>distance) //Wir der Gegenstand vom Licht getroffen, oder ist ein Objekt dazwischen?
        {
          diffuselight(clr, Hitze, light, raylight);
          specularlight(clr, Hitze, light, raylight, ray);
        }//sonst ist da Schatten
}
/*->*/void Renderer::diffuselight(Color & clr, Hit const& Hitze, std::shared_ptr<Light> const& light,  Ray const& raylight)
      {
        float faktor=(glm::dot((Hitze.m_normal) , raylight.direction));
        clr+= (light->m_color) * (Hitze.m_shape->material()->kd) * (std::max(faktor,0.0f));  
      }

/*->*/void Renderer::specularlight(Color & clr, Hit const& Hitze, std::shared_ptr<Light> const& light,  Ray const& raylight, Ray const& ray)
      {
        auto r = glm::normalize(glm::reflect(raylight.direction, Hitze.m_normal));
        float cosb = std::max(0.0f, glm::dot(r, glm::normalize(ray.direction)));          //evtl hier nochmal mit transf. ray probieren!
        clr+= light->m_color * Hitze.m_shape->material()->ks * pow(cosb, Hitze.m_shape->material()->m);
      }

void Renderer::reflectedlight(Color & clr, Hit const& Hitze, Ray const& ray, unsigned int depth)
{
  glm::vec3 direct=glm::normalize(glm::reflect(ray.direction,Hitze.m_normal));
  Ray rayrefly{Hitze.m_intersection+(direct*0.001f),direct};  
  
  Color refColor = raytrace(rayrefly, depth-1);
  clr += (refColor) * (Hitze.m_shape->material()->ks) * (Hitze.m_shape->material()->kr);
}

Color Renderer::render_antialiase(Ray rayman, float antialiase_faktor, unsigned int depth)
{
  Color tempcolor;
  int samples = sqrt(antialiase_faktor);
  --depth;
  for (int xAA=1;xAA<samples+1;++xAA){
    for (int yAA=1;yAA<samples+1;++yAA){
      Ray aaRay;
      aaRay.direction.x = rayman.direction.x +(float) (xAA)/(float)samples-0.5f; 
      aaRay.direction.y = rayman.direction.y +(float) (yAA)/(float)samples-0.5f;
      aaRay.direction.z = rayman.direction.z;
      tempcolor +=raytrace(aaRay, depth);
    }
  }
  tempcolor.r = tempcolor.r/antialiase_faktor;
  tempcolor.g = tempcolor.g/antialiase_faktor;
  tempcolor.b = tempcolor.b/antialiase_faktor;

  return tempcolor;
}


Color Renderer::tonemap(Color tempcolor)
{
  Color p_color;
  p_color.r= m_scene.m_A*pow(tempcolor.r, m_scene.m_gamma); //kontrastanpassung
  p_color.g= m_scene.m_A*pow(tempcolor.g, m_scene.m_gamma); //kontrastanpassung
  p_color.b= m_scene.m_A*pow(tempcolor.b, m_scene.m_gamma); //kontrastanpassung
  return p_color;
}