#include "Deform_With_Seg.h"

Deform_With_Seg::Deform_With_Seg(void)
{
	near_point = 20;
	scale_factor = 1.5;
}


Deform_With_Seg::~Deform_With_Seg(void)
{

}

void Deform_With_Seg::GetConnection(vector<vector<int>> connection)
{
	connection_box = connection;
}

void Deform_With_Seg::GetPoints(vector<Sample> box, vector<Sample> shape)
{
	sourse_sample = box;
	target_sample = shape;
	cout << "get point " << target_sample.size() << endl;
	cout << "sourse_sample " << sourse_sample.size() << endl;
}

void Deform_With_Seg::Find_Soft_Map()
{
	SetDisThresh();
	dis_thread_hold = 2.0f;
	soft_map_near.clear();
	cout << "get point " << target_sample.size() << endl;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		vector<int> near_id;
		near_id.clear();
		soft_map_near.push_back(near_id);
	}
	cout << "begin findind" << endl;
	vector<float> average_dis;
	average_dis.clear();
	FindNearest test(sourse_sample,target_sample, near_point);
	soft_map_near = test.FindNearestType(MATCHINGTYPE);
	cout << "end findind" << endl;
	for(size_t i = 0; i < target_sample.size(); i++)
	{
		for(size_t j = 0; j < soft_map_near[i].size();j++)
		{
			average_dis.push_back(target_sample[i].dist_feature(sourse_sample[soft_map_near[i][j]],DISTANCETYPE));
		}
		//if(soft_map_near[i].size() > 0)
		//{
		//	//average_dis += dist(target_sample[i].position, sourse_sample[soft_map_near[i][0]].position);
		//	average_dis += target_sample[i].dist_feature(sourse_sample[soft_map_near[i][0]],DISTANCETYPE);
		//}
	}
	cout << "end average" << endl;
	//int k = 50;
	//vector<NamedPoint> points;
	//for (size_t i = 0; i < sourse_sample.size(); i++)
	//{
	//	points.push_back(NamedPoint(sourse_sample[i].position[0], sourse_sample[i].position[1], sourse_sample[i].position[2], i));
	//}
	//KDTree3<NamedPoint> stree(points.begin(), points.end());

	//for (size_t i = 0; i < target_sample.size(); i++)
	//{
	//	vector<int> near;
	//	near.clear();
	//	NamedPoint query(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2]);
	//	BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
	//	stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
	//	for (size_t ind = 0; ind< k; ind++)
	//	{
	//		int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;

	//		if ((sourse_sample[nearest_id].normal DOT target_sample[i].normal) > 0 || check_normal == 0)
	//		{
	//			near.push_back(nearest_id);
	//		}
	//	}
	//	if (near.size() >= near_point)
	//	{
	//		int nearest_point_id = near[0];
	//		average_dis += dist(sourse_sample[nearest_point_id].position, target_sample[i].position);
	//		//cout <<"average_dis" <<  dist(sourse_sample[nearest_point_id].position, target_sample[i].position) << endl;
	//		for (size_t ind = 0; ind< near_point; ind++)
	//		{
	//			if (dist(sourse_sample[near[ind]].position, target_sample[i].position) < 2.0f * dis_thread_hold)
	//			{
	//				soft_map_near[i].push_back(near[ind]);
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (check_normal == 0)
	//		{
	//			int nearest_point_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
	//			average_dis += dist(sourse_sample[nearest_point_id].position, target_sample[i].position);
	//			for (size_t ind = 0; ind< near_point; ind++)
	//			{
	//				int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
	//				/*
	//				soft_map_near[i].push_back(near[ind]); */

	//				if (dist(sourse_sample[nearest_id].position, target_sample[i].position) < 2.0f * dis_thread_hold)
	//				{
	//					soft_map_near[i].push_back(near[ind]);
	//				}
	//			}
	//		}
	//	}
	//}
	float mean_dis;
	float var_dis;
	GetMean(average_dis,mean_dis,var_dis);
	//stand_dev = 0.5*dis_thread_hold;
	cout << "mean_dis " << mean_dis << " var_dis " << var_dis <<endl;
	soft_map_weight.clear();
	vector<float> sum_weight;
	sum_weight.resize(target_sample.size(), 0);
	cout << "begin weight" << endl;
	for (size_t i = 0; i< soft_map_near.size(); i++)
	{
		vector<float> weight_t;
		weight_t.clear();
		//cout << "weight " <<i <<" "; 
		for (size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			//float dis = dist(target_sample[i].position, sourse_sample[soft_map_near[i][j]].position);
			float dis = target_sample[i].dist_feature(sourse_sample[soft_map_near[i][j]],DISTANCETYPE);
			float weight = exp(-(dis - mean_dis) * (dis - mean_dis) / (2 * var_dis));
			weight *= target_seg_prob[i][sourse_sample[soft_map_near[i][j]].face_id];
			//cout << weight <<" ";
			sum_weight[i] += weight;
			weight_t.push_back(weight);
		}
		//cout << endl;
		soft_map_weight.push_back(weight_t);
	}
	cout << "end weight" << endl;
	cout << "begin normalize" << endl;
	// normalize
	for (size_t i = 0; i < soft_map_weight.size(); i++)
	{
		//cout << "point i  soft_map_weight[i][j] ";
		for (size_t j = 0; j < soft_map_weight[i].size(); j++)
		{
			soft_map_weight[i][j] /= sum_weight[i];
			/*if (soft_map_weight[i][j] < 0.05)
			{
				soft_map_weight[i][j] = 0.05;
			}*/
			//cout <<soft_map_weight[i][j]<<" ";
		}
		//cout << endl;

	}
	cout << "end normalize" << endl;
}

