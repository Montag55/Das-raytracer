#include <string>
#include "scene.hpp"
#include "sdfloader.hpp"
#include <fstream>
#include <sstream>


Scene SDFLoader::load(std::string const& inpath){
  	Scene scene;
  	std::string line;
  	std::ifstream myfile(inpath);
  	    std::cout <<"Deine mutter rotzt in der gegnd umher Vol.2" <<"\n";

  	/* TESTCODE:
    std::string name="rabenblau";
    Material mat(std::string("rabenblau"),Color(1.0,0.0,0.0),Color(1.0,0.0,0.0),Color(1.0,0.0,0.0), 1.2f);

    std::string name1="row";
    Material mat1(std::string("row"),Color(1.0,1.0,0.0),Color(1.0,0.0,0.0),Color(1.0,0.0,0.0), 1.2f);
    

    Shape* b1 = new Sphere(name, mat,glm::vec3(0,0,15.0), 12.983f);
    Shape* b2 = new Box(name1, mat1 ,glm::vec3(0, 0, 15.0),glm::vec3(20, 20, 40));
    
    scene.shapes.push_back(b1);
    scene.shapes.push_back(b2);
    scene.materials.insert(std::pair<std::string, Material*>(mat.name, &mat));
    scene.materials.insert(std::pair<std::string, Material*>(mat1.name, &mat1));
    */

	if (myfile.is_open())
    { 	std::cout <<"Deine mutter rotzt in der gegnd umher Vol.3" <<"\n";
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
	     			std::cout << "Material: ";
	     			Material mat;
	     			ss >> mat.name;
	     			std::cout << mat.name << "  ";

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

	     				Material* material = (scene.materials.find(materialname)->second);

	     				Sphere* sphere = new Sphere(spherename, material, center, radius);
						
						scene.shapes.push_back(sphere);
	     			}
	     			
	     		}
	     	}
    	}
    myfile.close();
    std::cout <<"Deine mutter rotzt in der gegnd umher Vol.ii" <<"\n";
  }

  else std::cout << "Unable to open file"; 

 

  return scene;
}