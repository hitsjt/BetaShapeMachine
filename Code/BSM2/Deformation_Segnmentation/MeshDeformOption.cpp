#include "MeshDeformOption.h"


MeshDeformOption::MeshDeformOption(void)
{
	working_path.clear();
}


MeshDeformOption::~MeshDeformOption(void)
{

}


void MeshDeformOption::Init()
{
	GetMeshList();
	SetWorkingPath();
}

void MeshDeformOption::SetWorkingPath()
{
	unsigned sPos;
	sPos = input_mesh_path.find_last_of("\\");
	if(working_path.size() == 0)
	{
		working_path = input_mesh_path.substr(0,sPos);
		cout << working_path << endl;
	}
	else
	{
		_mkdir(working_path.c_str());
	}
	cout << working_path << endl;
	set_name = input_mesh_path.substr(sPos+ 1 , input_mesh_path.size() - sPos );
	cout << set_name << endl;
	// for template file
	temp_path = working_path;
	temp_path.append("/");
	temp_path.append(TEMPLATEFITTINGFOLDER);
	_mkdir(temp_path.c_str());

	sample_path = working_path;
	sample_path.append("/");
	sample_path.append(SAMPLEFOLDER);
	_mkdir(sample_path.c_str());

	eva_sample_path = working_path;
	eva_sample_path.append("/");
	eva_sample_path.append(EVASAMPLEFOLDER);
	_mkdir(eva_sample_path.c_str());


	target_feature_path  = working_path;
	target_feature_path.append("/");
	target_feature_path.append(TARGETFEATURE);
	_mkdir(target_feature_path.c_str());


	matrix_path = working_path;
	matrix_path.append("/");
	matrix_path.append(MATRIXFOLDER);
	_mkdir(matrix_path.c_str());

	ground_truth_path = working_path;
	ground_truth_path.append("/");
	ground_truth_path.append(GROUNDTRUTH);

	target_sample_path = working_path;
	target_sample_path.append("/");
	target_sample_path.append(TARGETSAMPLE);
}

void MeshDeformOption::CreateWorkingFloder(int ite)
{
	//out_deform
	deform_path = working_path;
	deform_path.append("/");
	deform_path.append(DEFORMFOLDER);
	deform_path.append("_");
	deform_path.append(to_string(ite));
	_mkdir(deform_path.c_str());

	rotation_deform_path = working_path;
	rotation_deform_path.append("/");
	rotation_deform_path.append(ROTATIONDEFORM);
	rotation_deform_path.append("_");
	rotation_deform_path.append(to_string(ite));
	_mkdir(rotation_deform_path.c_str());

	//matching
	matching_path = working_path;
	matching_path.append("/");
	matching_path.append(MATCHINGFOLDER);
	matching_path.append("_");
	matching_path.append(to_string(ite));
	_mkdir(matching_path.c_str());

	matching_path.append("/");
	matching_path.append("sparse");
	_mkdir(matching_path.c_str());

	out_sparse_path = working_path;
	out_sparse_path.append("/");
	out_sparse_path.append(SPARSEOUT);
	out_sparse_path.append("_");
	out_sparse_path.append(to_string(ite));
	_mkdir(out_sparse_path.c_str());


	out_eva_path = working_path;
	out_eva_path.append("/");
	out_eva_path.append(EVAOUT);
	out_eva_path.append("_");
	out_eva_path.append(to_string(ite));
	_mkdir(out_eva_path.c_str());
	cout << "out_eva_path ---------- " << out_eva_path << endl;

	learn_results_path = working_path;
	learn_results_path.append("/");
	learn_results_path.append(LEARNINGFOLDER);
	learn_results_path.append("_");
	learn_results_path.append(to_string(ite));
	_mkdir(learn_results_path.c_str());

	for(int i = 0; i < mesh_list.size(); i++)
	{
		string model_folder = matching_path;
		model_folder.append("/");
		unsigned ePos;
		ePos = mesh_list[i].find_last_of(".");
		string folder_name = mesh_list[i].substr(0, ePos);
		model_folder.append(folder_name);
		_mkdir(model_folder.c_str());
	}

	for(int i = 0; i < mesh_list.size(); i++)
	{
		string model_folder = matching_path;
		model_folder.append("/");
		unsigned ePos;
		ePos = mesh_list[i].find_last_of(".");
		string folder_name = mesh_list[i].substr(0, ePos);
		model_folder.append(folder_name);
		_mkdir(model_folder.c_str());
	}
}

