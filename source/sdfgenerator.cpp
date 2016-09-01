
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
		float z = 1;
		float x = 1;
		

		
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
		*/
		if(i<=90){
			 z = (0.005*i) + 1;
		}
		if(i>90 && i<=180 ){
			 z = (0.005*(180-i)) + 1;
		}
		if(i>180 && i<=270 ){
			 z = (0.005*(i-180)) + 1;
			 x = (0.005*(i-180)) + 1;
		}
		if(i>270 && i<=360 ){
			 z = (0.005*(360-i)) + 1;
			 x = (0.005*(360-i)) + 1;
		}
		

		fOut
			<<"define material red   1 0 0 1 0 0 1 1 1 0 0 40" << endl
			<<"define material green 0 1 0 0 1 0 1 1 1 0 0 40" << endl
			<<"define material blue  0 0 1 0 0 1 1 1 1 0 0 40" << endl
			<<"define material mat_yellow  0.70 0.30 0.15 0.70 0.30 0.15 0.90 0.90 0.90 0.5 0 40" << endl
			<<"define material mat_red     0.46 0.00 0.18 0.46 0.00 0.18 0.90 0.90 0.90 0.1 0.3 40" << endl
			<<"define material mat_blue    0.36 0.48 0.78 0.36 0.48 0.78 0.90 0.90 0.90 0.3 0 40" << endl
			<<"define material mat_lblue   0.42 0.82 1.00 0.42 0.82 1.00 0.90 0.90 0.90 0 0 40" << endl
			<<"define material mat_orange  0.60 0.20 0.20 0.60 0.20 0.20 0.90 0.90 0.90 0.3 0 40" << endl
			<<"define material yellow  1 1 0 1 1 0 0.90 0.90 0.90 0.8 0 40" << endl
			
			//Box
			<<"define shape box num1  -1  -1   -1    1    1    1   mat_orange" << endl
			<<"define shape box num2   7  -6  -93    17 -16  -83   mat_blue" << endl
			<<"define shape box num3 -29   5  -93   -19  -5  -83   red" << endl
			<<"define shape box num4  -5   5  -93     5  -5  -83   red" << endl
			<<"define shape box num5  19   5  -93    29  -5  -83   mat_lblue" << endl
			<<"define shape box num6  -1  -1   -1     1   1    1   mat_red" << endl
			<<"define shape box num7   7  16  -93    17   6  -83   mat_orange" << endl
			
			//Shpere
			<<"define shape sphere num9   -24  -11  -88  5 mat_yellow" << endl
			<<"define shape sphere num10    0  -11  -88  5 mat_red" << endl
			<<"define shape sphere num11   24  -11  -88  5 blue" << endl
			<<"define shape sphere num12  -12    0  -88  5 mat_blue" << endl
			<<"define shape sphere num13   12    0  -88  5 green" << endl
			<<"define shape sphere num14  -24   11  -88  5 mat_lblue" << endl
			<<"define shape sphere num15    0   11  -88  5 blue" << endl
			<<"define shape sphere num16   24   11  -88  5 mat_orange" << endl
			<<"define shape sphere num17   0   0  10  5 yellow" << endl
			
			//composite
			<<"define shape composite root num1 num2 num3 num4 num5 num6 num7 num8 num9 num10 num11 num12 num13 num14 num15 num16 num17" << endl

			//transform
			<<"transform num1 rotate " << to_string(anglex)<< " 1 1 0" << endl
			<<"transform num6 rotate " << to_string(anglex)<< " 1 1 0"<< endl

			<<"transform num14 scale "<< " 1 " << to_string(z) << " 1 "<< endl
			<<"transform num9 scale " << to_string(z)<< " 1 1"<< endl
			<<"transform num4 scale " << to_string(z)<< " " << to_string(x) <<"  1"<< endl
			
			
			
			
			<<"transform num1 scale 5 5 5" << endl 
			<<"transform num2 scale 1 1 1" << endl 
			<<"transform num3 scale 1 1 1" << endl 
			<<"transform num4 scale 1 1 1" << endl 
			<<"transform num5 scale 1 1 1" << endl 
			<<"transform num6 scale 5 5 5" << endl 
			<<"transform num7 scale 1 1 1" << endl 


			<<"transform num6 translate -10 11 -88" << endl 
			<<"transform num1 translate -10 -11 -88" << endl 
			//<<"define shape box num1 -17  -6  -93    -7 -16  -83   mat_orange" << endl
			//<<"define shape box num6 -17  16  -93    -7   6  -83   mat_red" << endl
			
			

			<<"#transform num2 translate 0 -1 0"<< endl
			<<"#transform num2 scale 100 0 1000"<< endl
			<<"#transform num3 scale " << to_string(z) << " 1 2" << endl

			//Lights
			<<"define light diffuse sun1 0 0 3 1 1 1" << endl
			<<"define light ambient ambient 0.1 0.08 0.1" << endl

			//Camera
			<<"#define camera guck 120 0 0 0" << endl;
			//<< cameraCmd << endl
		fOut.close();

	}

	return 0;
}
