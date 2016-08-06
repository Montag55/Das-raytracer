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
    		std::cout <<"Deine mutter rotzt in der gegnd umher Vol.i" <<"\n";
	     	std::stringstream ss;
	     	ss<<line;					//erste Zeile im Stream
	     	std::string firstWord;
	     	ss>>firstWord;
	     	if (firstWord=="define")
	     	{	
	     		std::cout << "Definiere: ";
	     		ss>>firstWord;
	     		if(firstWord == "material")
	     		{	
	     			std::string matname;
	     			Color ka;
	     			Color kd;
	     			Color ks;
	     			float faktor;

	     			std::cout << "Material: ";

	     			ss >> matname;

      				ss >> ka.r;
					ss >> ka.g;
					ss >> ka.b;

					ss >> kd.r;
					ss >> kd.g;
					ss >> kd.b;

					ss >> ks.r;
					ss >> ks.g;
					ss >> ks.b;

					ss >> faktor;

					Material* material = new Material(matname, ka, kd, ks, faktor);


					scene.materials.insert(std::pair<std::string, Material*>(matname, material));
	     		}     		
	     		else if(firstWord == "shape")
	     		{
	     			ss>>firstWord;
	     			std::cout << "Shape: ";

	     			if(firstWord == "box")
	     			{	
	     				std::cout << "Box: ";
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


	     				Material* material = new Material;
	     				material = (scene.materials.find(materialname)->second);
	     				std::cout << "Box2: ";

	     				Box* box = new Box(boxname, material, min, max);
	     				std::cout << "Box3: ";
						
						scene.shapes.push_back(box);
						std::cout << "Box4: ";

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


	     				Material* material1 = new Material;
	     				material1 = (scene.materials.find(materialname)->second);

	     				Sphere* sphere = new Sphere(spherename, material1, center, radius);
						
						scene.shapes.push_back(sphere);
	     			}
	     		else if(firstWord == "light")
	     		{
	     			ss>>firstWord;
	     			std::string lightname;
	     			Color lightcolor;
	     			glm::vec3 lightpoint;

	     			ss >> lightname;

	     			if(firstWord != "ambient")
	     			{
	     				ss >> lightpoint.x;
	     				ss >> lightpoint.y;
	     				ss >> lightpoint.z;
	     			}
	     			ss >> lightcolor.r;
	     			ss >> lightcolor.g;
	     			ss >> lightcolor.b;
	     			
	     			Light* light = new Light(lightname, lightcolor, lightpoint);

	     			scene.lights.push_back(light);

	     		}
	     			
	     		}
	     	}
    	}

    myfile.close();

  }

  else std::cout << "Unable to open file"; 

 

  return scene;
}