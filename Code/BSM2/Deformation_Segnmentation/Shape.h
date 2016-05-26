#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<sstream>
#include<vector>
#include<ctime>
#include "Eigen/Dense"
#include "Eigen/LU"
#include"SamplePoissonDisk.h"
#include"Sample.h"
#include"namepoint.h"
#include "TriMesh.h"
#include "namepoint.h"
#include "Compute_Feature.h"
#include "TriMesh_algo.h"
using namespace std;
class Shape
{
public:
	Shape(void);
	~Shape(void);
	TriMesh *Shape_Mesh;
	vector<Sample> shape_sample;
	vector<vector<Sample>> Shape_With_Seg;
	//vector<vec> face_normal;
	vector<vector<int>> face_group;
	vector<int> part_id;
	vector<ivec3> sample_color;
	void GetShape(string file);
	void Radius();
	void SaveFileWithSeg(string file_name, vector<int> true_index);
	void GetShape_Cut(int part_number, int with_resample = 0);
	void WriteShapeWithName(string file_name);
	void GetSamplePoint(int sample_size = 20000);
	void GetSamplePointForFaceSeg();
	void SetSampleColor(int index, ivec3 color) { sample_color[index] = color;};
	vec3 GetSamplePose(int index);
	vec3 GetSampleNormal(int index);
	void Rotate_Shape(vector<Sample> t_point);
	void AddBounday();
	void Fix_Normal();
	float shape_radiu;
	vec3 variance;
	void Viual_scan(string file_name);
	vector<int> face_part_id;
	vector<vector<int>> per_face_index; 
	void OutSeg(string mesh_file, string index_file, int seg_size);
	static float m_average_sampling_density;
	float GetAverageSampleDistance(int kNum = 5 );
	vector<Sample> SamplingByPart(int index,vector<int> face_list);
	void GetFaceGroup(int face_size);
	void RotateHalfPi();
	void RotateShape(int n_pi,string file_name);
	bool CheckInternal();
	void GetShapeFeature();
	void SaveSample(string file_name, vector<int> true_index);
	void OutPutSample(string s_file);
};