void Deform_With_Seg::GetMean(vector<float> dis_list, float &mean, float &var)
{
	mean = 0;
	var = 0;
	for(size_t i =0; i < dis_list.size(); i++)
	{
		mean += dis_list[i];
	}
	mean /= dis_list.size();
	for(size_t i =0; i < dis_list.size(); i++)
	{
		var += (dis_list[i]- mean)*(dis_list[i]- mean);
	}
	var /= dis_list.size();
}

void Deform_With_Seg::Find_Soft_Map_T()
{
	soft_map_near_t.clear();
	soft_map_weight_t.clear();
	for (size_t i = 0; i < sourse_sample.size(); i++)
	{
		vector<int> near_id;
		near_id.clear();
		soft_map_near_t.push_back(near_id);
	}
	//float average_dis = 0;
	vector<float> average_dis;
	average_dis.clear();
	//aterage_dis.resize(sourse_sample.size(),0);
	FindNearest test(target_sample,sourse_sample, near_point);
	soft_map_near_t = test.FindNearestType(MATCHINGTYPE);
	for(size_t i = 0; i < sourse_sample.size(); i++)
	{
		for(size_t j = 0; j < soft_map_near_t[i].size(); j++)
		{
			//aterage_dis[i] += dist(sourse_sample[i].position, target_sample[soft_map_near_t[i][j]].position);
			average_dis.push_back(sourse_sample[i].dist_feature(target_sample[soft_map_near_t[i][j]],DISTANCETYPE));
		}
	}
	//int k = 50; // number of nearest neighbors
	//if (k > target_sample.size())
	//{
	//	k = target_sample.size();
	//}
	//vector<NamedPoint> points;
	//for (size_t i = 0; i < target_sample.size(); i++)
	//{
	//	points.push_back(NamedPoint(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2], i));
	//}
	//KDTree3<NamedPoint> stree(points.begin(), points.end());

	//for (size_t i = 0; i < sourse_sample.size(); i++)
	//{
	//	vector<int> near_id;
	//	near_id.clear();
	//	NamedPoint query(sourse_sample[i].position[0], sourse_sample[i].position[1], sourse_sample[i].position[2]);
	//	BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
	//	stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
	//	for (size_t ind = 0; ind< k; ind++)
	//	{
	//		int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
	//		if ((sourse_sample[i].normal DOT target_sample[nearest_id].normal) > 0 || check_normal == 0)
	//		{
	//			near_id.push_back(nearest_id);
	//		}
	//	}
	//	if (near_id.size() >= near_point)
	//	{
	//		for (size_t ind = 0; ind< near_point; ind++)
	//		{
	//			int nearest_id = near_id[ind];
	//			soft_map_near_t[i].push_back(nearest_id);
	//			aterage_dis[i] += dist(target_sample[nearest_id].position, sourse_sample[i].position) / near_point;
	//		}
	//	}
	//	else
	//	{
	//		if (check_normal == 0)
	//		{
	//			for (size_t ind = 0; ind< near_point; ind++)
	//			{
	//				int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
	//				soft_map_near_t[i].push_back(nearest_id);
	//				aterage_dis[i] += dist(target_sample[nearest_id].position, sourse_sample[i].position) / near_point;
	//			}
	//		}
	//	}
	//}
	float mean_dis;
	float var_dis;
	GetMean(average_dis,mean_dis,var_dis);
	cout << "mean_dis " << mean_dis << " var_dis " << var_dis <<endl;
	soft_map_weight_t.clear();
	vector<float> sum_weight;
	sum_weight.resize(sourse_sample.size(), 0);
	for (size_t i = 0; i < soft_map_near_t.size(); i++)
	{

		vector<float> weight_t;
		weight_t.clear();

		for (size_t j = 0; j < soft_map_near_t[i].size(); j++)
		{
			//float dis = dist(sourse_sample[i].position, target_sample[soft_map_near_t[i][j]].position);
			float dis = sourse_sample[i].dist_feature(target_sample[soft_map_near_t[i][j]],DISTANCETYPE);
			float weight = exp(-(dis - mean_dis) * (dis - mean_dis) / (2 * var_dis));
			weight *= target_seg_prob[soft_map_near_t[i][j]][sourse_sample[i].face_id];
			//cout << "weight " << weight << endl;
			sum_weight[i] += weight;
			weight_t.push_back(weight);
		}

		soft_map_weight_t.push_back(weight_t);
	}
	// normalize
	for (size_t i = 0; i< soft_map_weight_t.size(); i++)
	{
		//cout << "point i soft_map_weight_t[i][j] ";
		for (size_t j = 0; j < soft_map_weight_t[i].size(); j++)
		{
			
			soft_map_weight_t[i][j] /= sum_weight[i];
			/*if (soft_map_weight_t[i][j] < 0.05)
			{
				soft_map_weight_t[i][j] = 0.05;
			}*/
			//cout << soft_map_weight_t[i][j] <<" ";
		}
		//cout << endl;
	}
}