void MeshDeformOption::GetMeshList()
{
	mesh_list.clear();
	string meshfile = input_mesh_path;
	meshfile.append("/");
	meshfile.append(MESHFILELIST);
	ifstream fin(meshfile);
	string para;
	while(fin >> para)
	{
		mesh_list.push_back(para);
		cout << para << endl;
	}

	mesh_list_AUTOALIGNED.clear();
	string meshfile_AUTOALIGNED = input_mesh_path;
	meshfile_AUTOALIGNED.append("/");
	meshfile_AUTOALIGNED.append(MESHFILELISTAUTOALIGNED);
	ifstream fin_AUTOALIGNED(meshfile_AUTOALIGNED);
	while (fin_AUTOALIGNED >> para)
	{
		mesh_list_AUTOALIGNED.push_back(para);
		cout << para << endl;
	}

	groundtruth_mesh.clear();
	string ground_mesh = input_mesh_path;
	ground_mesh.append("/");
	ground_mesh.append(GROUNDMESHFILELIST);
	ifstream fin2(ground_mesh);
	while(fin2 >> para)
	{
		groundtruth_mesh.push_back(para);
		cout << para << endl;
	}

	groundtruth_mesh_AUTOALIGNED.clear();
	string ground_mesh_AUTOALIGNED = input_mesh_path;
	ground_mesh_AUTOALIGNED.append("/");
	ground_mesh_AUTOALIGNED.append(GROUNDMESHFILELIST);
	ifstream fin2_AUTOALIGNED(ground_mesh_AUTOALIGNED);
	while (fin2_AUTOALIGNED >> para)
	{
		groundtruth_mesh_AUTOALIGNED.push_back(para);
		cout << para << endl;
	}
}

void MeshDeformOption::FindMatching(int ite)
{
	// sparse for learning
	for(int i = 0; i < mesh_list.size(); i++)
	{
		unsigned ePos;
		ePos = mesh_list[i].find_last_of(".");
		string temp_file_name = mesh_list[i].substr(0, ePos);
		string template_file = deform_path;
		template_file.append("/");
		template_file.append(temp_file_name);
		template_file.append(".txt");
		string sample_file = sample_path;
		sample_file.append("/");
		sample_file.append(temp_file_name);
		sample_file.append(".ply");
		string out_file = matching_path ;
		out_file.append("/");
		out_file.append(temp_file_name);
		out_file.append("/");
		out_file.append(temp_file_name);
		out_file.append(".txt");
		string out_file_check =  matching_path ;
		out_file_check.append("/");
		out_file_check.append(temp_file_name);
		out_file_check.append("/");
		out_file_check.append(temp_file_name);
		out_file_check.append("_check.txt");
	    string out_corre = out_sparse_path;
		out_corre.append("/");
		out_corre.append(temp_file_name);
		out_corre.append(".txt");
		Find_Match test;
		test.LoadTemplate(template_file);
		cout << "finish read temp" <<endl;
		test.ReadMeshSample(sample_file);
		cout << "finish read mesh" <<endl;
		test.FindMatchingBySample();
		test.OutPutResults(out_file_check);
		test.OutPutResults(out_corre);
		test.OutMatchBinary(out_file);
	} 

	// for correspondence 

	for (int i = 0; i < mesh_list.size(); i++)
	{
		unsigned ePos;
		ePos = mesh_list[i].find_last_of(".");
		string temp_file_name = mesh_list[i].substr(0, ePos);
		string template_file = rotation_deform_path;
		template_file.append("/");
		template_file.append(temp_file_name);
		template_file.append(".txt");
		string sample_file = eva_sample_path;
		sample_file.append("/");
		sample_file.append(temp_file_name);
		sample_file.append(".ply");
		string out_corre = out_eva_path;
		out_corre.append("/");
		out_corre.append(temp_file_name);
		out_corre.append(".txt");
		Find_Match test;
		test.LoadTemplate(template_file);
		cout << "finish read temp" << endl;
		test.ReadMeshSample(sample_file);
		cout << "finish read mesh" << endl;
		test.FindMatchingBySample();
		test.OutPutResults(out_corre);
	}



}

