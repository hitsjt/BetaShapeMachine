#include "Mean_Field_Deformation.h"

Mean_Field_Deformation::Mean_Field_Deformation(void)
{
	nearest_sample_size = 20;
}

Mean_Field_Deformation::~Mean_Field_Deformation(void)
{

}

Mean_Field_Deformation::Mean_Field_Deformation(vector<Sample> t_sample, vector<Sample> s_sample, vector<vector<int>> connection, int seg_size)
{
	target_sample = s_sample;
	template_sample =  t_sample;
	template_connection = connection;
	nearest_sample_size = 20;
	total_seg_size = seg_size;
	color_list.clear();
	ivec3 c(255,255,255);
	ivec3 c1(255,255,0);
	ivec3 c2(255,0,0);
	ivec3 c3(0,255,255);
	ivec3 c4(0,0,255);
	ivec3 c5(0,255,0);
	ivec3 c6(0,0,0);
	color_list.push_back(c);
	color_list.push_back(c1);
	color_list.push_back(c2);
	color_list.push_back(c3);
	color_list.push_back(c4);
	color_list.push_back(c5);
	color_list.push_back(c6);
	for(int  i =0; i < total_seg_size; i++)
	{
		color_list.push_back(ivec3((int)(255*(float)(rand())/RAND_MAX),(int)(255*(float)(rand())/RAND_MAX),(int)(255*(float)(rand())/RAND_MAX)));
	}
}

void Mean_Field_Deformation::Initial() // initial knn Neighbor
{
	//find the neighbor for each target sample on target model
	float target_rad = 0.0f;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		for (size_t j = 0; j < target_sample.size(); j++)
		{
			if(dist(target_sample[i].position, target_sample[j].position) > target_rad)
			{
				target_rad = dist(target_sample[i].position, target_sample[j].position);
			}
		}
	}
	cout << "begin initial " << endl;
	matching_target_target.clear();
	int average_neighbor = 0;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		vector<int> point_list;
		point_list.clear();
		for (size_t j = 0; j < target_sample.size(); j++)
		{
			if (j != i && dist(target_sample[i].position, target_sample[j].position) < 0.05 * target_rad && target_sample[i].patch_id == target_sample[j].patch_id)
			{
				point_list.push_back(j);
			}
		}
		average_neighbor += point_list.size();
		matching_target_target.push_back(point_list);
	}
	cout << "average neighbor size for target sample = " << average_neighbor/target_sample.size() << endl;
	// initial the segmentation 
	pro_target_seg.clear();
	for (size_t i = 0; i <  target_sample.size(); i++)
	{
		vector<float> pro_sample;
		pro_sample.resize(total_seg_size  + 1 ,1.0f/(float)(total_seg_size + 1)); // 1 means NULL assignment
		pro_target_seg.push_back(pro_sample);
	}
	cout << "endl initial " << endl;
}

void Mean_Field_Deformation::FindNeighbor()
{
	// neighbor for each target sample on template sample
	average_dis_template_target = 0;
	average_dis_target_template = 0;
	int total_1 = 0;
	int total_2 = 0;
	matching_targte_template.clear();
	matching_template_target.clear();
	vector<NamedPoint> points_template;
	for (size_t i = 0; i < template_sample.size(); i++)
	{
		points_template.push_back( NamedPoint(  template_sample[i].position[0], template_sample[i].position[1], template_sample[i].position[2], i ) );
	}
	PKDTree stree(points_template.begin(), points_template.end());
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		NamedPoint query( target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(TARGETNEARSIZE);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		vector<int> neighbor_list;
		neighbor_list.clear();
		for (size_t ind = 0; ind< TARGETNEARSIZE; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			neighbor_list.push_back(nearest_id);
			average_dis_target_template += dist(target_sample[i].position, template_sample[nearest_id].position);
			total_1++;
			
		}
		matching_targte_template.push_back(neighbor_list);
	}
	average_dis_target_template /= total_1;
	/*FindNearest test(template_sample,target_sample, TARGETNEARSIZE);
	matching_targte_template = test.FindNearestType(2);*/

	cout << "end find neighbor 1" << endl;
	vector<NamedPoint> points_target;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		points_target.push_back( NamedPoint( target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2], i ) );
	}
	PKDTree stree2(points_target.begin(), points_target.end());
	for (size_t i = 0; i < template_sample.size(); i++)
	{
		NamedPoint query( template_sample[i].position[0], template_sample[i].position[1], template_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(TEMPLATENEARSIZE);
		stree2.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		vector<int> neighbor_list;
		neighbor_list.clear();
		for (size_t ind = 0; ind< TEMPLATENEARSIZE; ind++)
		{
			int nearest_id = stree2.getElements()[k_closest_elems[ind].getIndex()].id;
			neighbor_list.push_back(nearest_id);
			matching_targte_template[nearest_id].push_back(i);
			average_dis_template_target += dist(target_sample[nearest_id].position, template_sample[i].position);
			total_2++;

		}
		matching_template_target.push_back(neighbor_list);
	}
	average_dis_template_target /= total_2;
	cout << "average_dis_template_target " << average_dis_template_target << "  average_dis_target_template " << average_dis_target_template << endl;
	/*FindNearest test1(target_sample,template_sample, TEMPLATENEARSIZE);
	matching_template_target = test1.FindNearestType(2);

	for(size_t i = 0; i < matching_template_target.size(); i++ )
	{
		for(size_t j = 0; j < matching_template_target[i].size(); j++)
		{
			matching_targte_template[matching_template_target[i][j]].push_back(i);
		}
	}*/
	//cout << "end find neighbor 2" << endl;
	pro_target_template.clear();
	float average_neighbor = 0;
	for (size_t i = 0; i < matching_targte_template.size(); i++)
	{
		vector<float> pro_sample;
		pro_sample.resize(matching_targte_template[i].size() + 1 , 1.0f / (float)(matching_targte_template[i].size() + 1));
		pro_sample.back() = EPSILON_NULL;
		pro_target_template.push_back(pro_sample);
		average_neighbor += matching_targte_template[i].size();
	}

	for(size_t i = 0; i < matching_template_target.size(); i++)
	{
		vector<float> pro_sample;
		pro_sample.resize( matching_template_target[i].size() , 1.0f / (float)( matching_template_target[i].size()));
		pro_template_target.push_back(pro_sample);
	}
	cout << "average neighbor size for target to template  sample = " << average_neighbor/matching_targte_template.size() << endl;
	cout << "end find neighbor 3" << endl;
}