void Deform_With_Seg::Deform_Soft(float smooth, float data)
{
	float weight_lapcican = smooth;
	float weight_position = data;
	vector<map<int, double> >  LapMat;
	vector<vector<double> >	  LapB;
	LapB.resize(3);
	for (size_t i = 0; i< sourse_sample.size(); i++)
	{
		for (size_t j = 0; j< connection_box[i].size(); j++)
		{
			LapMat.push_back(map<int, double>());
			(LapMat.back())[i] = weight_lapcican;
			int near_id = connection_box[i][j];
			(LapMat.back())[near_id] = -weight_lapcican;
			vec3 match_p = sourse_sample[i].position - sourse_sample[near_id].position;
			for (int j = 0; j<3; j++)
			{
				LapB[j].push_back(match_p[j] * weight_lapcican);
			}
		}
	}
	cout << "finish part 1" << endl;
	int nr_cols = sourse_sample.size();

	for (size_t i = 0; i< soft_map_near.size(); i++)
	{
		for (size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			if (soft_map_weight[i][j] > 0.001)
			{
				LapMat.push_back(map<int, double>());
				(LapMat.back())[soft_map_near[i][j]] = soft_map_weight[i][j] * weight_position *2.0f;
				vec3 match_p = target_sample[i].position;
				for (int jj = 0; jj<3; jj++)
				{
					LapB[jj].push_back(match_p[jj] * weight_position * soft_map_weight[i][j] * 2.0f);
				}
			}

		}

	}
	cout << "finish part 2" << endl;
	for (size_t i = 0; i< soft_map_near_t.size(); i++)
	{
		for (size_t j = 0; j < soft_map_near_t[i].size(); j++)
		{
			if (soft_map_weight_t[i][j] > 0.001)
			{
				LapMat.push_back(map<int, double>());
				int shape_id = soft_map_near_t[i][j];
				(LapMat.back())[i] = soft_map_weight_t[i][j] * weight_position;
				vec3 match_p = target_sample[shape_id].position;
				for (int jj = 0; jj<3; jj++)
				{
					LapB[jj].push_back(match_p[jj] * weight_position * soft_map_weight_t[i][j]);
				}
			}

		}

	}
	cout << "finish part 3" << endl;

	LeastSquaresSparseSolver solver;
	solver.Init(LapMat, nr_cols);
	vector<vector<double> > eRes;
	solver.Solve(LapB, eRes);
	deform_sourse_sample = sourse_sample;
	for (int i = 0; i< nr_cols; i++)
	{
		for (int j = 0; j<3; j++)
		{
			deform_sourse_sample[i].position[j] = eRes[j][i];
			//cout << eRes[j][i];
		}

		//cout << endl;
	}
	cout << "finish part 4" << endl;
}

