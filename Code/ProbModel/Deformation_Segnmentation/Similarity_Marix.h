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
#include"DeformFromShape.h"
#include"SegMeshFace.h"
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
	void laodSamplePoint(string file_path);
	void OutPutMatrix();
	void OutPutMatrixWithSize(int k_size);
	void OutputSBFile(vector<size_t> k_mean, int k, string file_name);
	void RunDeformationSegnmenation(vector<size_t> seg_list, int center_mesh, int base_size);
	void RunInPairs(string template_mesh_file, string template_gt_file, string seg_name, string mesh_name, string ply_file, string txt_file, string out_obj, string out_seg);
	vector<vector<Sample>> mean_shape_list;
	vector<string> meanlist;
	void GetMeanShapes(string file_path);
	void OutPutMatrixWithMean();
};

