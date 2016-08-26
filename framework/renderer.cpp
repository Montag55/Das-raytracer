#include "renderer.hpp"
#include <glm/glm.hpp>
  
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

 /*Fkt: renderer
######################################
Organisiert die Pixel Farbgebung! */
void Renderer::render()
{
  float distance = (-float(m_width))  / (2*tan(0.5*m_scene.m_camera.m_fov_x *M_PI / 180)); //krasser trigonometrischer kack zur Bestimmung der Bilddistanz // minus für neg. z Achse
  float height = (-float(m_height)/2); 
  std::cout << "Distanz:     " << distance<<"\n";

  for (unsigned y = 0; y < m_height; ++y) {     //Horizontal
    float width = (-float(m_width)/2);
    for (unsigned x = 0; x < m_width; ++x) {  
      //Vertikal
      
      Pixel p(x,y);
      

      Ray rayman {m_scene.m_camera.m_pos, glm::normalize(glm::vec3(width, height, distance))};
      std::cout << rayman.direction.x << "  " << rayman.direction.y << "  " << rayman.direction.z<<"\n";
      auto tempcolor = raytrace(rayman);
      p.color.r= m_scene.m_A*pow(tempcolor.r, m_scene.m_gamma); //kontrastanpassung
      p.color.g= m_scene.m_A*pow(tempcolor.g, m_scene.m_gamma); //kontrastanpassung
      p.color.b= m_scene.m_A*pow(tempcolor.b, m_scene.m_gamma); //kontrastanpassung
      

      write(p);

      width++;
     
    }
    height++;
  }
  m_ppm.save(m_outfile);
}

/*void Renderer::render()
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
  
}*/

 /*Fkt: write
######################################
Schreibt einfach schön herum! */
void Renderer::write(Pixel const& p)
{
  
  // flip pixels, suck dick , because of opengl glDrawPixels
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


 /*Fkt: Raytrace
######################################
Ermittelt die Fabrbe! */
Color Renderer::raytrace(Ray const& ray)
{  
  Hit Hitze = m_scene.m_composite->intersect(ray);

  
  Color clr;
  if(Hitze.m_hit==true) //Treffer?
  {
    clr +=(m_scene.m_ambient*(Hitze.m_shape->material()->ka)); //default Licht
    
    for(auto& light : m_scene.m_lights) 
    {
      glm::vec3 direction=glm::normalize(light->m_point-Hitze.m_intersection);
      glm::vec3 origin= Hitze.m_intersection+(direction)*0.001f; //Damit es sich nicht selbst trifft...
      Ray raylight = Ray(origin,direction);

      //Hit ShadowObject = ohit(transmat, raylight);
      Hit ShadowObject = m_scene.m_composite->intersect(raylight);

      
      float distance= glm::length(Hitze.m_intersection-light->m_point); //distanz zwischen Licht und
      
      if (ShadowObject.m_distance>distance) //Hier wird der Gegenstand direkt vom Licht getroffen.
      {
        
        float faktor=glm::dot(Hitze.m_normal, direction);
        if (faktor<0)  // wenn der Winkel des Lichteinfall unterhalb der Oberfläche selbst liegt,
        {
          faktor=0; // dann wird das Spatprodukt gleich null und es wird nichts zum Ambientlight addiert.
        }
            
        //glm::vec3 v = glm::normalize(origin); 
        glm::vec3 v = glm::normalize(Hitze.m_intersection - ray.direction);
        glm::vec3 r (glm::normalize(glm::reflect(raylight.direction, Hitze.m_normal)));

        float rv = glm::dot(r, v);
        if(rv<0)
        {
          rv = 0;
        }

        float faktor2 = pow(rv, Hitze.m_shape->material()->m);
        
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


 /*Fkt: ohit
######################################
Gibt das durch einen Ray als erstes
getroffene Objekt zurück! */



  
Hit Renderer::ohit(glm::mat4x4 const& trans_mat, Ray const& ray) const
{ 

  //Ray ray = transformRay(trans_mat, inray);

  Hit hit;
  Hit temphit;
  for ( auto &i : m_scene.m_shapes )
  {
    temphit= i->intersect(ray);
    if(temphit.m_distance<hit.m_distance)
    {
      hit =  temphit;  
      std::cout<<"hit\n";
    }
  } 
  std::cout << ray.direction.z << "\n";
  return hit;
}

/*ALTE ohit
Hit Renderer::ohit(Ray const& ray) const
{
  Hit hit;
  Hit temphit;
  for ( auto &i : m_scene.m_shapes )
  {
    temphit= i->intersect(ray);
    if(temphit.m_distance<hit.m_distance)
    {
      hit =  temphit;  
      std::cout<<"hit\n";
    }
  } 
  std::cout << "hat er was nicht getroffen?" << "\n";
  return hit;
}
*/