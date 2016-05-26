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
#include"Compute_Feature.h"
#include"FindNearest.h"
using namespace std;
#define DISTANCETYPE 1
#define MATCHINGTYPE 1
class Deform_With_Seg
{
public:
	Deform_With_Seg();
	~Deform_With_Seg();
	vector<Sample> sourse_sample;
	vector<Sample> target_sample;
	vector<vector<float>> target_seg_prob;
	vector<vector<int>> target_near_list;
	vector<vector<int>> connection_box;
	void GetConnection(vector<vector<int>> connection);
	vector<Sample> deform_sourse_sample;
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
	void UpdataFeature();
	void ReNormal(vector<Sample> &sample_list);
	float scale_factor;
	float mean_feature_dis;
	float var_feature_dis;
	float mean_feature_dis_t_s;
	float var_feature_dis_t_s;
	void GetTargetNeighbor();
	void SegnmentTarget();
	void UpdataTargetSegnmentPro();
	float ThetaFunction(Sample shape_sample_1, Sample shape_sample_2, int is_same);
	void SetMeanFeatureDis();
	int  total_seg_size;
	void SetInitialPro(int size);
	void Run();
	void VisualSeg();
	void SetMeanFeatureDisST(vector<vector<int>> near_list);
	void FixSef(int index);
	void GetMean(vector<float> dis_list, float &mean, float &var);
};

