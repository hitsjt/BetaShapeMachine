#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include <string>
#include<sstream>
#include"Shape.h"
#include <algorithm> 
#include "../GCO/GCoptimization.h"
#pragma comment(lib, "../x64/release/GCO.lib")
using namespace std;

class SegMeshFace
{
public:
	SegMeshFace(void);
	~SegMeshFace(void);
	static float DataFunc(int p, int l);
	static float DataFunc2(int p, int l);
	static float SmoothFunc(int p1, int p2, int l1, int l2);
	void GraphCut();
	void GraphCut_new();
	void GraphCut_refine();
	void OutResult(string mesh_file, string index_file);
	void AddConnectComponemnet();
	//new seg
	vector<Sample> seg_point;
	vector<int>  true_index;
	vector<int>  face_group;
	void LoadData(string  point_file, string mesh_file);
	void SegFace();
	void OutPutSeg(string mesh_file);
	void Refine();
	void OutPutSegFile(string out_file);
	void SetSmoothWeight(float weight = 5.5);
};

