#include "FindNearest.h"
FindNearest::FindNearest(void)
{
}


FindNearest::~FindNearest(void)
{
}

FindNearest::FindNearest(vector<Sample> sourse_sample, vector<Sample> target_sample, int k_size)
{
	s_sample = sourse_sample;
	t_sample = target_sample;
	k_near_size = k_size;
}

vector<vector<int>> FindNearest::FindKnearestByEdistance(int normal_chek)
{
	vector<vector<int>> nearlist;
	nearlist.clear();
	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near_id;
		near_id.clear();
		nearlist.push_back(near_id);
	}
	vector<NamedPoint> points;
	for (size_t i = 0; i < s_sample.size(); i++)
	{
		points.push_back(NamedPoint(s_sample[i].position[0], s_sample[i].position[1], s_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	int k = 2* k_near_size;
	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near;
		near.clear();
		NamedPoint query(t_sample[i].position[0], t_sample[i].position[1], t_sample[i].position[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for (size_t ind = 0; ind< k; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;

			if ((s_sample[nearest_id].normal DOT t_sample[i].normal) > 0 || normal_chek == 0)
			{
				near.push_back(nearest_id);
			}
		}
		if (near.size() >= k_near_size)
		{
			for (size_t ind = 0; ind< k_near_size; ind++)
			{
				nearlist[i].push_back(near[ind]);
			}
		}
		else
		{
			if (normal_chek == 0)
			{
				for (size_t ind = 0; ind< k_near_size; ind++)
				{
					int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
					nearlist[i].push_back(nearest_id);
				}
			}
		}
	}
	return nearlist;
}

vector<vector<int>> FindNearest::FindKnearestByFeature()
{
	vector<vector<int>> nearlist;
	nearlist.clear();
	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near_id;
		near_id.clear();
		nearlist.push_back(near_id);
	}
	int k = k_near_size; // number of nearest neighbors 
	int dim = 3 + s_sample[0].sdf.size() + 1;  // pos + sdf + average
	//int dim = 3 + 4 + 1;  // pos + sdf + average
	double eps = 0; // error bound
	int maxPts = s_sample.size();
	int nPts = s_sample.size(); // actual number of data points
	ANNpointArray dataPts; // data points
	ANNpoint queryPt; // query point
	ANNidxArray nnIdx; // near neighbor indices
	ANNdistArray dists; // near neighbor distances
	ANNkd_tree* kdTree; // search structure
	queryPt = annAllocPt(dim); // allocate query point
	dataPts = annAllocPts(maxPts, dim); // allocate data points
	nnIdx = new ANNidx[k]; // allocate near neigh indices
	dists = new ANNdist[k]; // allocate near neighbor dists
	for (size_t i = 0; i< s_sample.size(); i++)
	{
		dataPts[i][0] = s_sample[i].position[0];
		dataPts[i][1] = s_sample[i].position[1];
		dataPts[i][2] = s_sample[i].position[2];
		for(size_t j =0; j < s_sample[i].sdf.size(); j++)
		{
			dataPts[i][3 +j] = s_sample[i].sdf[j];
		}
		dataPts[i][7] = s_sample[i].angel_geo_dis[0];
		/*for(size_t j =0; j < 5 ; j++)
		{
			dataPts[i][3 +j] = s_sample[i].sample_features[j] * 0.2;
		}*/

	}

	kdTree = new ANNkd_tree( // build search structure
		dataPts, // the data points
		nPts, // number of points
		dim); // dimension of space

	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near;
		near.clear();
		queryPt[0] = t_sample[i].position[0];
		queryPt[1] = t_sample[i].position[1];
		queryPt[2] = t_sample[i].position[2];
		for(size_t j =0; j < t_sample[i].sdf.size(); j++)
		{
			queryPt[3 +j] = t_sample[i].sdf[j];
		}
		queryPt[7] = t_sample[i].angel_geo_dis[0];
		/*for(size_t j =0; j < 5; j++)
		{
			queryPt[3 +j] = t_sample[i].sample_features[j]* 0.2;
		}*/
		kdTree->annkSearch( // search
			queryPt, // query point
			k, // number of near neighbors
			nnIdx, // nearest neighbors (returned)
			dists, // distance (returned)
			eps); // error bound
		for(size_t j = 0 ; j < k_near_size; j++)
		{
			near.push_back(nnIdx[j]);
		}
		nearlist[i] = (near);
	}
	annClose();
	if(kdTree)
	{
		delete kdTree;
	}
	return nearlist;
}

vector<vector<int>> FindNearest::FindnearestByDiff()
{
	vector<vector<int>> nearlist;
	nearlist.clear();
	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near_id;
		near_id.clear();
		nearlist.push_back(near_id);
	}
	int k = k_near_size; // number of nearest neighbors 
	int dim = 3 + s_sample[0].diff_feature.size() + s_sample[0].sdf.size() + 1 + 16 ;  // pos + sdf + average
	double eps = 0; // error bound
	int maxPts = s_sample.size();
	int nPts = s_sample.size(); // actual number of data points
	ANNpointArray dataPts; // data points
	ANNpoint queryPt; // query point
	ANNidxArray nnIdx; // near neighbor indices
	ANNdistArray dists; // near neighbor distances
	ANNkd_tree* kdTree; // search structure
	queryPt = annAllocPt(dim); // allocate query point
	dataPts = annAllocPts(maxPts, dim); // allocate data points
	nnIdx = new ANNidx[k]; // allocate near neigh indices
	dists = new ANNdist[k]; // allocate near neighbor dists
	for (size_t i = 0; i< s_sample.size(); i++)
	{
		dataPts[i][0] = s_sample[i].position[0];
		dataPts[i][1] = s_sample[i].position[1];
		dataPts[i][2] = s_sample[i].position[2];
		for(size_t j =0; j < s_sample[i].sdf.size(); j++)
		{
			dataPts[i][3 +j] = s_sample[i].sdf[j];
		}
		dataPts[i][7] = s_sample[i].angel_geo_dis[0];
		for(size_t j = 0; j < 16; j++)
		{
			dataPts[i][8 +j] = s_sample[i].shape_context[j];
		}
		for(size_t j =0; j < s_sample[i].diff_feature.size(); j++)
		{
			dataPts[i][24 +j] = s_sample[i].diff_feature[j];
		}
	}

	kdTree = new ANNkd_tree( // build search structure
		dataPts, // the data points
		nPts, // number of points
		dim); // dimension of space

	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near;
		near.clear();
		queryPt[0] = t_sample[i].position[0];
		queryPt[1] = t_sample[i].position[1];
		queryPt[2] = t_sample[i].position[2];
		for(size_t j =0; j < t_sample[i].sdf.size(); j++)
		{
			queryPt[3 +j] = t_sample[i].sdf[j];
		}
		queryPt[7] = t_sample[i].angel_geo_dis[0];
		for(size_t j =0; j < 16; j++)
		{
			queryPt[8 +j] = t_sample[i].shape_context[j];
		}
		for(size_t j =0; j < t_sample[i].diff_feature.size(); j++)
		{
			queryPt[24 +j] = t_sample[i].diff_feature[j];
		}
		kdTree->annkSearch( // search
			queryPt, // query point
			k, // number of near neighbors
			nnIdx, // nearest neighbors (returned)
			dists, // distance (returned)
			eps); // error bound
		for(size_t j = 0 ; j < k_near_size; j++)
		{
			near.push_back(nnIdx[j]);
		}
		nearlist[i] = (near);
	}
	annClose();
	return nearlist;
}

