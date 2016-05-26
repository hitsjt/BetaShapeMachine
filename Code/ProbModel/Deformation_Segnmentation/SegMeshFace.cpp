#include "SegMeshFace.h"
TriMesh *Shape_Mesh;
static vector<vec3> face_center;
static vector<vec3> group_center;
static vector<vector<vec3>> shape_sample;
static vector<vec3> face_normal;
static float thread_hold;
static vector<vector<float>> prob;
static float smmoth_weight;

SegMeshFace::SegMeshFace(void)
{

}


SegMeshFace::~SegMeshFace(void)
{

}

float SegMeshFace::DataFunc(int p, int l)
{
	//if(l >= ms_template.Template_model.size() )
	//{
	//	return 10.0f;
	//}
	//Sample p_shape = ms_shape.shape_sample[p];
	//Sample p_temp = ms_template.Template_model[l].GetClosePoint(p_shape);
	//p_temp.position = ms_template.Template_model[l].center_posiotin;
	//float dis = dist2(p_shape.position, p_temp.position);
	//return dis;
	vec3 c_p = face_center[p];
	float min_dis = 100;
	for (size_t i = 0; i < shape_sample[l].size(); i++)
	{
		if (dist(c_p, shape_sample[l][i]) < min_dis)
		{
			min_dis = dist(c_p, shape_sample[l][i]);
		}
	}

	//return min_dis;
	double eps = 10e-6;
	return -log(min(prob[p][l] + eps,1.0)) ;
	return 1.0f - prob[p][l];
}

float SegMeshFace::DataFunc2(int p, int l)
{
	vec3 c_p = face_center[p];
	vec3 g_p = group_center[l];
	float min_dis = 100;
	double eps = 10e-6;
	return -log(min(prob[p][l] + eps, 1.0));
	return 1.0f - prob[p][l];
}


float SegMeshFace::SmoothFunc(int p1, int p2, int l1, int l2)
{
	//if (dist(face_center[p1], face_center[p2]) > thread_hold) // point far away
	//{
	//	return 0;
	//}
	if (l1 == l2) // close and with same lable
	{
		return 0.0f;
	}
	double eps = 10e-6;
	double e = -log(1 - max(double(face_normal[p1] DOT face_normal[p2]), 0.0) + eps);
	double signed_dihedral_angle = M_PI;
	for (int i = 0; i < 3; i++)
	{
		if (Shape_Mesh->across_edge[p1][i] == p2)
		{
			signed_dihedral_angle = Shape_Mesh->dihedral(p1, i);
		}

	}
	signed_dihedral_angle /= M_PI;

	float weight = 1.0;
	int is_nerbor = -1;
	for (int i = 0; i < 3; i++)
	{
		if (Shape_Mesh->across_edge[p1][i] == p2)
		{
			is_nerbor = 1;
			vec3 wedge = Shape_Mesh->vertices[Shape_Mesh->faces[p1][(i + 1) % 3]] - Shape_Mesh->vertices[Shape_Mesh->faces[p1][(i + 2) % 3]];
			weight = len(wedge);
		}
		
	}
	if (is_nerbor == 1)
	{
		return  smmoth_weight*weight*(max(-log(1 - min(signed_dihedral_angle, 1.0) + eps), 0.0)) + 0.1;
	}
	else
	{
		return (0.02 + max(e, 0.0))*0.05;
	}

	
	
}

void SegMeshFace::SetSmoothWeight(float weight)
{
   smmoth_weight = weight;
}

