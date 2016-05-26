#include "Find_Match.h"


Find_Match::Find_Match(void)
{
	temp_id = 0;
}


Find_Match::~Find_Match(void)
{
	if (themesh != NULL)
	{
		delete themesh;
		themesh = NULL;
	}
	temp_point.clear();
	temp_normal.clear();
	temp_color.clear();
	mesh_face_normal.clear();
	mesh_face_center.clear();
	match_point.clear();
	match_normal.clear();
	true_index.clear();
	part_id.clear();
	match_correspondence.clear();
}

void Find_Match::LoadTemplate(string temp_name)
{
	
	ifstream fin(temp_name);
	float x,y,z,nx,ny,nz;
	int cr,cg,cb;
	int p_id;
	temp_point.clear();
	temp_normal.clear();
	part_id.clear();
	true_index.clear();
	fin >> total_size;
	while(fin >> x >> y >> z >> nx >> ny >> nz >> temp_id>> p_id)
	{
		vec pos(x,y,z);
		vec nor(nx,ny,nz);
		normalize(nor);
		temp_point.push_back(pos);
		temp_normal.push_back(nor);
		part_id.push_back(temp_id);
		true_index.push_back(p_id);
		//point_by_part[p_id].push_back(pos);
	}
	temp_id = 0;
}

void Find_Match::ReadMeshSample(string file_name)
{
	//cout << "begin read " << file_name << endl;
	themesh = TriMesh::read(file_name);
}


void Find_Match::SetCorlor(string file_name)
{
	ifstream fin(file_name);
	int p_index;
	temp_color.clear();
	ivec3 c_p;
	while(fin  >> c_p[0] >> c_p[1] >> c_p[2])
	{
		temp_color.push_back(c_p);
	}
}

void Find_Match::FindMatchingBySample()
{
	match_correspondence.clear();
	//build kd tree
	int k = 100; // number of nearest neighbors
	int dim = 3; // dimension
	double eps = 0; // error bound
	//cout << "south" << Source_Point.size() <<endl;
	int maxPts = themesh->vertices.size(); // maximum number of data points
	int nPts =  themesh->vertices.size(); // actual number of data points
	ANNpointArray dataPts; // data points
	ANNpoint queryPt; // query point
	ANNidxArray nnIdx; // near neighbor indices
	ANNdistArray dists; // near neighbor distances
	ANNkd_tree* kdTree; // search structure
	queryPt = annAllocPt(dim); // allocate query point
	dataPts = annAllocPts(maxPts, dim); // allocate data points
	nnIdx = new ANNidx[k]; // allocate near neigh indices
	dists = new ANNdist[k]; // allocate near neighbor dists
	for(size_t i=0;i< themesh->vertices.size();i++)
	{
		dataPts[i][0] =  themesh->vertices[i][0];
		dataPts[i][1] =  themesh->vertices[i][1];
		dataPts[i][2] =  themesh->vertices[i][2];
		//cout << Source_Point[i][0] << " "<<Source_Point[i][1] <<" "<<Source_Point[i][2]<<endl;
	}
	//cout << "ok" << themesh->vertices.size() <<endl;
	kdTree = new ANNkd_tree( // build search structure
		dataPts, // the data points
		nPts, // number of points
		dim); // dimension of space
	//cout << "ok2" << Source_Point.size() <<endl;
	 match_point.clear();
	 match_normal.clear();
	 fit_err = 0;
	for(size_t i = 0;i < temp_point.size();i++)
	{
		queryPt[0] = temp_point[i][0];
		queryPt[1] = temp_point[i][1];
		queryPt[2] = temp_point[i][2];

		kdTree->annkSearch( // search
			queryPt, // query point
			k, // number of near neighbors
			nnIdx, // nearest neighbors (returned)
			dists, // distance (returned)
			eps); // error bound
		float min_dis = FLT_MAX;
		int close_tri_id = nnIdx[0]; float b_s = 0.3 , b_t = 0.3;
		for(int j = 0; j < k; j++)
		{
			int tri_id = nnIdx[j];
			vec n1 = temp_normal[i];
			vec n2 = themesh->normals[tri_id];
			if(n1[0]*n2[0] + n1[1]*n2[1] + n1[2]*n2[2] < 0)
			{
				//continue;
			}
			float dist_temp = dist(themesh->vertices[tri_id ],temp_point[i]);
			if(dist_temp < min_dis)
			{
				min_dis = dist_temp;
				close_tri_id = tri_id;
			}
		}
		
		vec m_p = themesh->vertices[close_tri_id];
		vec m_n = themesh->normals[close_tri_id];
		match_point.push_back(m_p);
		normalize(m_n);
		match_normal.push_back(m_n);		
		fit_err += dist2(m_p,temp_point[i]);
	}
	annClose();

	fit_err /= temp_point.size();
}