void Mean_Field_Deformation::GetInitialDistance()
{
	initial_distance.clear();
	for(size_t i = 0; i < template_sample.size(); i++)
	{
		vector<vec3> diff;
		diff.clear();
		for(size_t j = 0; j < template_connection[i].size(); j++)
		{
			vec3 diff_pos = template_sample[i].position - template_sample[template_connection[i][j]].position;
			diff.push_back(diff_pos);
		}
		initial_distance.push_back(diff);
	}
}

void Mean_Field_Deformation::SetInitialSigmaValue()
{
	cout << "begin sigma" << endl;
	// sigma 1
	vec3 p(0, 0 , 0);
	sigma_1 = p;
	sigma_2.resize(target_sample[0].sample_features.size(), 0);
	sigma_3 = p;
	sigma_4.resize(target_sample[0].sample_features.size(), 0);
	sigma_5 = p;
	sigma_6.resize(target_sample[0].sample_features.size(), 0);
	sigma_7 = p;
	sigma_8.resize(target_sample[0].sample_features.size(), 0);
	sigma_dis_1 = 0;
	sigma_dis_2 = 0;
	sigma_dis_3 = 0;
	sigma_dis_4 = 0;
	float mu_1 = 0;
	for(size_t i = 0; i < matching_targte_template.size(); i++)
	{
		for(size_t j = 0; j <  matching_targte_template[i].size(); j++)
		{
			mu_1 += pro_target_template[i][j];
			vec3 pos_diff =  target_sample[i].position - template_sample[matching_targte_template[i][j]].position;
			sigma_dis_1 += pro_target_template[i][j] * len(pos_diff);
			sigma_1[0] += pro_target_template[i][j]*pos_diff[0] * pos_diff[0];
			sigma_1[1] += pro_target_template[i][j]*pos_diff[1] * pos_diff[1];
			sigma_1[2] += pro_target_template[i][j]*pos_diff[2] * pos_diff[2];
			vector<float> fea_diff = FeatureDiff( target_sample[i], template_sample[matching_targte_template[i][j]]);
			float diff_fea = 0;
			for(size_t f = 0; f < sigma_2.size(); f++)
			{
				sigma_2[f] += pro_target_template[i][j]*fea_diff[f]*fea_diff[f];
				diff_fea += pro_target_template[i][j]*fea_diff[f]*fea_diff[f];
			}
			sigma_dis_2 += sqrt(diff_fea);
		}
	}
	sigma_1 /= mu_1;
	sigma_dis_1 /= mu_1;
	sigma_dis_2 /= mu_1;
	sigma_1[0] += EPSILON_DEV;
	sigma_1[1] += EPSILON_DEV;
	sigma_1[2] += EPSILON_DEV;
	for(size_t f = 0; f < sigma_2.size(); f++)
	{
		sigma_2[f] /= mu_1;
		sigma_2[f] += EPSILON_DEV;
	}
	float mu_kp = 0;
	for(size_t i = 0; i < template_sample.size(); i++)
	{
		//cout << i  << " / " <<template_sample.size()<<" " << template_connection[i].size() << endl;
		for(size_t j = 0; j < template_connection[i].size(); j++)
		{
			mu_kp += 1.0f;
			int index_near = template_connection[i][j];
			vec3 pos_diff = template_sample[i].position - template_sample[index_near].position;
			sigma_3[0] += pos_diff[0] * pos_diff[0];
			sigma_3[1] += pos_diff[1] * pos_diff[1];
			sigma_3[2] += pos_diff[2] * pos_diff[2];
		}
	}
	sigma_3 /= mu_kp;
	sigma_3[0] += EPSILON_DEV;
	sigma_3[1] += EPSILON_DEV;
	sigma_3[2] += EPSILON_DEV;
//	cout <<"end sigma_3 " << sigma_3<< endl;
	vector<float> feature_diff;
	feature_diff.clear();
	float mu_k = 0;
	for(size_t i = 0; i < target_sample.size(); i++)
	{
		for(size_t j = 0; j < matching_target_target[i].size(); j++)
		{
			int index_near = matching_target_target[i][j];
			mu_k += 1.0f;
			vec3 pos_diff = target_sample[i].position - target_sample[index_near].position;
			sigma_dis_3 += len(pos_diff);
			sigma_5[0] += pos_diff[0] * pos_diff[0];
			sigma_5[1] += pos_diff[1] * pos_diff[1];
			sigma_5[2] += pos_diff[2] * pos_diff[2];
			vector<float> diff_v = FeatureDiff( target_sample[i], target_sample[index_near]);
			float diff_fea = 0;
			for(size_t f = 0; f < diff_v.size(); f++)
			{
				sigma_6[f] += diff_v[f]*diff_v[f];
				diff_fea += diff_v[f]*diff_v[f];
			}
			sigma_dis_4 += diff_fea;
			feature_diff.push_back(sqrt(diff_fea));
		}
	}
	sigma_dis_3 /= mu_k;
	sigma_dis_4 /= mu_k;
	
	getfeatureVar(feature_diff, sigma_dis_4, var_4);
	cout << "sigma_dis_4 " << sigma_dis_4 << " var_4 " << var_4 << endl;
	sigma_5 /= mu_k;
	for(size_t f = 0; f < sigma_6.size(); f++)
	{
		sigma_6[f] /= mu_k;
		sigma_6[f] += EPSILON_DEV;
		//cout << sigma_6[f] << endl;
	}
	//cout <<"end sigma_6 " << endl;
	float mu_kk = 0;
	for(size_t i = 0; i < matching_template_target.size(); i++)
	{
		for(size_t j = 0; j <  matching_template_target[i].size(); j++)
		{
			mu_kk  += pro_template_target[i][j];
			vec3 pos_diff =  template_sample[i].position - target_sample[matching_template_target[i][j]].position;
			sigma_7[0] += pro_template_target[i][j]*pos_diff[0] * pos_diff[0];
			sigma_7[1] += pro_template_target[i][j]*pos_diff[1] * pos_diff[1];
			sigma_7[2] += pro_template_target[i][j]*pos_diff[2] * pos_diff[2];
			vector<float> fea_diff = FeatureDiff( template_sample[i], target_sample[matching_template_target[i][j]]);
			float diff_fea = 0;
			for(size_t f = 0; f < sigma_8.size(); f++)
			{
				diff_fea += fea_diff[f] * fea_diff[f];
				sigma_8[f] += pro_template_target[i][j]*fea_diff[f]*fea_diff[f];
			}
		
		}
	}

	sigma_7 /= mu_kk;
	sigma_7[0] += EPSILON_DEV;
	sigma_7[1] += EPSILON_DEV;
	sigma_7[2] += EPSILON_DEV;
	//cout <<"sigma_7 " << sigma_7 << endl;
	//cout << sigma_8.size() << endl;
	for(size_t f = 0; f < sigma_8.size(); f++)
	{
		sigma_8[f] /= mu_kk;
		sigma_8[f] += EPSILON_DEV;
	}

}

