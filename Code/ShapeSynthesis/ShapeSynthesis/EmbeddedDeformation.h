#pragma once
#include<iostream>
#include<fstream>
#include <string>
#include<sstream>
#include<vector>
#include<ctime>
#include "TriMesh.h"
#include "TriMesh_algo.h"
#include "namepoint.h"
#include"sparse_solver_eigen.h"
#include"Eigen\Dense"
#include"SamplePoissonDisk.h"
using namespace std;
using namespace trimesh;
#define WEIGHTROT 5
#define WEIGHTREG 20
#define WEIGHTCON 120
#define RINGNEIGHBOR 20
#define NODESIZE 100
class EmbeddedDeformation
{
public:
	EmbeddedDeformation(void);
	~EmbeddedDeformation(void);
	EmbeddedDeformation(string mesh_name, string c_file, string m_file, string out_mesh);
	EmbeddedDeformation(TriMesh* &input_mesh, vector<vec3> &original_point, vector<vec3> moved_point);
private:
	TriMesh *mesh; // orginal mesh
	vector<vec3> node_point;
	vector<vec3> constraint_point;
	vector<vec3> sampled_constraint_point;
	vector<vector<int>> node_connection;
	vector<vector<float>> weight_vertex;
	vector<vec3>  moved_constraint_point;
	vector<vec3>  sampled_moved_constraint_point;
	vector<vector<int>> constrain_node_connection;
	vector<vector<int>> sampled_constrain_node_connection;
	vector<vector<float>> weight_constraint;
	vector<vector<float>> weight_sampled_constraint;
	vector<vector<float>> trans_matrix_node; // 12*1 for each node
	vector<vector<int>> vetrex_node_connection;
	void generateNodeSample();
	void aligmentPoint();
	void loadMesh(string mesh_name);
	void loadconstraintPoint(string file_name);
	void loadMovedconstraintPoint(string file_name);
	void calculateWeight();
	void buildNodeConnection();
	void initialMatrix();
	void addNodeNeighbor(int node_1, int node_2);
	void gaussnewtonMethod();
	void deformation();
	void outputMesh(string mesh_name);
	void visualNodeGraph(string ply_name);
	void gaussnewtonMethodNew();
	void refineConstraintPoint();
	void makeControlPointSymmetry(vector<vec3> &point_set);
	void visualPointLine(vector<vec3> polit_list1, vector<vec3> polit_list2, int color_type1, int color_type2,string file_name);
	void sampleconstraintPoint();
};

