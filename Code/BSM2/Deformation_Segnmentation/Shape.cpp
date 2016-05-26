#include "Shape.h"
float Shape:: m_average_sampling_density = 0.1;

Shape::Shape(void)
{

}


Shape::~Shape(void)
{
	if (Shape_Mesh != NULL)
	{
		delete Shape_Mesh;
		Shape_Mesh = NULL;
	}
}

void Shape::GetShape(string file)
{
    Shape_Mesh = TriMesh::read(file);
	Shape_Mesh->normals.clear();
	Shape_Mesh->need_neighbors();
	Shape_Mesh->need_across_edge();
	Shape_Mesh->need_adjacentfaces();
	Shape_Mesh->need_normals();
}

void Shape::GetSamplePointForFaceSeg()
{
	
}


void Shape::GetSamplePoint(int sample_size)
{
	vector<ivec3> face_list;
	face_list.clear();
	for(size_t i = 0; i < Shape_Mesh->faces.size(); i++)
	{
		ivec3 f(Shape_Mesh->faces[i][0],Shape_Mesh->faces[i][1],Shape_Mesh->faces[i][2]);
		face_list.push_back(f);
	}
	SamplePoissonDisk test(face_list, Shape_Mesh->vertices, Shape_Mesh->normals);
	shape_sample = test.GetSample(sample_size);
	m_average_sampling_density = GetAverageSampleDistance();
	Radius();
	//GetShapeFeature();
	sample_color.clear();
	ivec3 p_c(255,255,0);
	for(size_t i =0; i< shape_sample.size(); i++)
	{
		sample_color.push_back(p_c);
	}
}

void Shape::GetShapeFeature()
{
	//Fix_Normal();
	cout <<"begin get feature " << endl;
	Compute_Feature test(shape_sample);
	shape_sample = test.GetFeaturedSample(); 
	/*variance[0] = 0;
	variance[1] = 0;
	variance[2] = 0;
	vec3 mean_pca(0,0,0);
	for(size_t i = 0; i < shape_sample.size(); i++)
	{
		mean_pca += shape_sample[i].angel_with_up;
	}
	mean_pca /= shape_sample.size();
	for(size_t i = 0; i < shape_sample.size(); i++)
	{
		variance[0] += (shape_sample[i].angel_with_up[0] - mean_pca[0])*(shape_sample[i].angel_with_up[0] - mean_pca[0]);
		variance[1] += (shape_sample[i].angel_with_up[1] - mean_pca[1])*(shape_sample[i].angel_with_up[1] - mean_pca[1]);
		variance[2] += (shape_sample[i].angel_with_up[2] - mean_pca[2])*(shape_sample[i].angel_with_up[2] - mean_pca[2]);
	}
	variance[0] = sqrt((variance[0]/shape_sample.size()));
	variance[1] = sqrt((variance[1]/shape_sample.size()));
	variance[2] = sqrt((variance[2]/shape_sample.size()));
	cout <<"variance " <<  variance[0] << " " << variance[1] <<" " << variance[2] << endl; 
	cout << "cout get feature " << endl;*/
}

void Shape::WriteShapeWithName(string file_name)
{
	cout << "begin here" <<endl;
	ofstream fout(file_name) ;
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
		fout<<(shape_sample[i].position[0] )<<" "<< (shape_sample[i].position[1] )<<" "<< (shape_sample[i].position[2] )<<" ";
		fout<< shape_sample[i].normal[0] <<" "<< shape_sample[i].normal[1] <<" "<< shape_sample[i].normal[2] <<" ";
		fout<<  sample_color[i][0] <<" "<< sample_color[i][1]  <<" "<< sample_color[i][2] <<endl;
		//fout<<  (int)(shape_sample[i].angel_with_up[0]*255) <<" "<< (int)(shape_sample[i].angel_with_up[1]*255)  <<" "<< (int)(shape_sample[i].angel_with_up[2]*255) <<endl;
		//fout<<  (int)(255) <<" "<< (int)(shape_sample[i].pca[1]*255)  <<" "<< (int)(shape_sample[i].pca[2]*255) <<endl;
	}
}



