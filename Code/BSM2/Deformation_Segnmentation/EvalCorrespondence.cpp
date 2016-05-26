#include "EvalCorrespondence.h"
#include "TriMesh.h"


EvalCorrespondence::EvalCorrespondence(void)
{

}


EvalCorrespondence::~EvalCorrespondence(void)
{

}


EvalCorrespondence::EvalCorrespondence(vector<string> list, string gtpath, string matchingpath, string meshpath)
{
	model_list = list;
	gt_path = gtpath;
	matching_point_path = matchingpath;
	mesh_path = meshpath;
}

void EvalCorrespondence::GetRadious()
{
	for (size_t i = 0; i < mesh_radius.size(); i++)
	{
		cout << "before " << mesh_radius[i] << endl;
		float radious_max = FLT_MIN;
		for (size_t j = 0; j < model_point[i].size(); j++)
		{
			for (size_t jj = 0; jj < model_point[i].size(); jj++)
			{
				if (dist(model_point[i][j], model_point[i][jj]) > radious_max)
				{
					radious_max = dist(model_point[i][j], model_point[i][jj]);
				}
			}
		}
		cout << "after " << radious_max << endl;
		mesh_radius[i] = radious_max;
	}
}

void EvalCorrespondence::ReadPointOther()
{
	model_point.resize(model_list.size());
	mesh_radius.resize(model_list.size());
//#pragma omp parallel for 
	for (int i = 0; i < model_list.size(); i++)
	{
		unsigned ePos = model_list[i].find_last_of(".");
		string newFile = model_list[i].substr(0, ePos);
		string match_file = matching_point_path;
		match_file.append("/");
		match_file.append(newFile);
		match_file.append(".ply");
		TriMesh *mesh;
		cout << match_file << endl;
		mesh = TriMesh::read(match_file);
		vector<vec3> point;
		point.clear();
		for (int j = 0; j < mesh->vertices.size(); j++)
		{
			point.push_back(mesh->vertices[j]);
		}
		model_point[i] = point;
	}

}

void EvalCorrespondence::ReadPoint()
{
	cout << model_list.size() << endl;
	model_point.resize(model_list.size());
	point_index.resize(model_list.size());
	mesh_radius.resize(model_list.size());
	point_part_id.resize(model_list.size());
//#pragma omp parallel for 
	for(int i = 0; i < model_list.size(); i++ )
	{
		unsigned ePos = model_list[i].find_last_of(".");
		string newFile = model_list[i].substr(0, ePos); 
		string match_file = matching_point_path;
		cout << matching_point_path << endl;
		match_file.append("/");
		match_file.append(newFile);
		match_file.append(".txt");
		cout << match_file << endl;
		ifstream f_model(match_file);
		cout << model_list[i] << endl;
		vector<vec3> point;
		point.clear();
		vector<int> index;
		index.clear();
		vector<int> part_id_list;
		part_id_list.clear();
		int total_point;
		int total_size;
		f_model >> total_point;
		f_model >> total_size;
		float err;
		f_model >> err;
		float x, y, z, nx,ny,nz;
		int part_id, point_id, temp_id;
		float dis, angel;
		while(f_model >> x >> y >> z >> nx >> ny >> nz >> temp_id >> part_id >> point_id >> dis >> angel)
		{
			vec3 p(x,y,z);
			point.push_back(p);
			index.push_back(point_id);
			part_id_list.push_back(part_id);
		}	
		//cout << point.size() << endl;
		model_point[i] = point;
		point_index[i] = index;
		point_part_id[i] = part_id_list;
		cout << model_point[i].size() << endl;
	}
}



