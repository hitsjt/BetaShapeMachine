#pragma once
#include "TriMesh.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include<iostream>
#include<vector>
#include"ANN\include\ANN.h"
using namespace std;
using namespace trimesh;
class Find_Match
{
public:
	Find_Match(void);
	~Find_Match(void);
	//vector<vector<vec>> point_by_part;
	//vector<vector<int>> point_index_by_part;
	vector<vec> temp_point;
	vector<vec> temp_normal;
	vector<ivec3> temp_color;
	vector<vec> mesh_face_normal;
	vector<vec> mesh_face_center;
	vector<vec> match_point;
	vector<vec> match_normal;
	vector<int> true_index;
	TriMesh *themesh;
	int temp_id;
	float fit_err;
	vector<int> part_id;
	int total_size;
	vector<int> match_correspondence;
	void ReadMesh(string mesh_name);
    void LoadTemplate(string temp_name);
	void SetCorlor(string file_name);
	void ReadMeshSample(string file_name);
	void FindMatchingBySample();
	void OutPutResults(string out_name);
	void OutMatchingPly(string out_ply);
	void OutMatchBinary(string out_name);
};