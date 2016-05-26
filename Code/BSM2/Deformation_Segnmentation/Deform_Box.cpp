#include "Deform_Box.h"


Deform_Box::Deform_Box(void)
{

}


Deform_Box::~Deform_Box(void)
{

}

void Deform_Box::GetConnection(vector<vector<int>> connection)
{
	connection_box = connection;
}

void Deform_Box::GetPoints(vector<Sample> box, vector<Sample> shape)
{
	box_sample = box;
	shape_sample = shape;
	shape_refine_sample = shape;
}

void Deform_Box::Find_Soft_Map()
{
	soft_map_near.clear();
	for(size_t i = 0;i < box_sample.size();i++)
	{
		vector<int> near_id;
		near_id.clear();
		soft_map_near.push_back(near_id);
	}

	float average_dis = 0;
	int k = 100;
	vector<NamedPoint> points;
	for (size_t i = 0; i < box_sample.size(); i++)
	{
		points.push_back( NamedPoint( box_sample[i].position[0], box_sample[i].position[1], box_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < shape_refine_sample.size();i++)
	{
		vector<int> near;
		near.clear();
		NamedPoint query( shape_refine_sample[i].position[0], shape_refine_sample[i].position[1], shape_refine_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for(size_t ind = 0; ind< k; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;

			if( (box_sample[nearest_id].normal DOT shape_refine_sample[i].normal) > 0 || check_normal == 0 )
			{
				near.push_back(nearest_id);
			}
		}
		if( near.size()>= 6)
		{
			int nearest_point_id = near[0];
			average_dis += dist(box_sample[nearest_point_id].position,shape_refine_sample[i].position);
			for(size_t ind = 0; ind< 6; ind++)
			{
				soft_map_near[near[ind]].push_back(i);
			}
		}
		else
		{
			if(check_normal == 0)
			{
				int nearest_point_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
				average_dis += dist(box_sample[nearest_point_id].position,shape_refine_sample[i].position);
				for(size_t ind = 0; ind< 6; ind++)
				{
					int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
					soft_map_near[nearest_id].push_back(i);
				}
			}
		}


	}
	average_dis /= shape_sample.size();
	float stand_dev = 0.5*average_dis;
	cout << "dev " << stand_dev <<endl;
	vector<float> sum_weight;
	sum_weight.resize(box_sample.size(),0);
	for(size_t i = 0; i< soft_map_near.size(); i++)
	{
		vector<float> weight_t;
		weight_t.clear();
		for(size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			float dis = dist(box_sample[i].position, shape_refine_sample[soft_map_near[i][j]].position);
			float weight = exp(-(dis - average_dis) * (dis - average_dis) /(2 * stand_dev *  stand_dev));
			sum_weight[i] += weight;
			weight_t.push_back(weight);
		}
		soft_map_weight.push_back(weight_t);
	}
	// normalize
	for(size_t i = 0; i< soft_map_weight.size(); i++)
	{
		for(size_t j = 0; j < soft_map_weight[i].size(); j++)
		{
			soft_map_weight[i][j] /= sum_weight[i];
		}	
	}

}

void Deform_Box::Deform_Soft(float smooth, float data)
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
	int nr_cols = box_sample.size();
	for(size_t i = 0; i< soft_map_near.size(); i++)
	{
		for(size_t j = 0; j < soft_map_near[i].size(); j++)
		{
			if(soft_map_weight[i][j] > 0.001)
			{
				LapMat.push_back(map<int,double>());
				(LapMat.back())[i] = soft_map_weight[i][j] * weight_position ;
				vec3 match_p = shape_sample[soft_map_near[i][j]].position;
				for(int jj=0;jj<3;jj++) 
				{
					LapB[jj].push_back(match_p[jj] * weight_position * soft_map_weight[i][j]);
				}
			}

		}

		if(soft_map_near[i].size() == 0)
		{
			for(size_t j = 0; j < soft_map_near_t[i].size(); j++)
			{
				if(soft_map_weight_t[i][j] > 0.001)
				{
					LapMat.push_back(map<int,double>());
					(LapMat.back())[i] = soft_map_weight_t[i][j] * 1.0f;
					vec3 match_p = shape_sample[soft_map_near_t[i][j]].position;
					for(int jj=0;jj<3;jj++) 
					{
						LapB[jj].push_back(match_p[jj] * 1.0f * soft_map_weight_t[i][j]);
					}
				}
			}
		}

	}
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
	}
}

void Deform_Box::Find_Soft_Map_T()
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
	int k = 100; // number of nearest neighbors
	if( k > shape_refine_sample.size())
	{
		k = shape_refine_sample.size();
	}
	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_refine_sample.size(); i++)
	{
		points.push_back( NamedPoint( shape_refine_sample[i].position[0], shape_refine_sample[i].position[1], shape_refine_sample[i].position[2], i ) );
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
			if( (box_sample[i].normal DOT shape_refine_sample[nearest_id].normal) > 0 || check_normal == 0)
			{
				near_id.push_back(nearest_id);
			}
		}
		if( near_id.size()>= 6)
		{
			//int nearest_point_id = near_id[0];
			//average_dis += dist(box_sample[nearest_point_id].position,shape_refine_sample[i].position);
			for(size_t ind = 0; ind< 6; ind++)
			{
				int nearest_id = near_id[ind];
				soft_map_near_t[i].push_back(nearest_id);
				aterage_dis[i] += dist(shape_refine_sample[nearest_id].position,box_sample[i].position) / 6;
			}
		}
		else
		{
			if(check_normal == 0)
			{
				for(size_t ind = 0; ind< 6; ind++)
				{
					int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
					soft_map_near_t[i].push_back(nearest_id);
					aterage_dis[i] += dist(shape_refine_sample[nearest_id].position,box_sample[i].position) / 6;

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
	for(size_t i = 0; i< soft_map_near_t.size(); i++)
	{
		average_dis = aterage_dis[i];
		float stand_dev = 0.5*average_dis;
		vector<float> weight_t;
		weight_t.clear();
		for(size_t j = 0; j < soft_map_near_t[i].size(); j++)
		{
			float dis = dist(box_sample[i].position, shape_refine_sample[soft_map_near_t[i][j]].position);
			float weight = exp(-(dis - average_dis) * (dis - average_dis) /(2 * stand_dev *  stand_dev));
			sum_weight[i] += weight;
			weight_t.push_back(weight);
		}
		soft_map_weight_t.push_back(weight_t);
	}
	// normalize
	for(size_t i = 0; i< soft_map_weight_t.size(); i++)
	{
		for(size_t j = 0; j < soft_map_weight_t[i].size(); j++)
		{
			soft_map_weight_t[i][j] /= sum_weight[i];
		}	
	}
}

void Deform_Box::BulidShapeConnection()
{
	shape_connection.clear();
	//build kd tree
	int k = 100; // number of nearest neighbors
	if(k > shape_sample.size())
	{
		k = shape_sample.size();
	}
	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		points.push_back( NamedPoint( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < shape_sample.size();i++)
	{
		vector<int> near;
		near.clear();
		vector<int> near_id;
		near_id.clear();
		NamedPoint query( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed

		for(size_t ind = 0; ind< k; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			if(abs(shape_sample[nearest_id].normal DOT shape_sample[i].normal) > 0 && nearest_id != i )
			{
				near.push_back(nearest_id);
			}
		}
		if( near.size()>= 6)
		{
			for(size_t ind = 0; ind< 6; ind++)
			{
				near_id.push_back(near[ind]);
			}
		}
		else
		{
			for(size_t ind = 0; ind< 6; ind++)
			{
				int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
				if(nearest_id != i)
				{
					near_id.push_back(nearest_id);
				}
			}
		}


		shape_connection.push_back(near_id);
	}

	// get lapalican 

	shape_lapalican.clear();
	for(size_t i = 0; i< shape_sample.size(); i++)
	{
		vec3 l_i = shape_sample[i].position;
		for(size_t j =0; j< shape_connection[i].size();j++)
		{
			int near_id = shape_connection[i][j];
			l_i = l_i - shape_sample[near_id].position * (1.0f /shape_connection[i].size());
		}
		shape_lapalican.push_back(l_i);
	}
}

void Deform_Box::GetMatchPoint()
{
	match_point.clear();
	vector<NamedPoint> points;
	for (size_t i = 0; i < box_sample.size(); i++)
	{
		points.push_back( NamedPoint( box_sample[i].position[0], box_sample[i].position[1], box_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());

	for(size_t i = 0;i < shape_sample.size();i++)
	{
		vector<int> near_id;
		near_id.clear();
		NamedPoint query( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(100);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		int is_find_match = 0;
		for(int ind = 0 ; ind < 100; ind++ )
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			if( (box_sample[nearest_id].normal DOT shape_sample[i].normal) > 0 || check_normal == 0)
			{
				match_point.push_back(box_sample[nearest_id].position);
				is_find_match = 1;
				break;
			}
		}

		if(is_find_match == 0)
		{
			int nearest_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
			match_point.push_back(box_sample[nearest_id].position);
		}

	}

}

void Deform_Box::Refine()
{
	/*ofstream fout("shape_sample_before.ply") ;
	fout << "ply" << endl;
	fout << "format ascii 1.0" << endl;
	fout << "element vertex " << shape_sample.size() << endl;
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
	for(size_t i=0;i< shape_sample.size();i++)
	{
	//	cout <<box_sample[i][0]<<" "<<box_sample[i][1]<<" "<<box_sample[i][2] <<endl;
	fout<<shape_sample[i].position[0]<<" "<<shape_sample[i].position[1]<<" "<<shape_sample[i].position[2]<<" "<< 0 <<" "<< 0 <<" "<< 1 <<" "<< 255 <<" "<< 0 <<" "<< 0 <<endl;
	}*/
	cout << "begin bulid" <<endl;
	BulidShapeConnection();
	cout << "end bulid" <<endl;
	GetMatchPoint();
	float weight_lapcican = 2.0 ;
	float weight_position = 1.0 ;
	/*if(ite > 2)
	{
	weight_lapcican = 10.0 ;
	weight_position = 20.0 ;
	}*/
	vector<map<int,double> >  LapMat;
	vector<vector<double> >	  LapB;
	LapB.resize(3);
	for(size_t i = 0; i< shape_sample.size(); i++)
	{
		LapMat.push_back(map<int,double>());
		LapMat[i][i] = 1.0f * weight_lapcican ;
		for(int j=0;j<3;j++) 
		{
			LapB[j].push_back(shape_lapalican[i][j] * weight_lapcican );
		}
		for(size_t j =0; j< shape_connection[i].size();j++)
		{
			int near_id = shape_connection[i][j];
			LapMat[i][near_id ] = -1.0f/shape_connection[i].size() * weight_lapcican ;
		}
	}
	int nr_cols = LapMat.size();
	for(size_t i = 0; i< shape_sample.size(); i++)
	{   

		LapMat.push_back(map<int,double>());
		(LapMat.back())[i] = 1 * weight_position ;
		vec3 match_p = match_point[i];
		for(int j=0;j<3;j++) 
		{
			LapB[j].push_back(match_p[j] * weight_position );
		}
	}
	LeastSquaresSparseSolver solver;
	solver.Init(LapMat,nr_cols);
	vector<vector<double> > eRes;
	solver.Solve(LapB,eRes);
	//Shape_Refine = shape_sample;
	for (int i=0; i< nr_cols; i++)
	{

		for (int j=0;j<3;j++)
		{
			shape_refine_sample[i].position[j] = eRes[j][i]; 
		}	

	}
	/*ofstream  fout1("shape_sample_after.ply") ;
	fout1 << "ply" << endl;
	fout1 << "format ascii 1.0" << endl;
	fout1 << "element vertex " << shape_refine_sample.size() << endl;
	fout1 << "property float32 x" << endl;
	fout1 << "property float32 y" << endl;
	fout1 << "property float32 z" << endl;
	fout1 << "property float32 nx" << endl;
	fout1 << "property float32 ny" << endl;
	fout1 << "property float32 nz" << endl;
	fout1 << "property uchar red" << endl;
	fout1 << "property uchar green" << endl;
	fout1 << "property uchar blue" << endl;
	fout1 << "element face 0" << endl;
	fout1 << "property list uint8 int32 vertex_index" << endl;
	fout1 << "end_header" << endl;
	for(size_t i=0;i< shape_refine_sample.size();i++)
	{
	//	cout <<box_sample[i][0]<<" "<<box_sample[i][1]<<" "<<box_sample[i][2] <<endl;
	fout1<< shape_refine_sample [i].position[0]<<" "<< shape_refine_sample[i].position[1]<<" "<<shape_refine_sample[i].position[2]<<" "<< 0 <<" "<< 0 <<" "<< 1 <<" "<< 255 <<" "<< 255 <<" "<< 0 <<endl;
	}*/

}
