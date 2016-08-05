// raytracer.cpp 
// Thorbe GREAT
#include "raytracer.hpp"
#include "sdfloader.hpp"
#include "renderer.hpp"
//
#include <iostream>
#include <algorithm>
#include <string>
#include <dirent.h>

//

#include <thread>
#include <fensterchen.hpp>


//
//KONSTRUTOREN----------------------------------------------------------------------
  
  //Default
  
   /*Custom 1 
  ######################################
  Setzt Raytracer Custom auf. Kann nun
  in gewünschter Auflösung beliebig viele
  ".sdf" Dateien nacheinander Rendern! */
  Raytracer::Raytracer(std::string const& inpath, unsigned int width, unsigned int height, std::string const& outpath):
	  m_in {inpath}, 
	  m_width {width}, 
	  m_height {height},
	  m_out{outpath}
	  {}


  //Destruktor

//FUNKTIONEN----------------------------------------------------------------------
 
  /*FKT 1
  ######################################	
  Aufruf zum rendern. Fkt organisiert in 
  Form einer Schleife alle zu rendernden
  Dateien und übergibt die Scenen dazu an
  den Renderer weiter!*/

  bool has_suffix(const std::string& s, const std::string& suffix) //ausgelagerte Funktion in Lambda?
  {
    return (s.size() >= suffix.size()) && equal(suffix.rbegin(), suffix.rend(), s.rbegin());    
  }

  void Raytracer::render()
	{
    /*
    ######################################
    Zum durchsuchen der Ordner siehe Quelle:
    http://stackoverflow.com/questions/19189014
    /how-do-i-find-files-with-a-specific-extension
    -in-a-directory-that-is-provided-by
    ######################################*/
    
    DIR *dir = opendir(m_in.c_str());         //In Input-path
    dirent *entry;                            
    unsigned int count=1;

    while((entry = readdir(dir))!=nullptr)    //durch alle files
    {

       if(has_suffix(entry->d_name, ".txt"))  // ".txt"?
        { //Ablauf für eine SDF-Datei:
          std::cout << "<Datei: " << count << std::endl; 

          std::cout << "-SDFLoader:" << entry->d_name << std::endl;
          Scene scene = SDFLoader::load(entry->d_name); 
          
          std::string outputfile=std::string(m_out)+"/out"+entry->d_name;
          outputfile =outputfile.substr(0, outputfile.size()-3);//delete txt
          outputfile+="ppm";

          std::cout << "-outputfile: " << outputfile<< std::endl;

          Renderer rendi(scene, m_width, m_height, outputfile); 
          std::thread thr([&rendi]() { rendi.render(); });
        //folgendes nachher löschen, nur zur Ansicht schön..----------------
          Window win(glm::ivec2(m_width,m_height));

          while (!win.shouldClose()) 
          {
            if (win.isKeyPressed(GLFW_KEY_ESCAPE)) 
            {
                win.stop();
            }

            glDrawPixels( m_width, m_height, GL_RGB, GL_FLOAT
            , rendi.colorbuffer().data());

            win.update();
          }
          thr.join();
        //-------------------------------------------------------------------
          count++;
        }
    }

    closedir(dir);


  }
  