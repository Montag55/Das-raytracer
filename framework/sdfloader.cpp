#include <string>
#include "scene.hpp"
#include "sdfloader.hpp"
#include <fstream>
#include <sstream>


Scene SDFLoader::load(std::string const& inpath){
  	Scene scene;
  	std::string line;
  	//std::ifstream myfile(inpath);
  	/*
	if (myfile.is_open())
    { 
		while (getline(myfile,line))
    	{
	     	std::stringstream ss;
	     	ss<<line;					//erste Zeile im Stream
	     	std::string firstWord;
	     	ss>>firstWord;
	     	if (firstWord=="define")
	     	{
	     		ss>>firstWord;
	     		if(firstWord == "material")
	     		{
	     			Material mat;
	     			ss >> mat.name;

      				ss >> mat.ka.r;
					ss >> mat.ka.g;
					ss >> mat.ka.b;

					ss >> mat.kd.r;
					ss >> mat.kd.g;
					ss >> mat.kd.b;

					ss >> mat.ks.r;
					ss >> mat.ks.g;
					ss >> mat.ks.b;

					ss >> mat.m;
					scene.materials.insert(mat);
	     		}
	     		else if(firstWord == "shape")
	     		{
	     			ss>>firstWord;

	     			if(firstWord == "box")
	     			{
	     				Box box;
	     				ss >> box.name;

      					ss >> box.m_min.x;
						ss >> box.m_min.y;
						ss >> box.m_min.z;

						ss >> box.m_max.x;
						ss >> box.m_max.y;
						ss >> box.m_max.z;

						ss >> box.ks.r;
						
						scene.shapes.push_back(box);
	     			}
	     			else if(firstWord == "sphere")
	     			{
	     				Sphere sphere;
	     				ss >> sphere.name;

      					ss >> sphere.m_center.x;
						ss >> sphere.m_center.y;
						ss >> sphere.m_center.z;

						ss >> sphere.m_radius;

						ss >> sphere.material;
						
						scene.shapes.push_back(sphere);
	     			}
	     		}
	     	}
    	}
    myfile.close();
  }

  else std::cout << "Unable to open file"; 
 
*/
  return scene;
}