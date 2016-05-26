#include "Deform_Box_New.h"


Deform_Box_New::Deform_Box_New(void)
{
	near_point = 20;
}


Deform_Box_New::~Deform_Box_New(void)
{

}

void Deform_Box_New::GetConnection(vector<vector<int>> connection)
{
	connection_box = connection;
}

void Deform_Box_New::GetPoints(vector<Sample> box, vector<Sample> shape)
{
	box_sample = box;
	shape_sample = shape;
	cout << "get point " << shape_sample.size() << endl;
}

void Deform_Box_New::Find_Soft_Map_new()
{
	SetDisThresh();
	dis_thread_hold *= 2.0f;
	soft_map_near.clear();
	cout << "get point " << shape_sample.size() << endl;
	for(size_t i = 0;i < shape_sample.size();i++)
	{
		vector<int> near_id;
		near_id.clear();
		soft_map_near.push_back(near_id);
	}

	float average_dis = 0;
	int k = 20;
	int count = 0;
	vector<NamedPoint> points;
	for (size_t i = 0; i < box_sample.size(); i++)
	{
		points.push_back( NamedPoint( box_sample[i].position[0], box_sample[i].position[1], box_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < shape_sample.size();i++)
	{
		vector<int> near;
		near.clear();
		NamedPoint query( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for(size_t ind = 0; ind< k; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;

			if( (box_sample[nearest_id].normal DOT shape_sample[i].normal) > 0 || check_normal == 0 )
			{
				near.push_back(nearest_id);
			}
		}
		if(near.size() > 0)
		{
			int nearest_point_id = near[0];	
			float near_dis  = dist(box_sample[nearest_point_id].position,shape_sample[i].position);
			if(near_dis >  2.0f * dis_thread_hold)
			{
				average_dis += near_dis;
				count++;
				for(size_t ind = 0; ind< near.size(); ind++)
				{	
					if(ind < near_point)
					{
						soft_map_near[i].push_back(near[ind]);
					}
				}
			}
		}
	}
	average_dis /= count;
	float stand_dev = 0.5*average_dis;
	//float stand_dev = dis_thread_hold;
	cout << "dev " << stand_dev <<endl;
	vector<float> sum_weight;
	sum_weight.resize(shape_sample.size(),0);
	cout << "begin weight" << endl;
	for(size_t i = 0; i< soft_map_near.size(); i++)
	{
		vector<float> weight_t;
		weight_t.clear();
		for(size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			//cout << soft_map_near[i].size() << endl;
			float dis = dist(shape_sample[i].position, box_sample[soft_map_near[i][j]].position);
			//cout << "dis "<< dis << endl;
			float weight = exp(-(dis - average_dis) * (dis - average_dis) /(2 * stand_dev *  stand_dev));
			//cout << "weight" << weight << endl;
			sum_weight[i] += weight;
			weight_t.push_back(weight);
		}
		soft_map_weight.push_back(weight_t);
	}
	cout << "end weight" << endl;
	// normalize
	for(size_t i = 0; i< soft_map_weight.size(); i++)
	{
		for(size_t j = 0; j < soft_map_weight[i].size(); j++)
		{
			if(sum_weight[i] < 1e-6)
			{
				soft_map_weight[i][j] = 0;
			}
			else
			{
				soft_map_weight[i][j] /= sum_weight[i];
			}
		}	
	}
	cout << "end normalize" << endl;
	
}

void Deform_Box_New::Find_Soft_Map()
{
	SetDisThresh();
	dis_thread_hold = 2.0f;
	soft_map_near.clear();
	cout << "get point " << shape_sample.size() << endl;
	for(size_t i = 0;i < shape_sample.size();i++)
	{
		vector<int> near_id;
		near_id.clear();
		soft_map_near.push_back(near_id);
	}

	float average_dis = 0;
	int k = 50;
	vector<NamedPoint> points;
	for (size_t i = 0; i < box_sample.size(); i++)
	{
		points.push_back( NamedPoint( box_sample[i].position[0], box_sample[i].position[1], box_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < shape_sample.size();i++)
	{
		vector<int> near;
		near.clear();
		NamedPoint query( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for(size_t ind = 0; ind< k; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;

			if( (box_sample[nearest_id].normal DOT shape_sample[i].normal) > 0 || check_normal == 0 )
			{
				near.push_back(nearest_id);
			}
		}
		if( near.size()>= near_point)
		{
			int nearest_point_id = near[0];
			average_dis += dist(box_sample[nearest_point_id].position,shape_sample[i].position);
			//cout <<"average_dis" <<  dist(box_sample[nearest_point_id].position, shape_sample[i].position) << endl;
			for(size_t ind = 0; ind< near_point; ind++)
			{
				if(dist(box_sample[near[ind]].position,shape_sample[i].position) < 2.0f * dis_thread_hold)
				{
					soft_map_near[i].push_back(near[ind]);
				}
			}
		}
		else
		{
			if(check_normal == 0)
			{
				int nearest_point_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
				average_dis += dist(box_sample[nearest_point_id].position,shape_sample[i].position);
				for(size_t ind = 0; ind< near_point; ind++)
				{
					int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
					/*
					soft_map_near[i].push_back(near[ind]); */

					if(dist(box_sample[nearest_id].position,shape_sample[i].position) < 2.0f * dis_thread_hold)
					{
						soft_map_near[i].push_back(near[ind]);
					}
				}
			}
		}


	}
	average_dis /= shape_sample.size();
	float stand_dev = 0.5*average_dis;
	//stand_dev = 0.5*dis_thread_hold;
	cout << "dev " << stand_dev <<endl;
	vector<float> sum_weight;
	sum_weight.resize(shape_sample.size(),0);
	cout << "begin weight" << endl;
	for(size_t i = 0; i< soft_map_near.size(); i++)
	{
		vector<float> weight_t;
		weight_t.clear();
		for(size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			float dis = dist(shape_sample[i].position, box_sample[soft_map_near[i][j]].position);
			float weight = exp(-(dis - average_dis) * (dis - average_dis) /(2 * stand_dev *  stand_dev));
			//cout << "weight " << weight << endl;
			sum_weight[i] += weight;
			weight_t.push_back(weight);
		}
		soft_map_weight.push_back(weight_t);
	}
	cout << "end weight" << endl;
	// normalize
	for (size_t i = 0; i < soft_map_weight.size(); i++)
	{	
			for (size_t j = 0; j < soft_map_weight[i].size(); j++)
			{
				soft_map_weight[i][j] /= sum_weight[i];
			}

	}
	cout << "end normalize" << endl;
	
}

void Deform_Box_New::Find_Soft_Map_T()
{
	soft_map_near_t.clear();
	soft_map_weight_t.clear();
	for(size_t i = 0;i < box_sample.size();i++)
	{
		vector<int> near_id;
		near_id.clear();
		soft_map_near_t.push_back(near_id);
	}
	float average_dis = 0;
	vector<float> aterage_dis;
	aterage_dis.resize(box_sample.size(),0);
	int k = 50; // number of nearest neighbors
	if( k > shape_sample.size())
	{
		k = shape_sample.size();
	}
	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		points.push_back( NamedPoint( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < box_sample.size();i++)
	{
		vector<int> near_id;
		near_id.clear();
		NamedPoint query( box_sample[i].position[0], box_sample[i].position[1], box_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for(size_t ind = 0; ind< k; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			if( (box_sample[i].normal DOT shape_sample[nearest_id].normal) > 0 || check_normal == 0)
			{
				near_id.push_back(nearest_id);
			}
		}
		if( near_id.size()>= near_point)
		{
			//int nearest_point_id = near_id[0];
			//average_dis += dist(box_sample[nearest_point_id].position,shape_refine_sample[i].position);
			for(size_t ind = 0; ind< near_point; ind++)
			{
				int nearest_id = near_id[ind];
				soft_map_near_t[i].push_back(nearest_id);
				aterage_dis[i] += dist(shape_sample[nearest_id].position,box_sample[i].position) / near_point;
				//cout << "aterage_dis[i]" << dist(shape_sample[nearest_id].position, box_sample[i].position) / near_point << endl;
			}
		}
		else
		{
			if(check_normal == 0)
			{
				for(size_t ind = 0; ind< near_point; ind++)
				{
					int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
					soft_map_near_t[i].push_back(nearest_id);
					aterage_dis[i] += dist(shape_sample[nearest_id].position,box_sample[i].position) / near_point;
					//cout << "aterage_dis[i]" << dist(shape_sample[nearest_id].position, box_sample[i].position) / near_point << endl;
				}
			}
		}

		//int nearest_point_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
		//average_dis += dist(shape_refine_sample[nearest_point_id].position,box_sample[i].position);	
	}

	//average_dis /= shape_sample.size();
	//float stand_dev = 0.5*average_dis;
	//cout << "dev " << stand_dev <<endl;
	vector<float> sum_weight;
	sum_weight.resize(box_sample.size(),0);
	for (size_t i = 0; i < soft_map_near_t.size(); i++)
	{
		average_dis = aterage_dis[i];
		float stand_dev = 0.5*average_dis;
		//stand_dev = 0.5*dis_thread_hold;
		//cout << stand_dev << endl;
		vector<float> weight_t;
		weight_t.clear();

		for (size_t j = 0; j < soft_map_near_t[i].size(); j++)
		{
			float dis = dist(box_sample[i].position, shape_sample[soft_map_near_t[i][j]].position);
			float weight = exp(-(dis - average_dis) * (dis - average_dis) / (2 * stand_dev *  stand_dev));
			//cout << "weight " << weight << endl;
			sum_weight[i] += weight;
			weight_t.push_back(weight);
		}

		soft_map_weight_t.push_back(weight_t);
	}
	// normalize
	for(size_t i = 0; i< soft_map_weight_t.size(); i++)
	{
			for (size_t j = 0; j < soft_map_weight_t[i].size(); j++)
			{
				soft_map_weight_t[i][j] /= sum_weight[i];
			}		
	}
}

void Deform_Box_New::DeformToShape(float smooth, float data)
{
	float weight_lapcican = smooth ;
	float weight_position =  data ;
	vector<map<int,double> >  LapMat;
	vector<vector<double> >	  LapB;
	LapB.resize(3);
	for(size_t i = 0; i< box_sample.size(); i++)
	{
		for(size_t j =0; j< connection_box[i].size();j++)
		{
			LapMat.push_back(map<int,double>());
			(LapMat.back())[i] = weight_lapcican ;
			int near_id = connection_box[i][j];
			(LapMat.back())[near_id ] = - weight_lapcican ;
			vec3 match_p = box_sample[i].position - box_sample[near_id].position;
			for(int j=0;j<3;j++) 
			{
				LapB[j].push_back(match_p[j] * weight_lapcican );
			}
		}
	}
	cout << "finish part 1" << endl;
	int nr_cols = box_sample.size();
	for(size_t i = 0; i< box_sample.size(); i++)
	{
		LapMat.push_back(map<int,double>());
		(LapMat.back())[i] = weight_lapcican ;
		vec3 match_p = box_sample[i].position;
		for(int j=0;j<3;j++) 
		{
			LapB[j].push_back(match_p[j] * weight_lapcican );
		}
	}
	for(size_t i = 0; i< soft_map_near.size(); i++)
	{
		for(size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			if(soft_map_weight[i][j] > 0.001)
			{
				LapMat.push_back(map<int,double>());
				(LapMat.back())[soft_map_near[i][j]] = soft_map_weight[i][j] * weight_position *5.0f;
				vec3 match_p = shape_sample[i].position;
				for(int jj=0;jj<3;jj++) 
				{
					LapB[jj].push_back(match_p[jj] * weight_position * soft_map_weight[i][j]*5.0f);
				}
			}

		}

	}
	cout << "finish part 3" << endl;

	LeastSquaresSparseSolver solver;
	solver.Init(LapMat,nr_cols);
	vector<vector<double> > eRes;
	solver.Solve(LapB,eRes);
	deform_box_sample = box_sample;
	for (int i=0; i< nr_cols; i++)
	{		
		for (int j=0;j<3;j++)
		{
			deform_box_sample[i].position[j] = eRes[j][i]; 
			
		}	

		//cout << endl;
	}
	cout << "finish part 4" << endl;
}

void Deform_Box_New::Deform_Soft(float smooth, float data)
{
	cout << "out 1 " << endl;
	float weight_lapcican = smooth ;
	float weight_position =  data ;
	vector<map<int,double> >  LapMat;
	vector<vector<double> >	  LapB;
	LapB.resize(3);
	for(size_t i = 0; i< box_sample.size(); i++)
	{
		for(size_t j =0; j< connection_box[i].size();j++)
		{
			LapMat.push_back(map<int,double>());
			(LapMat.back())[i] = weight_lapcican ;
			int near_id = connection_box[i][j];
			(LapMat.back())[near_id ] = - weight_lapcican ;
			vec3 match_p = box_sample[i].position - box_sample[near_id].position;
			for(int j=0;j<3;j++) 
			{
				LapB[j].push_back(match_p[j] * weight_lapcican );
			}
		}
	}
	cout << "finish part 1" << endl;
	int nr_cols = box_sample.size();

	for(size_t i = 0; i< soft_map_near.size(); i++)
	{
		for(size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			if(soft_map_weight[i][j] > 0.001)
			{
				LapMat.push_back(map<int,double>());
				(LapMat.back())[soft_map_near[i][j]] = soft_map_weight[i][j] * weight_position *2.0f;
				vec3 match_p = shape_sample[i].position;
				for(int jj=0;jj<3;jj++) 
				{
					LapB[jj].push_back(match_p[jj] * weight_position * soft_map_weight[i][j] * 2.0f);
				}
			}

		}

	}
	cout << "finish part 2" << endl;
	for(size_t i = 0; i< soft_map_near_t.size(); i++)
	{
		for(size_t j = 0; j < soft_map_near_t[i].size(); j++)
		{
			if(soft_map_weight_t[i][j] > 0.001)
			{
				LapMat.push_back(map<int,double>());
				int shape_id = soft_map_near_t[i][j];
				(LapMat.back())[i] = soft_map_weight_t[i][j] * weight_position;
				vec3 match_p = shape_sample[shape_id].position;
				for(int jj=0;jj<3;jj++) 
				{
					LapB[jj].push_back(match_p[jj] * weight_position * soft_map_weight_t[i][j]) ;
				}
			}

		}

	}
	cout << "finish part 3" << endl;

	LeastSquaresSparseSolver solver;
	solver.Init(LapMat,nr_cols);
	vector<vector<double> > eRes;
	solver.Solve(LapB,eRes);
	deform_box_sample = box_sample;
	for (int i=0; i< nr_cols; i++)
	{		
		for (int j=0;j<3;j++)
		{
			deform_box_sample[i].position[j] = eRes[j][i]; 
			//cout << eRes[j][i];
		}	

		//cout << endl;
	}
	cout << "finish part 4" << endl;
}

void Deform_Box_New::SetDisThresh()
{
	vector<Sample> target_sample;
	vector<Sample> sourse_sample;
	if(box_sample.size() > shape_sample.size())
	{
		target_sample = box_sample;
		sourse_sample = shape_sample;
	}
	else
	{
		target_sample = shape_sample;
		sourse_sample = box_sample;
	}

	dis_thread_hold = 0;

	vector<NamedPoint> points;
	for (size_t i = 0; i < target_sample.size(); i++)
	{
		points.push_back( NamedPoint( target_sample[i].position[0], target_sample[i].position[1], target_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < sourse_sample.size();i++)
	{
		vector<int> near;
		near.clear();
		NamedPoint query( sourse_sample[i].position[0], sourse_sample[i].position[1], sourse_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed

		int nearest_id = stree.getElements()[k_closest_elems[0].getIndex()].id;

		dis_thread_hold += dist(sourse_sample[i].position, target_sample[nearest_id].position);
	}

	dis_thread_hold /= sourse_sample.size();
}