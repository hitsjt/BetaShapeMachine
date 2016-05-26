#include "DeformFromShape.h"


DeformFromShape::DeformFromShape()
{
}


DeformFromShape::~DeformFromShape()
{
}

void DeformFromShape::GetSample(string s_file, string t_file)
{
	Shape s_shape;
	s_shape.GetShape(s_file);
	s_shape.GetSamplePoint(8000);
	s_shape_sample = s_shape.shape_sample;


	Shape t_shape;
	t_shape.GetShape(t_file);
	t_shape.GetSamplePoint(30000);
	t_shape_sample = t_shape.shape_sample;

}

void DeformFromShape::RigidAlignment()
{
	vector<vec3> s_sample;
	s_sample.clear();
	for(size_t i = 0; i < s_shape_sample.size(); i++)
	{
		s_sample.push_back(s_shape_sample[i].position);
	}
	vector<vec3> t_sample;
	t_sample.clear();
	for(size_t i = 0; i < t_shape_sample.size(); i++)
	{
		t_sample.push_back(t_shape_sample[i].position);
	}
	ICP test(s_sample,t_sample);
	vector<vec3> s_rotate = test.RunICP();
	for(size_t j = 0; j <  s_shape_sample.size() ; j++)
	{
		 s_shape_sample[j].position = s_rotate[j];
	}
}



void DeformFromShape::GetSampleFromBaseShapes(string mesh_file, string gt_file)
{
	Shape base_shape;
	base_shape.GetShape(mesh_file);
	base_shape.GetSamplePoint(4000);
	s_shape_sample = base_shape.shape_sample;
	cout << gt_file << endl;
	vector<int> face_gt;
	face_gt.clear();
	ifstream fin(gt_file);
	int seg_id;
	while(fin >> seg_id)
	{
		face_gt.push_back(seg_id);
	}
	cout << face_gt.size() << "  face_gt " << endl; 

	for(size_t i =0 ; i < s_shape_sample.size(); i++)
	{
		int face_id = s_shape_sample[i].face_id;
		//cout << face_gt[face_id]  << endl;
		s_shape_sample[i].face_id = face_gt[face_id];
	}
	s_shape_index.clear();
	s_shape_part.clear();
	int part_id;
	int count = 0;
	for(size_t i = 0; i < s_shape_sample.size(); i++)
	{
		part_id = s_shape_sample[i].face_id;
		s_shape_index.push_back(i);
		s_shape_part.push_back(part_id);
	}
	cout << "end get base sample" << endl;
}

void DeformFromShape::GetSampleFromBaseShapesWithMesh(string file_name, string mesh_file)
{

	s_shape_sample.clear();
	s_shape_index.clear();
	s_shape_part.clear();
	ifstream f_model(file_name);
	float x, y, z, nx, ny, nz;
	int part_id;
	int count = 0;
	while (f_model >> x >> y >> z >> nx >> ny >> nz >> part_id)
	{
		vec3 pos(x, y, z);
		vec3 nor(nx, ny, nz);
		for (size_t i = 0; i < valid_group.size(); i++)
		{
			if (valid_group[i] == part_id)
			{
				Sample s_sample(pos, nor);
				s_sample.face_id = i;
				s_shape_sample.push_back(s_sample);
				s_shape_index.push_back(count);
				s_shape_part.push_back(part_id);
			}
		}
		count++;
	}
	TriMesh *mesh;
	mesh = TriMesh::read(mesh_file);
	Compute_Feature test(s_shape_sample);
	test.exportSDF(mesh);
	s_shape_sample = test.GetFeaturedSample(1); 
	if(mesh != NULL)
	{
		delete mesh;
		mesh = NULL;
	}
}

void DeformFromShape::GetSampleFeatureFromMatching(string f_file, string s_file)
{
	vector<float> feature_list;
	feature_list.clear();
	ifstream fin_f(f_file);
	float fea;
	while(fin_f >> fea)
	{
		feature_list.push_back(fea);
	}
	s_shape_sample.clear();
	s_shape_index.clear();
	s_shape_part.clear();
	ifstream f_model(s_file);
	float x, y, z, nx, ny, nz;
	int part_id;
	int count = 0;
	while (f_model >> x >> y >> z >> nx >> ny >> nz >> part_id)
	{
		vec3 pos(x, y, z);
		vec3 nor(nx, ny, nz);
		for (size_t i = 0; i < valid_group.size(); i++)
		{
			if (valid_group[i] == part_id)
			{
				Sample s_sample(pos, nor);
				s_sample.face_id = i;
				s_sample.sample_features.clear();
				s_shape_sample.push_back(s_sample);
				s_shape_index.push_back(count);
				s_shape_part.push_back(part_id);
			}
		}
		count++;
	}
	int feature_pre_sample = feature_list.size()/count;
	for(size_t i = 0; i < s_shape_index.size();i++)
	{
		int sample_index = s_shape_index[i];
		for(size_t j = 0; j < feature_pre_sample; j++)
		{
			   if(j < 4)
			   {
			     s_shape_sample[i].sample_features.push_back(feature_list[sample_index*feature_pre_sample + j]);
			   }
		}
	}
	Compute_Feature test(s_shape_sample);
	s_shape_sample = test.GetFeaturedSample(0); 
}