void SegMeshFace::GraphCut_refine()
{
	vector<int> graphCutsResult(true_index.size(), -1);
	GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(face_center.size(), true_index.size());
	for (size_t i = 0; i < face_group.size(); i++)
	{
		int face_id;
		for (size_t j = 0; j < true_index.size(); j++)
		{
			if (true_index[j] == face_group[i])
			{
				face_id = j;
				break;
			}
		}
		gc->setLabel(i, face_id);
	}

	cout << " innitial " << endl;
	gc->setDataCost(&DataFunc);
	gc->setSmoothCost(&SmoothFunc);
	float neighCnt = 0;

	Shape_Mesh->need_across_edge();
	for (size_t i = 0; i < Shape_Mesh->faces.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Shape_Mesh->across_edge[i][j] >= 0)
			{
				gc->setNeighbors(i, Shape_Mesh->across_edge[i][j]);
				neighCnt++;
			}

		}
	}
	GCoptimization::EnergyTermType* costArray = new GCoptimization::EnergyTermType[true_index.size()];
	for (size_t i = 0; i < true_index.size(); i++)
	{
		costArray[i] = 0.1f;
	}
	gc->setLabelCost(costArray);
	cout << "set term" << endl;
	cout << gc->giveDataEnergy() << endl;
	cout << gc->giveSmoothEnergy() << endl;
	cout << gc->giveLabelEnergy() << endl;
	printf("\nBefore optimization energy is %f", gc->compute_energy());
	//cout << "begin cut" <<endl;
	gc->expansion(10000);
	//gc->swap( 10000);
	printf("\nAfter optimization energy is %f\n", gc->compute_energy());
	//m_shape.ResetId();
	face_group.resize(face_center.size(), 0);
	for (size_t i = 0; i < face_group.size(); i++)
	{
		int most_box = gc->whatLabel(i);
		face_group[i] = true_index[most_box];
	}
	//m_shape.WritheShape();
	if (NULL != gc)
	{
		delete gc;
		gc = NULL;
	}
	if (NULL != costArray)
	{
		delete[] costArray;
		costArray = NULL;
	}

}

void SegMeshFace::GraphCut_new()
{
	vector<int> graphCutsResult(true_index.size(), -1);
	GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(face_center.size(), true_index.size());
	for (size_t i = 0; i < face_group.size(); i++)
	{
		int face_id;
		for (size_t j = 0; j < true_index.size(); j++)
		{
			if (true_index[j] == face_group[i])
			{
				face_id = j;
				break;
			}
		}
		gc->setLabel(i, face_id);
	}

	cout << " innitial " << endl;
	gc->setDataCost(&DataFunc);
	gc->setSmoothCost(&SmoothFunc);
	float neighCnt = 0;

	Shape_Mesh->need_across_edge();
	/*for (size_t i = 0; i< face_center.size(); i++)
	{
		for (size_t j = i + 1; j< face_center.size(); j++)
		{
			const vec3& p1 = face_center[i];
			const vec3& p2 = face_center[j];
			if (dist(p1, p2) < thread_hold)
			{
				int is_neighber = 1;
				for (int k = 0; k < 3; k++)
				{
					if (Shape_Mesh->across_edge[i][k] == j)
					{
						is_neighber = -1;
					}
				}
				if (is_neighber == 1)
				{
					gc->setNeighbors(i, j);
					neighCnt++;
				}
				
			}
		}
	}*/

	
	for (size_t i = 0; i < Shape_Mesh->faces.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (Shape_Mesh->across_edge[i][j] >= 0 )
			{
				gc->setNeighbors(i, Shape_Mesh->across_edge[i][j]);
				neighCnt++;
			}

		}
	}
	GCoptimization::EnergyTermType* costArray = new GCoptimization::EnergyTermType[true_index.size()];
	for (size_t i = 0; i < true_index.size(); i++)
	{
		costArray[i] = 0.1f;
	}
	gc->setLabelCost(costArray);
	cout << "set term" << endl;
	cout << gc->giveDataEnergy() << endl;
	cout << gc->giveSmoothEnergy() << endl;
	cout << gc->giveLabelEnergy() << endl;
	printf("\nBefore optimization energy is %f", gc->compute_energy());
	//cout << "begin cut" <<endl;
	gc->expansion(10000);
	//gc->swap( 10000);
	printf("\nAfter optimization energy is %f\n", gc->compute_energy());
	//m_shape.ResetId();
	face_group.resize(face_center.size(),0);
	for (size_t i = 0; i < face_group.size(); i++)
	{
		int most_box = gc->whatLabel(i);
		face_group[i] = true_index[most_box];
	}
	//m_shape.WritheShape();
	if (NULL != gc)
	{
		delete gc;
		gc = NULL;
	}
	if (NULL != costArray)
	{
		delete[] costArray;
		costArray = NULL;
	}

}