void EvalCorrespondence::ReadGroundTruth()
{
	ground_truth.clear();
	is_valid.clear();
	for(size_t i = 0; i < model_list.size(); i++ )
	{
		unsigned ePos = model_list[i].find_last_of(".");
		string newFile = model_list[i].substr(0, ePos); 
		newFile.append(".obj");
		string file_name_model = mesh_path;
		file_name_model.append("/");
		file_name_model.append(newFile);
		TriMesh *mesh;
	    mesh = TriMesh::read(file_name_model);
		mesh->need_bbox();
		mesh_radius[i] = dist(mesh->bbox.max, mesh->bbox.min);
		string file_name = gt_path; 
		file_name.append("/");
		file_name.append(model_list[i].substr(0, ePos));
		file_name.append(".txt");
		ifstream f_model(file_name);
		//cout << file_name << endl;
		vector<vec3> point;
		point.clear();
		vector<int> index;
		index.clear();
		int check;
		while(f_model >> check)
		{
			//cout << check << endl;
			if(check >= 0)
			{
				float x, y,z ;
				//f_model >> x >> y >> z;
				vec3 p = mesh->vertices[check];
				point.push_back(p);
				index.push_back(1);
			}
			else
			{
				vec3 p(100,100,100);
				point.push_back(p);
				index.push_back(0);
			}
		}
		delete mesh;
		mesh = NULL;
		//cout << point.size() << endl;
		ground_truth.push_back(point);
		is_valid.push_back(index);
	}
}

void EvalCorrespondence::ReadGroundTruthByPosition()
{
	ground_truth.clear();
	is_valid.clear();
	for(size_t i = 0; i < model_list.size(); i++ )
	{
		unsigned ePos = model_list[i].find_last_of(".");
		string newFile = model_list[i].substr(0, ePos); 
		newFile.append(".obj");
		string file_name_model = mesh_path;
		file_name_model.append("/");
		file_name_model.append(newFile);
		TriMesh *mesh;
	    mesh = TriMesh::read(file_name_model);
		mesh->need_bbox();
		mesh_radius[i] = dist(mesh->bbox.max, mesh->bbox.min);
		string file_name = gt_path; 
		file_name.append("/");
		file_name.append(model_list[i].substr(0, ePos));
		file_name.append(".txt");
		ifstream f_model(file_name);
		cout << file_name << endl;
		//cout << f_model.is_open() << endl;
		vector<vec3> point;
		point.clear();
		vector<int> index;
		index.clear();
		int check;
		int count = 0;
		while (f_model >> check && count < 7)
		{
			cout << check << endl;
			if(check > -1)
			{
				float x, y,z ;
				f_model >> x >> y >> z;
				if (abs(x) > 100 || abs(y) > 100 || abs(z) > 100)
				{
					cout << "err " << endl;
					cout << model_list[i] << endl;
				}
				vec3 p(x,y,z);
				point.push_back(p);
				if (check == 8)
				{
					check = 9;
				}
				else if (check == 9)
				{
					check = 8;
				}
				if (count == 5)
				{
					check = 4;
				}
				index.push_back(check);
			}
			else
			{
				vec3 p(100,100,100);
				point.push_back(p);
				index.push_back(check);
			}
			count++;
		}
		delete mesh;
		mesh = NULL;
		ground_truth.push_back(point);
		is_valid.push_back(index);
	}
	for (size_t i = 0; i < model_list.size(); i++)
	{

		cout << is_valid.size() << endl;
		cout << ground_truth.size() << endl;
	}

	for (size_t i = 0; i < ground_truth.size(); i++)
	{
		//cout << ground_truth[i].size() << endl;
		if (ground_truth[i].size() != 22)
		{
			cout << model_list[i] << endl;
		}
	}

	GetRadious();
}

