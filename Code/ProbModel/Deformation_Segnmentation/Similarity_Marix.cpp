#include "Similarity_Marix.h"


Similarity_Marix::Similarity_Marix(void)
{
}


Similarity_Marix::~Similarity_Marix(void)
{
}

void Similarity_Marix::GetMeanShapes(string file_path)
{
	working_path = file_path;
	string mesh_file = working_path;
	mesh_file.append("\\meanlist.txt");
	string para;
	ifstream fin(mesh_file);
	meanlist.clear();
	while(fin >> para)
	{
		meanlist.push_back(para);
	}
	// get samples for each model
	mean_shape_list.clear();
	mean_shape_list.resize(meanlist.size());
#pragma omp parallel for
	for(int i = 0; i < meanlist.size(); i++)
	{
		unsigned ePos;
		ePos = meanlist[i].find_last_of(".");
		string mesh_name = working_path;
		mesh_name.append("\\rotate_model\\");
		mesh_name.append(meanlist[i].substr(0,ePos));
		string ply_name = mesh_name;
		mesh_name.append(".obj");
		ply_name.append(".ply");
		Shape t_shape;
		t_shape.GetShape(mesh_name);
		t_shape.GetSamplePoint(3000);
		mean_shape_list[i] = (t_shape.shape_sample);
	}
}

void Similarity_Marix:: laodSamplePoint(string file_path)
{
	working_path = file_path;
	string mesh_file = working_path;
	mesh_file.append("\\meshlist.txt");
	string para;
	ifstream fin(mesh_file);
	meshlist.clear();
	while(fin >> para)
	{
		meshlist.push_back(para);
	}
	mesh_sample.clear();
	mesh_sample.resize(meshlist.size());
#pragma omp parallel for
	for(int i = 0; i < meshlist.size(); i++)
	{
		mesh_sample[i].clear();
		unsigned ePos;
		ePos = meshlist[i].find_last_of(".");
		string sample_name = working_path;
		string feature_name = working_path;
		sample_name.append("\\downsample\\");
		sample_name.append(meshlist[i].substr(0,ePos));
		sample_name.append(".txt");
		feature_name.append("\\downfeature\\");
		feature_name.append(meshlist[i].substr(0,ePos));
		feature_name.append(".txt");
		ifstream fpos(sample_name);
		float x,y,z,nx,ny,nz;
		while(fpos >> x >> y >> z >> nx >> ny >> nz)
		{
			vec3 pos(x,y,z);
			vec3 nor(nx,ny,nz);
			Sample p(pos,nor);
			mesh_sample[i].push_back(p);
		}
		cout << "load  sample " <<mesh_sample[i].size() << endl ;
		vector<float> feature_list;
		feature_list.clear();
		float fea;
		ifstream fin(feature_name);
		while(fin >> fea)
		{
			feature_list.push_back(fea);
		}
		int feature_pre_sample = feature_list.size()/mesh_sample[i].size();
		cout << "feature_pre_sample " <<feature_pre_sample<< endl ;
		for(size_t j = 0; j < mesh_sample[i].size();j++)
		{
			for(size_t jj = 0; jj < feature_pre_sample; jj++)
			{
				mesh_sample[i][j].sample_features.push_back(feature_list[j*feature_pre_sample + jj]);
			}
		}
	}
}

void Similarity_Marix::LoadMesh(string file_path)
{
	working_path = file_path;
	string mesh_file = working_path;
	mesh_file.append("\\meshlist.txt");
	string para;
	ifstream fin(mesh_file);
	meshlist.clear();
	while(fin >> para)
	{
		meshlist.push_back(para);
	}
	// get samples for each model
	mesh_sample.clear();
	mesh_sample.resize(meshlist.size());
#pragma omp parallel for
	for(int i = 0; i < meshlist.size(); i++)
	{
		unsigned ePos;
		ePos = meshlist[i].find_last_of(".");
		string mesh_name = working_path;
		mesh_name.append("\\rotate_model\\");
		mesh_name.append(meshlist[i].substr(0,ePos));
		string ply_name = mesh_name;
		mesh_name.append(".obj");
		ply_name.append(".ply");
		Shape t_shape;
		t_shape.GetShape(mesh_name);
		//t_shape.GetSamplePoint(i*10000+5000);
		t_shape.GetSamplePoint(1500);
		//t_shape.WriteShapeWithName(ply_name);
		//cout << t_shape.shape_sample.size() << endl;
		mesh_sample[i] = (t_shape.shape_sample);
	}
}

