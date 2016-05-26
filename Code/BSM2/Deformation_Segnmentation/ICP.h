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
#include"namepoint.h"
using namespace std;
class ICP
{
public:
	ICP(void);
	~ICP(void);
	ICP(vector<vec3> s_p, vector<vec3> t_p);
	vector<vec3> s_point;
	vector<vec3> t_point;
	void Translation();
	void Scale();
	void Rotation();
	vec3 center_t;
	vector<vec3> RunICP();
};


