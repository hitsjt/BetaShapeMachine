#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<sstream>
#include<vector>
#include<ctime>
using namespace std;
class ShapeKmeans
{
public:
	ShapeKmeans(void);
	~ShapeKmeans(void);
	ShapeKmeans(vector<vector<float>> sample, int k);
	vector<vector<float>> sample_list;
	vector<vector<float>> center_sample;
	vector<int> sample_group;
	vector<int> group_count;
	int k_size;
	int FindClose();
	void UpdataMean();
	void Initial();
	float Distance(vector<float> p1, vector<float> p2);
	vector<int> RunKmean();
};