void EvalCorrespondence::GetPlot_Other(string file_name)
{
	cout << "reading matching point" << endl;
	ReadPointOther();
	cout << "reading ground truth point" << endl;
	//ReadGroundTruth();
	ReadGroundTruthByPosition();
	vector<int> accume;
	accume.resize(200, 0);
	int total_count = 0;
	cout << "begin eva" << endl;
	for (int i = 0; i < model_list.size(); i++)
	{
		for (int pi = 0; pi < ground_truth[i].size(); pi++)
		{
			if (is_valid[i][pi] > -1)
			{
				for (int j = 0; j < model_list.size(); j++)
				{
					if (i == j)
					{
						continue;
					}
					if (is_valid[j][pi] > -1)
					{
						total_count++;
						int is_found = 0;
						float min_dis = 100;
						float min_id = -1;
						for (size_t pd = 0; pd < model_point[j].size(); pd++)
						{

							if (dist(ground_truth[i][pi], model_point[j][pd]) < min_dis )
							{
								min_dis = dist(ground_truth[i][pi], model_point[j][pd]);
								min_id = pd;
							}
						}

						float dis_match = dist(ground_truth[j][pi], model_point[j][min_id]) / mesh_radius[j];
						int a = (int)(dis_match / (0.25 / 200));
						if (a > 199)
						{
							a = 199;
						}
						accume[a]++;
					}
				}
			}
		}
	}

	cout << total_count << endl;
	ofstream fout(file_name);
	for (size_t i = 0; i < accume.size(); i++)
	{
		fout << accume[i] << endl;
	}
}