void MeshDeformOption::CorrespondenceAccracy(int ite)
{
	int true_ite = ite;
	while (true)
	{
		string accuracy_plot = working_path;
		accuracy_plot.append("/accuracy_plot");
		accuracy_plot.append(to_string(true_ite));
		accuracy_plot.append(".txt");
		ifstream file(accuracy_plot);
		if (file.is_open())
		{
			true_ite++;
		}
		else
		{
			break;
		}
	}
	//EvalCorrespondence test(groundtruth_mesh, ground_truth_path,out_sparse_path,input_mesh_path);
	cout << "---------" << out_eva_path << endl;
	EvalCorrespondence test(groundtruth_mesh, ground_truth_path, out_eva_path, input_mesh_path);
	
	string accuracy_plot = working_path;
	accuracy_plot.append("/accuracy_plot");
	accuracy_plot.append(to_string(true_ite));
	accuracy_plot.append(".txt");
	//test.GetPlot(accuracy_plot);
	test.GetPlot_Soft(accuracy_plot);
}


/* VVV change */
void MeshDeformOption::ReconstructionFromLearning(int ite)
{
	matching_path = working_path;
	matching_path.append("/");
	matching_path.append(MATCHINGFOLDER);
	matching_path.append("_");
	matching_path.append(to_string(ite));
	// learning code
	SNL::Options options;
	options.set("fitting_threshold",1000.0f); // instead of 100.0f since we are using the sparse fitting error

	string boltzmann_file = working_path;
	boltzmann_file.append("/");
	boltzmann_file.append(set_name);
	boltzmann_file.append(to_string(ite));
	boltzmann_file.append(".bin"); // append output folder + replace with child folder of argv[2] and also iteration id
	string input_matching_path = matching_path;	 // replace with the folder that contains 'sparse'	
	ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel( boltzmann_file, "", input_matching_path, options );
	//SNL::PCA::PCAModel* dm = new SNL::PCA::PCAModel(boltzmann_file, "", input_matching_path, options);
	vector< vector<Point> > output = dm->reconstructInput(input_matching_path, false, 1, true);

	// for each mesh in output
	//    for each point in output[mesh]
	//        copy point.p to your currently deformed template for that mesh, and recompute its normal
	for(int i = 0; i < mesh_list.size(); i++)
	{
		unsigned ePos;
		ePos = mesh_list[i].find_last_of(".");
		string temp_file_name = mesh_list[i].substr(0, ePos);
		temp_file_name.append(".txt");
		string temp_file = learn_results_path;
		cout << learn_results_path << endl;
		temp_file.append("/");
		temp_file.append(temp_file_name);
		ofstream fout(temp_file);
		for(int j = 0 ; j < output[i].size(); j++)
		{
			fout << output[i][j].p[0] << " " << output[i][j].p[1] <<" " << output[i][j].p[2] <<" " << output[i][j].id << " " << output[i][j].part_id << endl;
		}	
	}
	delete dm;
}

