#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include<iostream>
#include"Sample.h"
#include<vector>
#include"namepoint.h"
#include"ANN\include\ANN.h"
class FindNearest
{
public:
	FindNearest(void);
	~FindNearest(void);
	FindNearest(vector<Sample> sourse_sample, vector<Sample> target_sample, int k_size);
	vector<Sample> s_sample; 
	vector<Sample> t_sample;  // find k nearest sample in s_sample for each t_sample;
	int k_near_size;
	vector<vector<int>> FindKnearestByEdistance(int normal_check = 1);
	vector<vector<int>> FindKnearestByFeature();
	vector<vector<int>> FindKnearestBySDF();
	vector<vector<int>> FindnearestBySC();
	vector<vector<int>> FindnearestByDiff();
	vector<vector<int>> FindNearestType(int type = 0);
};