void DeformFromShape::GetSampleFromMatching(string s_file)
{
	//s_shape_sample.clear();
	//s_shape_index.clear();
	//s_shape_part.clear();
	//ifstream f_model(s_file);
	//float x, y, z, nx, ny, nz;
	//int part_id;
	//int count = 0;
	//while (f_model >> x >> y >> z >> nx >> ny >> nz >> part_id)
	//{
	//	vec3 pos(x, y, z);
	//	vec3 nor(nx, ny, nz);
	//	Sample s_sample(pos, nor);
	//	s_shape_sample.push_back(s_sample);
	//	s_shape_index.push_back(count);
	//	s_shape_part.push_back(part_id);
	//	count++;
	//}

	s_shape_sample.clear();
	s_shape_index.clear();
	s_shape_part.clear();
	ifstream f_model(s_file);
	float x, y, z, nx, ny, nz;
	int part_id;
	int count = 0;
	while (f_model >> x >> y >> z >> nx >> ny >> nz >> part_id)
	{
		vec3 pos(x, y, z);
		vec3 nor(nx, ny, nz);
		for (size_t i = 0; i < valid_group.size(); i++)
		{
			if (valid_group[i] == part_id)
			{
				Sample s_sample(pos, nor);
				s_sample.face_id = i;
				s_shape_sample.push_back(s_sample);
				s_shape_index.push_back(count);
				s_shape_part.push_back(part_id);
			}
		}
		count++;
	}
	cout << s_shape_sample.size() << endl;
	Compute_Feature test(s_shape_sample);
	s_shape_sample = test.GetFeaturedSample(); 
}

void DeformFromShape::LoadScanTargetSample(string s_file)
{
	cout << "begin load " << s_file << endl;
	t_shape_sample.clear();
	ifstream fin(s_file);
	string para;
	while(fin >> para)
	{
		if(para == "end_header")
		{
			float x, y, z, nx, ny, nz;
			int c_r,c_g,c_b, c_alpha;
			while(fin >> x >> y >> z >> nx >> ny >> nz >> c_r >> c_g >> c_b)
			{
				vec3 pos(x, y, z);
				vec3 nor(nx, ny, nz);
				Sample t_sample(pos, nor);
				t_sample.face_id = 0;
				t_shape_sample.push_back(t_sample);
			}
		}
	}
	cout << t_shape_sample.size() << endl;
	// refine target
	vec3 b_max(-FLT_MAX,-FLT_MAX,-FLT_MAX);
	vec3 b_min(-FLT_MIN,-FLT_MIN,-FLT_MIN);
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		vec3 pos = t_shape_sample[i].position;
		if(b_max[0] < pos[0])
		{
			b_max[0] = pos[0];
		}
		if(b_max[1] < pos[1])
		{
			b_max[1] = pos[1];
		}
		if(b_max[2] < pos[2])
		{
			b_max[2] = pos[2];
		}
		if(b_min[0] > pos[0])
		{
			b_min[0] = pos[0];
		}
		if(b_min[1] > pos[1])
		{
			b_min[1] = pos[1];
		}
		if(b_min[2] > pos[2])
		{
			b_min[2] = pos[2];
		}
	}
	vector<Sample> t_shape_sample_new;
	t_shape_sample_new.clear();
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		vec3 pos = t_shape_sample[i].position;
		if(pos[1] > b_min[1] + 0.15*(b_max[1] - b_min[1]))
		{
			t_shape_sample_new.push_back(t_shape_sample[i]);
		}
	}
	t_shape_sample = t_shape_sample_new;

	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		vec3 pos = t_shape_sample[i].position;
		vec3 nor = t_shape_sample[i].normal;
		vec3 pos_new(pos[0],-pos[2],pos[1]);
		vec3 nor_new(nor[0],-nor[2],nor[1]);
		t_shape_sample[i].position = pos_new;
		t_shape_sample[i].normal = nor_new;
	}
	cout << t_shape_sample.size() << endl;
}

void DeformFromShape::FilterTemplateSample()
{
	vector<int> s_shape_index_new;
	s_shape_index_new.clear();
	vector<int> s_shape_part_new;
	s_shape_part_new.clear();
	vector<Sample> s_shape_sample_new;
	s_shape_sample_new.clear();
	vector<NamedPoint> points_template;
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		points_template.push_back( NamedPoint(  t_shape_sample[i].position[0], t_shape_sample[i].position[1], t_shape_sample[i].position[2], i ) );
	}
	PKDTree stree(points_template.begin(), points_template.end());
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		NamedPoint query( s_shape_sample[i].position[0], s_shape_sample[i].position[1], s_shape_sample[i].position[2] );
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(10);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		int is_keep = 0;
		for(size_t ind = 0; ind< 10 ; ind++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			if((s_shape_sample[i].normal DOT t_shape_sample[nearest_id].normal) > 0.5f)
			{
			   is_keep = 1;
			}			
		}
		if(is_keep == 1)
		{
			s_shape_index_new.push_back(s_shape_index[i]);
			s_shape_part_new.push_back(s_shape_part[i]);
			s_shape_sample_new.push_back(s_shape_sample[i]);
		}
	}
	s_shape_index = s_shape_index_new;
	s_shape_part = s_shape_part_new;
	s_shape_sample = s_shape_sample_new;
}

