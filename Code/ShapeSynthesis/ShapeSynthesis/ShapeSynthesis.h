#pragma once
#include"EmbeddedDeformation.h"
#include <algorithm>
#define BOUNDARY_SIZE 5
#define MOVING_SCALE 1.0f
class ShapeSynthesis
{
public:
	ShapeSynthesis(void);
	~ShapeSynthesis(void);
	ShapeSynthesis(string point_file, string m_path, string p_path, string out_mesh, int deformation_type = 0);
	ShapeSynthesis(string point_file, string m_path, string p_path, string connect_file, string bound_path, string out_mesh, int deformation_type);
private:
	vector<vector<vec3>> control_point;
	vector<vector<int>> boundary_firstpart;
	vector<vector<int>> boundary_second;
	vector<int> first_part_list;
	vector<int> second_part_list;
	vector<vector<vec3>> orignal_point; 
	int total_point;
	vector<int>  part_list;
	vector<int>  symmtric_part_list;
	vector<string> model_list;
	string mesh_path;
	string point_path;
	string out_path;
	string boundary_path;
	int deformation_mode; // 0 means no deformation, 1 for emb deformation
	vector<vector<vec3>> loadOrignalPoint(vector<string> mesh_list,int index);
	vector<TriMesh *>    loadOrignalMesh(vector<string> mesh_list,int index);
	void loadSymmtricPart(string file_name);
	void loadPartConnetion(string file_name);
	void outputMesh(string mesh_name);
	void loadControlPoint(string point_file);
	void makeControlPointSymmetric();
	float errWithSymmtric(vec3 symmtric_vector);
	vector<vec3> getPatrCenter();
	vector<vector<string>> getSymmetricModelList();
	bool checkSymmetric(vector<vector<string>> symmtric_list);
	void deformation(vector<TriMesh *> &mesh_list);
	void loadMeshBoundary();
	void findBoudaryPoint();
	void findBoundarySample();
	vector<int> getCenterPartBoundary(string center_file,int part_id);
	vector<int> getPartBoundary(string part_file);
	vector<int> findBoundaryIndex(int part_1, int parrt_2);
	void assembelPart(vector<TriMesh *> &mesh_list, vector<vector<vec3>> sample_list);
	vec3 getCenterOfBoundary(TriMesh * mesh, vector<vec3> sample, vector<int> bounday_list);
	vec3 symmrtric_vec;
	// change input file
	float deforma_prob;
	void outputSymmetricControl(string point_file,vector<string> file_name,int index);
};

