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
#include"Shape.h"
#include"sparse_solver_eigen.h"
#include"namepoint.h"
#include"ICP.h"
#include"Compute_Feature.h"
#include"ShapeKmeans.h"
#include"KMeans.h"
class Similarity_Marix
{
public:
	Similarity_Marix(void);
	~Similarity_Marix(void);
	vector<vector<float>> Distance_matrix;
	string working_path;
	vector<string> meshlist;
	vector<vector<Sample>> mesh_sample;
	vector<float> GetDistance(int index);
	float SimilarityDistance(vector<Sample> s_point, vector<Sample> t_point);
	float GetMeanDist(vector<Sample> target_sample);
	void LoadMesh(string file_path);
	void OutPutMatrix();
	void OutputSBFile(vector<size_t> k_mean, int k, string file_name);
};

