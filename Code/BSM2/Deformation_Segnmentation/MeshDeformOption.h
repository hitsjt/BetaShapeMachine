#pragma once
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>
#include <map>
#include <sys/stat.h>
#include <direct.h>
#include "Find_Match.h"
#include "EvalCorrespondence.h"
#include "SegMeshFace.h"
#include "DeformFromShape.h"
//#include"Compute_Feature.h"
#include "../../BSM/Source/SNL.hpp"
#include "../../BSM/Source/Plugins/DL13/DL13_ShapeGenModel.hpp"
#include "../../BSM/Source/Plugins/PCA/PCA_Model.hpp"
#include "../../BSM/Source/Plugins/DL13/DL13_Point.hpp"

#define INITIALTEMP             "initial_temp"
#define MESHFILELIST			"meshlist.txt"
#define MESHFILELISTAUTOALIGNED			"meshlist_AUTOALIGNED.txt"
#define GROUNDMESHFILELIST			 "groundtruth_meshlist.txt"
#define GROUNDMESHFILELISTAUTOALIGNED "groundtruth_meshlist_AUTOALIGNED.txt"
#define TEMPLATEFITTINGFOLDER			"template_fit"
#define DEFORMFOLDER			"out_deform"
#define MATCHINGFOLDERBEFOREMAP          "matching_before"
#define MATCHINGFOLDER          "matching"
#define SPARSEOUT               "sparse_sample"
#define EVAOUT                  "eva_out"
#define TARGETFEATURE            "target_feature"
#define DENSEOUT               "dense_sample"
#define LEARNINGFOLDER          "after_learn"
#define DENSEMATCHING           "dense_matching"
#define GROUNDTRUTH             "ground_truth"
#define SUBMESHFOLDER           "sub_mesh"
#define SAMPLEFOLDER           "sample"
#define MATRIXFOLDER           "rotation_matrix"
#define ROTATIONDEFORM           "rotation_deform"
#define EVASAMPLEFOLDER           "eva_sample"
#define BASESHAPE               "base_shapes"
#define BASEFEATURE               "base_feature"
#define TARGETSAMPLE             "target_sample"
#define FILE_STRING_SIZE						4096
using namespace trimesh;
using namespace std;
using namespace SNL;
using namespace DL13;

string parent(string const & file_path);
string getFullPath(string const & dir, string const & filename);

class MeshDeformOption
{
public:
	MeshDeformOption(void);
	~MeshDeformOption(void);
	int ite_time;
	int current_deform_mode;  // 0 for animal (with segenmention),  1 for other sets.  2 for objection detection, 3  
	string input_mesh_path;
	vector<string> groundtruth_mesh;
	vector<string> groundtruth_mesh_AUTOALIGNED; 
	string set_name;
	string out_dense_path;
	string out_sparse_path;
	string out_eva_path;
	string working_path;
	string temp_path;
	string deform_path;
	string rotation_deform_path;
	string matching_path;
	string matching_path_before_map;
	string learn_results_path;
	string dense_matching_path;
	string ground_truth_path;
	string initial_temp_path;
	string sub_mesh_path;
	string sample_path;
	string eva_sample_path;
	string target_sample_path;
	string matrix_path;
	string target_feature_path;
	vector<string> mesh_list; 
	vector<string> mesh_list_AUTOALIGNED;

	float fitting_threshold_first_iteration;

	void GetMeshList();
	void SetWorkingPath();
	void CreateWorkingFloder(int ite);
	void DefromeWithFixSeg(int ite);
	void Deform(int ite);
	void Learning(int ite);
	void Run();
	void Init();
	void FindMatching(int ite); 
	void CorrespondenceAccracy(int ite);
	void ReconstructionFromLearning(int ite);
	void WriteBinaryMap();
	void ObjecteDetection(int ite);
	void FixAlignment(int ite);
	void MeshSegnmentation(vector<size_t> seg_list, int center_mesh, int base_size);
};