void MeshDeformOption::ObjecteDetection(int ite)
{
	//cout << "ObjecteDetection " << endl;
	matching_path = working_path;
	matching_path.append("/");
	matching_path.append(MATCHINGFOLDER);
	matching_path.append("_");
	matching_path.append(to_string(ite));
	// learning code
	SNL::Options options;
	options.set("fitting_threshold", 1000.0f); // instead of 100.0f since we are using the sparse fitting error
    string boltzmann_file = working_path;
	boltzmann_file.append("/");
	boltzmann_file.append(set_name);
	boltzmann_file.append(to_string(ite));
	boltzmann_file.append(".bin"); // append output folder + replace with child folder of argv[2] and also iteration id
	string input_matching_path = matching_path;	 // replace with the folder that contains 'sparse'
	ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel( boltzmann_file, "", input_matching_path, options );
	vector< vector< Point > > output = dm->reconstructInput(input_matching_path, false, 1, true);
	// for each mesh in output
	//    for each point in output[mesh]
	//        copy point.p to your currently deformed template for that mesh, and recompute its normal
	for(int i = 0; i < mesh_list.size(); i++)
	{
		/*mesh_name = input_mesh_path;
		seg_name = working_path;
		temp_file = working_path;
		ply_file = working_path;
		out_obj = working_path;
		out_seg = working_path;
		ePos = mesh_list[seg_list[i]].find_last_of(".");
		mesh_name.append(mesh_list[seg_list[i]].substr(0, ePos));
		mesh_name.append(".obj");
		temp_file.append("\\template1.txt");
		ply_file.append("/out_");
		ply_file.append(to_string(base_size));
		ply_file.append("/");
		ply_file.append(mesh_list[seg_list[i]].substr(0, ePos));
		txt_file = ply_file;
		ply_file_1 = ply_file;
		txt_file_1 = ply_file;
		txt_file.append(".txt");
		ply_file.append(".ply");
		txt_file_1.append("shape.txt");
		ply_file_1.append("shape.ply");
		cout << ply_file << " " << txt_file << endl;
		cout << ply_file_1 << " " << txt_file_1 << endl;
		seg_name.append("\\patch_sample\\");
		seg_name.append(mesh_list[seg_list[i]].substr(0, ePos));
		seg_name.append(".txt");
		test.GetSampleFromBaseShapes(template_mesh_file, template_gt_file);
		test.GetTargetSampleWithSeg(mesh_name, seg_name);
		test.SetColor();
		test.ScaleSample();
		test.BuiltShapeConnection();
		test.Deformation_With_Seg();
		test.OutPutAndVisual(ply_file, txt_file, 0);
		test.OutPutAndVisual(ply_file_1, txt_file_1, 1);
		seg.LoadData(txt_file, mesh_name);
		seg.SegFace();
		seg.SetSmoothWeight(10.0f);
		seg.GraphCut_new();
		out_obj.append("/");
		out_obj.append("seg_");
		out_obj.append(to_string(base_size));
		out_obj.append("/");
		out_obj.append(mesh_list[seg_list[i]].substr(0, ePos));
		out_obj.append(".obj");
		out_seg.append("/");
		out_seg.append("new_");
		out_seg.append(to_string(base_size));
		out_seg.append("/");
		out_seg.append(mesh_list[seg_list[i]].substr(0, ePos));
		out_seg.append(".seg");
		seg.OutPutSeg(out_obj);
		seg.OutPutSegFile(out_seg);*/
	}
}

void MeshDeformOption::Learning(int ite)
{
	// load err
	if (ite == 0)
	{
		cout << "begin load " << endl;
		vector<float> model_err;
		model_err.clear();
		for (size_t i = 0; i < mesh_list.size(); i++)
		{
			unsigned ePos;
			ePos = mesh_list[i].find_last_of(".");
			string file_name_model = working_path;
			file_name_model.append("/");
			file_name_model.append(MATCHINGFOLDER);
			file_name_model.append("_");
			file_name_model.append(to_string(ite));
			file_name_model.append("\\sparse\\");
			file_name_model.append(mesh_list[i].substr(0, ePos));
			file_name_model.append("\\");
			file_name_model.append(mesh_list[i].substr(0, ePos));
			file_name_model.append(".txt");
			//cout << file_name_model << endl;
			ifstream file(file_name_model, ios::in | ios::binary);
			int size_int = sizeof(int);
			int size_float = sizeof(float);
			int total_szie;
			int part_size;
			float err;
			if (file.is_open())
			{
				file.read((char*)(&total_szie), size_int);
				file.read((char*)(&part_size), size_int);
				file.read((char*)(&err), size_float);
				model_err.push_back(err);
				file.close();
			}
		}
		int precentage_thread = (int)(.95f * (float)mesh_list.size());
		std::nth_element(model_err.begin(), model_err.begin() + precentage_thread, model_err.end());
		fitting_threshold_first_iteration = model_err[precentage_thread];
		cout << " fitting_threshold " << fitting_threshold_first_iteration << endl;
	}
	matching_path = working_path;
	matching_path.append("/");
	matching_path.append(MATCHINGFOLDER);
	matching_path.append("_");
	matching_path.append(to_string(ite));
	// learning code 
	SNL::Options options;   
	options.set("fitting_threshold", fitting_threshold_first_iteration); // make it adaptive
	options.set("learning_epochs", 2000 + 1000*ite ); 
	options.set("decreasing_factor_for_number_of_hidden_nodes", 10.0f);
	options.set("regularization_type", (int)LS1L1);
	options.set("regularization_weight", .001); 
	options.set("num_hidden_layers", 3);  
	options.set("keep_variance_percentage", .95); // for PCA
	//options.set("use_dropout", true);
	//options.set("batch_size_proportion_of_dataset", 0.1f);

	string boltzmann_file = working_path; 
	boltzmann_file.append("/");
	boltzmann_file.append(set_name);
	boltzmann_file.append(to_string(ite));
	boltzmann_file.append(".bin"); // append output folder + replace with child folder of argv[2] and also iteration id
	string input_matching_path = matching_path;	 // replace with the folder that contains 'sparse'
	ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel( "", "", input_matching_path, options );
	///////ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel(boltzmann_file, "", input_matching_path, options );
	//SNL::PCA::PCAModel* dm = new SNL::PCA::PCAModel("", "", input_matching_path, options);
	
	dm->train(boltzmann_file);
	if (dm != NULL)
	{
		delete dm;
		dm = NULL;
	}
}