void Find_Match::OutPutResults(string out_name)
{

	ofstream fout(out_name);
	fout << total_size << endl;
	fout << temp_point.size() << endl;
	fout << fit_err << endl;
	for(size_t i = 0;i < temp_point.size();i++)
	{
		float dis = dist(temp_point[i],match_point[i]);
		float angel = temp_normal[i][0]*match_normal[i][0] + temp_normal[i][1]*match_normal[i][1] + temp_normal[i][2]*match_normal[i][2];
		fout << match_point[i][0] <<" "<< match_point[i][1] <<" "<< match_point[i][2] <<" ";
		fout << match_normal[i][0] <<" "<< match_normal[i][1] <<" "<< match_normal[i][2] <<" ";
		fout<< temp_id<< " ";
		fout << part_id[i] <<" ";
		fout<< true_index[i]<<" ";
		fout<< dis <<" "<<angel << endl;
	}
}

void Find_Match::OutMatchBinary(string out_name)
{
	ofstream fout(out_name, ios::out | ios::binary);
	int size_int = sizeof(int);
	int size_float = sizeof(float);
	int model_size = temp_point.size();
	cout << total_size << endl;
	fout.write((char*)(&total_size),size_int);
	fout.write((char*)(&model_size),size_int);
	fout.write((char*)(&fit_err),size_float);
	for(size_t i = 0;i < temp_point.size();i++)
	{
		float dis = dist(temp_point[i],match_point[i]);
		float angel = temp_normal[i][0]*match_normal[i][0] + temp_normal[i][1]*match_normal[i][1] + temp_normal[i][2]*match_normal[i][2];
		fout.write((char*)(&match_point[i][0]),size_float);
		fout.write((char*)(&match_point[i][1]),size_float);
		fout.write((char*)(&match_point[i][2]),size_float);
		fout.write((char*)(&match_normal[i][0]),size_float);
		fout.write((char*)(&match_normal[i][1]),size_float);
		fout.write((char*)(&match_normal[i][2]),size_float);
		fout.write((char*)(&temp_id),size_int);
		//cout << temp_id << endl;
		fout.write((char*)(&part_id[i]),size_int);
		int index = i;
		index  = true_index[i] ;
		fout.write((char*)(&index),size_int);
		fout.write((char*)(&dis),size_float);
		fout.write((char*)(&angel),size_float);
	}

}

void Find_Match::OutMatchingPly(string out_ply)
{
	ofstream fout(out_ply);
	fout << "ply" << endl;
	fout << "format ascii 1.0" << endl;
	fout << "element vertex " << match_point.size() << endl;
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
	for(size_t i = 0;i < match_point.size();i++)
	{
		fout << match_point[i][0] <<" "<< match_point[i][1] <<" "<< match_point[i][2] <<" ";
		fout << match_normal[i][0] <<" "<< match_normal[i][1] <<" "<< match_normal[i][2] <<" ";
		fout<< temp_color[true_index[i]][0] <<" "<< temp_color[true_index[i]][1] <<" "<< temp_color[true_index[i]][2]<<endl;
	}
}