void Shape::GetShape_Cut(int part_number, int with_resample)
{
	Shape_With_Seg.clear();

	for(size_t i = 0; i< part_number; i++)
	{
		vector<Sample> shape_p;
		shape_p.clear();
		Shape_With_Seg.push_back(shape_p);
	}
	for(size_t i = 0; i < shape_sample.size(); i++)
	{
		Shape_With_Seg[part_id[i]].push_back(shape_sample[i]);
	}

	if(with_resample == 1)
	{
		GetFaceGroup(part_number);
	}

	
}

void Shape::RotateShape(int n_pi, string file_name)
{
	if(n_pi == 0)
	{
		;
	}
	if(n_pi == 1)
	{
		for( size_t i = 0; i< Shape_Mesh->vertices.size();i++)
		{
			vec3 pos = Shape_Mesh->vertices[i];
			vec3 pos_new(-pos[2],pos[1],pos[0]);
			Shape_Mesh->vertices[i] = pos_new;
		}
	}
	if(n_pi == 2)
	{
		for( size_t i = 0; i< Shape_Mesh->vertices.size();i++)
		{
			vec3 pos = Shape_Mesh->vertices[i];
			vec3 pos_new(-pos[0],pos[1],-pos[2]);
			Shape_Mesh->vertices[i] = pos_new;
		}
	}

	if(n_pi == 3)
	{
		for( size_t i = 0; i< Shape_Mesh->vertices.size();i++)
		{
			vec3 pos = Shape_Mesh->vertices[i];
			vec3 pos_new(pos[2],pos[1],-pos[0]);
			Shape_Mesh->vertices[i] = pos_new;
		}
	}

	Shape_Mesh->write(file_name);
}

void Shape::Fix_Normal()
{
	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		points.push_back( NamedPoint(  shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2], i ) );
	}
	PKDTree stree(points.begin(), points.end());
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		NamedPoint query( shape_sample[i].position[0], shape_sample[i].position[1],shape_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(100);
		Eigen::Matrix3d local_covariance_matrix = Eigen::Matrix3d::Constant(3,3,0);
		Eigen::Vector3d centroid(0,0,0);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  //-1 means there's no limit on the maximum allowed
		for (int kn = 0; kn < k_closest_elems.size(); kn++)
		{
			if ( stree.getElements()[k_closest_elems[kn].getIndex()].id != i)
			{
				NamedPoint kpoint = stree.getElements()[k_closest_elems[kn].getIndex()];
				Eigen::Vector3d v(kpoint.position.x, kpoint.position.y, kpoint.position.z);
				centroid += v;
			}
		}
		centroid /= (float)k_closest_elems.size();

		for (int kn = 0; kn < k_closest_elems.size(); kn++)
		{
			if ( stree.getElements()[k_closest_elems[kn].getIndex()].id != i)
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
		vec3 normal(n(0),n(1),n(2));
		if( (Shape_Mesh->trinorm(shape_sample[i].face_id) DOT normal ) > 0)
		{
			shape_sample[i].normal = normal;
		}
		else
		{
			shape_sample[i].normal = -normal;
		}
	}
}

void Shape::Radius()
{
	shape_radiu = 0.0f;
	for(size_t i = 0; i < shape_sample.size(); i++)
	{
		for(size_t j = 0; j < shape_sample.size(); j++)
		{
			float dis = dist(shape_sample[i].position, shape_sample[j].position);
			if(shape_radiu < dis)
			{
				shape_radiu = dis;
			}
		}
	}
	cout << "shape_radiu " << shape_radiu << endl;
}