/* VVV end of change */


void MeshDeformOption::FixAlignment(int ite)
{
	matching_path = working_path;
	matching_path.append("/");
	matching_path.append(MATCHINGFOLDER);
	matching_path.append("_");
	matching_path.append(to_string(ite));
	// learning code
	SNL::Options options;
	options.set("fitting_threshold", 1000.0f); // instead of 100.0f since we are using the sparse fitting error
	string boltzmann_file = working_path;
	boltzmann_file.append("/");
	boltzmann_file.append(set_name);
	boltzmann_file.append(to_string(ite));
	boltzmann_file.append(".bin"); // append output folder + replace with child folder of argv[2] and also iteration id
	string input_matching_path = matching_path;	 // replace with the folder that contains 'sparse'
	ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel(boltzmann_file, "", input_matching_path, options);
	vector<float> prob = dm->getLogProbabilityForAlignment(input_matching_path);

	float max_prob = -FLT_MAX;
	int  best_rotation = -1;
	for (size_t i = 0; i < prob.size(); i++)
	{
		cout << prob[i] << endl;
		if (max_prob < prob[i])
		{
			max_prob = prob[i];
			best_rotation = i;
		}
	}
	cout << "best rotaion " << best_rotation << " " << mesh_list[best_rotation] << endl;
}