vector<float> Mean_Field_Deformation::FeatureDiff(Sample sample_1, Sample sample_2)
{
	vector<float> feature_diff;
	feature_diff.clear();
	for(size_t i = 0; i < sample_1.sample_features.size(); i++)
	{
		feature_diff.push_back(sample_1.sample_features[i] - sample_2.sample_features[i]);
	}
	return feature_diff;
}



int Mean_Field_Deformation::CheckNeighbor(int target_index, int template_index)
{
	int index = -1;
	for(size_t  i = 0; i < matching_targte_template[target_index].size(); i++)
	{
		if(matching_targte_template[target_index][i] == template_index)
		{
			index = i;
			break;
		}
	}
	return index;
}

void Mean_Field_Deformation::UpdatePosition(int ite)
{
    


	float weight_lapcican = 2.0f;
	if((sigma_1[0]/sigma_3[0] + sigma_1[1]/sigma_3[1] + sigma_1[2]/sigma_3[2])/3.0f  < 2)
	{
		weight_lapcican = 2.0f;
	}
	//cout << weight_lapcican << "weight_lapcican " << endl;
	float weight_position = 1 ;
	vector<map<int, double> >  LapMat;
	vector<vector<double> >	  LapB;
	LapB.resize(3);
	for (size_t i = 0; i< template_sample.size(); i++)
	{
		for (size_t j = 0; j< template_connection[i].size(); j++)
		{
			LapMat.push_back(map<int, double>());
			(LapMat.back())[i] = weight_lapcican;
			int near_id = template_connection[i][j];
			(LapMat.back())[near_id] = -weight_lapcican;
			vec3 match_p = template_sample[i].position - template_sample[near_id].position;
			for (int j = 0; j<3; j++)
			{
				LapB[j].push_back(match_p[j] * weight_lapcican);
			}
		}
	}
	//cout << "finish part 1" << endl;
	int nr_cols = template_sample.size();

	for (size_t i = 0; i<  matching_targte_template.size(); i++)
	{
		for (size_t j = 0; j <  matching_targte_template[i].size(); j++)
		{
			LapMat.push_back(map<int, double>());
			(LapMat.back())[matching_targte_template[i][j]] = pro_target_template[i][j]* weight_position *1.0f;
			vec3 match_p = target_sample[i].position;
			for (int jj = 0; jj<3; jj++)
			{
				LapB[jj].push_back(match_p[jj] * weight_position * pro_target_template[i][j] * 1.0);
			}
		}

	}

	for (size_t i = 0; i<  matching_template_target.size(); i++)
	{
		for (size_t j = 0; j <  matching_template_target[i].size(); j++)
		{
			LapMat.push_back(map<int, double>());
			(LapMat.back())[i] = pro_template_target[i][j]* weight_position *(average_dis_target_template/(average_dis_template_target + EPSILON_DEV))*1.5f;
			vec3 match_p = target_sample[matching_template_target[i][j]].position;
			for (int jj = 0; jj<3; jj++)
			{
				LapB[jj].push_back(match_p[jj] * weight_position * pro_template_target[i][j] * (average_dis_target_template / (average_dis_template_target + EPSILON_DEV))*1.5f);
			}
		}

	}

	LeastSquaresSparseSolver solver;
	solver.Init(LapMat, nr_cols);
	vector<vector<double> > eRes;
	solver.Solve(LapB, eRes);
	for (int i = 0; i< nr_cols; i++)
	{
		for (int j = 0; j<3; j++)
		{
			template_sample[i].position[j] = eRes[j][i];
		}
	}
}

