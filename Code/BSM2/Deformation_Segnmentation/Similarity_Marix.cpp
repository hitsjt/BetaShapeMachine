#include "Similarity_Marix.h"


Similarity_Marix::Similarity_Marix(void)
{
}


Similarity_Marix::~Similarity_Marix(void)
{
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
	for(size_t i = 0; i < meshlist.size(); i++)
	{
		unsigned ePos;
		ePos = meshlist[i].find_last_of(".");
		string mesh_name = working_path;
		mesh_name.append("\\rotate_model\\");
		mesh_name.append(meshlist[i].substr(0,ePos));
		mesh_name.append(".obj");
		Shape t_shape;
		t_shape.GetShape(mesh_name);
		t_shape.GetSamplePoint(2000);
		cout << t_shape.shape_sample.size() << endl;
		mesh_sample.push_back(t_shape.shape_sample);
	}
}

vector<float> Similarity_Marix::GetDistance(int index)
{
	vector<float> dis;
	//dis.resize(meshlist.size(),1.0f);
	dis.resize(meshlist.size(),0.0f);
	//float mean_distance = GetMeanDist(mesh_sample[index]);
	for(size_t i = 0; i < meshlist.size(); i++)
	{
		if(i ==  index)
		{
			//dis[i] -= 1.0f;
			dis[i] = 0.0f;
		}
		else
		{
			cout << index << " "<< i <<" ";
			//float distemp = SimilarityDistance(mesh_sample[index], mesh_sample[i]) - mean_distance;
			//distemp /=(mean_distance);
			//dis[i] -= exp(-distemp*distemp);
			dis[i] = exp(SimilarityDistance(mesh_sample[index], mesh_sample[i]));
		}
	}
	return dis;
}

float Similarity_Marix::SimilarityDistance(vector<Sample> s_point, vector<Sample> t_point)
{
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
	}
	fit_s_t /= s_point.size();

	float fit_t_s = 0;
	vector<NamedPoint> points_s;
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
	fit_t_s /= t_point.size();
	cout << fit_s_t + fit_t_s << endl;
	return fit_s_t + fit_t_s;
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
		fout << "group "<< i << endl;
		for(size_t j = 0; j <  meshlist.size(); j++)
		{
			if(k_mean[j] == i)
			{
				fout << meshlist[j] << endl;
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
					if(k_mean[jj] == i)
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