void SegMeshFace::LoadData(string  point_file, string mesh_file)
{
	shape_sample.clear();
	Shape_Mesh = TriMesh::read(mesh_file);
	Shape_Mesh->need_bbox();
	thread_hold = dist(Shape_Mesh->bbox.max, Shape_Mesh->bbox.min) * 0.02;
	ifstream fin(point_file);
	int total_point;
	int total_size;
	//fin >> total_point;
	fin >> total_size;
	//cout << total_size << endl;
	//float err;
	//fin >> err;
	float x, y, z, nx, ny, nz, dis, angel;
	int part_id, point_id, temp_id;
	true_index.clear();
	/*while (fin >> x >> y >> z >> nx >> ny >> nz >> temp_id >> part_id >> point_id >> dis >> angel)*/
	while (fin >> x >> y >> z >> nx >> ny >> nz >> part_id >> point_id )
	{
		
		int id_new = 1;
		for (size_t j = 0; j < true_index.size(); j++)
		{
			if (true_index[j] == part_id)
			{
				id_new = 0;
			}
		}
		if (id_new == 1)
		{
			true_index.push_back(part_id);
			vector<vec3> sample_list;
			shape_sample.push_back(sample_list);
		}
		vec3 p(x, y, z);
		vec3 n(nx, ny, nz);
		Sample s(p, n, 1.0, part_id);
		seg_point.push_back(s);

		int id_index = -1;
		for (size_t j = 0; j < true_index.size(); j++)
		{
			if (true_index[j] == part_id)
			{
				id_index = j;
			}
		}
		shape_sample[id_index].push_back(p);
	}
	cout << "read end " << true_index.size() << " " << seg_point.size() <<  endl;
}

