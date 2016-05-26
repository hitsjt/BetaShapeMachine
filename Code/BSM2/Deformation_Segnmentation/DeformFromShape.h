#pragma once
#include"Shape.h"
#include"Deform_With_Seg.h"
#include"Mean_Field_Deformation.h"
class DeformFromShape
{
public:
	DeformFromShape();
	~DeformFromShape();
	vector<vector<int>> s_connection;
	vector<Sample> s_shape_sample;
	vector<int> valid_group;
	vector<Sample> t_shape_sample;
	vector<ivec3> color_list;
	vector<int> s_shape_index;
	vector<int> s_shape_part;
	vec3 target_center;
	void GetSample(string s_file, string t_file);
	void GetSampleFromBaseShapesWithMesh(string file_name, string mesh_file);
	void LoadTargetSampleWithPreSeg(string s_file, string mesh_file);
	void LoadTargetSampleWithegFeature(string s_file, string f_file);
	void GetSampleFromBaseShapes(string mesh_file, string gt_file);
	void GetTargetSampleWithSeg(string mesh_file, string path_file);
	void GetSampleFromMatching(string s_file);
	void GetSampleFeatureFromMatching(string f_file, string s_file);
	void GetSampleFromTemplate(string s_file);
	void GetTargetSample(string t_file);
	void SetValidTemplateSample();
	void GetBoxDetectionSample(string file_name);
	void SetValidGroup(string file_name);
	void SetColor();
	void BuiltShapeConnection();
	void Deformation();
	void Deformation_With_Seg();
	void OutPutAndVisual(string p_file, string s_file, int out_type = 0);
	void ScaleSample();
	void AlignmentToCenter();
	void ScaleTemplate();
	void RotateDeformation(string m_file, string out_file);
	void ReNormal(vector<Sample> &sample_list);
	void DeformMeanField();
	vector<vector<int>> BulitConnectionByGroup(vector<Sample> sample_list);
	void RefineDefomration(string file_name, string mesh_file, string out_mesh);
	void ReSetFromLearing(string file_name);
	int total_template_size;
	// for feature
	void GetSampleFeature(string s_file, string t_file);
	float CalFeature();
	void RigidAlignment();
	
};