void EvalCorrespondence::GetPlot_Soft(string file_name)
{
	cout << "reading matching point" << endl;
	ReadPoint();
	cout << "reading ground truth point" << endl;
	//ReadGroundTruth();
	ReadGroundTruthByPosition();
	cout << "begin eva " << endl;
	vector<int> accume;
	accume.resize(200, 0);
	int total_count = 0;
	vector<vector<int>> accuracy_pre_model;
	vector<vector<int>> accuracy_pre_point;
	for (int i = 0; i < model_list.size(); i++)
	{

		vector<int> accuracy;
		accuracy.resize(200, 0);
		accuracy_pre_model.push_back(accuracy);
	}
	for (int pi = 0; pi < ground_truth[0].size(); pi++)
	{
		vector<int> accuracy;
		accuracy.resize(200, 0);
		accuracy_pre_point.push_back(accuracy);
	}
	for (int i = 0; i < model_list.size(); i++)
	{
	
		// build ann tree for search 
		int k = 5; // number of nearest neighbors 
		int dim = 4;
		double eps = 0; // error bound
		int maxPts = model_point[i].size();
		int nPts = model_point[i].size(); // actual number of data points
		ANNpointArray dataPts; // data points
		ANNpoint queryPt; // query point
		ANNidxArray nnIdx; // near neighbor indices
		ANNdistArray dists; // near neighbor distances
		ANNkd_tree* kdTree; // search structure
		queryPt = annAllocPt(dim); // allocate query point
		dataPts = annAllocPts(maxPts, dim); // allocate data points
		nnIdx = new ANNidx[k]; // allocate near neigh indices
		dists = new ANNdist[k]; // allocate near neighbor dists

		for (size_t ii = 0; ii < model_point[i].size(); ii++)
		{
			dataPts[ii][0] = model_point[i][ii][0];
			dataPts[ii][1] = model_point[i][ii][1];
			dataPts[ii][2] = model_point[i][ii][2];
			dataPts[ii][3] = point_part_id[i][ii] * 50;
		}
		kdTree = new ANNkd_tree( // build search structure
			dataPts, // the data points
			nPts, // number of points
			dim); // dimension of space
		cout << "end kd tree" << " "<<i << endl;
		for (int pi = 0; pi < ground_truth[i].size(); pi++)
		{

			if (is_valid[i][pi] != -1)
			{
				queryPt[0] = ground_truth[i][pi][0];
				queryPt[1] = ground_truth[i][pi][1];
				queryPt[2] = ground_truth[i][pi][2];
				queryPt[3] = is_valid[i][pi] * 50;
				kdTree->annkSearch( // search
					queryPt, // query point
					k, // number of near neighbors
					nnIdx, // nearest neighbors (returned)
					dists, // distance (returned)
					eps); // error bound
				// get weight 
				//cout << "end search" << endl;
				vector<int> index_list;
				index_list.clear();
				vector<float> dis_list;
				dis_list.clear();
				for (size_t ii = 0; ii < k; ii++)
				{
					index_list.push_back(point_index[i][nnIdx[ii]]);
					dis_list.push_back(dist(ground_truth[i][pi], model_point[i][nnIdx[ii]]));
				}
				//cout << "end search 1" << endl;
				float mean;
				float var;
				GetMean(dis_list, mean, var);
				//cout << mean << var << endl;
				// cal weight
				float total_weight = 0;
				vector<float> weight;
				weight.clear();
				for (size_t ii = 0; ii < k; ii++)
				{
					float p_weight = exp(-0.5*(dis_list[ii] - mean)*(dis_list[ii] - mean) /(var+0.001));
					weight.push_back(p_weight);
					//cout << p_weight << endl;
					total_weight += p_weight;
				}
				cout << total_weight << endl;
				for (size_t ii = 0; ii < k; ii++)
				{
					weight[ii] /= total_weight;
				}
				//cout << "ok 2" << endl;
				for (int j = 0; j < model_list.size(); j++)
				{
					/*cout << "ok 4" << model_list[j] << endl;*/
					if (i == j)
					{
						continue;
					}
					if (is_valid[j][pi] != -1)
					{
						total_count++;
						vec3 exp_point(0, 0, 0);
						for (size_t ii = 0; ii < index_list.size(); ii++)
						{
							for (size_t pd = 0; pd < model_point[j].size(); pd++)
							{
								if (point_index[j][pd] == index_list[ii])
								{
									exp_point += model_point[j][pd] * weight[ii];
									break;
								}
							}
						}

						float dis_match = dist(ground_truth[j][pi], exp_point) / mesh_radius[j];
						int a = (int)(dis_match / (0.25 / 200));
						if (a > 199)
						{
							a = 199;
						}
						accume[a]++;
						accuracy_pre_model[i][a] ++;
						accuracy_pre_point[pi][a]++;
					}
				}
			}
		}
	}


	cout << total_count << endl;
	ofstream fout(file_name);
	for (size_t i = 0; i < accume.size(); i++)
	{
		fout << accume[i] << endl;
	}

	for (size_t i = 0; i < accuracy_pre_model.size(); i++)
	{
		unsigned ePos = model_list[i].find_last_of(".");
		string newFile = model_list[i].substr(0, ePos);
		newFile.append("_accuracy_1.txt");
		ofstream fmodel(newFile);
		for (size_t j = 0; j < accuracy_pre_model[i].size(); j++)
		{
			fmodel << accuracy_pre_model[i][j] << endl;
		}
	}

	for (size_t i = 0; i < accuracy_pre_point.size(); i++)
	{
		string newFile("accuracy_point_");
		newFile.append(to_string(i));
		newFile.append("_1.txt");
		ofstream fpoint(newFile);
		for (size_t j = 0; j < accuracy_pre_point[i].size(); j++)
		{
			fpoint << accuracy_pre_point[i][j] << endl;
		}
	}

}

