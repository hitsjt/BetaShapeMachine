#pragma once
#include "TriMesh.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include<iostream>
#include<vector>
#include"namepoint.h"
#include"ANN\include\ANN.h"
using namespace std;
using namespace trimesh;
class EvalCorrespondence
{
public:
	EvalCorrespondence(void);
	~EvalCorrespondence(void);
	EvalCorrespondence(vector<string> list, string gtpath, string matchingpath, string meshpath);
	vector<string> model_list;
	string gt_path;
	string matching_point_path;
	string mesh_path;
	vector<vector<vec3>> model_point;
	vector<vector<int>> point_index;
	vector<float> mesh_radius;
	void ReadPoint();
	void ReadGroundTruth();
	void ReadGroundTruthByPosition();
	void GetRadious();
	vector<vector<vec3>> ground_truth;
	vector<vector<int>> is_valid;
	vector<vector<int>> point_part_id;
	void GetPlot(string file_name);
	void GetPlot_Other(string file_name);
	void GetPlot_Soft(string file_name);
	void ReadPointOther();
	void GetMean(vector<float> dis_list, float &mean, float &var);
};