void Shape::AddBounday()
{
	cout << "add" << endl;
	vector<Sample> All_points;
	All_points.clear();
	vector<int> point_index;
	point_index.clear();
	for(size_t i = 0; i < Shape_With_Seg.size(); i++ )
	{
		for(size_t j = 0; j < Shape_With_Seg[i].size() ; j++)
		{
			All_points.push_back(Shape_With_Seg[i][j]);
			point_index.push_back(i);
		}
	}
	// built
	int k = 25;
	//build kd tree
	vector<NamedPoint> points;
	for (size_t i = 0; i < All_points.size(); i++)
	{
		points.push_back( NamedPoint( All_points[i].position[0], All_points[i].position[1], All_points[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for(size_t i = 0;i < All_points.size();i++)
	{
		NamedPoint query( All_points[i].position[0], All_points[i].position[1], All_points[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(k);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for(size_t ind = 0; ind < k; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			if(point_index[nearest_id] != point_index[i])
			{
				Shape_With_Seg[point_index[nearest_id]].push_back(All_points[i]);
			}
		}
		
	}
	cout << "end add" << endl;
}

void Shape::RotateHalfPi()
{
	for(size_t i = 0; i < shape_sample.size(); i++)
	{
		vec3 pos = shape_sample[i].position;
		vec3 pos_new(-pos[2], pos[1], pos[0]);
		shape_sample[i].position = pos_new;
		vec3 nor = shape_sample[i].normal;
		vec3 nor_new(-nor[2], nor[1], nor[0]);
		shape_sample[i].normal = nor_new;
	}
}




void Shape::OutSeg(string mesh_file, string index_file, int seg_size)
{

	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		points.push_back( NamedPoint( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	//ofstream fout(index_file);
	
	for( size_t i = 0; i< Shape_Mesh->faces.size();i++)
	{
		vec3 v1 = Shape_Mesh->vertices[Shape_Mesh->faces[i][0]];
		vec3 v2 = Shape_Mesh->vertices[Shape_Mesh->faces[i][1]];
		vec3 v3 = Shape_Mesh->vertices[Shape_Mesh->faces[i][2]]; 
		vec3 v_c = (v1+v2+v3)*(1.0f/3);
		NamedPoint query( v_c[0], v_c[1], v_c[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(20);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		//
		vector<int> size_per_part;
		size_per_part.resize(20, 0);
		for (int j = 0; j < 20; j++)
		{
			int p_id = part_id[k_closest_elems[j].getIndex()];
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
	}
}

void Shape::OutPutSample(string s_file)
{
	ofstream fout(s_file);
	for (size_t j = 0; j < shape_sample.size(); j++)
	{
		fout << shape_sample[j].position[0] << " " << shape_sample[j].position[1] << " " << shape_sample[j].position[2] << " ";
		fout << shape_sample[j].normal[0] << " " << shape_sample[j].normal[1] << " " << shape_sample[j].normal[2] << endl;
	}
}

void Shape::SaveSample(string file_name, vector<int> true_index)
{
	ofstream fout(file_name);
	for (size_t i = 0; i < true_index.size(); i++)
	{
		for (size_t j = 0; j < shape_sample.size(); j++)
		{
			if (part_id[j] == i)
			{
				fout << shape_sample[j].position[0] << " " << shape_sample[j].position[1] << " " << shape_sample[j].position[2] << " ";
				fout << shape_sample[j].normal[0] << " " << shape_sample[j].normal[1] << " " << shape_sample[j].normal[2] << " ";
				fout << true_index[part_id[j]] << endl;
			}
		}
	}
}

void Shape::SaveFileWithSeg(string file_name, vector<int> true_index)
{
	vector<int> comp_size;
	vector<int> comps;
	find_comps(Shape_Mesh, comps, comp_size, false);

	// check for each comps
	vector<vector<int>> comp_seg;
	comp_seg.clear();

	for (size_t i = 0; i < comp_size.size(); i++)
	{
		vector<int> part_comp;
		part_comp.resize(true_index.size(), 0);
		comp_seg.push_back(part_comp);
	}

	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		int face_id = shape_sample[i].face_id;
		comp_seg[comps[face_id]][part_id[i]]++;
	}

	vector<int> comp_in_group;
	comp_in_group.resize(comp_size.size(), -1);
	// check for each compont
	for (size_t i = 0; i < comp_size.size(); i++)
	{
		int seg_count = 0;
		int max_id = -1;
		int max_size = -1;
		for (size_t j = 0; j < comp_seg[i].size(); j++)
		{
			if (comp_seg[i][j] > 0)
			{
				seg_count++;
			}
			if (comp_seg[i][j] > max_size)
			{
				max_size = comp_seg[i][j];
				max_id = j;
			}
		}

		if (seg_count < 3)
		{
			comp_in_group[i] = max_id;
		}
	}



	face_group.clear();
	for (int i = 0; i < true_index.size(); i++)
	{
		vector<int> face_list;
		face_list.clear();
		face_group.push_back(face_list);
	}
	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		points.push_back(NamedPoint(shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for (size_t i = 0; i< Shape_Mesh->faces.size(); i++)
	{
		if (comp_in_group[comps[i]] != -1)
		{
			face_group[comp_in_group[comps[i]]].push_back(i);
			continue;
		}
		vec3 v1 = Shape_Mesh->vertices[Shape_Mesh->faces[i][0]];
		vec3 v2 = Shape_Mesh->vertices[Shape_Mesh->faces[i][1]];
		vec3 v3 = Shape_Mesh->vertices[Shape_Mesh->faces[i][2]];
		vec3 v_c = (v1 + v2 + v3)*(1.0f / 3);
		NamedPoint query(v_c[0], v_c[1], v_c[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(20);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		//
		vector<int> size_per_part;
		size_per_part.resize(20, 0);
		for (int j = 0; j < 20; j++)
		{
			int p_id = part_id[k_closest_elems[j].getIndex()];
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
		face_group[max_index].push_back(i);
	}

	//out put 
	ofstream fout(file_name);
	for (size_t i = 0; i < Shape_Mesh->vertices.size(); i++)
	{
		fout << "v " << Shape_Mesh->vertices[i][0] << " " << Shape_Mesh->vertices[i][1] << " " << Shape_Mesh->vertices[i][2] << endl;
	}

	for (size_t i = 0; i < face_group.size(); i++)
	{
		fout << "g " << true_index[i] << endl;
		for (int j = 0; j < face_group[i].size(); j++)
		{
			int face_id = face_group[i][j];
			fout << "f " << Shape_Mesh->faces[face_id][0] + 1 << " " << Shape_Mesh->faces[face_id][1] + 1 << " " << Shape_Mesh->faces[face_id][2] + 1 << endl;
		}
	}
}

void Shape::GetFaceGroup(int face_size)
{
	face_group.clear();
	for(int i = 0; i < face_size; i++)
	{
		vector<int> face_list;
		face_list.clear();
		face_group.push_back(face_list);
	}
	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		points.push_back( NamedPoint( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for( size_t i = 0; i< Shape_Mesh->faces.size();i++)
	{
		vec3 v1 = Shape_Mesh->vertices[Shape_Mesh->faces[i][0]];
		vec3 v2 = Shape_Mesh->vertices[Shape_Mesh->faces[i][1]];
		vec3 v3 = Shape_Mesh->vertices[Shape_Mesh->faces[i][2]]; 
		vec3 v_c = (v1+v2+v3)*(1.0f/3);
		NamedPoint query( v_c[0], v_c[1], v_c[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		int p_id = part_id[k_closest_elems[0].getIndex()];
		face_group[p_id].push_back(i);
	}
#pragma omp parallel for 
	for(int  i = 0; i < face_group.size(); i++)
	{
		vector<Sample> point = SamplingByPart(i , face_group[i]);
		Shape_With_Seg[i] = point ;
	}
  cout << "end part sampling " << endl;
  shape_sample.clear();
  for(int  i = 0; i < face_group.size(); i++)
  {
	  vector<Sample> point = Shape_With_Seg[i];
	  shape_sample.insert(shape_sample.end(), point.begin(), point.end());
  }
  GetShapeFeature();

}

float Shape::GetAverageSampleDistance(int kNum /* = 5 */)
{
	cout << "begin average" << endl;
	kNum = kNum + 1;
	vector<NamedPoint> points;
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		points.push_back( NamedPoint( shape_sample[i].position[0], shape_sample[i].position[1], shape_sample[i].position[2], i ) );
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for( size_t i = 0; i< shape_sample.size();i++)
	{
		vec3 p = shape_sample[i].position;
		NamedPoint query( p[0], p[1], p[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		for(int k=1 ; k < kNum; k++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[k].getIndex()].id;
			dist_average += dist(p, shape_sample[nearest_id].position);
		}
	}

	cout << "end average" << endl;
	dist_average /= (kNum - 1)*float(shape_sample.size());
	return dist_average;
}


vector<Sample> Shape::SamplingByPart(int index,vector<int> face_list)
{
	vector<ivec3> sample_face_list;
	face_list.clear();
	for(size_t i = 0; i < face_list.size(); i++)
	{
		ivec3 f(Shape_Mesh->faces[face_list[i]][0],Shape_Mesh->faces[face_list[i]][1],Shape_Mesh->faces[face_list[i]][2]);
		sample_face_list.push_back(f);
	}
	SamplePoissonDisk test(sample_face_list, Shape_Mesh->vertices, Shape_Mesh->normals);
	cout << "begin sample" << endl;
	vector<Sample> sample_r;
	sample_r = test.GetSample(2000);
	return sample_r;
}
