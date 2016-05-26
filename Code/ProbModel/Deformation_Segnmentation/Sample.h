#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include<iostream>
#include<vector>
#include "TriMesh.h"
using namespace std;
using namespace trimesh;
class Sample
{
public:
	Sample(void);
	~Sample(void);
	Sample(vec3 pos, vec3 nor, float weg = 1.0f, int id = -1);
	vec3 position;
	vec3 normal;
	vec3 pca;
	vec3 angel;
	vec3 angel_with_up;
	ivec3 color;
	float weight;
	int face_id;
	int patch_id;
	vector<float> diff_feature;
	vector<float> sample_features; // just for check each feature
	vector<float> shape_context;
	vector<float> var_sc; // var for shape_context in each dim
	vector<float> angel_geo_dis;
	vector<float> var_agd;
	vector<float> spin_image;
	vector<float> var_si;
	vector<float> sample_pca;
	vector<float> curvature;
	vector<float> var_cur;
	vector<float> sdf;
	int is_sigular ;
	float dist_feature(Sample p1, int feature_type);
	float dist_with_normal(Sample p1);
	float dist_with_feature(Sample p1);
	float dis_curvature(Sample p1);
	float dis_shapeconetx(Sample p1);
};