void DeformFromShape::LoadTargetSampleWithPreSeg(string s_file, string mesh_file)
{
	t_shape_sample.clear();
	ifstream fin(s_file);
	string para;
	while(fin >> para)
	{
		if(para == "end_header")
		{
			float x, y, z, nx, ny, nz;
			int face_id, patch_id;
			int c_r,c_g,c_b;
			while(fin >> x >> y >> z >> nx >> ny >> nz >> face_id >> patch_id >> c_r >> c_g >> c_b )
			{
				vec3 pos(x, y, z);
				vec3 nor(nx, ny, nz);
				Sample t_sample(pos, nor);
				t_sample.face_id = face_id;
				t_sample.patch_id = patch_id;
				t_shape_sample.push_back(t_sample);
			}
		}
	}
	TriMesh *mesh;
	mesh = TriMesh::read(mesh_file);
	Compute_Feature test(t_shape_sample);
	test.exportSDF(mesh);
	test.exportShapeContex();
	t_shape_sample = test.GetFeaturedSample(0); 
	if(mesh!= NULL)
	{
		delete mesh;
		mesh =  NULL;
	}
}

void DeformFromShape::LoadTargetSampleWithegFeature(string s_file, string f_file)
{
	t_shape_sample.clear();
	ifstream fin(s_file);
	string para;
	while(fin >> para)
	{
		if(para == "end_header")
		{
			float x, y, z, nx, ny, nz;
			int face_id, path_id;
			int c_r,c_g,c_b;
			while(fin >> x >> y >> z >> nx >> ny >> nz >> c_r >> c_g >> c_b >> face_id >> path_id)
			{
				vec3 pos(x, y, z);
				vec3 nor(nx, ny, nz);
				Sample t_sample(pos, nor);
				t_sample.face_id = face_id;
				t_sample.patch_id = path_id;
				t_sample.sample_features.clear();
				t_shape_sample.push_back(t_sample);
				
			}
		}
	}

	vector<float> feature_list;
	feature_list.clear();
	ifstream fin_f(f_file);
	float fea;
	while(fin_f >> fea)
	{
		feature_list.push_back(fea);
	}

	int feature_pre_sample = feature_list.size()/t_shape_sample.size();
	for(size_t i =0; i < feature_list.size(); i++)
	{
		int sample_index = i / feature_pre_sample;
		if(t_shape_sample[sample_index].sample_features.size() < 4)
		{
		   t_shape_sample[sample_index].sample_features.push_back(feature_list[i]);
		}
	}
 
	Compute_Feature test(t_shape_sample);
	t_shape_sample = test.GetFeaturedSample(0); 
}

void DeformFromShape::GetTargetSampleWithSeg(string mesh_file, string path_file)
{
	Shape t_shape;
	t_shape.GetShape(mesh_file);
	t_shape.GetSamplePoint(10000);
	t_shape_sample = t_shape.shape_sample;
	ifstream fin(path_file);
	int path_id;
	vector<int> path_list;
	path_list.clear();
	while(fin >> path_id)
	{
		path_list.push_back(path_id);
	}
	for(size_t i =0; i < t_shape_sample.size(); i++)
	{
		t_shape_sample[i].patch_id = path_list[t_shape_sample[i].face_id];
	}
}

void DeformFromShape::GetTargetSample(string t_file)
{
	Shape t_shape;
	t_shape.GetShape(t_file);
	t_shape.GetSamplePoint(10000);
	t_shape_sample = t_shape.shape_sample;
}

void DeformFromShape::GetBoxDetectionSample(string file_name)
{
	TriMesh *mesh;
	mesh = TriMesh::read(file_name);
	t_shape_sample.clear();
	for (size_t i = 0; i < mesh->vertices.size(); i++)
	{
		vec3 pos = mesh->vertices[i];
		vec3 nor = mesh->normals[i];
		Sample p(pos, nor, 1.0f, -1);
		t_shape_sample.push_back(p);
	}
}

void DeformFromShape::SetValidGroup(string file_name)
{
	valid_group.clear();
	// read template file
	ifstream fin(file_name);
	if (fin.fail() == true)
	{
		cout << "Failed to load box from config file " << "!\n";
		return;
	}
	string param;
	vec3 o_1, o_2, o_3;
	vec3 center, scale;
	while (fin >> param)
	{

		if (param == string("TEMPLATE_ID"))
		{
			int temp_id;
			fin >> temp_id;
		}
		if (param == string("BOX_SIZE"))
		{
			int n_part;
			fin >> n_part;
		}
		else if (param == string("PART_ID"))
		{
			int part_id;
			fin >> part_id;
			valid_group.push_back(part_id);
		}
		else if (param == string("PARTTYPE"))
		{
			int part_type;
			fin >> part_type;
		}
		else if (param == string("BOXCENTER"))
		{
			fin >> center[0] >> center[1] >> center[2];
		}
		else if (param == string("BOXSCALE"))
		{
			fin >> scale[0] >> scale[1] >> scale[2];
		}
		else if (param == string("BOXORIX"))
		{
			fin >> o_1[0] >> o_1[1] >> o_1[2];

		}
		else if (param == string("BOXORIY"))
		{
			fin >> o_2[0] >> o_2[1] >> o_2[2];
		}
		else if (param == string("BOXORIZ"))
		{
			fin >> o_3[0] >> o_3[1] >> o_3[2];
		}
	}
	cout << valid_group.size() << endl;
}

