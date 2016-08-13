
#include <iostream>
#include <fstream>
#include <string>
#include "material.hpp"
#include <sstream>
#include "raytracer.hpp"
#include "renderer.hpp"
#include "camera.hpp"





int main(int argc, char* argv[]){
  
  Raytracer ray1("./input", 600, 600, "framework");
  

  ray1.render();
  /*std::string line;
  std::ifstream myfile ("../../../framework/material.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::stringstream ss;
      ss<<line;
      Material mat;
      std::string keyword;
      ss>>keyword;
      ss>>keyword;
      ss>>mat.name;

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


      std::cout<<mat;
    }
    myfile.close();
  }

  else std::cout << "Unable to open file"; 
  */
  return 0;
}