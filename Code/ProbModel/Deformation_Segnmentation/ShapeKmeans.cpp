#include "ShapeKmeans.h"


ShapeKmeans::ShapeKmeans(void)
{
}


ShapeKmeans::~ShapeKmeans(void)
{
}

ShapeKmeans::ShapeKmeans(vector<vector<float>> sample, int k)
{
	sample_list = sample;
	k_size = k;
}

void ShapeKmeans::Initial()
{
	/*vector<float> c_max;
	c_max.resize(sample_list[0].size(),FLT_MIN);
	vector<float> c_min;
	c_min.resize(sample_list[0].size(),FLT_MAX);
	for(size_t i = 0; i < sample_list.size(); i++)
	{
		for(size_t j  = 0; j < sample_list[i].size(); j++)
		{
			if(c_max[j] < sample_list[i][j])
			{
				c_max[j] = sample_list[i][j];
			}
			if(c_min[j] > sample_list[i][j])
			{
				c_min[j] = sample_list[i][j];
			}
		}
	}
	center_sample.clear();
	for(int i = 0; i < k_size; i++)
	{
		vector<float> center;
		center.resize(sample_list[0].size(),0);
		for(size_t j = 0; j < center.size(); j++)
		{
			center[j] = c_min[j] + (c_max[j] - c_min[j])*(float((i+1)))/(float(k_size));
		}
		center_sample.push_back(center);
	}*/
	/*center_sample.clear();
	for(int i = 0; i < k_size; i++)
	{
		center_sample.push_back(sample_list[i]);
	}*/
	sample_group.resize(sample_list.size(), -1);
	group_count.resize(k_size,0);
	for(size_t i = 0; i < sample_list.size(); i++)
	{
		int g_id = i % k_size;
		sample_group[i] = g_id;
		group_count[g_id]++;
	}
	
}

float ShapeKmeans::Distance(vector<float> p1, vector<float> p2)
{
	float dis = 0;
	for(size_t i = 0; i < p1.size(); i++)
	{
		dis += (p1[i]-p2[i])*(p1[i]-p2[i]);
	}
	return dis;
}

int ShapeKmeans::FindClose()
{
	for(int i = 0; i < k_size; i++)
	{
		group_count[i] = 0;;
	}
	int change_count = 0;
	vector<int> group_old = sample_group;
	//sample_group.clear();
	//sample_group.resize(sample_list.size(), -1);
	//group_count.resize(k_size,0);
	for(size_t i = 0; i < sample_list.size(); i++)
	{
		float min_dis = FLT_MAX;
		int group_p = -1;
		for(size_t k = 0; k < k_size; k++)
		{
			if(Distance(sample_list[i], center_sample[k]) < min_dis)
			{
				min_dis = Distance(sample_list[i], center_sample[k]);
				group_p = k;
			}
		}
		sample_group[i] = group_p ;
		if(sample_group[i] != group_old[i])
		{
			change_count++;
		}

		group_count[group_p]++;
	}
	return change_count;
}

void ShapeKmeans::UpdataMean()
{
	center_sample.clear();
	for(int i = 0; i < k_size; i++)
	{
		vector<float> center;
		center.resize(sample_list[0].size(), 0);
		center_sample.push_back(center);
	}
	
	for(size_t i = 0; i < sample_list.size(); i++)
	{
		for(size_t j = 0; j < sample_list[i].size(); j++)
		{
			center_sample[sample_group[i]][j] += sample_list[i][j];
		}
		
	}

	for(int i = 0; i < k_size; i++)
	{
		for(size_t j = 0; j < center_sample[i].size(); j++)
		{
			center_sample[i][j] /= group_count[i];
		}
	}
	for(int i = 0; i < k_size; i++)
	{
		cout << " group " << i <<" "<< group_count[i] << endl;
	}
}

vector<int> ShapeKmeans::RunKmean()
{
	Initial();
	int change = 1;
	while(change !=0)
	{
	   cout << "begin update " << endl;
       UpdataMean();
	   cout << "begin FindClose " << endl;
	   change = FindClose();
	   cout << change << endl;
	}
	
	//FindClose();
	return sample_group;
}