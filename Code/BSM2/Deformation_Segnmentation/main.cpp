#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "MeshDeformOption.h"
#include"CheckFeature.h"
#include"Shape.h"
using namespace std;

int main(int argc, char* argv[])
{
	MeshDeformOption options;
	if (strcmp(argv[1], "-reconstruction") == 0) 
	{
		options.current_deform_mode = 0;
		options.input_mesh_path = string(argv[2]);
		if(strcmp(argv[3], "-ite") == 0)
		{
			options.ite_time = stoi(argv[4]);
		}
		options.Init();
	    options.Run();
	} 
	if (strcmp(argv[1], "-learning") == 0) 
	{
		options.current_deform_mode = 1;
		options.input_mesh_path = string(argv[2]);
		if(strcmp(argv[3], "-ite") == 0)
		{
			options.ite_time = stoi(argv[4]);
		}
		options.Init();
	    options.Run();
	} 

	if (strcmp(argv[1], "-objecteDetection") == 0)
	{
		options.current_deform_mode = 2;
		options.input_mesh_path = string(argv[2]);
		if (strcmp(argv[3], "-ite") == 0)
		{
			options.ite_time = stoi(argv[4]);
		}
		options.Init();
		options.Run();
	}

	if (strcmp(argv[1], "-fixAlignment") == 0)
	{
		options.current_deform_mode = 3;
		options.input_mesh_path = string(argv[2]);
		if (strcmp(argv[3], "-ite") == 0)
		{
			options.ite_time = stoi(argv[4]);
		}
		options.Init();
		options.Run();
	}

	return 0;

}