vector<float> Similarity_Marix::GetDistance(int index)
{
	vector<float> dis;
	dis.resize(meshlist.size(),100.0f);
#pragma omp parallel for
	for(int i = 0; i < meshlist.size(); i++)
	{
		if(i ==  index)
		{
			dis[i] = 0.0f;
		}
		else
		{
			//cout << index << " "<< i <<" ";
			//dis[i] = exp(SimilarityDistance(mesh_sample[index], mesh_sample[i]));
			//dis[i] = SimilarityDistance(mesh_sample[index], mesh_sample[i]) + SimilarityDistance (mesh_sample[i],mesh_sample[index]);
			dis[i] = SimilarityDistance(mesh_sample[index], mesh_sample[i]);
			//cout << "dis " << dis[i]  << endl;
		}
	}
	return dis;
}

float Similarity_Marix::SimilarityDistance(vector<Sample> s_point, vector<Sample> t_point)
{
	/*vector<vector<int>> connection;
	Mean_Field_Deformation test(t_point,s_point,connection,5);
	test.Initial();
	test.FindNeighbor();
	test.SetInitialSigmaValue();
	return test.EvaluateErr();*/
	float max_dis = 0.0f;
	float fit_s_t = 0;
	vector<NamedPoint> points;
	for (size_t i = 0; i < t_point.size(); i++)
	{
		points.push_back( NamedPoint(t_point[i].position[0], t_point[i].position[1], t_point[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < s_point.size();i++)
	{
		NamedPoint query( s_point[i].position[0], s_point[i].position[1], s_point[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		int nearest_point_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
		fit_s_t += t_point[nearest_point_id].dist_with_feature(s_point[i]);
		if(t_point[nearest_point_id].dist_with_feature(s_point[i]) > max_dis)
		{
			max_dis = t_point[nearest_point_id].dist_with_feature(s_point[i]);
		}
	}
	//return max_dis;
	fit_s_t /= s_point.size();

	float fit_t_s = 0;
	/*vector<NamedPoint> points_s;
	for (size_t i = 0; i < s_point.size(); i++)
	{
	points_s.push_back( NamedPoint(s_point[i].position[0], s_point[i].position[1], s_point[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree_s(points_s.begin(), points_s.end());

	for(size_t i = 0;i < t_point.size();i++)
	{
	NamedPoint query( t_point[i].position[0], t_point[i].position[1], t_point[i].position[2] );
	BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
	stree_s.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
	int nearest_point_id = stree_s.getElements()[k_closest_elems[0].getIndex()].id;
	fit_t_s += s_point[nearest_point_id].dist_with_feature(t_point[i]);
	}
	fit_t_s /= t_point.size();*/
	//cout << fit_s_t + fit_t_s << endl;
	return fit_s_t + fit_t_s;
}

void Similarity_Marix::OutPutMatrixWithSize(int k_size)
{
	Distance_matrix.clear();
	for(size_t i = 0; i < meshlist.size(); i++)
	{
		cout << "finished " << i <<" \\" << meshlist.size() <<"\r" ;
		Distance_matrix.push_back(GetDistance(i));
	}
	string out_file = working_path;
	out_file.append("\\distance_matrix.txt");
	ofstream fout(out_file);
	for(size_t i = 0; i< Distance_matrix.size(); i++)
	{
		for(size_t j = 0; j < Distance_matrix[i].size(); j++)
		{
			fout << Distance_matrix[i][j] << " ";
		}
		fout << endl;
	}
	string  file_sbk = working_path;
	file_sbk.append("\\sb");
	file_sbk.append(to_string(k_size));
	file_sbk.append(".txt");
	KMeans<float> kmeansk(Distance_matrix, k_size);
	vector<size_t> sbk = kmeansk.CI;
	OutputSBFile(sbk,k_size,file_sbk);

}

void Similarity_Marix::OutPutMatrixWithMean()
{

	vector<int> group_index;
	group_index.resize(mesh_sample.size(),-1);
#pragma omp parallel for
	for(int i = 0; i < meshlist.size();i++)
	{
		float min_dis = FLT_MAX;
		int min_index = -1;
		for(size_t j = 0; j < mean_shape_list.size(); j++)
		{
			float dis = SimilarityDistance(mean_shape_list[j],mesh_sample[i]);
			if(dis < min_dis)
			{
				min_dis = dis;
				min_index = j;
			}
		}
		group_index[i] = min_index;
	}

	string  file_sbk = working_path;
	file_sbk.append("\\sb");
	file_sbk.append(to_string(mean_shape_list.size()));
	file_sbk.append(".txt");
	ofstream fout(file_sbk);
	for(size_t i = 0; i < mean_shape_list.size(); i++)
	{
		fout << "group "<< i << endl;
		for(size_t j = 0; j < meshlist.size();j++)
		{
			if(group_index[j] == i)
			{
				fout << meshlist[j] << endl;
			}
		}
		fout << "center_model " << meanlist[i] << endl;;
	}
}

void Similarity_Marix::OutPutMatrix()
{
	Distance_matrix.clear();
	for(size_t i = 0; i < meshlist.size(); i++)
	{
		Distance_matrix.push_back(GetDistance(i));
	}
	string out_file = working_path;
	out_file.append("\\distance_matrix.txt");
	ofstream fout(out_file);
	for(size_t i = 0; i< Distance_matrix.size(); i++)
	{
		for(size_t j = 0; j < Distance_matrix[i].size(); j++)
		{
			fout << Distance_matrix[i][j] << " ";
		}
		fout << endl;
	}
	// output SB1
	vector<size_t> sb1;
	sb1.resize(meshlist.size(), 0);
	string  file_sb1 = working_path;
	file_sb1.append("\\sb1.txt");
	OutputSBFile(sb1,1,file_sb1);
	//KMeans test(Distance_matrix,)
	KMeans<float> kmeans2(Distance_matrix, 2);
	vector<size_t> sb2 = kmeans2.CI;
	//ShapeKmeans test(Distance_matrix,2);
	//vector<int> sb2 = test.RunKmean();
	string  file_sb2 = working_path;
	file_sb2.append("\\sb2.txt");
	OutputSBFile(sb2,2,file_sb2);
	//ShapeKmeans test1(Distance_matrix,3);
	//vector<int> sb3 = test1.RunKmean();
	KMeans<float> kmeans3(Distance_matrix, 3);
	vector<size_t> sb3 = kmeans3.CI;
	string  file_sb3 = working_path;
	file_sb3.append("\\sb3.txt");
	OutputSBFile(sb3,3,file_sb3);

}

void Similarity_Marix::OutputSBFile(vector<size_t> k_mean, int k, string file_name)
{
	ofstream fout(file_name);
	for(int  i = 0; i < k; i++)
	{
		vector<size_t> modellist;
		modellist.clear();
		fout << "group "<< i << endl;
		for(size_t j = 0; j <  meshlist.size(); j++)
		{
			if(k_mean[j] == i)
			{
				fout << meshlist[j] << endl;
				modellist.push_back(j);
			}
		}
		fout << "center_model ";
		float min_dis = FLT_MAX;
		float index = -1;
		for(size_t j = 0; j <  Distance_matrix.size(); j++)
		{
			if(k_mean[j] == i)
			{
				float dis = 0;
				for(size_t jj =0 ; jj < Distance_matrix[j].size(); jj++)
				{
					//if(k_mean[jj] == i)
					{
						dis += Distance_matrix[j][jj];
					}
				}
				if(dis < min_dis)
				{
					min_dis = dis;
					index = j;
				}
			}
		}

		fout << meshlist[index] << endl;
		//RunDeformationSegnmenation(modellist, index, k);
	}
}

float Similarity_Marix::GetMeanDist(vector<Sample> target_sample)
{
	//return 0.2;
	float mean_feature_dis = 0;
	int count = 0;
	vector<NamedPoint> points;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		points.push_back(NamedPoint(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		NamedPoint query(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(5);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		for (size_t j = 0; j < 5; j++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[j].getIndex()].id;
			mean_feature_dis += target_sample[nearest_id].dist_with_feature(target_sample[i]);
			count++;
		}
	}
	mean_feature_dis /= count;
	//mean_feature_dis /= 2;
	cout <<"mean_feature_dis " << mean_feature_dis << " "<< count << endl;
	return mean_feature_dis;
}

void Similarity_Marix::RunDeformationSegnmenation(vector<size_t> seg_list, int center_mesh, int base_size)
{
	unsigned Pos;
	Pos = meshlist[center_mesh].find_last_of(".");
	string template_mesh_file =  working_path;
	//template_mesh_file.append("\\sample\\");
	//template_mesh_file.append(meshlist[center_mesh].substr(0,Pos));
	//template_mesh_file.append("_out.txt");
	template_mesh_file.append("\\rotate_model\\");
	template_mesh_file.append(meshlist[center_mesh].substr(0,Pos));
	template_mesh_file.append(".obj");
	string template_gt_file =  working_path;
	template_gt_file.append("\\gt\\");
	template_gt_file.append(meshlist[center_mesh].substr(0,Pos));
	template_gt_file.append(".seg");
	unsigned ePos;
	string seg_name;
	string mesh_name;
	string temp_file;
	string ply_file;
	string txt_file;
	string ply_file_1;
	string txt_file_1;
	DeformFromShape test;
	SegMeshFace seg;
	string out_obj ;
	string out_seg;
	//#pragma omp parallel for private(test,ePos,temp_file,ply_file,txt_file,seg,out_seg,out_obj,mesh_name)
	for(int i = 0; i < seg_list.size(); i++)
	{
		mesh_name = working_path;
		seg_name = working_path;
		temp_file = working_path;
		ply_file = working_path;
		out_obj =  working_path;
		out_seg = working_path;
		ePos = meshlist[seg_list[i]].find_last_of(".");	
		mesh_name.append("\\rotate_model\\");
		mesh_name.append(meshlist[seg_list[i]].substr(0,ePos));
		mesh_name.append(".obj");
		temp_file.append("\\template1.txt");	
		ply_file.append("/out_");
		ply_file.append(to_string(base_size));
		ply_file.append("/");
		ply_file.append(meshlist[seg_list[i]].substr(0,ePos));
		txt_file = ply_file;
		ply_file_1 = ply_file;
		txt_file_1 = ply_file;
		txt_file.append(".txt");
		ply_file.append(".ply");
		txt_file_1.append("shape.txt");
		ply_file_1.append("shape.ply");
		cout << ply_file << " "<< txt_file << endl;
		cout << ply_file_1 << " "<< txt_file_1 << endl;
		seg_name.append("\\patch_sample\\");
		seg_name.append(meshlist[seg_list[i]].substr(0,ePos));
		//seg_name.append(".txt");
		seg_name.append(".ply");
		//test.SetValidGroup(temp_file);
		//test.GetSampleFromMatching(template_mesh_file);
		//test.GetSampleFromMatching(template_mesh_file);
		test.GetSampleFromBaseShapes(template_mesh_file,template_gt_file);
		//test.GetTargetSample(mesh_name);
		test.LoadTargetSampleWithPreSeg(seg_name,mesh_name);
		//test.GetTargetSampleWithSeg(mesh_name,seg_name);
		test.SetColor();
		//test.RigidAlignment();
		test.ScaleSample();
		test.BuiltShapeConnection();
		test.Deformation_With_Seg();
		test.OutPutAndVisual(ply_file,txt_file,0);
		//test.OutPutAndVisual(ply_file_1,txt_file_1,1);
		seg.LoadData(txt_file,mesh_name);
		seg.SegFace();
		seg.SetSmoothWeight(10.0f);
		seg.GraphCut_new();

		out_obj.append("/");
		out_obj.append("seg_");
		out_obj.append(to_string(base_size));
		out_obj.append("/");
		out_obj.append(meshlist[seg_list[i]].substr(0,ePos));
		out_obj.append(".obj");

		out_seg.append("/");
		out_seg.append("new_");
		out_seg.append(to_string(base_size));
		out_seg.append("/");
		out_seg.append(meshlist[seg_list[i]].substr(0,ePos));
		out_seg.append(".seg");
		seg.OutPutSeg(out_obj);
		seg.OutPutSegFile(out_seg);
	}

}

void Similarity_Marix::RunInPairs(string template_mesh_file, string template_gt_file, string seg_name, string mesh_name, string ply_file, string txt_file, string out_obj, string out_seg)
{
	DeformFromShape test;
	SegMeshFace seg;
	test.GetSampleFromBaseShapes(template_mesh_file,template_gt_file);
	test.LoadTargetSampleWithPreSeg(seg_name,mesh_name);
	test.SetColor();
	test.ScaleSample();
	test.BuiltShapeConnection();
	test.Deformation_With_Seg();
	test.OutPutAndVisual(ply_file,txt_file,0);
	seg.LoadData(txt_file,mesh_name);
	seg.SegFace();
	seg.SetSmoothWeight(20.0f);
	seg.GraphCut_new();
	seg.OutPutSeg(out_obj);
	seg.OutPutSegFile(out_seg);
}