vector<vector<int>> FindNearest::FindnearestBySC()
{
	vector<vector<int>> nearlist;
	nearlist.clear();
	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near_id;
		near_id.clear();
		nearlist.push_back(near_id);
	}
	int k = k_near_size; // number of nearest neighbors 
	int dim = 3 + s_sample[0].sdf.size() + 1 + 16 + 4;  // pos + sdf + average
	double eps = 0; // error bound
	int maxPts = s_sample.size();
	int nPts = s_sample.size(); // actual number of data points
	ANNpointArray dataPts; // data points
	ANNpoint queryPt; // query point
	ANNidxArray nnIdx; // near neighbor indices
	ANNdistArray dists; // near neighbor distances
	ANNkd_tree* kdTree; // search structure
	queryPt = annAllocPt(dim); // allocate query point
	dataPts = annAllocPts(maxPts, dim); // allocate data points
	nnIdx = new ANNidx[k]; // allocate near neigh indices
	dists = new ANNdist[k]; // allocate near neighbor dists
	for (size_t i = 0; i< s_sample.size(); i++)
	{
		dataPts[i][0] = s_sample[i].position[0];
		dataPts[i][1] = s_sample[i].position[1];
		dataPts[i][2] = s_sample[i].position[2];
		for(size_t j =0; j < s_sample[i].sdf.size(); j++)
		{
			dataPts[i][3 +j] = s_sample[i].sdf[j];
		}
		dataPts[i][7] = s_sample[i].angel_geo_dis[0];
		for(size_t j = 0; j < 16; j++)
		{
			dataPts[i][8 +j] = s_sample[i].shape_context[j];
		}
		dataPts[i][24] = s_sample[i].curvature[0]/5;
		dataPts[i][25] = s_sample[i].curvature[1]/5;
		dataPts[i][26] = s_sample[i].curvature[6]/5;
		dataPts[i][27] = s_sample[i].curvature[7]/10;
	}

	kdTree = new ANNkd_tree( // build search structure
		dataPts, // the data points
		nPts, // number of points
		dim); // dimension of space

	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near;
		near.clear();
		queryPt[0] = t_sample[i].position[0];
		queryPt[1] = t_sample[i].position[1];
		queryPt[2] = t_sample[i].position[2];
		for(size_t j =0; j < t_sample[i].sdf.size(); j++)
		{
			queryPt[3 +j] = t_sample[i].sdf[j];
		}
		queryPt[7] = t_sample[i].angel_geo_dis[0];
		for(size_t j =0; j < 16; j++)
		{
			queryPt[8 +j] = t_sample[i].shape_context[j];
		}
		queryPt[24] = t_sample[i].curvature[0]/5;
		queryPt[25] = t_sample[i].curvature[1]/5;
		queryPt[26] = t_sample[i].curvature[6]/5;
		queryPt[27] = t_sample[i].curvature[7]/10;
		kdTree->annkSearch( // search
			queryPt, // query point
			k, // number of near neighbors
			nnIdx, // nearest neighbors (returned)
			dists, // distance (returned)
			eps); // error bound
		for(size_t j = 0 ; j < k_near_size; j++)
		{
			near.push_back(nnIdx[j]);
		}
		nearlist[i] = (near);
	}
	annClose();
	return nearlist;
}

