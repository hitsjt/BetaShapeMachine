#pragma once
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
using namespace std;
class Deform_Box
{
public:
	Deform_Box(void);
	~Deform_Box(void);
	vector<Sample> box_sample;
	vector<Sample> shape_sample;
	vector<Sample> shape_refine_sample;
	vector<vector<int>> connection_box;
	void GetConnection(vector<vector<int>> connection);
	vector<vec3> box_Lapalican;
	vector<Sample> deform_box_sample;
	vector<int> box_shape_correspondence;
	void GetPoints(vector<Sample> box, vector<Sample> shape);
	// soft map
	vector<vector<int>> soft_map_near;
	vector<vector<float>> soft_map_weight;
	void Find_Soft_Map();
	void Deform_Soft(float smooth, float data);
	vector<vector<int>> soft_map_near_t;
	vector<vector<float>> soft_map_weight_t;
	void Find_Soft_Map_T();

	// refine shape_sample
	vector<vec3> match_point;
	vector<vector<int>>  shape_connection;
	vector<vec3> shape_lapalican;
	void BulidShapeConnection();
	void GetMatchPoint();
	void Refine();
	int check_normal;
	vector<vector<int>> Find_KNN(vector<Sample> source_point, vector<Sample> target_point, int k);
};

