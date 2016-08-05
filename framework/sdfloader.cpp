#include <string>
#include "scene.hpp"
#include "sdfloader.hpp"
#include <fstream>
#include <sstream>


Scene SDFLoader::load(std::string const& inpath){
  	Scene scene;
  	std::string line;
  	std::ifstream myfile(inpath);

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

					scene.materials.insert(std::pair<std::string, Material*>(mat.name, &mat));
	     		}
	     		else if(firstWord == "shape")
	     		{
	     			ss>>firstWord;

	     			if(firstWord == "box")
	     			{	
	     				std::string boxname;
						glm::vec3 min;
						glm::vec3 max;
						std::string materialname;


	     				ss >> boxname;
	     				ss >> min.x;
	     				ss >> min.y;
	     				ss >> min.z;

						ss >> max.x;
	     				ss >> max.y;
	     				ss >> max.z;

	     				ss >> materialname;

	     				Material* material = (scene.materials.find(materialname)->second);


	     				Box box(boxname, material, min, max);

	     				/*
	     				Box box;
	     				ss >> box.name_;

      					ss >> box.m_min.x;
						ss >> box.m_min.y;
						ss >> box.m_min.z;

						ss >> box.m_max.x;
						ss >> box.m_max.y;
						ss >> box.m_max.z;

						ss >> box.material_;
						*/
						
						scene.shapes.push_back(&box);
	     			}
	     			
	     			else if(firstWord == "sphere")
	     			{	
	     				std::string spherename;
	     				glm::vec3 center;
	     				float radius;
	     				std::string materialname;
	     				

	     				ss >> spherename;

	     				ss >> center.x;
	     				ss >> center.y;
	     				ss >> center.z;

	     				ss >> radius;
	     				ss >> materialname;

	     				Material* material = (scene.materials.find(materialname)->second);

	     				Sphere sphere(spherename, material, center, radius);
						/*
	     				ss >> sphere.name_;

      					ss >> sphere.m_center.x;
						ss >> sphere.m_center.y;
						ss >> sphere.m_center.z;

						ss >> sphere.m_radius;

						ss >> sphere.material_;
						*/
						
						scene.shapes.push_back(&sphere);
	     			}
	     			
	     		}
	     	}
    	}
    myfile.close();
  }

  else std::cout << "Unable to open file"; 

 

  return scene;
}