void MeshDeformOption::Deform(int ite)
{
	vector<string> base_shapes;
	base_shapes.clear();
	vector<string> base_feature;
	base_feature.clear();
	vector<string> template_list;
	template_list.clear();
	vector<string> target_list;
	target_list.clear();
	vector<string> target_feature;
	target_feature.clear();
	vector<string> out_sample;
	out_sample.clear();
	vector<string> out_ply;
	out_ply.clear();
	vector<string> eva_list;
	eva_list.clear();

	vector<string> matrix_list;
	matrix_list.clear();

	vector<string> reset_list;
	reset_list.clear();
	for(int i = 0; i < mesh_list.size(); i++)
	{
		unsigned ePos;
		ePos = mesh_list[i].find_last_of(".");
		string temp_file_name = mesh_list[i].substr(0, ePos);
		string template_file = temp_path;
		template_file.append("/");
		template_file.append(temp_file_name);
		template_file.append(".txt");
		template_list.push_back(template_file);

		string base_file = working_path;
		base_file.append("/");
		base_file.append(BASESHAPE);
		base_file.append("/");
		base_file.append(temp_file_name);
		base_file.append(".txt");
		base_shapes.push_back(base_file);
		
		string base_feafile= working_path;
		base_feafile.append("/");
		base_feafile.append(BASEFEATURE);
		base_feafile.append("/");
		base_feafile.append(temp_file_name);
		base_feafile.append(".txt");
		base_feature.push_back(base_feafile);


		string target_file = input_mesh_path;
		target_file.append("/");
		target_file.append(temp_file_name);
		target_file.append(".ply");
		target_list.push_back(target_file);

		string target_feafile = target_feature_path;
		target_feafile.append("/");
		target_feafile.append(temp_file_name);
		target_feafile.append(".txt");
		target_feature.push_back(target_feafile);


		//string target_file = input_mesh_path;
		//target_file.append("/");
		//target_file.append(temp_file_name);
		//target_file.append(".ply");
		//target_list.push_back(target_file);

     /*   string target_file = target_sample_path;
=======
      /*  string target_file = target_sample_path;
>>>>>>> .r180
		target_file.append("/");
		target_file.append(temp_file_name);
		target_file.append(".txt");
		target_list.push_back(target_file);*/
		string out_sample_file = deform_path;
		out_sample_file.append("/");
		out_sample_file.append(temp_file_name);
		out_sample_file.append(".txt");
		out_sample.push_back(out_sample_file);
		string out_ply_file = deform_path;
		out_ply_file.append("/");
		out_ply_file.append(temp_file_name);
		out_ply_file.append(".ply");
		out_ply.push_back(out_ply_file);

		string eva_file = rotation_deform_path;
		eva_file.append("/");
		eva_file.append(temp_file_name);
		eva_file.append(".txt");
		eva_list.push_back(eva_file);

		string matrix_file = matrix_path;
		matrix_file.append("/");
		matrix_file.append(temp_file_name);
		matrix_file.append(".txt");
		matrix_list.push_back(matrix_file);

		if(ite > 0)
		{
			string reset_learn = working_path;
			reset_learn.append("/");
			reset_learn.append(LEARNINGFOLDER);
			reset_learn.append("_");
			reset_learn.append(to_string(ite - 1));
			reset_learn.append("/");
			reset_learn.append(temp_file_name);
			reset_learn.append(".txt");
			reset_list.push_back(reset_learn);
		}
	}

	DeformFromShape test;  // VVV change
#pragma omp parallel for private(test) // VVV change
	for(int i = 0; i < mesh_list.size(); i++)
	{
		
		test.SetValidGroup(template_list[i]);
		//test.GetSampleFromMatching(template_mesh_file);
		test.GetSampleFeatureFromMatching(base_feature[i], base_shapes[i]);
		//cout << base_feature[i] << endl;
		//test.GetSampleFromMatching(base_shapes[i]);
		//test.GetTargetSample(target_list[i]);
		test.LoadTargetSampleWithegFeature(target_list[i], target_feature[i]);
		//test.LoadTargetSampleWithPreSeg(target_list[i]);
		if(ite > 0)
		{
			test.ReSetFromLearing(reset_list[i]);
		}
		test.SetColor();
		//test.AlignmentToCenter();
		test.ScaleSample();
		test.BuiltShapeConnection();
		test.Deformation_With_Seg();
		//test.Rescale();
		test.OutPutAndVisual(out_ply[i],out_sample[i]);
		test.RotateDeformation(matrix_list[i], eva_list[i]);
	}
	cout << "end " << endl;
}

void MeshDeformOption::DefromeWithFixSeg(int ite)
{
	
}

void MeshDeformOption::Run()
{
	cout << "current_deform_mode " << current_deform_mode << endl;
	if (current_deform_mode == 0)
	{

		for (int ite = 0; ite < ite_time; ite++)
		{
			CreateWorkingFloder(ite);
			Deform(ite);
			//FindMatching(ite);
			//CorrespondenceAccracy(ite);
			Learning(ite);
			/*if (ite == 0 && mesh_list_AUTOALIGNED.size() > 0)
			{
				mesh_list = mesh_list_AUTOALIGNED;
			}
			if (ite == 0 && groundtruth_mesh_AUTOALIGNED.size() > 0)
			{
				groundtruth_mesh = groundtruth_mesh_AUTOALIGNED;
			}
			if (ite != ite_time - 1)
			{
				ReconstructionFromLearning(ite);
			}*/
		}
	}

	if(current_deform_mode == 2)
	{
		for(int ite = 0; ite < ite_time; ite++ )
		{
			CreateWorkingFloder(ite);
			ObjecteDetection(ite);
		}

	}

	if (current_deform_mode == 3)
	{
		for (int ite = 0; ite < ite_time; ite++)
		{
			CreateWorkingFloder(ite);
			Deform(ite);
			FindMatching(ite);
			FixAlignment(ite);
		}
	}
}