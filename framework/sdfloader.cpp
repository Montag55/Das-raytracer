#include <string>
#include "scene.hpp"
#include "composite.hpp"
#include "sdfloader.hpp"
#include <fstream>
#include <sstream>
#include <memory>


Scene SDFLoader::load(std::string const& inpath)
{
    typedef std::shared_ptr<Shape> shape_pointer;

    Scene scene;
    //scene.m_composite= std::make_shared<Composite>("compname");
    std::map<std::string, shape_pointer> tmpcomp;


    std::string line;
    std::ifstream myfile(inpath);

    if (myfile.is_open())
    {   
        std::cout <<"Deine mutter rotzt in der gegnd umher Vol.i" <<"\n";
        while (getline(myfile,line))
        {   
            std::stringstream ss;
            ss<<line;                   //First Line in
            std::string firstWord;
            ss>>firstWord;              //First Word in
            
            if(firstWord == "transform")
            {
                std::string shapename, transform;
                float x, y, z;

                ss >> shapename;

                auto shape = tmpcomp.find(shapename);
                if(shape != tmpcomp.end()) 
                {   
                    ss >> transform;
                    if (transform == "scale") 
                    {
                        ss >> x;
                        ss >> y;
                        ss >> z;

                        shape->second->scale(glm::vec3(x,y,z));
                    }else if (transform == "rotate") 
                    {     
                        float angle;
                        ss >> angle;

                        ss >> x;
                        ss >> y;
                        ss >> z;

                        shape->second->rotate(angle,glm::vec3(x,y,z));
                    }
                    else if (transform == "translate")
                    {
                        ss >> x;
                        ss >> y;
                        ss >> z;

                        shape->second->translate(glm::vec3(x,y,z));
                    }
                }
            }else if (firstWord=="define")
            {   
                std::cout << "Definiere: ";
                ss>>firstWord;
                if(firstWord == "material")//##############-Material
                {   
                    //Material-Info------
                    std::string matname;
                    Color ka;
                    Color kd;
                    Color ks;
                    float faktor;
                    //-------------------

                    std::cout << "Material\n";
                    //Einlesen:
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

                    //Einspeichern
                    std::shared_ptr<Material> material=std::make_shared<Material>(matname, ka, kd, ks, faktor);
                    scene.m_materials.insert(std::pair<std::string, std::shared_ptr<Material>>(matname, material));
                }           
                else if(firstWord == "shape")//##############-Shape
                {
                    ss>>firstWord;
                    std::cout << "Shape: ";

                    if(firstWord == "box") //##############-Box
                    {   
                        std::cout << "Box\n";
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

                        //Einspeichern
                        std::shared_ptr<Material> material=(scene.m_materials.find(materialname)->second);
        
                        shape_pointer box= std::make_shared<Box>(boxname, material, min, max);
                        tmpcomp.insert(std::pair<std::string, shape_pointer>(box->name(), box));
                 
                    }else if(firstWord == "sphere") //##############-Sphere
                    {   
                        std::cout << "Sphere\n";
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

                        //Einspeichern
                        std::shared_ptr<Material> material=(scene.m_materials.find(materialname)->second);

                        shape_pointer sphere= std::make_shared<Sphere>(spherename, material, center, radius);
                        tmpcomp.insert(std::pair<std::string, shape_pointer>(sphere->name(), sphere));
                        
                    }else if (firstWord == "composite")
                    {
                        std::cout<< "Composite\n";
                        std::string compname;
                        std::string shapename;

                        ss >> compname;
                        std::cout<< "Objekt\n";
                        std::cout<< compname;
                        std::cout<< "Nr.1"<< compname << "\n";
                        scene.m_composite= std::make_shared<Composite>(compname);
                        

                        while (!ss.eof())
                        {	

                            ss>>shapename;
                            std::cout<< "Nr.1" <<shapename << "\n";
                            auto search = tmpcomp.find(shapename);
                            if(search != tmpcomp.end()) 
                            {	
                                std::cout<< "Katzenklo\n";
                            	std::shared_ptr<Shape> tempshape = search->second;
                                scene.m_composite->add(tempshape);
                            }   
                        
                       
                        /*
                        for( auto &i : scene.m_composite->m_shapes){
                        std::cout<< "Objekt in Comp."<<"\n";
                        //scene.m_composite->set_name("Vadda");
                        */
                        }
                        auto i = scene.m_composite->intersect(Ray());
                    }
                }
                else if(firstWord == "light") //##############-Light
                {
                    ss>>firstWord;
                    std::string lightname;
                    Color lightcolor;
                    glm::vec3 lightpoint;

                    std::cout << "Lights: ";

                    if(firstWord != "ambient") //##############-stand.Light
                    {   
                        std::cout << "Diffuse\n";
                        ss >> lightname;
                        ss >> lightpoint.x;
                        ss >> lightpoint.y;
                        ss >> lightpoint.z;

                        ss >> lightcolor.r;
                        ss >> lightcolor.g;
                        ss >> lightcolor.b;
                    
                        //Einspeichern
                        std::shared_ptr<Light> light= std::make_shared<Light>(lightname, lightcolor, lightpoint);
                        scene.m_lights.push_back(light);
                    }
                    else                                //##############-ambi. Light
                    {                               
                        std::cout << "Ambient\n";
                        ss >> lightname; //ambient needs no lightname -> its just a color.
                        ss >> lightcolor.r;
                        ss >> lightcolor.g;
                        ss >> lightcolor.b;

                        //Einspeichern
                        scene.m_ambient = lightcolor;
                    }
                }else if(firstWord == "camera")//##############-Camera
                {
                    ss >> scene.m_camera.m_name;
                    ss >> scene.m_camera.m_fov_x;
                }
            }
        }
   		myfile.close();
  	}
  	else std::cout << "Unable to open file"; 

    scene.m_composite->set_name("Vadda123s");
	return scene;

}
