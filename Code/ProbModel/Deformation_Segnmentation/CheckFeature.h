#pragma once
#include"Sample.h"
#include"namepoint.h"
#include"Compute_Feature.h"
#include"Shape.h"
class CheckFeature
{
public:
	CheckFeature(void);
	~CheckFeature(void);
	vector<Sample> s_sample;
	vector<Sample> t_sample;
	void LoadFeature(vector<Sample> &samplelist, string file_name);
	float CheckDiff();
	float Diff(vector<float> f1, vector<float> f2);
	void OutPutFeature(string mesh_name, string file_name);
};