void DeformFromShape::GetSampleFeature(string s_file, string t_file)
{
	Shape s_shape;
	s_shape.GetShape(s_file);
	s_shape.GetSamplePoint(3000);
	s_shape_sample = s_shape.shape_sample;


	Shape t_shape;
	t_shape.GetShape(t_file);
	t_shape.GetSamplePoint(3000);
	t_shape_sample = t_shape.shape_sample;

}

float DeformFromShape::CalFeature()
{
	float err_all = 0; 
	vector<NamedPoint> points;
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		points.push_back(NamedPoint(t_shape_sample[i].position[0], t_shape_sample[i].position[1], t_shape_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for (size_t i = 0; i< s_shape_sample.size(); i++)
	{
		vector<int> s_c;
		s_c.clear();
		vec3 p = s_shape_sample[i].position;
		NamedPoint query(p[0], p[1], p[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		int nearest_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
		err_all += dist(s_shape_sample[i].position, t_shape_sample[nearest_id].position);
	}
	err_all /= s_shape_sample.size();
	return err_all;
}

void DeformFromShape::SetColor()
{
	color_list.clear();
	vec3 s_max(-100, -100, -100);
	vec3 s_min(100, 100, 100);
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		if (s_shape_sample[i].position[0] > s_max[0])
		{
			s_max[0] = s_shape_sample[i].position[0];
		}
		if (s_shape_sample[i].position[1] > s_max[1])
		{
			s_max[1] = s_shape_sample[i].position[1];
		}
		if (s_shape_sample[i].position[2] > s_max[2])
		{
			s_max[2] = s_shape_sample[i].position[2];
		}

		if (s_shape_sample[i].position[0] < s_min[0])
		{
			s_min[0] = s_shape_sample[i].position[0];
		}
		if (s_shape_sample[i].position[1] < s_min[1])
		{
			s_min[1] = s_shape_sample[i].position[1];
		}
		if (s_shape_sample[i].position[2] < s_min[2])
		{
			s_min[2] = s_shape_sample[i].position[2];
		}
	}

	cout << s_max << endl;
	cout << s_min << endl;
	//ofstream fout("bike_color_map.txt");
	vector<ivec3> color2;
	for (int i = 0; i < 20; i++)
	{
		ivec3 p((int)(255 * (float)(rand()) / RAND_MAX), (int)(255 * (float)(rand()) / RAND_MAX), (int)(255 * (float)(rand()) / RAND_MAX));
		color2.push_back(p);
	}
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		ivec3 color;
		color[0] = (s_shape_sample[i].position[0] - s_min[0]) / (s_max[0] - s_min[0]) * 255;
		color[1] = (s_shape_sample[i].position[1] - s_min[1]) / (s_max[1] - s_min[1]) * 255;
		color[2] = (s_shape_sample[i].position[2] - s_min[2]) / (s_max[2] - s_min[2]) * 255;
		s_shape_sample[i].color = color;
		color_list.push_back(color);
	}
}


void DeformFromShape::ScaleTemplate()
{
	vec3 s_max(-100, -100, -100);
	vec3 s_min(100, 100, 100);
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		if (s_shape_part[i] == 0)
		{
			if (s_shape_sample[i].position[0] > s_max[0])
			{
				s_max[0] = s_shape_sample[i].position[0];
			}
			if (s_shape_sample[i].position[0] < s_min[0])
			{
				s_min[0] = s_shape_sample[i].position[0];
			}
		}

	}

	vec3 ss_max(-100, -100, -100);
	vec3 ss_min(100, 100, 100);
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		if (s_shape_part[i] == 8 || s_shape_part[i] == 9)
		{
			if (s_shape_sample[i].position[0] > ss_max[0])
			{
				ss_max[0] = s_shape_sample[i].position[0];
			}

			if (s_shape_sample[i].position[0] < ss_min[0])
			{
				ss_min[0] = s_shape_sample[i].position[0];
			}
		}

	}

	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		if (s_shape_part[i] == 8 || s_shape_part[i] == 9)
		{
			if (s_shape_sample[i].position[0] > 0)
			{
				s_shape_sample[i].position[0] *= (s_max[0] / ss_max[0]);
			}
			if (s_shape_sample[i].position[0] < 0)
			{
				s_shape_sample[i].position[0] *= (s_min[0] / ss_min[0]);
			}
		}

	}

}