void Mean_Field_Deformation::UpdateSigma()
{
	vec3 p(0, 0 , 0);
	sigma_1 = p;
	sigma_2.resize(target_sample[0].sample_features.size(), 0);
	sigma_7 = p;
	sigma_8.resize(target_sample[0].sample_features.size(), 0);
	sigma_dis_1 = 0;
	sigma_dis_2 = 0;
	float mu_1 = 0;
	for(size_t i = 0; i < matching_targte_template.size(); i++)
	{
		for(size_t j = 0; j <  matching_targte_template[i].size(); j++)
		{
			mu_1 += pro_target_template[i][j];
			vec3 pos_diff =  target_sample[i].position - template_sample[matching_targte_template[i][j]].position;
			sigma_dis_1 += len(pos_diff);
			sigma_1[0] += pro_target_template[i][j]*pos_diff[0] * pos_diff[0];
			sigma_1[1] += pro_target_template[i][j]*pos_diff[1] * pos_diff[1];
			sigma_1[2] += pro_target_template[i][j]*pos_diff[2] * pos_diff[2];
			vector<float> fea_diff = FeatureDiff( target_sample[i], template_sample[matching_targte_template[i][j]]);
			float diff_fea = 0;
			for(size_t f = 0; f < sigma_2.size(); f++)
			{
				sigma_2[f] += pro_target_template[i][j]*fea_diff[f]*fea_diff[f];
				diff_fea += fea_diff[f]*fea_diff[f];
			}
			sigma_dis_2 += sqrt(diff_fea);
		}
	}
	sigma_1 /= mu_1;
	sigma_dis_1 /= mu_1;
	sigma_dis_2 /= mu_1;
	sigma_1[0] += EPSILON_DEV;
	sigma_1[1] += EPSILON_DEV;
	sigma_1[2] += EPSILON_DEV;
	//cout <<"sigma_1 " << sigma_1 << endl;
	//cout << sigma_2.size() << endl;
	for(size_t f = 0; f < sigma_2.size(); f++)
	{
		sigma_2[f] /= mu_1;
		sigma_2[f] += EPSILON_DEV;
	}
	//cout <<"end sigma_2 " << endl;

	float mu_kp = 0;
	for(size_t i = 0; i < template_sample.size(); i++)
	{
		//cout << i  << " / " <<template_sample.size()<<" " << template_connection[i].size() << endl;
		for(size_t j = 0; j < template_connection[i].size(); j++)
		{
			mu_kp += 1.0f;
			int index_near = template_connection[i][j];
			vec3 pos_diff = template_sample[i].position - template_sample[index_near].position;
			sigma_3[0] += pos_diff[0] * pos_diff[0];
			sigma_3[1] += pos_diff[1] * pos_diff[1];
			sigma_3[2] += pos_diff[2] * pos_diff[2];
		}
	}
	sigma_3 /= mu_kp;
	sigma_3[0] += EPSILON_DEV;
	sigma_3[1] += EPSILON_DEV;
	sigma_3[2] += EPSILON_DEV;
//	cout <<"end sigma_3 " << sigma_3<< endl;

	float mu_kk = 0;
	for(size_t i = 0; i < matching_template_target.size(); i++)
	{
		for(size_t j = 0; j <  matching_template_target[i].size(); j++)
		{
			mu_kk  += pro_template_target[i][j];
			vec3 pos_diff =  template_sample[i].position - target_sample[matching_template_target[i][j]].position;
			sigma_7[0] += pro_template_target[i][j]*pos_diff[0] * pos_diff[0];
			sigma_7[1] += pro_template_target[i][j]*pos_diff[1] * pos_diff[1];
			sigma_7[2] += pro_template_target[i][j]*pos_diff[2] * pos_diff[2];
			vector<float> fea_diff = FeatureDiff( template_sample[i], target_sample[matching_template_target[i][j]]);
			float diff_fea = 0;
			for(size_t f = 0; f < sigma_8.size(); f++)
			{
				sigma_8[f] += pro_template_target[i][j]*fea_diff[f]*fea_diff[f];
			}
		}
	}

	sigma_7 /= mu_kk;
	sigma_7[0] += EPSILON_DEV;
	sigma_7[1] += EPSILON_DEV;
	sigma_7[2] += EPSILON_DEV;
	//cout <<"sigma_7 " << sigma_7 << endl;
	//cout << sigma_8.size() << endl;
	for(size_t f = 0; f < sigma_8.size(); f++)
	{
		sigma_8[f] /= mu_kk;
		sigma_8[f] += EPSILON_DEV;
	}

}