void Deform_With_Seg::SetDisThresh()
{
	vector<Sample> target_sample;
	vector<Sample> sourse_sample;
	if (sourse_sample.size() > target_sample.size())
	{
		target_sample = sourse_sample;
		sourse_sample = target_sample;
	}
	else
	{
		target_sample = target_sample;
		sourse_sample = sourse_sample;
	}

	dis_thread_hold = 0;

	vector<NamedPoint> points;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		points.push_back(NamedPoint(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for (size_t i = 0; i < sourse_sample.size(); i++)
	{
		vector<int> near;
		near.clear();
		NamedPoint query(sourse_sample[i].position[0], sourse_sample[i].position[1], sourse_sample[i].position[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed

		int nearest_id = stree.getElements()[k_closest_elems[0].getIndex()].id;

		dis_thread_hold += dist(sourse_sample[i].position, target_sample[nearest_id].position);
	}

	dis_thread_hold /= sourse_sample.size();
}

void Deform_With_Seg::GetTargetNeighbor()
{
	target_near_list.clear();
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		vector<int> point_list;
		point_list.clear();
		for (size_t j = 0; j < target_sample.size(); j++)
		{
			if (j != i && dist(target_sample[i].position, target_sample[j].position) < 0.15 && target_sample[i].patch_id == target_sample[j].patch_id)
			{
				point_list.push_back(j);
			}
		}
		target_near_list.push_back(point_list);
	}

}
void Deform_With_Seg::SetMeanFeatureDis()
{
	mean_feature_dis = 0;
	var_feature_dis = 0;
	int count = 0;
	vector<float> distance;
	distance.clear();
	vector<NamedPoint> points;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		points.push_back(NamedPoint(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	int near_size = 5;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		NamedPoint query(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(near_size);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		for (size_t j = 0; j < near_size; j++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[j].getIndex()].id;
			float dis_temp = target_sample[nearest_id].dist_feature(target_sample[i],DISTANCETYPE);
			mean_feature_dis += dis_temp;
			distance.push_back(dis_temp);
			count++;
		}
	}
	mean_feature_dis /= count;
	for(size_t i =0; i < distance.size(); i++)
	{
		var_feature_dis += (distance[i] - mean_feature_dis) * (distance[i] - mean_feature_dis)/count;
	}
	cout <<"mean_feature_dis " << mean_feature_dis << " var_feature_dis "<< var_feature_dis <<  endl;
}

float Deform_With_Seg::ThetaFunction(Sample shape_sample_1, Sample shape_sample_2, int is_same)
{
	float diff = shape_sample_1.dist_feature(shape_sample_2,DISTANCETYPE);
	diff = -(diff - mean_feature_dis)*(diff - mean_feature_dis)/(var_feature_dis* 2.0f);
	if(is_same == 1)
	{
		if(exp(diff) < 1e-6)
		{
			return 1e-6;
		}
		return exp(diff);
	}
	else
	{
		if( 1.0f - exp(diff) < 1e-6)
		{
			return 1e-6;
		}
		return 1.0f - exp(diff);
	}
}

void Deform_With_Seg::SetInitialPro(int size)
{
	total_seg_size = size;
	target_seg_prob.clear();
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		vector<float> prob;
		prob.resize(total_seg_size, 1.0f / total_seg_size);
		target_seg_prob.push_back(prob);
	}
}

void Deform_With_Seg::SetMeanFeatureDisST(vector<vector<int>> near_list)
{
	mean_feature_dis_t_s = 0;
	var_feature_dis_t_s = 0;
	int count = 0;
	vector<float> distance;
	distance.clear();
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		for (size_t j = 0; j < near_point; j++)
		{
			int nearest_id = near_list[i][j];
			mean_feature_dis_t_s  += target_sample[i].dist_feature(sourse_sample[nearest_id],DISTANCETYPE);
			count++;
			distance.push_back(target_sample[i].dist_feature(sourse_sample[nearest_id],DISTANCETYPE));
		}
	}
	mean_feature_dis_t_s /= count;
	for(size_t i =0; i < distance.size(); i++)
	{
		var_feature_dis_t_s += (distance[i] - mean_feature_dis_t_s) * (distance[i] - mean_feature_dis_t_s)/count;
	}
	cout <<"mean_feature_dis_t_s " << mean_feature_dis_t_s << " var_feature_dis_t_s "<< var_feature_dis_t_s <<  endl;
}

void Deform_With_Seg::UpdataTargetSegnmentPro()
{
	/*vector<NamedPoint> points;
	for (size_t i = 0; i < sourse_sample.size(); i++)
	{
		points.push_back(NamedPoint(sourse_sample[i].position[0], sourse_sample[i].position[1], sourse_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());*/
	vector<vector<int>> nearlist;
	FindNearest test(sourse_sample,target_sample, near_point);
	nearlist = test.FindNearestType(MATCHINGTYPE);
	SetMeanFeatureDisST(nearlist);
	cout << "begin UpdateProShapetoSeg" << endl;
	vector<vector<float>>  prob_new = target_seg_prob;
	vector<float> total_weight;
	total_weight.resize(target_sample.size(), 0);
//#pragma omp parallel for
	for (int i = 0; i < target_sample.size(); i++)
	{
		/*NamedPoint query(target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(near_point);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);*/
		for (size_t ind = 0; ind < total_seg_size; ind++)
		{
			float weight_temp = 0.0f;
			for (size_t j = 0; j < near_point; j++)
			{
				int nearest_id = nearlist[i][j];
				//cout << "nearest_id" << nearest_id << endl;
				//if (sourse_sample[nearest_id].face_id == ind)
				//{
				//	float weight = -(target_sample[i].dist_feature(sourse_sample[nearest_id],DISTANCETYPE) - mean_feature_dis_t_s)*(target_sample[i].dist_feature(sourse_sample[nearest_id],DISTANCETYPE) - mean_feature_dis_t_s)/(var_feature_dis_t_s* 2.0f);
				//	//cout << "weight 1 " << weight <<  endl;
				//	//weight_temp += exp(weight);
				//	weight_temp += 1.0f/near_point;
				//}
			}
			for (size_t j = 0; j < target_near_list[i].size(); j++)
			{
				int sample_index = target_near_list[i][j];
				/*for (size_t jj = 0; jj < total_seg_size; jj++)
				{
					if (jj != ind)
					{
						weight_temp+= exp(log(ThetaFunction(target_sample[i], target_sample[sample_index], 0))*target_seg_prob[sample_index][jj]);
					}
					//cout << "weight_temp 0 " << exp(log(ThetaFunction(target_sample[i], target_sample[sample_index], 0))*target_seg_prob[sample_index][jj]) <<  endl;
				}*/
				//weight_temp += exp(log(ThetaFunction(target_sample[i], target_sample[sample_index], 1)) * target_seg_prob[sample_index][ind])/target_near_list[i].size();
				//cout << "weight_temp 1 " << exp(log(ThetaFunction(target_sample[i], target_sample[sample_index], 1)) * target_seg_prob[sample_index][ind]) <<  endl;
				weight_temp += target_seg_prob[sample_index][ind]/target_near_list[i].size();
			}
			prob_new[i][ind] = weight_temp;
			total_weight[i] += weight_temp;
		}
	}

	for (size_t i = 0; i < target_sample.size(); i++)
	{
		//cout << "point " << i ;
		for (size_t ind = 0; ind < total_seg_size; ind++)
		{
			target_seg_prob[i][ind] = prob_new[i][ind] / total_weight[i];
			//cout << target_seg_prob[i][ind] << " ";
		}
		//cout << endl;
	}
}

void Deform_With_Seg::UpdataFeature()
{
	Compute_Feature test(sourse_sample);
	sourse_sample = test.GetFeaturedSample();
}


void Deform_With_Seg::ReNormal(vector<Sample> &sample_list)
{
	vector<NamedPoint> points;
	for (size_t i = 0; i < sample_list.size(); i++)
	{
		points.push_back(NamedPoint(sample_list[i].position[0], sample_list[i].position[1], sample_list[i].position[2], i));
	}
	PKDTree stree(points.begin(), points.end());
	for (size_t i = 0; i < sample_list.size(); i++)
	{
		NamedPoint query(sample_list[i].position[0], sample_list[i].position[1], sample_list[i].position[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(30);
		Eigen::Matrix3d local_covariance_matrix = Eigen::Matrix3d::Constant(3, 3, 0);
		Eigen::Vector3d centroid(0, 0, 0);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  //-1 means there's no limit on the maximum allowed
		for (int kn = 0; kn < k_closest_elems.size(); kn++)
		{
			if (stree.getElements()[k_closest_elems[kn].getIndex()].id != i)
			{
				NamedPoint kpoint = stree.getElements()[k_closest_elems[kn].getIndex()];
				Eigen::Vector3d v(kpoint.position.x, kpoint.position.y, kpoint.position.z);
				centroid += v;
			}
		}
		centroid /= (float)k_closest_elems.size();

		for (int kn = 0; kn < k_closest_elems.size(); kn++)
		{
			if (stree.getElements()[k_closest_elems[kn].getIndex()].id != i)
			{
				NamedPoint kpoint = stree.getElements()[k_closest_elems[kn].getIndex()];
				Eigen::Vector3d v(kpoint.position.x, kpoint.position.y, kpoint.position.z);
				v = v - centroid;
				local_covariance_matrix += v * v.transpose();
			}
		}

		local_covariance_matrix /= (float)k_closest_elems.size();
		Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d>eigensolver(local_covariance_matrix);
		Eigen::Vector3d n = eigensolver.eigenvectors().col(0);
		vec3 normal(n(0), n(1), n(2));
		if ((sample_list[i].normal DOT normal) > 0)
		{
			sample_list[i].normal = normal;
		}
		else
		{
			sample_list[i].normal = -normal;
		}
	}
}


void Deform_With_Seg::Run()
{
	float smooth = 2.0;
	float data = 1.0;
	GetTargetNeighbor();
	SetMeanFeatureDis();
	for (int ite = 0; ite < 5; ite++)
	{
		check_normal = 1;
		Find_Soft_Map();
		Find_Soft_Map_T();
		smooth -= 0.1*ite;
		data += 0.1*ite;
		cout << "begin deform " << endl;
		Deform_Soft(smooth, data);
		cout << "end deform " << endl;
		sourse_sample = deform_sourse_sample;
		UpdataFeature();
		ReNormal(sourse_sample);
		for(size_t i = 0; i < 5; i++)
		{
		  UpdataTargetSegnmentPro();
		}
		VisualSeg();
	}
}

void Deform_With_Seg::VisualSeg()
{
	vector<ivec3> color_list;
	color_list.clear();
	for(int  i =0; i < total_seg_size; i++)
	{
		color_list.push_back(ivec3((int)(255*(float)(rand())/RAND_MAX),(int)(255*(float)(rand())/RAND_MAX),(int)(255*(float)(rand())/RAND_MAX)));
	}
	for(size_t i = 0; i < target_sample.size(); i++)
	{
		int max_index = 0;
		float max_pro = 0;
		for(size_t j = 0; j < target_seg_prob[i].size(); j++)
		{
			//cout << pro_shape_sample[i][j] <<" ";
			if(target_seg_prob[i][j] > max_pro)
			{
				max_pro = target_seg_prob[i][j];
				max_index = j;
			}
		}
		if(max_pro *total_seg_size < 1 )
		{
			cout << "err" << endl;
			cout <<"weight_ " << i<<" "; 
			for (size_t ind = 0; ind < total_seg_size; ind++)
			{
				//target_seg_prob[i][ind] = prob_new[i][ind] / total_weight[i];
				cout << target_seg_prob[i][ind]<<" ";
			}
			cout << endl;
			FixSef(i);
			for(size_t j = 0; j < target_seg_prob[i].size(); j++)
			{
				//cout << pro_shape_sample[i][j] <<" ";
				if(target_seg_prob[i][j] > max_pro)
				{
					max_pro = target_seg_prob[i][j];
					max_index = j;
				}
			}

		}
		//cout << pro_shape_sample[i][j] <<" ";
		//cout <<  max_pro << endl;
		target_sample[i].color = color_list[max_index];
		target_sample[i].face_id = max_index;
	}

	/*ofstream fout("seg_out.ply") ;

	fout << "ply" << endl;
	fout << "format ascii 1.0" << endl;
	fout << "element vertex " << target_sample.size() << endl;
	fout << "property float32 x" << endl;
	fout << "property float32 y" << endl;
	fout << "property float32 z" << endl;
	fout << "property float32 nx" << endl;
	fout << "property float32 ny" << endl;
	fout << "property float32 nz" << endl;
	fout << "property uchar red" << endl;
	fout << "property uchar green" << endl;
	fout << "property uchar blue" << endl;
	fout << "element face 0" << endl;
	fout << "property list uint8 int32 vertex_index" << endl;
	fout << "end_header" << endl;
	for(size_t i=0;i< target_sample.size();i++)
	{
		fout<<(target_sample[i].position[0] )<<" "<< (target_sample[i].position[1] )<<" "<< (target_sample[i].position[2] )<<" ";
		fout<< target_sample[i].normal[0] <<" "<< target_sample[i].normal[1] <<" "<< target_sample[i].normal[2] <<" ";
		fout<< target_sample[i].color[0] <<" "<< target_sample[i].color[1]  <<" "<< target_sample[i].color[2] <<endl;
	}*/
}

void Deform_With_Seg::FixSef(int index)
{
	vector<NamedPoint> points;
	for (size_t i = 0; i < sourse_sample.size(); i++)
	{
		points.push_back(NamedPoint(sourse_sample[i].position[0], sourse_sample[i].position[1], sourse_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	NamedPoint query(target_sample[index].position[0], target_sample[index].position[1], target_sample[index].position[2]);
	BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(near_point);
	stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
	for (size_t ind = 0; ind < total_seg_size; ind++)
	{
		float weight_temp = 0;
		for (size_t j = 0; j < near_point; j++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[j].getIndex()].id;
			if (sourse_sample[nearest_id].face_id == ind)
			{
    			weight_temp += 1;
			}
		}
		weight_temp /= near_point;
		target_seg_prob[index][ind] = weight_temp;
	}
}