vector<vector<int>> FindNearest::FindKnearestBySDF()
{
	vector<vector<int>> nearlist;
	nearlist.clear();
	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near_id;
		near_id.clear();
		nearlist.push_back(near_id);
	}
	int k = k_near_size; // number of nearest neighbors 
	int dim = 3 + 4;  // pos + sdf 
	double eps = 0; // error bound
	int maxPts = s_sample.size();
	int nPts = s_sample.size(); // actual number of data points
	ANNpointArray dataPts; // data points
	ANNpoint queryPt; // query point
	ANNidxArray nnIdx; // near neighbor indices
	ANNdistArray dists; // near neighbor distances
	ANNkd_tree* kdTree; // search structure
	queryPt = annAllocPt(dim); // allocate query point
	dataPts = annAllocPts(maxPts, dim); // allocate data points
	nnIdx = new ANNidx[k]; // allocate near neigh indices
	dists = new ANNdist[k]; // allocate near neighbor dists
	for (size_t i = 0; i< s_sample.size(); i++)
	{
		dataPts[i][0] = s_sample[i].position[0];
		dataPts[i][1] = s_sample[i].position[1];
		dataPts[i][2] = s_sample[i].position[2];
		/*for(size_t j =0; j < s_sample[i].sdf.size(); j++)
		{
			dataPts[i][3 +j] = s_sample[i].sdf[j];
		}*/
		for(size_t j =0; j < 4; j++)
		{
			dataPts[i][3 +j] = s_sample[i].sample_features[j] * 0.25 ;
		}
	}

	kdTree = new ANNkd_tree( // build search structure
		dataPts, // the data points
		nPts, // number of points
		dim); // dimension of space

	for (size_t i = 0; i < t_sample.size(); i++)
	{
		vector<int> near;
		near.clear();
		queryPt[0] = t_sample[i].position[0];
		queryPt[1] = t_sample[i].position[1];
		queryPt[2] = t_sample[i].position[2];
	/*	for(size_t j =0; j < t_sample[i].sdf.size(); j++)
		{
			queryPt[3 +j] = t_sample[i].sdf[j];
		}*/
		for(size_t j =0; j < 4; j++)
		{
			queryPt[3 +j] = t_sample[i].sample_features[j]*  0.25;
		}
		kdTree->annkSearch( // search
			queryPt, // query point
			k, // number of near neighbors
			nnIdx, // nearest neighbors (returned)
			dists, // distance (returned)
			eps); // error bound
		for(size_t j =0 ; j < k_near_size; j++)
		{
			near.push_back(nnIdx[j]);
		}
		nearlist[i] = (near);
	}
	annClose();
	return nearlist;
}

vector<vector<int>> FindNearest::FindNearestType(int type)
{
	if(type == 0)
	{
		return FindKnearestByEdistance(1);
	}
	if(type == 1)
	{
		return FindKnearestBySDF();
	}
	if(type == 2)
	{
		return FindKnearestByFeature();
	}
	if(type == 3)
	{
		return FindnearestBySC();
	}
	if(type == 4)
	{
		return FindnearestByDiff();
	}
}