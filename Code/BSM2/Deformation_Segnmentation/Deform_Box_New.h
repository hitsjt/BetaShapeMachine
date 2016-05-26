#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<sstream>
#include<vector>
#include<ctime>
#include "Eigen/Dense"
#include "Eigen/LU"
#include"Sample.h"
#include"sparse_solver_eigen.h"
#include"namepoint.h"
#include"ICP.h"
using namespace std;
class Deform_Box_New
{
public:
	Deform_Box_New(void);
	~Deform_Box_New(void);
	vector<Sample> box_sample;
	vector<Sample> shape_sample;
	vector<vector<int>> connection_box;
	void GetConnection(vector<vector<int>> connection);
	vector<Sample> deform_box_sample;
	void GetPoints(vector<Sample> box, vector<Sample> shape);
	// soft map from shape to box
    vector<vector<int>> soft_map_near;
	vector<vector<float>> soft_map_weight;
	void Find_Soft_Map();
	void Find_Soft_Map_new();
	// soft map from box to shape
	vector<vector<int>> soft_map_near_t;
	vector<vector<float>> soft_map_weight_t;
	void Find_Soft_Map_T();
	void SetDisThresh();
	float dis_thread_hold;
	// deformation
    void Deform_Soft(float smooth, float data);
	void DeformToShape(float smooth, float data);
	int check_normal;
	int near_point;
};

