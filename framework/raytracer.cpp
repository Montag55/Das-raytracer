#include "raytracer.hpp"
#include "renderer.hpp"
#include "scene.hpp"
#include <thread>
#include <string>
#include <iostream>
#include "sdfloader.hpp"
#include <fensterchen.hpp>



//Constructor
Raytracer::Raytracer(std::string const& inpath, unsigned int width, unsigned int height, std::string const& outpath):
m_inpath {inpath},
m_width {width},
m_height {height},
m_outpath {outpath}
{}

/* ORIGINAL
void Raytracer::render(){
	bool i = true;
	Scene scene;
	while (i){
		scene = SDFLoader::load("../scene.txt");
		i = false;																				//	Gedanke: EINE Scene laden bis 
	}                                                 	//	keine Textdatei mehr im Ordner
 																											//	Idee: Material Filename + index
*/
	 void Raytracer::render()
	{
    /*
    ######################################
    Idee.: per while schleife durch Ordner 
    und die jeweilige.txt datei an den 
    Renderer schicken...
    mit boost oder doch lieber Vector oder 
!   andere Lösung... später!
    ######################################*/

    std::string file="../input/test.txt"; //path->file[1]
    bool done = false;
    while (!done)  //durch n files
    {
      if (true) //eine ".txt"
      {
        Scene scene = SDFLoader::load(file); 
        std::string outputfile="out.ppm";
        Renderer rendi(scene, m_width, m_height, outputfile); 

        std::thread thr([&rendi]() { rendi.render(); });
        Window win(glm::ivec2(m_width,m_height));

        while (!win.shouldClose()) {
          if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
              win.stop();
          }

          glDrawPixels( m_width, m_height, GL_RGB, GL_FLOAT
          , rendi.colorbuffer().data());

          win.update();
        }

      thr.join();

      }
      done = true;
    }
} 
