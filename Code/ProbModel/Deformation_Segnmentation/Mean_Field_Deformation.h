#pragma once
#include "TriMesh.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include<iostream>
#include<vector>
#include"namepoint.h"
#include "Compute_Feature.h"
#include"Sample.h"
#include <math.h>
#include"sparse_solver_eigen.h"
#include"FindNearest.h"
#define EPSILON_NULL 0.5
#define EPSILON_DEV 0.0001
#define TARGETNEARSIZE 20
#define TEMPLATENEARSIZE 100
#define EPSILON_SEGNMENTATION 0.001
#define THETATHRESHOLD -3
using namespace std;
using namespace trimesh;
class Mean_Field_Deformation
{
public:
	Mean_Field_Deformation(void);
	~Mean_Field_Deformation(void);
	Mean_Field_Deformation(vector<Sample> t_sample, vector<Sample> s_sample, vector<vector<int>> connection, int seg_size);
	vector<Sample> target_sample;
	vector<Sample> template_sample;
	int nearest_sample_size;
	int total_seg_size;
	vector<ivec3> color_list;
	vector<vector<float>> pro_target_seg; // s_p = s 
	vector<vector<float>> pro_target_template; // s_p = s 
	vector<vector<int>> template_connection;  // n(k)
	vector<vector<int>> matching_template_target; // N(p)
    vector<vector<float>> pro_template_target; // (U_r = p)
	vector<vector<int>> matching_targte_template; // N(p)
	vector<vector<int>> matching_target_target; // N(p)
	vector<vector<vec3>> initial_distance;
	vec3 sigma_1;
	vector<float> sigma_2;
	vec3 sigma_3;
    vector<float> sigma_4;
	vec3 sigma_5;
	vector<float> sigma_6;
	vec3 sigma_7;
	vector<float> sigma_8;
	float sigma_dis_1;
	float sigma_dis_2;
	float sigma_dis_3;
	float sigma_dis_4;
	float average_dis_template_target;
	float average_dis_target_template;
	float Theta(Sample &shape_sample_1, Sample &shape_sample_2, int is_same); 
	void Initial();
    void FindNeighbor();
	void SetInitialSigmaValue();
	void GetInitialDistance();
	void UpdatePosition(int ite);
	void UpdateSigma();
	void UpdateFeature();
	void UpdateSegnmenatation();
	void UpdataShapeTemplateMatching();
	void UpdataTemplateShapeMatching();
	vector<Sample> DeformToShape();
	void TestTemplateSample(string mesh_out,string shape_out);
	void CutShapeSample();
	float EvaluateErr(int with_seg = 0);
	int CheckNeighbor(int target_index, int template_index);
	vector<float> FeatureDiff(Sample sample_1, Sample sample_2);
	void  ReNormal(vector<Sample> &sample_list);
	void  VisualDeform(int ite1, int ite2);
	void  VisualSeg(int ite);
	vector<vec3> gt_point;
	vector<int> match_index;
	vector<ivec3> gt_color_List;
	void LoadGtPoint(string  gt_file);
	void VisualCorrespondence(int ite);
	vector<vector<int>> BulitConnectionByGroup(vector<Sample> sample_list);

};