void DeformFromShape::outPutSampleFeature(string file_name)
{
	//ofstream fout(file_name);
	//for(size_t i = 0; i < t_shape_sample.size(); i++)
	//{
	//	cout << t_shape_sample[i].sdf.size() << endl;
	//	for(size_t j = 0; j < t_shape_sample[i].sdf.size(); j++)
	//	{
	//		fout << t_shape_sample[i].sdf[j] << " " ;
	//	}
	//	cout << t_shape_sample[i].angel_geo_dis.size() << endl;
	//	for(size_t j = 0; j < t_shape_sample[i].angel_geo_dis.size(); j++)
	//	{
	//		fout << t_shape_sample[i].angel_geo_dis[j] << " " ;
	//	}
	//	cout << t_shape_sample[i].shape_context.size() << endl;
	//	for(size_t j = 0; j < t_shape_sample[i].shape_context.size(); j++)
	//	{
	//		fout << t_shape_sample[i].shape_context[j] << " " ;
	//	}
	//	fout << endl;
	//}

	ofstream fout(file_name);
	for(size_t i = 0; i < s_shape_sample.size(); i++)
	{
		cout << s_shape_sample[i].sdf.size() << endl;
		for(size_t j = 0; j < s_shape_sample[i].sdf.size(); j++)
		{
			fout << s_shape_sample[i].sdf[j] << " " ;
		}
		cout << s_shape_sample[i].angel_geo_dis.size() << endl;
		for(size_t j = 0; j < s_shape_sample[i].angel_geo_dis.size(); j++)
		{
			fout << s_shape_sample[i].angel_geo_dis[j] << " " ;
		}
		cout << s_shape_sample[i].shape_context.size() << endl;
		for(size_t j = 0; j < s_shape_sample[i].shape_context.size(); j++)
		{
			fout << s_shape_sample[i].shape_context[j] << " " ;
		}
		fout << endl;
	}
}

void DeformFromShape::BuiltShapeConnection()
{
	s_connection.clear();
	int kNum = 100;
	vector<NamedPoint> points;
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		points.push_back(NamedPoint(s_shape_sample[i].position[0], s_shape_sample[i].position[1], s_shape_sample[i].position[2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for (size_t i = 0; i< s_shape_sample.size(); i++)
	{
		vector<int> s_c;
		s_c.clear();
		vec3 p = s_shape_sample[i].position;
		NamedPoint query(p[0], p[1], p[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		for (int k = 1; k < kNum; k++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[k].getIndex()].id;
			if (s_shape_part[i] == s_shape_part[nearest_id] && s_c.size() < 10 && nearest_id != i)
			{
				s_c.push_back(nearest_id);
			}
			if (s_c.size() == 10)
			{
				break;
			}	
		}

		s_connection.push_back(s_c);
	}
}

vector<vector<int>> DeformFromShape::BulitConnectionByGroup(vector<Sample> sample_list)
{
	vector<vector<int>> connection;
	connection.clear();
	int kNum = 5;
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
			s_c.push_back(nearest_id);
		}

		connection.push_back(s_c);
	}

	return connection;
}

void DeformFromShape::DeformMeanField()
{
	for (int i = 0; i < 1; i++)
	{
		Mean_Field_Deformation test(s_shape_sample, t_shape_sample, s_connection, valid_group.size());
		test.TestTemplateSample("test_mesh.ply", "test.ply");
		//s_shape_sample = test.DeformToShape();
		//ReNormal(s_shape_sample);
	}
	
}

void DeformFromShape::Deformation_With_Seg()
{
	vector<int> true_index;
	true_index.clear();
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		int group_id = s_shape_sample[i].face_id;
		int is_new = 1;
		for (size_t j = 0; j < true_index.size(); j++)
		{
			if (group_id == true_index[j])
			{
				is_new = 0;
			}
		}
		if (is_new == 1)
		{
			true_index.push_back(group_id);
		}
	}

	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		int group_id = s_shape_sample[i].face_id;
		for (size_t j = 0; j < true_index.size(); j++)
		{
			if (group_id == true_index[j])
			{
				s_shape_sample[i].face_id = j;
			}
		}
	}
	/*Deform_With_Seg test;
	test.check_normal = 1;
	test.GetPoints(s_shape_sample, t_shape_sample);
	test.GetConnection(s_connection);
	cout << "true_index.size() " << true_index.size() << endl;
	test.SetInitialPro(true_index.size());
	test.Run();
	s_shape_sample = test.sourse_sample;
	t_shape_sample = test.target_sample;*/
	Mean_Field_Deformation m_test(s_shape_sample, t_shape_sample,s_connection,true_index.size());
	m_test.TestTemplateSample("11.ply","22.ply");
	s_shape_sample = m_test.template_sample;
	t_shape_sample = m_test.target_sample;
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		int group_id = s_shape_sample[i].face_id;
		s_shape_sample[i].face_id = true_index[group_id];
		//t_shape_sample[i].face_id = true_index[t_shape_sample[i].face_id];
	}

	/*for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		int group_id = t_shape_sample[i].face_id;
		t_shape_sample[i].face_id = true_index[group_id];
	}*/
}

