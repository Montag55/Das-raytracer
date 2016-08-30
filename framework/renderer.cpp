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
  std::cout << "Distanz:     " << distance<<"\n";

  for (unsigned y = 0; y < m_height; ++y) {     //Horizontal
    float samplePosX = (-float(m_width)/2);
    for (unsigned x = 0; x < m_width; ++x) {  //Vertikal
      
      Pixel p(x,y);
      
      Ray rayman = m_scene.m_camera.calculate_eye_ray(samplePosX, samplePosY, distance);
      Color tempcolor;

      if (m_scene.m_antialiase>0) //antialiasing
      {
        tempcolor = render_antialiase(rayman, m_scene.m_antialiase);
      }
      else{
        tempcolor = raytrace(rayman);
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

Color Renderer::raytrace(Ray const& ray)
{  
  Hit Hitze = m_scene.m_composite->intersect(ray);

  
  Color clr;
 
 /* clr.r = Hitze.m_normal.x;
  clr.g = Hitze.m_normal.y;   //Normalenüberprüfung :)
  clr.b = Hitze.m_normal.z;

  */

  if(Hitze.m_hit==true) //Treffer?
  {
    clr +=(m_scene.m_ambient*(Hitze.m_shape->material()->ka)); //default Licht
    
    for(auto& light : m_scene.m_lights) 
    {
      glm::vec3 light_direction=glm::normalize(light->m_point-Hitze.m_intersection);
      glm::vec3 light_origin= Hitze.m_intersection+(light_direction)*0.001f; //Damit es sich nicht selbst trifft...
      Ray raylight = Ray(light_origin,light_direction);

      //Hit ShadowObject = ohit(transmat, raylight);
      Hit ShadowObject = m_scene.m_composite->intersect(raylight);

      
      float distance= glm::length(Hitze.m_intersection-light->m_point); //distanz zwischen Licht und
              std::cout << "Position:  "<< Hitze.m_intersection.x << "Position:  "<<Hitze.m_intersection.y << "Position:  "<<Hitze.m_intersection.z << "\n";

      if (ShadowObject.m_distance>distance) //Hier wird der Gegenstand direkt vom Licht getroffen.
      {
        
        float faktor=(glm::dot(light_direction, Hitze.m_normal));
        std::cout << "Normale:  "<< Hitze.m_normal.x << "Normale:  "<< Hitze.m_normal.y<< "Normale:  " << Hitze.m_normal.z << "\n";
        std::cout << "Faktor:  "<< faktor << "\n";
        
        if (faktor<0)  // wenn der Winkel des Lichteinfall unterhalb der Oberfläche selbst liegt,
        {
          faktor=0; // dann wird das Spatprodukt gleich null und es wird nichts zum Ambientlight addiert.
        }
        
        //glm::vec3 v = glm::normalize(light_origin); 
        glm::vec3 v = glm::normalize(Hitze.m_intersection - glm::normalize(ray.direction));
        glm::vec3 r (glm::normalize(glm::reflect(raylight.direction, Hitze.m_normal)));

        float rv = (glm::dot(r, v));
        std::cout << "Faktor 2:  "<< rv << "   "<< v.x << "\n";
        if(rv<0)
        {
          rv = 0;
        }

        float faktor2 = (pow(rv, Hitze.m_shape->material()->m));
        
        clr+= light->m_color*((Hitze.m_shape->material()->kd * faktor)+
                              Hitze.m_shape->material()->ks* faktor2);
      }  
    // Hier kommt Reflekttion hin -> wie berechnet man Austrittswinkel aus normale?
    
    }
    return clr;
    
  }
  clr+=m_scene.m_ambient;
  
  return clr;   
}   


Color Renderer::render_antialiase(Ray rayman, float antialiase_faktor)
{
  Color tempcolor;
  int samples = sqrt(antialiase_faktor);
  for (int xAA=0;xAA<samples;++xAA){
    for (int yAA=0;yAA<samples;++yAA){
      Ray aaRay;
      aaRay.direction.x = rayman.direction.x +(float) (xAA)/(float)samples-0.5f; 
      aaRay.direction.y = rayman.direction.y +(float) (yAA)/(float)samples-0.5f;
      aaRay.direction.z = rayman.direction.z;
      tempcolor +=raytrace(aaRay);
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