void Mean_Field_Deformation::UpdateSegnmenatation()
{
	//pro_target_seg.clear();
	//for (size_t i = 0; i <  target_sample.size(); i++)
	//{
	//	vector<float> pro_sample;
	//	pro_sample.resize(total_seg_size  + 1 ,1.0f/(float)(total_seg_size + 1)); // 1 means NULL assignment
	//	pro_target_seg.push_back(pro_sample);
	//}
	cout << "endl initial " << endl;
	float min_div = FLT_MAX;
	float max_div = -FLT_MAX;
	cout << " UpdateSegnmenatation " << endl;
	vector<float> total_weight;
	total_weight.resize(target_sample.size(), 0);
	vector<vector<float>> pro_target_seg_new;
	pro_target_seg_new.clear();
	for(size_t i = 0; i < target_sample.size(); i++)
	{
		//cout << i << "/" << target_sample.size()<< "\r";

		vector<float> prob_i;
		prob_i.resize(total_seg_size + 1,0);
		for(size_t j = 0; j <= total_seg_size; j++)
		{
			// data part
			for(size_t pt = 0; pt < matching_targte_template[i].size(); pt++)
			{
				int template_id = matching_targte_template[i][pt];
				if(template_sample[template_id].face_id != j)
				{
					prob_i[j] += pro_target_template[i][pt]*log(EPSILON_SEGNMENTATION);
				}
				/*if(template_sample[template_id].face_id == j)
				{
					prob_i[j] += 1.0f;
				}*/
			}
			//fout << prob_i[j] << " ";
			// smooth part
			for(size_t pt = 0; pt < matching_target_target[i].size(); pt++)
			{
				int target_id = matching_target_target[i][pt];
				float theta_value = Theta(target_sample[i],target_sample[target_id],1);
				//fout << theta_value << endl;
				if((theta_value)  > max_div)
				{
					max_div = (theta_value) ;
				}
				if((theta_value)  < min_div)
				{
					min_div = (theta_value) ;
				}
				prob_i[j] += pro_target_seg[target_id][j] * (log(theta_value/(1- theta_value+ EPSILON_DEV)));
				//prob_i[j] += pro_target_seg[target_id][j] * (log(1 - theta_value)) /total_seg_size;
				//cout << (log(theta_value/(1- theta_value+ EPSILON_DEV))) << endl;
			}

			//fout << prob_i[j] << " ";
		}
		//fout << endl;
		pro_target_seg_new.push_back(prob_i);
	}
	//cout << endl;
	//cout << "max_div " << max_div << " " << "min_ div " << min_div << endl;
	// normalize
	for(size_t i = 0; i < pro_target_seg_new.size(); i++)
	{
		//cout << i << " ";
		float min_value = FLT_MAX;
		float max_value = - FLT_MAX;
		for(size_t j =0; j < pro_target_seg_new[i].size(); j++)
		{

			if(min_value > pro_target_seg_new[i][j])
			{
				min_value = pro_target_seg_new[i][j];
			}

			if( max_value < pro_target_seg_new[i][j])
			{
				max_value = pro_target_seg_new[i][j];
			}
	
		}
	
		float total_weight = 0;
		for(size_t j =0; j < pro_target_seg_new[i].size(); j++)
		{
			float diff = pro_target_seg_new[i][j] - max_value;
			if(diff < -6)
			{
				diff = -6;
			}
			pro_target_seg_new[i][j] = exp(diff);

			total_weight += pro_target_seg_new[i][j];
		}
		//cout << min_value <<" " << max_value << " "<< total_weight << endl;
		for(size_t j =0; j < pro_target_seg_new[i].size(); j++)
		{
			pro_target_seg_new[i][j] /= total_weight;
		}
		//pro_target_seg_new[i].back() = 0.5;
		//cout << endl;
	}
	pro_target_seg = pro_target_seg_new;
}