void DeformFromShape::Deformation()
{
	//float smooth = 2.0;
	//float data = 1.0;
	//for (int ite = 0; ite < 5; ite++)
	//{
	//	//Deform_Box test;
	//	Deform_Box_New test;
	//	test.check_normal = 1;
	//	test.GetPoints(s_shape_sample, t_shape_sample);
	//	test.GetConnection(s_connection);
	//	test.Find_Soft_Map();
	//	test.Find_Soft_Map_T();
	//	cout << "Find_Soft_Map" << endl;
	//	smooth -= 0.1*ite;
	//	data += 0.1*ite;
	//	cout << "begin deform " << endl;
	//	test.Deform_Soft(smooth, data);
	//	cout << "end deform " << endl;
	//	s_shape_sample = test.deform_box_sample;
	//	ReNormal(s_shape_sample);
	//}
}

void DeformFromShape::ReSetFromLearing(string file_name)
{
	vector<vector<vec3>> new_sample;
	vector<int> part_sample;
	new_sample.clear();
	part_sample.clear();
	ifstream fin(file_name);
	float x, y, z;
	int id;
	int index;
	while (fin >> x >> y >> z >> index >> id)
	{
		vec3 pos(x, y, z);
		int is_new_part = 1;
		for (size_t i = 0; i < part_sample.size(); i++)
		{
			if (part_sample[i] == id)
			{
				is_new_part = 0;
			}
		}
		if (is_new_part == 1)
		{
			vector<vec3> new_part_sample;
			new_part_sample.clear();
			new_sample.push_back(new_part_sample);
			part_sample.push_back(id);
		}
		new_sample.back().push_back(pos);
	}


	// seg templaet
	vector < vector < Sample >> s_sample_by_part;
	s_sample_by_part.clear();
	s_sample_by_part.resize(valid_group.size());
	for (size_t j = 0; j < s_shape_sample.size(); j++)
	{
		for (size_t i = 0; i < valid_group.size(); i++)
		{
			if (valid_group[i] == s_shape_part[j])
			{
				s_sample_by_part[i].push_back(s_shape_sample[j]);
			}
		}
	}

	// reset
	for (size_t i = 0; i < valid_group.size(); i++)
	{
		for (size_t j = 0; j < part_sample.size(); j++)
		{
			if (valid_group[i] == part_sample[j] && s_sample_by_part[i].size() == new_sample[j].size())
			{
				for (size_t jj = 0; jj < new_sample[j].size(); jj++)
				{
					s_sample_by_part[i][jj].position = new_sample[j][jj];
				}
			}
		}
	}
	// defomration 
	s_shape_sample.clear();
	for (size_t i = 0; i < valid_group.size(); i++)
	{
		for (int j = 0; j < s_sample_by_part[i].size(); j++)
		{
			s_shape_sample.push_back(s_sample_by_part[i][j]);
		}
	}

	//Deformation();
}

void DeformFromShape::ReNormal(vector<Sample> &sample_list)
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

void DeformFromShape::OutPutAndVisual(string p_file, string s_file, int out_type)
{
	cout << "begin output " << endl;
	if(out_type == 0)
	{
		ofstream fout(p_file);
		fout << "ply" << endl;
		fout << "format ascii 1.0" << endl;
		fout << "element vertex " << s_shape_sample.size() << endl;
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
		for (size_t i = 0; i< s_shape_sample.size(); i++)
		{
			ivec3 color = color_list[s_shape_part[i]];
			//color = template_sample_color[i];
			fout << s_shape_sample[i].position[0] << " " << (s_shape_sample[i].position[1]) << " " << (s_shape_sample[i].position[2]) << " ";
			fout << s_shape_sample[i].normal[0] << " " << s_shape_sample[i].normal[1] << " " << s_shape_sample[i].normal[2] << " ";
			fout << color[0] << " " << color[1] << " " << color[2] << endl;
		}

		ofstream fout_s(s_file);
		for (size_t i = 0; i< s_shape_sample.size(); i++)
		{
			fout_s << s_shape_sample[i].position[0] << " " << (s_shape_sample[i].position[1]) << " " << (s_shape_sample[i].position[2]) << " ";
			fout_s << s_shape_sample[i].normal[0] << " " << s_shape_sample[i].normal[1] << " " << s_shape_sample[i].normal[2] << " ";
			fout_s << s_shape_part[i] << " ";
			fout_s << s_shape_index[i] << endl;
			//fout_s << 1 << " ";
			//fout_s << i << endl;
		}
	}
	else
	{
		ofstream fout(p_file);
		fout << "ply" << endl;
		fout << "format ascii 1.0" << endl;
		fout << "element vertex " << t_shape_sample.size() << endl;
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
		for (size_t i = 0; i< t_shape_sample.size(); i++)
		{
			ivec3 color = color_list[t_shape_sample[i].face_id];
			//color = template_sample_color[i];
			fout << t_shape_sample[i].position[0] << " " << (t_shape_sample[i].position[1]) << " " << (t_shape_sample[i].position[2]) << " ";
			fout << t_shape_sample[i].normal[0] << " " << t_shape_sample[i].normal[1] << " " << t_shape_sample[i].normal[2] << " ";
			fout << color[0] << " " << color[1] << " " << color[2] << endl;
		}

		ofstream fout_s(s_file);
		for (size_t i = 0; i< t_shape_sample.size(); i++)
		{
			fout_s << t_shape_sample[i].position[0] << " " << (t_shape_sample[i].position[1]) << " " << (t_shape_sample[i].position[2]) << " ";
			fout_s << t_shape_sample[i].normal[0] << " " << t_shape_sample[i].normal[1] << " " << t_shape_sample[i].normal[2] << " ";
			fout_s << t_shape_sample[i].face_id <<" ";
			fout_s << 1 << endl;
		}
	}
}