void SegMeshFace::SegFace()
{
	prob.clear();
	//cout << "ok 1" << endl;
	face_group.clear();
	face_center.clear();
	face_normal.clear();
	int kNum = 20;
	vector<NamedPoint> points;
	for (size_t i = 0; i < seg_point.size(); i++)
	{
		points.push_back(NamedPoint(seg_point[i].position[0], seg_point[i].position[1], seg_point[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for (size_t i = 0; i< Shape_Mesh->faces.size(); i++)
	{
		int v1 = Shape_Mesh->faces[i][0];
		int v2 = Shape_Mesh->faces[i][1];
		int v3 = Shape_Mesh->faces[i][2];
 		vec3 p = (Shape_Mesh->vertices[v1] + Shape_Mesh->vertices[v2] + Shape_Mesh->vertices[v3]) * (1.0f /3);
		face_center.push_back(p);
		face_normal.push_back(Shape_Mesh->trinorm(i));
		NamedPoint query(p[0], p[1], p[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		vector<int> size_per_part;
		size_per_part.resize(20, 0);
		for (int j = 0; j < 20; j++)
		{
			int p_id = seg_point[k_closest_elems[j].getIndex()].face_id;
			size_per_part[p_id] += 1;
		}
		int max_index = 0;
		int max_size = 0;
		for (int j = 0; j < size_per_part.size(); j++)
		{
			if (size_per_part[j] > max_size)
			{
				max_size = size_per_part[j];
				max_index = j;
			}
		}
		face_group.push_back(max_index);
		vector<float> prob_sample;
		prob_sample.resize(true_index.size(), 0);
		for (int j = 0; j < true_index.size(); j++)
		{
			prob_sample[j] = ((float)size_per_part[true_index[j]]) / 20.0f;
		}

		prob.push_back(prob_sample);
	}
}

void SegMeshFace::Refine()
{
	
	int kNum = 20;
	vector<NamedPoint> points;
	for (size_t i = 0; i < face_center.size(); i++)
	{
		points.push_back(NamedPoint(face_center[i][0], face_center[i][1], face_center[i][2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for (int ite = 0; ite < 5; ite++)
	{
		cout << ite << endl;
		vector<int> face_group_new = face_group;
		for (size_t i = 0; i< face_center.size(); i++)
		{
			if (i % 1000 == 0)
			{
				cout << i << endl;
			}
			vec3 p = face_center[i];
			NamedPoint query(p[0], p[1], p[2]);
			BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
			stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
			vector<int> size_per_part;
			size_per_part.resize(20, 0);
			for (int j = 0; j < 20; j++)
			{
				int p_id = face_group[k_closest_elems[j].getIndex()];
				size_per_part[p_id] += 1;
			}
			int max_index = 0;
			int max_size = 0;
			for (int j = 0; j < size_per_part.size(); j++)
			{
				if (size_per_part[j] > max_size)
				{
					max_size = size_per_part[j];
					max_index = j;
				}
			}
			face_group_new[i] = (max_index);
		}

		face_group = face_group_new;
	}
	
}

void SegMeshFace::AddConnectComponemnet()
{
	vector<int> comp_size;
	vector<int> comps;
	find_comps(Shape_Mesh, comps, comp_size, false);
	for (size_t i = 0; i < comp_size.size(); i++)
	{
		vector<int> face_part_size;
		face_part_size.resize(true_index.size(), 0);
		vector<float> face_part_area;
		face_part_area.resize(true_index.size(), 0);
		float total_area = 0;
		for (size_t j = 0; j < Shape_Mesh->faces.size(); j++)
		{
			if (comps[j] == i)
			{
				for (int k = 0; k < true_index.size(); k++)
				{
					if (true_index[k] == face_group[j])
					{
						face_part_size[k] ++;
						float _area = len(Shape_Mesh->trinorm(j));
						face_part_area[k] += _area;
						total_area += _area;
					}
				}
			}
		}
		int max_index = -1;
		for (size_t j = 0; j < face_part_area.size(); j++)
		{
			if (face_part_area[j] / total_area > 0.5)
			{
				max_index = true_index[j];
			}
		}
		if (max_index != -1)
		{
			for (size_t j = 0; j < Shape_Mesh->faces.size(); j++)
			{
				if (comps[j] == i)
				{
					face_group[j] = max_index;
				}
			}
		}
	}
}

void SegMeshFace::OutPutSegFile(string out_file)
{
	ofstream fout(out_file);
	for (size_t i = 0; i < Shape_Mesh->faces.size(); i++)
	{
		fout << face_group[i] << endl;
	}

}



void SegMeshFace::OutPutSeg(string mesh_file)
{
	ofstream fout(mesh_file);
	for (size_t i = 0; i < Shape_Mesh->vertices.size(); i++)
	{
		fout << "v " << Shape_Mesh->vertices[i][0] << " " << Shape_Mesh->vertices[i][1] << " " << Shape_Mesh->vertices[i][2] << endl;
	}

	for (size_t i = 0; i < true_index.size(); i++)
	{
		fout << "g " << true_index[i] << endl;
		for (int j = 0; j < Shape_Mesh->faces.size(); j++)
		{
			if (face_group[j] == true_index[i])
			{
				fout << "f " << Shape_Mesh->faces[j][0] + 1 << " " << Shape_Mesh->faces[j][1] + 1 << " " << Shape_Mesh->faces[j][2] + 1 << endl;
			}

		}
	}
	vector<ivec3> color;
	for (int i = 0; i < 20; i++)
	{
		ivec3 p((int)(255 * (float)(rand()) / RAND_MAX), (int)(255 * (float)(rand()) / RAND_MAX), (int)(255 * (float)(rand()) / RAND_MAX));
		color.push_back(p);
	}
	unsigned ePos = mesh_file.find_last_of(".");
	string newFile = mesh_file.substr(0, ePos);
	newFile.append(".ply");
	ofstream fout2(newFile);
	fout2 << "ply" << endl;
	fout2 << "format ascii 1.0" << endl;
	fout2 << "element vertex " << Shape_Mesh->vertices.size() << endl;
	fout2 << "property float32 x" << endl;
	fout2 << "property float32 y" << endl;
	fout2 << "property float32 z" << endl;
	fout2 << "element face " << Shape_Mesh->faces.size() << endl;
	fout2 << "property list uint8 int32 vertex_index" << endl;
	fout2 << "property uchar red" << endl;
	fout2 << "property uchar green" << endl;
	fout2 << "property uchar blue" << endl;
	fout2 << "end_header" << endl;
	for (size_t i = 0; i < Shape_Mesh->vertices.size(); i++)
	{
		fout2 << Shape_Mesh->vertices[i][0] << " " << Shape_Mesh->vertices[i][1] << " " << Shape_Mesh->vertices[i][2] << endl;
	}


	for (int j = 0; j < Shape_Mesh->faces.size(); j++)
	{
		fout2 << 3 << " " << Shape_Mesh->faces[j][0] << " " << Shape_Mesh->faces[j][1] << " " << Shape_Mesh->faces[j][2] << " " << color[face_group[j]][0] << " " << color[face_group[j]][1] << " " << color[face_group[j]][2] << endl;
	}

}