void Mean_Field_Deformation::UpdataTemplateShapeMatching()
{
	cout << " UpdataTemplateShapeMatching " << endl;
	vector<vector<float>> pro_template_target_new;
	pro_template_target_new.clear();
	for(size_t i = 0; i < matching_template_target.size(); i++)
	{
		//cout << i << "/" << matching_template_target.size() << " \r";
		vector<float> pro_i;
		pro_i.clear();
		vector<float> fd_diff;
		fd_diff.clear();
		for(size_t j = 0; j < matching_template_target[i].size(); j++)
		{
			int t_index = matching_template_target[i][j];
			float temp = 0;
			vec3 diff_pos = template_sample[i].position - target_sample[t_index].position;
			temp -= 0.5f*diff_pos[0]*diff_pos[0]/sigma_7[0];
			temp -= 0.5f*diff_pos[1]*diff_pos[1]/sigma_7[1];
			temp -= 0.5f*diff_pos[2]*diff_pos[2]/sigma_7[2];
			//temp += len(diff_pos);
			vector<float> feature_diff = FeatureDiff(template_sample[i],target_sample[t_index]);
			float diff_fea = 0;
			for(size_t k = 0; k < feature_diff.size(); k++)
			{
				temp -= 0.5f*feature_diff[k]*feature_diff[k]/sigma_8[k];
				//diff_fea += feature_diff[k] * feature_diff[k];
			}
			//temp += 0.2*sqrt(diff_fea);
			//fd_diff.push_back(temp);
			/*if (temp < THETATHRESHOLD)
			{
				temp = THETATHRESHOLD;
			}*/
			pro_i.push_back(temp);
		}
	/*	float d_mean, d_var;
		getfeatureVar(fd_diff, d_mean, d_var);
		for (size_t j = 0; j < matching_template_target[i].size(); j++)
		{
			if ((fd_diff[j] - d_mean)*(fd_diff[j] - d_mean) < 3.0f* (d_var * 2 + EPSILON_DEV))
			{
				pro_i.push_back(-(fd_diff[j] - d_mean)*(fd_diff[j] - d_mean) / (d_var * 2 + EPSILON_DEV));
			}
			else
			{
				pro_i.push_back(-3.0f);
			}
			
		}*/
		pro_template_target_new.push_back(pro_i);
	}
	//cout << endl;
	for(size_t i = 0; i < pro_template_target_new.size(); i++)
	{
		float min_value = FLT_MAX;
		float max_value = - FLT_MAX;
		for(size_t j =0; j < pro_template_target_new[i].size(); j++)
		{
			if(min_value > pro_template_target_new[i][j])
			{
				min_value = pro_template_target_new[i][j];
			}
			if(max_value < pro_template_target_new[i][j])
			{
				max_value = pro_template_target_new[i][j];
			}
		}
		//cout <<  min_value <<" " << max_value << endl;
		float total_weight = 0;
		for(size_t j =0; j < pro_template_target_new[i].size(); j++)
		{
			pro_template_target_new[i][j] = exp(pro_template_target_new[i][j] - max_value);
			total_weight += pro_template_target_new[i][j];
		}
		for(size_t j =0; j < pro_template_target_new[i].size(); j++)
		{
			pro_template_target_new[i][j] /= total_weight;
		}
	}
	pro_template_target = pro_template_target_new;
}

void Mean_Field_Deformation::UpdataShapeTemplateMatching()
{
	cout << " UpdataShapeTemplateMatching " << endl;
	vector<vector<float>> pro_target_template_new;
	pro_target_template_new.clear();
	for(size_t i = 0; i < matching_targte_template.size(); i++)
	{
		//cout << i << "/" << matching_targte_template.size() << " \r";
		vector<float> pro_i;
		pro_i.clear();
		vector<float> fd_diff;
		fd_diff.clear();
		for(size_t j = 0; j < matching_targte_template[i].size(); j++)
		{
			int t_index = matching_targte_template[i][j];
			float temp = pro_target_seg[i][template_sample[t_index].face_id] * EPSILON_SEGNMENTATION;
			vec3 diff_pos = target_sample[i].position - template_sample[t_index].position;
			temp -= 0.5f*diff_pos[0]*diff_pos[0]/sigma_1[0];
			temp -= 0.5f*diff_pos[1]*diff_pos[1]/sigma_1[1];
			temp -= 0.5f*diff_pos[2]*diff_pos[2]/sigma_1[2];
			//temp = len(diff_pos);
			vector<float> feature_diff = FeatureDiff(target_sample[i],template_sample[t_index]);
			float diff_fea = 0;
			for(size_t k = 0; k < feature_diff.size(); k++)
			{
				diff_fea += feature_diff[k]*feature_diff[k];
				temp -= 0.5f*feature_diff[k]*feature_diff[k]/sigma_2[k];
			}
			//temp += 0.2*sqrt(diff_fea);
			//fd_diff.push_back(temp);
			/*if (temp < THETATHRESHOLD)
			{
				temp = THETATHRESHOLD;
			}*/
			pro_i.push_back(temp);
		}
		//float d_mean, d_var;
		//getfeatureVar(fd_diff, d_mean, d_var);
		////cout << d_mean << " " << d_var << endl;
		//for (size_t j = 0; j < matching_targte_template[i].size(); j++)
		//{
		//	if ((fd_diff[j] - d_mean)*(fd_diff[j] - d_mean) > 3.0 * (d_var * 2 + EPSILON_DEV))
		//	{
		//		pro_i.push_back(-(fd_diff[j] - d_mean)*(fd_diff[j] - d_mean) / (d_var * 2 + EPSILON_DEV));
		//	}
		//	else
		//	{
		//		pro_i.push_back(-3.0f);
		//	}
		//	
		//}
		pro_target_template_new.push_back(pro_i);
	}
	//cout << endl;
	for(size_t i = 0; i < pro_target_template_new.size(); i++)
	{
		float min_value = FLT_MAX;
		float max_value = - FLT_MAX;
		for(size_t j =0; j < pro_target_template_new[i].size(); j++)
		{
			if(min_value > pro_target_template_new[i][j])
			{
				min_value = pro_target_template_new[i][j];
			}
			if(max_value < pro_target_template_new[i][j])
			{
				max_value = pro_target_template_new[i][j];
			}
		}
		//cout <<  min_value <<" " << max_value << endl;
		float total_weight = 0;
		for(size_t j =0; j < pro_target_template_new[i].size(); j++)
		{
			pro_target_template_new[i][j] = exp(pro_target_template_new[i][j] - max_value);
			total_weight += pro_target_template_new[i][j];
		}
		for(size_t j =0; j < pro_target_template_new[i].size(); j++)
		{
			pro_target_template_new[i][j] /= total_weight;
		}
	}
	pro_target_template = pro_target_template_new;
}