void DeformFromShape::RefineTargetSample()
{
	vec3 s_max(-100, -100, -100);
	vec3 s_min(100, 100, 100);
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		if (s_shape_sample[i].position[0] > s_max[0])
		{
			s_max[0] = s_shape_sample[i].position[0];
		}
		if (s_shape_sample[i].position[1] > s_max[1])
		{
			s_max[1] = s_shape_sample[i].position[1];
		}
		if (s_shape_sample[i].position[2] > s_max[2])
		{
			s_max[2] = s_shape_sample[i].position[2];
		}

		if (s_shape_sample[i].position[0] < s_min[0])
		{
			s_min[0] = s_shape_sample[i].position[0];
		}
		if (s_shape_sample[i].position[1] < s_min[1])
		{
			s_min[1] = s_shape_sample[i].position[1];
		}
		if (s_shape_sample[i].position[2] < s_min[2])
		{
			s_min[2] = s_shape_sample[i].position[2];
		}
	}

	cout << s_max << " " << s_min << endl;
	vec3 t_max(-100, -100, -100);
	vec3 t_min(100, 100, 100);
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		if (t_shape_sample[i].position[0] > t_max[0])
		{
			t_max[0] = t_shape_sample[i].position[0];
		}
		if (t_shape_sample[i].position[1] > t_max[1])
		{
			t_max[1] = t_shape_sample[i].position[1];
		}
		if (t_shape_sample[i].position[2] > t_max[2])
		{
			t_max[2] = t_shape_sample[i].position[2];
		}

		if (t_shape_sample[i].position[0] < t_min[0])
		{
			t_min[0] = t_shape_sample[i].position[0];
		}
		if (t_shape_sample[i].position[1] < t_min[1])
		{
			t_min[1] = t_shape_sample[i].position[1];
		}
		if (t_shape_sample[i].position[2] < t_min[2])
		{
			t_min[2] = t_shape_sample[i].position[2];
		}
	}

	// move target

	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		t_shape_sample[i].position -= (t_min + t_max)*0.5f - (s_max + s_min)*0.5f ;
	}

	Compute_Feature test(t_shape_sample);
	t_shape_sample = test.GetFeaturedSample(); 

	vector<vec3> t_sample;
	t_sample.clear();
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		t_sample.push_back(t_shape_sample[i].position);
	}
	vector<vec3> s_sample;
	s_sample.clear();
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		s_sample.push_back(s_shape_sample[i].position);
	}
	ICP test1(t_sample,s_sample);
	t_sample = test1.RunICP();
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		t_shape_sample[i].position = t_sample[i];
	}


}

void DeformFromShape::ScaleSample()
{
	vec3 s_max(-100, -100, -100);
	vec3 s_min(100, 100, 100);
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		if (s_shape_sample[i].position[0] > s_max[0])
		{
			s_max[0] = s_shape_sample[i].position[0];
		}
		if (s_shape_sample[i].position[1] > s_max[1])
		{
			s_max[1] = s_shape_sample[i].position[1];
		}
		if (s_shape_sample[i].position[2] > s_max[2])
		{
			s_max[2] = s_shape_sample[i].position[2];
		}

		if (s_shape_sample[i].position[0] < s_min[0])
		{
			s_min[0] = s_shape_sample[i].position[0];
		}
		if (s_shape_sample[i].position[1] < s_min[1])
		{
			s_min[1] = s_shape_sample[i].position[1];
		}
		if (s_shape_sample[i].position[2] < s_min[2])
		{
			s_min[2] = s_shape_sample[i].position[2];
		}
	}


	vec3 t_max(-100, -100, -100);
	vec3 t_min(100, 100, 100);
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		if (t_shape_sample[i].position[0] > t_max[0])
		{
			t_max[0] = t_shape_sample[i].position[0];
		}
		if (t_shape_sample[i].position[1] > t_max[1])
		{
			t_max[1] = t_shape_sample[i].position[1];
		}
		if (t_shape_sample[i].position[2] > t_max[2])
		{
			t_max[2] = t_shape_sample[i].position[2];
		}

		if (t_shape_sample[i].position[0] < t_min[0])
		{
			t_min[0] = t_shape_sample[i].position[0];
		}
		if (t_shape_sample[i].position[1] < t_min[1])
		{
			t_min[1] = t_shape_sample[i].position[1];
		}
		if (t_shape_sample[i].position[2] < t_min[2])
		{
			t_min[2] = t_shape_sample[i].position[2];
		}
	}

	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		float scale_x = 1.0;
		float scale_y = 1.0;
		float scale_z = 1.0f;
		if (s_shape_sample[i].position[0] > 0)
		{
			s_shape_sample[i].position[0] *= (t_max[0] / s_max[0]);
			scale_x *= (t_max[0] / s_max[0]);
		}
		if (s_shape_sample[i].position[0] < 0)
		{
			s_shape_sample[i].position[0] *= (t_min[0] / s_min[0]);
			scale_x *= (t_min[0] / s_min[0]);
		}

		if (s_shape_sample[i].position[1] > 0)
		{
			s_shape_sample[i].position[1] *= (t_max[1] / s_max[1]);
			scale_y *= (t_max[1] / s_max[1]);
		}
		if (s_shape_sample[i].position[1] < 0)
		{
			s_shape_sample[i].position[1] *= (t_min[1] / s_min[1]);
			scale_y *= (t_min[1] / s_min[1]);
		}

		if (s_shape_sample[i].position[2] > 0)
		{
			s_shape_sample[i].position[2] *= (t_max[2] / s_max[2]);
			scale_z *= (t_max[2] / s_max[2]);
		}
		if (s_shape_sample[i].position[2] < 0)
		{
			s_shape_sample[i].position[2] *= (t_min[2] / s_min[2]);
			scale_z *= (t_min[2] / s_min[2]);
		}
		s_shape_sample[i].normal[0] /= scale_x;
		s_shape_sample[i].normal[1] /= scale_y;
		s_shape_sample[i].normal[2] /= scale_z;
		s_shape_sample[i].normal = normalize(s_shape_sample[i].normal);

	}

}