void EvalCorrespondence::GetPlot(string file_name)
{
	cout << "reading matching point" << endl;
	ReadPoint();
	cout << "reading ground truth point" << endl;
	//ReadGroundTruth();
	ReadGroundTruthByPosition();
	cout << "begin eva " << endl;
	vector<int> accume;
	accume.resize(200,0);
	int total_count = 0;
	vector<vector<int>> accuracy_pre_model;
	vector<vector<int>> accuracy_pre_point;
	for (int i = 0; i < model_list.size(); i++)
	{

		vector<int> accuracy;
		accuracy.resize(200, 0);
		accuracy_pre_model.push_back(accuracy);
	}
	for (int pi = 0; pi < ground_truth[0].size(); pi++)
	{
		vector<int> accuracy;
		accuracy.resize(200, 0);
		accuracy_pre_point.push_back(accuracy);
	}
	for(int i = 0; i < model_list.size(); i++)
	{
	
		for(int pi = 0 ; pi < ground_truth[i].size(); pi++)
		{
			
			if(is_valid[i][pi] != -1)
			{
				int in_group = is_valid[i][pi];
				//in_group = -1;
				int min_id = -1;
				float min_dis = 100;
				for(size_t pd =0; pd < model_point[i].size(); pd++)
				{
					if(dist( ground_truth[i][pi], model_point[i][pd]) < min_dis && in_group == point_part_id[i][pd])
					{
						min_id = point_index[i][pd];
						min_dis = dist( ground_truth[i][pi], model_point[i][pd]);
					}
				}
				//cout << "ok 1" << endl;
				if(min_id == -1)
				{
					min_dis = 100;
					for(size_t pd =0; pd < model_point[i].size(); pd++)
					{
						if(dist( ground_truth[i][pi], model_point[i][pd]) < min_dis)
						{
							min_id = point_index[i][pd];
							min_dis = dist( ground_truth[i][pi], model_point[i][pd]);
						}
					}
				}
				//cout << "ok 2" << endl;
				for(int j = 0; j < model_list.size(); j++)
				{
					/*cout << "ok 4" << model_list[j] << endl;*/
					if(i == j)
					{
						continue;
					}
					if(is_valid[j][pi] != -1)
					{
						total_count++;
						int is_found = 0;
						for(size_t pd =0; pd < model_point[j].size(); pd++)
						{
							
							if(point_index[j][pd] == min_id)
							{
								//cout << mesh_radius[j] << endl;
								is_found = 1;
								float dis_match = dist( ground_truth[j][pi], model_point[j][pd])/mesh_radius[j];
								int a = (int) (dis_match/(0.25/200));
					
								if(a > 199)
								{
									a = 199;
								}
								accume[a]++;
								accuracy_pre_model[i][a] ++;
								accuracy_pre_point[pi][a]++;
								break;
							}
						}
						if(is_found == 0)
						{
							accume[199]++;
							accuracy_pre_model[i][199] ++;
							accuracy_pre_point[pi][199]++;
							//cout << "missing matching .." << model_list[i] << " " << model_list[j] << endl;
							//cout << "missing pair .." << is_valid[j][pi] << " " << point_part_id[i][min_id] << endl;
						}
						//cout << "ok 3" << model_list[j] << endl;
					}
				}
			}
		}
	}


	cout << total_count << endl;
	ofstream fout(file_name);
	for(size_t i =0 ; i < accume.size(); i++)
	{
		fout << accume[i] << endl;
	}

	/*for (size_t i = 0; i < accuracy_pre_model.size(); i++)
	{
		unsigned ePos = model_list[i].find_last_of(".");
		string newFile = model_list[i].substr(0, ePos);
		newFile.append("_accuracy.txt");
		ofstream fmodel(newFile);
		for (size_t j = 0; j < accuracy_pre_model[i].size(); j++)
		{
			fmodel << accuracy_pre_model[i][j] << endl;
		}
	}

	for (size_t i = 0; i < accuracy_pre_point.size(); i++)
	{
		string newFile("accuracy_point_");
		newFile.append(to_string(i));
		newFile.append("_1.txt");
		ofstream fpoint(newFile);
		for (size_t j = 0; j < accuracy_pre_point[i].size(); j++)
		{
			fpoint << accuracy_pre_point[i][j] << endl;
		}
	}*/
}

void EvalCorrespondence::GetMean(vector<float> dis_list, float &mean, float &var)
{
	mean = 0;
	var = 0;
	for (size_t i = 0; i < dis_list.size(); i++)
	{
		mean += dis_list[i];
	}
	mean /= dis_list.size();
	for (size_t i = 0; i < dis_list.size(); i++)
	{
		var += (dis_list[i] - mean)*(dis_list[i] - mean);
	}
	var /= dis_list.size();
}