float Mean_Field_Deformation::Theta(Sample &shape_sample_1, Sample &shape_sample_2, int is_same)
{
	float diff = 0;
	vec3 pos_diff = shape_sample_1.position - shape_sample_2.position;
	vector<float> feature_diff = FeatureDiff(shape_sample_1, shape_sample_2);
	float diff_fea = 0;
	for(size_t i = 0; i < feature_diff.size() ; i++)
	{
		diff += feature_diff[i]* feature_diff[i]/sigma_6[i];
		diff_fea += feature_diff[i] * feature_diff[i];
	}
	//diff_fea = sqrt(diff_fea);
	//diff = (diff_fea - sigma_dis_4) * (diff_fea - sigma_dis_4) / (var_4 + EPSILON_DEV);
	//diff = diff_fea/sigma_dis_4;
	diff*= -0.5;
	if(diff < THETATHRESHOLD)
	{
		diff  = THETATHRESHOLD;
	}
	if(is_same == 1)
	{
		return exp(diff);
	}
	else
	{
		return 1-exp(diff);
	}
}

float Mean_Field_Deformation::EvaluateErr(int with_seg) // 0 for initial err, other for total
{
	float total_err = 0;
	if( with_seg == 0)
	{
		for(size_t i = 0; i < matching_targte_template.size(); i++)
		{
			for(size_t j = 0; j <  matching_targte_template[i].size(); j++)
			{

				vec3 pos_diff =  target_sample[i].position - template_sample[matching_targte_template[i][j]].position;
				total_err += (pos_diff[0] * pos_diff[0])/sigma_1[0];
				total_err += (pos_diff[1] * pos_diff[1])/sigma_1[1];
				total_err += (pos_diff[2] * pos_diff[2])/sigma_1[2];
				vector<float> fea_diff = FeatureDiff( target_sample[i], template_sample[matching_targte_template[i][j]]);
				for(size_t f = 0; f < sigma_2.size(); f++)
				{
					if(sigma_2[f] > 0.01)
					{
						total_err += fea_diff[f]*fea_diff[f]/sigma_2[f];
					}
				}
			}
		}
		/*for(size_t i = 0; i < target_sample.size(); i++)
		{
		for(size_t j = 0; j < matching_target_target[i].size(); j++)
		{
		int index_near = matching_target_target[i][j];
		for(size_t ki = 0; ki < matching_targte_template[i].size(); ki++)
		{
		int sample_ki = matching_targte_template[i][ki];
		for(size_t kj = 0 ; kj < matching_targte_template[index_near].size(); kj++)
		{
		vector<float> diff__v = FeatureDiff( target_sample[i], target_sample[index_near]);
		vector<float> diff_k = FeatureDiff( template_sample[ki], template_sample[kj]);
		for(size_t f = 0; f < sigma_4.size(); f++)
		{
		if(sigma_4[f] > 0.01)
		{
		total_err += (diff__v[f] - diff_k[f])*(diff__v[f] - diff_k[f])/sigma_4[f];
		}
		}
		}
		}
		}
		}*/
	}
	else
	{

	}
	return total_err  ;
}


void Mean_Field_Deformation::UpdateFeature()
{
	ReNormal(template_sample);
	//Compute_Feature feature_template(template_sample);
	//template_sample = feature_template.GetFeaturedSample(); 

}