void DeformFromShape::SetValidTemplateSample()
{
	vector<int> is_valid;
	is_valid.resize(s_shape_sample.size(), 0);
	
	/*vector<NamedPoint> points;
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		points.push_back(NamedPoint(s_shape_sample[i].position[0], s_shape_sample[i].position[1], s_shape_sample[i].position[2], i));
	}
	int kNum = 20;
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for (size_t i = 0; i< t_shape_sample.size(); i++)
	{
		vec3 p = t_shape_sample[i].position;
		NamedPoint query(p[0], p[1], p[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		for (int k = 1; k < kNum; k++)
		{
			int nearest_id = stree.getElements()[k_closest_elems[k].getIndex()].id;
			if ((t_shape_sample[i].normal DOT s_shape_sample[nearest_id].normal) > 0)
			{
				is_valid[nearest_id] = 1;
			}
		}
	}*/

	for (size_t id = 0; id < valid_group.size(); id++)
	{
		vector<NamedPoint> points;
		for (size_t i = 0; i < s_shape_sample.size(); i++)
		{
			if (s_shape_part[i] == valid_group[id])
			{
				points.push_back(NamedPoint(s_shape_sample[i].position[0], s_shape_sample[i].position[1], s_shape_sample[i].position[2], i));
			}
			
		}
		int kNum = 20;
		KDTree3<NamedPoint> stree(points.begin(), points.end());
		float dist_average = 0;
		for (size_t i = 0; i< t_shape_sample.size(); i++)
		{
			vec3 p = t_shape_sample[i].position;
			NamedPoint query(p[0], p[1], p[2]);
			BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
			stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
			for (int k = 1; k < kNum; k++)
			{
				int nearest_id = stree.getElements()[k_closest_elems[k].getIndex()].id;
				is_valid[nearest_id] = 1;

			}
		}
	}
	/*vector<NamedPoint> points;
	for (size_t i = 0; i < t_shape_sample.size(); i++)
	{
		points.push_back(NamedPoint(t_shape_sample[i].position[0], t_shape_sample[i].position[1], t_shape_sample[i].position[2], i));
	}
	vector<float> dis_per_sample;
	dis_per_sample.clear();
	int kNum = 1;
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	float dist_average = 0;
	for (size_t i = 0; i< s_shape_sample.size(); i++)
	{
		vec3 p = s_shape_sample[i].position;
		NamedPoint query(p[0], p[1], p[2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(kNum);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
		int nearest_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
		dis_per_sample.push_back(dist(p, t_shape_sample[nearest_id].position));
		dist_average += dis_per_sample.back();
	}
	dist_average /= s_shape_sample.size();*/

	vector<Sample> sample_new;
	sample_new.clear();
	for (size_t i = 0; i < s_shape_sample.size(); i++)
	{
		if (is_valid[i] == 1)
		{
			sample_new.push_back(s_shape_sample[i]);
		}
		/*if (dis_per_sample[i] < dist_average *2.0)
		{
			sample_new.push_back(s_shape_sample[i]);
		}*/
	}
	s_shape_sample = sample_new;

	ofstream fout("after_cut.ply");
	fout << "ply" << endl;
	fout << "format ascii 1.0" << endl;
	fout << "element vertex " << s_shape_sample.size() << endl;
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
	for (size_t i = 0; i< s_shape_sample.size(); i++)
	{
		ivec3 color = color_list[i];
		//color = template_sample_color[i];
		fout << s_shape_sample[i].position[0] << " " << (s_shape_sample[i].position[1]) << " " << (s_shape_sample[i].position[2]) << " ";
		fout << s_shape_sample[i].normal[0] << " " << s_shape_sample[i].normal[1] << " " << s_shape_sample[i].normal[2] << " ";
		fout << color[0] << " " << color[1] << " " << color[2] << endl;
	}
}