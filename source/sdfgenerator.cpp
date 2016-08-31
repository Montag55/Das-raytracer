
// sdfGenerator.cpp : Defines the entry point for the console application.
//

#include <string>
#include <fstream>
#include <vector>
#include <array>
#include <iostream>
#include <sys/stat.h>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
	const int imagecount = 360;
	array<string, imagecount> outputNames;

	for (int  i = 0; i < imagecount; ++i) {
		outputNames[i] = "scene" + to_string(i) + ".sdf";
		
		cout << outputNames[i] << endl;
	}


	array <string, imagecount> outputImage;

	for (int i = 0; i <imagecount; ++i){
		outputImage[i] = "image" + to_string(i) + ".ppm";
	}

	for (int i = 0; i < imagecount; ++i){

		ofstream fOut("input/"+outputNames[i]);
		//string cameraCmd = "define camera eye 65.0 0 0 " + to_string(i) + " 0 0 -1 0 1 0";
		//string outputImg = "render eye /Users/Lorenz/Studium/Programmiersprachen/Übung/Raytracer/PS-Raytracer/output/tmp/" + outputImage[i] + " 1280 720 4";
		int anglex;
		int angley=0;
		int j = 1;
		int k = 1;
		int l = 0;
		int m = 1;
		int n = 0;
		int o = 0;
		float z = 2;
		


		if(i<=360)
		{
			anglex = i;
		}
		/*
		if(45<i && i<=90)
		{
			anglex = -i+90;
			angley = i-45;
		}
		if(i>90)
		{
			anglex = -i+90;
			angley = 135 - i;
		}
		
		
		if(i<=15){
			 z = (0.1*i) + 1;
		}

		if(i>15){
			 z = 4 - (0.1*i);
		}
		*/
		

		fOut
			<<"define material red 1 0 0 1 0 0 1 1 1 1 40" << endl
			<<"define material green 0 1 0 0 1 0 1 1 1 1 240" << endl
			<<"define material blue 0 1 0 0 1 0.5 1 1 1 1 240" << endl
			<<"define shape box num1 -1 -1 -1 1 1 1 red" << endl
			<<"#define shape box num2 -1 -1 1 1 1 -1 red" << endl
			<<"#define shape sphere num3 -2 1 -4 1 red" << endl
			<<"define shape composite root num1 num2 num3 num4 num5 num6 num7 num8 num9" << endl
			<<"transform num1 rotate " << to_string(anglex)<< " " << to_string(j)<< " " << to_string(k)<< " " << to_string(l) << endl
			<<"#transform num1 rotate " << to_string(angley)<< " " << to_string(m)<< " "  << to_string(n)<< " "  << to_string(o) << endl
			<<"transform num1 translate 0 0 -5" << endl
			<<"transform num1 scale 1 1 1" << endl 
			<<"#transform num2 translate 0 -1 0"<< endl
			<<"#transform num2 scale 100 0 1000"<< endl
			<<"#transform num3 scale " << to_string(z) << " 1 2" << endl
			<<"define light diffuse sun1 0 0 10 1 1 1" << endl
			<<"define light ambient ambient 0.2 0.2 0.2" << endl
			<<"#define camera guck 120 0 0 0" << endl;
			//<< cameraCmd << endl
		fOut.close();

	}

	return 0;
}