void Mean_Field_Deformation::TestTemplateSample(string mesh_out,string shape_out)
{
	Initial();
	FindNeighbor();
	SetInitialSigmaValue();
	////FindNeighbor();	
	for(int ite = 0; ite < 6 ; ite ++)
	{		
	    UpdataShapeTemplateMatching();
		UpdataTemplateShapeMatching();
		UpdateSegnmenatation();
		//VisualSeg(ite);
	   for(size_t i = 0; i < 10; i++)
		{
			UpdatePosition(i);
			//VisualDeform(ite, i);
		} 
		//UpdateFeature();
	    //template_connection=  BulitConnectionByGroup(template_sample);
		FindNeighbor();	
		UpdateSigma();
	}

	for (size_t i = 0; i < target_sample.size(); i++)
	{
		float max_pro = FLT_MIN;
		float min_pro = FLT_MAX;
		int seg_id = -1;
		for (size_t j = 0; j < pro_target_seg[i].size() - 1; j++)
		{
			if (max_pro < pro_target_seg[i][j])
			{
				max_pro = pro_target_seg[i][j];
				seg_id = j;
			}
		}
		target_sample[i].face_id = seg_id;
	}
}

void Mean_Field_Deformation::ReNormal(vector<Sample> &sample_list)
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
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(100);
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


void Mean_Field_Deformation::VisualDeform(int ite1, int ite2)
{
	string file_name("deform_");
	if(ite1 < 10)
	{
		file_name.append(to_string(0));
	}
	file_name.append(to_string(ite1));
	file_name.append("_");
	if(ite2 < 10)
	{
		file_name.append(to_string(0));
	}
	file_name.append(to_string(ite2));
	file_name.append(".ply");
	ofstream fout2(file_name);
	fout2 << "ply" << endl;
	fout2 << "format ascii 1.0" << endl;
	fout2 << "element vertex " << template_sample.size() << endl;
	fout2 << "property float32 x" << endl;
	fout2 << "property float32 y" << endl;
	fout2 << "property float32 z" << endl;
	fout2 << "property float32 nx" << endl;
	fout2 << "property float32 ny" << endl;
	fout2 << "property float32 nz" << endl;
	fout2 << "property uchar red" << endl;
	fout2 << "property uchar green" << endl;
	fout2 << "property uchar blue" << endl;
	fout2 << "element face 0" << endl;
	fout2 << "property list uint8 int32 vertex_index" << endl;
	fout2 << "end_header" << endl;
	for(size_t i = 0; i < template_sample.size(); i++)
	{
		ivec3 color = color_list[template_sample[i].face_id];
		fout2 << template_sample[i].position[0] << " " << (template_sample[i].position[1]) << " " << (template_sample[i].position[2]) << " ";
		fout2 << template_sample[i].normal[0] << " " << template_sample[i].normal[1] << " " << template_sample[i].normal[2] << " ";
		fout2 << (int)color[0] << " " << (int)color[1] << " " << (int)color[2] << endl;
	}
}

void Mean_Field_Deformation::VisualSeg(int ite)
{
	string file_name("seg_");
	file_name.append(to_string(ite));
	file_name.append(".ply");
	ofstream fout(file_name);
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
	for(size_t i = 0; i < target_sample.size(); i++)
	{
		float max_pro = FLT_MIN;
		float min_pro = FLT_MAX;
		int seg_id = -1;
		ivec3 color(255,255,0);
		for(size_t j = 0; j < pro_target_seg[i].size() - 1 ; j++)
		{
			if(max_pro < pro_target_seg[i][j])
			{
				max_pro = pro_target_seg[i][j];
				seg_id = j;
			}
		}
		color = color_list[seg_id];
		fout << target_sample[i].position[0] << " " << (target_sample[i].position[1]) << " " << (target_sample[i].position[2]) << " ";
		fout << target_sample[i].normal[0] << " " << target_sample[i].normal[1] << " " << target_sample[i].normal[2] << " ";
		fout << color[0] << " " << color[1] << " " << color[2] << endl;
	}
}

vector<vector<int>> Mean_Field_Deformation::BulitConnectionByGroup(vector<Sample> sample_list)
{
	vector<vector<int>> connection;
	connection.clear();
	int kNum = 100;
	vector<NamedPoint> points;
	for (size_t i = 0; i < sample_list.size(); i++)
	{
		points.push_back(NamedPoint(sample_list[i].position[0], sample_list[i].position[1], sample_list[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for (size_t i = 0; i< sample_list.size(); i++)
	{
		vector<int> s_c;
		s_c.clear();
		vec3 p = sample_list[i].position;
		NamedPoint query(p[0], p[1], p[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		for (int k = 1; k < kNum; k++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[k].getIndex()].id;
			if (sample_list[i].face_id == sample_list[nearest_id].face_id && s_c.size() < 10 && nearest_id != i)
			{
				s_c.push_back(nearest_id);
			}
			if (s_c.size() == 10)
			{
				break;
			}
		}

		connection.push_back(s_c);
	}

	return connection;
}

void Mean_Field_Deformation::getfeatureVar(vector<float> feature, float &mean, float &var)
{
	mean = 0;
	for (size_t i = 0; i < feature.size(); i++)
	{
		mean += feature[i];
	}
	mean /= feature.size();
	var = 0;
	for (size_t i = 0; i < feature.size(); i++)
	{
		var += (feature[i] - mean) * (feature[i] - mean);
	}
	var /= feature.size();
}