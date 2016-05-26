#include "ShapeSynthesis.h"


ShapeSynthesis::ShapeSynthesis(void)
{

}


ShapeSynthesis::~ShapeSynthesis(void)
{

}

ShapeSynthesis::ShapeSynthesis(string point_file, string m_path, string p_path, string out_mesh,int deformation_type)
{
	deformation_mode = deformation_type;
	mesh_path = m_path;
	point_path = p_path;
	out_path = out_mesh;
	loadControlPoint(point_file);
	findBoudaryPoint();
	makeControlPointSymmetric();

}

ShapeSynthesis::ShapeSynthesis(string point_file, string m_path, string p_path, string connect_file, string bound_path, string out_mesh, int deformation_type)
{
	deformation_mode = deformation_type;
	mesh_path = m_path;
	point_path = p_path;
	out_path = out_mesh;
	boundary_path = bound_path;
	loadControlPoint(point_file);
	loadPartConnetion(connect_file);
	//findBoundarySample();
	cout << "begin load bounday " << endl;
	loadMeshBoundary();
	makeControlPointSymmetric();
}

void ShapeSynthesis::loadControlPoint(string point_file)
{
	total_point = 0;
	ifstream fin(point_file);
	float xp,yp,zp;
	int point_index, part_id;
	string model_name;
	int int1,int2;
	control_point.clear();
	model_list.clear();
	part_list.clear();
	fin >> deforma_prob;
	while(fin >> xp >> yp >> zp >> point_index >> part_id >> model_name >> int1 >> int2)
	{
		total_point ++;
		vec3 pos(xp,yp,zp);
		int is_new = 1;
		for(size_t i = 0; i < part_list.size(); i++)
		{
			if(part_id == part_list[i])
			{
				is_new = 0;
			}
		}
		if(is_new == 1)
		{
			vector<vec3> p_point;
			p_point.clear();
			control_point.push_back(p_point);
			part_list.push_back(part_id);
			model_list.push_back(model_name);
		}
		control_point.back().push_back(pos);
	}

	cout << "load " << part_list.size() << " part" <<endl;
	for(size_t i = 0; i < part_list.size(); i++)
	{
		cout << "part " << i << " wiht label "<< part_list[i] << " " << control_point[i].size() << " total point wiht model " << model_list[i] <<  endl;
	}
	vec3 x(-1,1,1);
	vec3 y(1,-1,1);
	vec3 z(1,1,-1);
	float err_x = errWithSymmtric(x);
	float err_y = errWithSymmtric(y);
	float err_z = errWithSymmtric(z);
	if( err_x <err_y && err_x <err_z)
	{
		symmrtric_vec = x;
	}
	if(err_y <err_x && err_y <err_z)
	{
		symmrtric_vec = y;
	}
	if(err_z <err_y && err_z <err_x)
	{
		symmrtric_vec = z;
	}
	cout << symmrtric_vec << endl;
	vector<vector<vec3>> control_point_syeemtric;
	control_point_syeemtric.clear();
	vector<vec3> center_list = getPatrCenter();
	symmtric_part_list.clear();
	for (size_t i = 0; i < center_list.size(); i++)
	{
		vec3 center_symmtric_i(center_list[i][0]*symmrtric_vec[0],center_list[i][1]*symmrtric_vec[1],center_list[i][2]*symmrtric_vec[2]);
		float min_dis = FLT_MAX;
		int index_min = -1;
		for(size_t j = 0; j < center_list.size();j++ )
		{
			if(dist(center_symmtric_i,center_list[j]) < min_dis)
			{
				min_dis = dist(center_symmtric_i,center_list[j]);
				index_min = j;
			}
		}
		cout << "part " << part_list[i]  << "  and " << "part " << part_list[index_min] << " are symmtric" << endl;
		cout << center_list[i] << " " << center_list[index_min] << endl;
		symmtric_part_list.push_back(index_min);
	}
	for (size_t i = 0; i < center_list.size(); i++)
	{
		vector<vec3> part_sample;
		part_sample.clear();
		for(size_t j = 0; j < control_point[i].size(); j++)
		{
			part_sample.push_back(control_point[i][j]);
		}
		for(size_t j = 0; j < control_point[symmtric_part_list[i]].size(); j++)
		{
			vec3 sample = control_point[symmtric_part_list[i]][j];
			sample[0] = sample[0]*symmrtric_vec[0];
			sample[1] = sample[1]*symmrtric_vec[1];
			sample[2] = sample[2]*symmrtric_vec[2];
			part_sample.push_back(sample);
		}
		control_point_syeemtric.push_back(part_sample);
	}
	control_point = control_point_syeemtric;
	// make it symmetric

}

void ShapeSynthesis::outputSymmetricControl(string point_file,vector<string> file_name,int index)
{
	unsigned ePos = point_file.find_last_of(".");
	string exten_name = point_file.substr(ePos,point_file.size() - ePos);
	string newFile = out_path;
	newFile.append("//");
	newFile.append(point_file.substr(0, ePos));
	newFile.append("_");
	newFile.append(to_string(index));
	newFile.append(exten_name);
	ofstream fout(newFile);
	fout << deforma_prob << endl;
	int count = 0;
	for(size_t i = 0; i < control_point.size(); i++)
	{
		for(size_t j = 0; j < control_point[i].size(); j++)
		{
			fout << control_point[i][j][0] <<" " << control_point[i][j][1] <<" " <<control_point[i][j][2] <<" ";
			fout <<count <<" " <<part_list[i] <<" "<<  file_name[i] <<" " << 0 <<" " << 1 << endl;
			count++;
		}
	}
}

void ShapeSynthesis::makeControlPointSymmetric()
{
	// check the symmetric plane
	/*vector<vector<string>> run_list = getSymmetricModelList();
	for(size_t i = 0; i < run_list.size(); i++)
	{
		orignal_point = loadOrignalPoint(run_list[i],i);
		loadOrignalMesh(run_list[i],i);
	}*/
	orignal_point = loadOrignalPoint(model_list,0);
	loadOrignalMesh(model_list,0);
}

vector<int> ShapeSynthesis::findBoundaryIndex(int first_part_id, int second_part_id)
{
	    vector<float> min_dis;
		min_dis.clear();
	    vector<NamedPoint> points;
		for (size_t i = 0; i < control_point[second_part_id].size(); i++)
		{
			points.push_back(NamedPoint(control_point[second_part_id][i][0], control_point[second_part_id][i][1], control_point[second_part_id][i][2], i));
		}
		KDTree3<NamedPoint> stree(points.begin(), points.end());
		for(size_t j = 0; j < control_point[first_part_id].size(); j++)
		{
			NamedPoint query(control_point[first_part_id][j][0],control_point[first_part_id][j][1],control_point[first_part_id][j][2]);
			BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
			stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
			int near_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
			min_dis.push_back(dist(control_point[first_part_id][j],control_point[second_part_id][near_id]));
		}
		vector<float> min_dis_sort = min_dis;
		int precentage_thread = (int)(.1f * (float)min_dis_sort.size());
		std::nth_element(min_dis_sort.begin(), min_dis_sort.begin() + precentage_thread,min_dis_sort.end());
		float dis_threshold = min_dis_sort[precentage_thread];
		vector<int> boundary_index;
		boundary_index.clear();
		for(size_t i = 0; i < min_dis.size(); i++)
		{
			if(min_dis[i] < dis_threshold)
			{
				boundary_index.push_back(i);
			}
		}
		return boundary_index;
}

void ShapeSynthesis::findBoundarySample()
{
	boundary_firstpart.clear();
	boundary_second.clear();
	for(size_t i = 0; i < first_part_list.size(); i++)
	{
		boundary_firstpart.push_back(findBoundaryIndex(first_part_list[i],second_part_list[i]));
		boundary_second.push_back(findBoundaryIndex(second_part_list[i],first_part_list[i]));
	}
}

vector<int> ShapeSynthesis::getCenterPartBoundary(string center_file,int part_id)
{
	vector<int> bound_list;
	bound_list.clear();
	string para;
	ifstream fin(center_file);
	while(fin >> para)
	{
		if(para == "boundary_with")
		{
			int part;
			fin >> part;
			if(part == part_id)
			{
				while(fin >> para)
				{
					if(para != "boundary_with")
					{
						bound_list.push_back(stoi(para));
					}
					else
					{
						return bound_list;
					}
				}
			}
		}
	}

	return bound_list;
}

vector<int> ShapeSynthesis::getPartBoundary(string part_file)
{
	vector<int> bound_list;
	bound_list.clear();
	ifstream fin(part_file);
	int index;
	while(fin >> index)
	{
		bound_list.push_back(index);
	}
	return bound_list;
}


void ShapeSynthesis::loadMeshBoundary()
{
	boundary_firstpart.clear();
	boundary_second.clear();
	for(size_t i = 0; i < first_part_list.size(); i++)
	{
		cout << first_part_list[i] <<" " <<second_part_list[i] << endl;
		string center_part(boundary_path);
		center_part.append("//");
		center_part.append(model_list[first_part_list[i]]);
		center_part.append("_center.txt");
		cout << center_part << endl;
		boundary_firstpart.push_back(getCenterPartBoundary(center_part,second_part_list[i]));
		string side_part(boundary_path);
		side_part.append("//");
		side_part.append(model_list[second_part_list[i]]);
		side_part.append("_");
		side_part.append(to_string(second_part_list[i]));
		side_part.append(".txt");
		cout << side_part << endl;
		boundary_second.push_back(getPartBoundary(side_part));
	}
}

float ShapeSynthesis::errWithSymmtric(vec3 symmtric_vector)
{
	float fit_err = 0.0f;
	vector<NamedPoint> points;
	int point_count = 0;
	for (size_t i = 0; i < control_point.size(); i++)
	{
		for(size_t j = 0; j < control_point[i].size(); j++)
		{
			points.push_back(NamedPoint(control_point[i][j][0], control_point[i][j][1], control_point[i][j][2], point_count));
		}
		point_count++;
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for (size_t i = 0; i < control_point.size(); i++)
	{
		for(size_t j = 0; j < control_point[i].size(); j++)
		{
			vec3 check_point(control_point[i][j][0]*symmtric_vector[0], control_point[i][j][1]*symmtric_vector[1], control_point[i][j][2]*symmtric_vector[2]);
			NamedPoint query(check_point[0],check_point[1],check_point[2]);
			BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
			stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
			vec3 close_p(stree.getElements()[k_closest_elems[0].getIndex()].position[0],stree.getElements()[k_closest_elems[0].getIndex()].position[1],stree.getElements()[k_closest_elems[0].getIndex()].position[2]);
			fit_err += dist(check_point,close_p);
		}

	}
	cout << "fit_err  " << fit_err << endl;
	return fit_err;
}

vector<vec3> ShapeSynthesis::getPatrCenter()
{
	vector<vec3> center_list;
	center_list.clear();
	for (size_t i = 0; i < control_point.size(); i++)
	{
		vec3 center(0,0,0);
		for(size_t j = 0; j < control_point[i].size(); j++)
		{
			center += control_point[i][j];
		}
		center /= control_point[i].size();
		center_list.push_back(center);
	}
	return center_list;
}

vector<vector<string>> ShapeSynthesis::getSymmetricModelList()
{
	vector<vector<string>> Symmtriclist;
	Symmtriclist.clear();
	Symmtriclist.push_back(model_list);
	while(!checkSymmetric(Symmtriclist))
	{
		for(size_t i = 0; i < Symmtriclist.size(); i++)
		{
			for(size_t j = 0; j < Symmtriclist[i].size(); j++)
			{
				if(Symmtriclist[i][j]!= Symmtriclist[i][symmtric_part_list[j]])
				{
					string model_1 = Symmtriclist[i][j];
					string model_2 = Symmtriclist[i][symmtric_part_list[j]];
					vector<string> list_new = Symmtriclist[i];
					Symmtriclist[i][symmtric_part_list[j]] = Symmtriclist[i][j];
					list_new[j] = model_2;
					Symmtriclist.push_back(list_new);
					break;
				}
			}
		}
	}
	return Symmtriclist;
}

bool ShapeSynthesis::checkSymmetric(vector<vector<string>> symmtric_list)
{
	//cout << symmtric_list.size() << endl;
	for(size_t i = 0; i < symmtric_list.size(); i++)
	{
		for(size_t j = 0; j < symmtric_list[i].size(); j++)
		{
			if(symmtric_list[i][j]!= symmtric_list[i][symmtric_part_list[j]])
			{
				return false;
			}
		}
	}
	return true;
}

void ShapeSynthesis::loadSymmtricPart(string file_name)
{
	symmtric_part_list.clear();
	ifstream fin(file_name);
	int part_id;
	while(fin >> part_id)
	{
		symmtric_part_list.push_back(part_id);
	}
}

void ShapeSynthesis::loadPartConnetion(string file_name)
{
	first_part_list.clear();
	second_part_list.clear();
	ifstream fin(file_name);
	int part_1, part_2;
	while(fin >> part_1 >> part_2)
	{
		first_part_list.push_back(part_1);
		second_part_list.push_back(part_2);
	}
}

vector<TriMesh*> ShapeSynthesis::loadOrignalMesh(vector<string> mesh_list,int index)
{
	vector<TriMesh*> shape_mesh;
	shape_mesh.clear();
	for(size_t i = 0; i < mesh_list.size(); i++)
	{
		string mesh_file =  mesh_path;
		mesh_file.append("\\");
		mesh_file.append(mesh_list[i]);
		mesh_file.append("\\");
		mesh_file.append(to_string(part_list[i]));
		mesh_file.append(".obj");
		TriMesh* mesh;
		mesh = TriMesh::read(mesh_file);
		if(mesh == NULL)
		{
			exit(0);
		}
		shape_mesh.push_back(mesh);
	}
	if(deformation_mode == 1)
	{
		deformation(shape_mesh);
	}
	assembelPart(shape_mesh,orignal_point);
	TriMesh* mesh_test;
	mesh_test = new TriMesh;
	int current_vertex_size = 0;
	for(size_t i = 0; i < shape_mesh.size(); i++)
	{
		for(size_t j = 0; j < shape_mesh[i]->vertices.size();j++)
		{
			mesh_test->vertices.push_back(shape_mesh[i]->vertices[j]);
		}
		for(size_t j = 0; j < shape_mesh[i]->faces.size();j++)
		{
			TriMesh::Face f(shape_mesh[i]->faces[j][0] + current_vertex_size,shape_mesh[i]->faces[j][1] + current_vertex_size,shape_mesh[i]->faces[j][2] + current_vertex_size);
			mesh_test->faces.push_back(f);
		}
		current_vertex_size += shape_mesh[i]->vertices.size();

	}
	string out_file_name(out_path);
	//out_file_name.append("\\");
	//out_file_name.append(to_string(index));
	//out_file_name.append(".obj");
	if(deformation_mode == 0)
	{
		mesh_test->write(out_file_name);
	}
	else
	{
		ofstream fout(out_file_name);
		for(size_t i = 0; i < mesh_test->vertices.size(); i++)
		{
			fout <<"v " << mesh_test->vertices[i][0] << " " << mesh_test->vertices[i][1] <<" " << mesh_test->vertices[i][2] <<" " << 1 << " " << 0 <<" "<< 0 << endl;
		}
		for(size_t i = 0; i < mesh_test->faces.size(); i++)
		{
			fout <<"f " <<  mesh_test->faces[i][0] + 1 << " " << mesh_test->faces[i][1]+ 1 <<" " << mesh_test->faces[i][2]+ 1 << endl;
		}
	}

}

void ShapeSynthesis::deformation(vector<TriMesh *> &mesh_list)
{
	for(size_t i = 0; i < mesh_list.size(); i++)
	{
		if(i != 3)
		{
		 cout << "begin sample size" << orignal_point[i].size() <<endl;
		 EmbeddedDeformation test(mesh_list[i],orignal_point[i],control_point[i]);
		 cout << "end sample size" << orignal_point[i].size() <<endl;
		}
	}
}

void ShapeSynthesis::findBoudaryPoint()
{
	boundary_firstpart.clear();
	boundary_second.clear();
	first_part_list.clear();
	second_part_list.clear();
	vector<vec3> point_list;
	point_list.clear();
	vector<int> part_pre_point;
	part_pre_point.clear();
	vector<int> cum_point_size;
	cum_point_size.clear();
	cum_point_size.push_back(0);
	for (size_t i = 0; i < control_point.size(); i++)
	{
		for(size_t j = 0; j < control_point[i].size(); j++)
		{
			point_list.push_back(control_point[i][j]);
			part_pre_point.push_back(i);
		}
		cum_point_size.push_back(control_point[i].size());
	}
	vector<vector<int>> boundary_list;
	boundary_list.clear();
	vector<NamedPoint> points;
	for (size_t i = 0; i < point_list.size(); i++)
	{
		points.push_back(NamedPoint(point_list[i][0], point_list[i][1], point_list[i][2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for (size_t i = 0; i < control_point.size(); i++)
	{
		vector<int> is_boundary;
		is_boundary.resize(control_point[i].size(),-1);
		for(size_t j = 0; j < control_point[i].size(); j++)
		{
			NamedPoint query(control_point[i][j][0],control_point[i][j][1],control_point[i][j][2]);
			BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(BOUNDARY_SIZE);
			stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
			for (size_t ind = 0; ind< BOUNDARY_SIZE; ind++)
			{
				int near_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
				if(part_pre_point[near_id] != i)
				{
					is_boundary[j] = part_pre_point[near_id];
				}
			}
		}
		boundary_list.push_back(is_boundary);
	}
	for(size_t i = 0; i < boundary_list.size(); i++)
	{
		for(size_t j = i+1; j < boundary_list.size(); j++)
		{
			int is_new_pair = 0;
			vector<int> firstpart;
			vector<int> second_part;
			for(size_t jj  = 0; jj < boundary_list[i].size(); jj++)
			{
				if(boundary_list[i][jj] == j)
				{
					is_new_pair = 1;
					firstpart.push_back(jj);
				}
			}
			if(is_new_pair == 1)
			{
				is_new_pair = 0;
				for(size_t jj  = 0; jj < boundary_list[j].size(); jj++)
				{
					if(boundary_list[j][jj] == i)
					{
						is_new_pair = 1;
						second_part.push_back(jj);
					}
				}
			}
			if(is_new_pair == 1)
			{
				first_part_list.push_back(i);
				second_part_list.push_back(j);
				boundary_firstpart.push_back(firstpart);
				boundary_second.push_back(second_part);
			}
		}
	}

	for(size_t i = 0; i < first_part_list.size(); i++)
	{
		cout << "part " << part_list[first_part_list[i]] << " connects to " << part_list[second_part_list[i]] << endl;
	}
}

vector<vector<vec3>> ShapeSynthesis::loadOrignalPoint(vector<string> mesh_list, int index)
{
	vector<vector<vec3>> shape_sample;
	shape_sample.clear();
	int total_point = 0;
	for(size_t i = 0; i < mesh_list.size(); i++)
	{
		string point_file =  point_path;
		point_file.append("\\");
		point_file.append(mesh_list[i]);
		point_file.append("\\");
		point_file.append(to_string(part_list[i]));
		point_file.append(".txt");
		ifstream fin(point_file);
		cout << point_file << endl;
		vector<vec3> part_point;
		part_point.clear();
		float x,y,z;
		while(fin >> x >> y >> z)
		{
			vec3 pos(x,y,z);
			part_point.push_back(pos);
		}
		shape_sample.push_back(part_point);
		total_point  += part_point.size();
	}
	vector<vector<vec3>> shape_sample_symmtric;
	shape_sample_symmtric.clear();
	for (size_t i = 0; i < shape_sample.size(); i++)
	{
		vector<vec3> part_sample;
		for(size_t j = 0; j < shape_sample[i].size(); j++)
		{

			part_sample.push_back(shape_sample[i][j]);
		}
		for(size_t j = 0; j < shape_sample[symmtric_part_list[i]].size(); j++)
		{
			vec3 sample = shape_sample[symmtric_part_list[i]][j];
			sample[0] = sample[0]*symmrtric_vec[0];
			sample[1] = sample[1]*symmrtric_vec[1];
			sample[2] = sample[2]*symmrtric_vec[2];
			part_sample.push_back(sample);
		}
		shape_sample_symmtric.push_back(part_sample);
	}
	shape_sample = shape_sample_symmtric;

	return shape_sample;
}

void ShapeSynthesis::assembelPart(vector<TriMesh *> &mesh_list, vector<vector<vec3>> sample_list)
{
	cout << "begin assmbel " << endl;
	for(size_t i = 1; i < first_part_list.size(); i++)
	{
		int first_mesh = first_part_list[i];
		cout << first_mesh << endl;
		int second_mesh = second_part_list[i];
		cout << second_mesh << endl;
		vec3 first_boundary_center = getCenterOfBoundary(mesh_list[first_mesh], sample_list[first_mesh],boundary_firstpart[i]);
		cout << " first_boundary_center  "<< first_boundary_center  << endl;
		vec3 second_boundary_center = getCenterOfBoundary(mesh_list[second_mesh], sample_list[second_mesh],boundary_second[i]);
		cout << " second_boundary_center   "<< second_boundary_center   << endl;
		float scale_factor= MOVING_SCALE;
		if(second_mesh == 3)
		{
			scale_factor = 1.5f;
		}
		for(size_t j = 0; j < mesh_list[second_mesh]->vertices.size(); j++)
		{
			mesh_list[second_mesh]->vertices[j][0] =  mesh_list[second_mesh]->vertices[j][0] + (first_boundary_center[0] - second_boundary_center[0])*scale_factor;
			mesh_list[second_mesh]->vertices[j][1] =  mesh_list[second_mesh]->vertices[j][1] + (first_boundary_center[1] - second_boundary_center[1])*scale_factor;
			mesh_list[second_mesh]->vertices[j][2] =  mesh_list[second_mesh]->vertices[j][2] + (first_boundary_center[2] - second_boundary_center[2])*scale_factor;
		}
	}

	// align wing
	vec3 center_wing_1(0,0,0);
	for(size_t j = 0; j < mesh_list[1]->vertices.size(); j++)
	{
		center_wing_1 += mesh_list[1]->vertices[j];
	}
	center_wing_1 /= mesh_list[1]->vertices.size();
	vec3 center_wing_2(0,0,0);
	for(size_t j = 0; j < mesh_list[2]->vertices.size(); j++)
	{
		center_wing_2 += mesh_list[2]->vertices[j];
	}
	center_wing_2 /= mesh_list[2]->vertices.size();
	for(size_t j = 0; j < mesh_list[1]->vertices.size(); j++)
	{
		mesh_list[1]->vertices[j][2] = mesh_list[1]->vertices[j][2] - center_wing_1[2] + center_wing_2[2];
	}
	// for the back and seat
	/*vec3 first_boundary_center = getCenterOfBoundary(mesh_list[0], sample_list[0],boundary_firstpart[0]);
	vec3 second_boundary_center = getCenterOfBoundary(mesh_list[1], sample_list[1],boundary_second[0]);

	// scale it
	mesh_list[0]->need_bbox();
	mesh_list[1]->need_bbox();
	for(size_t j = 0; j < mesh_list[1]->vertices.size(); j++)
	{
		mesh_list[1]->vertices[j][0] = (mesh_list[1]->vertices[j][0] - (mesh_list[1]->bbox.max[0] + mesh_list[1]->bbox.min[0])*0.5f)/(mesh_list[1]->bbox.max[0] - mesh_list[1]->bbox.min[0])*(mesh_list[0]->bbox.max[0] - mesh_list[0]->bbox.min[0]) +  (mesh_list[0]->bbox.max[0] + mesh_list[0]->bbox.min[0])*0.5;
		mesh_list[1]->vertices[j][1] = mesh_list[1]->vertices[j][1] + (first_boundary_center[1] - second_boundary_center[1])*1.05;
		mesh_list[1]->vertices[j][2] = mesh_list[1]->vertices[j][2] + (first_boundary_center[2] - second_boundary_center[2])*1.05;
	}*/
	
	

	
	 

	// make it symmetric
	/*for(size_t i = 0; i < part_list.size(); i++)
	{
	if(symmtric_part_list[i] != i)
	{
	vec3 first_mesh_center(0,0,0);
	vec3 second_mesh_center(0,0,0);
	for(size_t j = 0; j < mesh_list[i]->vertices.size(); j++)
	{
	first_mesh_center += mesh_list[i]->vertices[j];
	}
	first_mesh_center /= mesh_list[i]->vertices.size();
	for(size_t j = 0; j < mesh_list[symmtric_part_list[i]]->vertices.size(); j++)
	{
	second_mesh_center += mesh_list[symmtric_part_list[i]]->vertices[j];
	}
	second_mesh_center /= mesh_list[symmtric_part_list[i]]->vertices.size();
	vec3 new_first(first_mesh_center[0] + symmrtric_vec[0] * second_mesh_center[0], first_mesh_center[1] + symmrtric_vec[1] * second_mesh_center[1] , first_mesh_center[2] + symmrtric_vec[2] * second_mesh_center[2]);
	new_first *= 0.5f;
	vec3 new_second(symmrtric_vec[0] * first_mesh_center[0] + second_mesh_center[0], symmrtric_vec[1] * first_mesh_center[1] + second_mesh_center[1], symmrtric_vec[2] * first_mesh_center[2] + second_mesh_center[2]);
	new_second *= 0.5f;
	for(size_t j = 0; j < mesh_list[i]->vertices.size(); j++)
	{
	mesh_list[i]->vertices[j] = mesh_list[i]->vertices[j]- first_mesh_center + new_first;
	}
	for(size_t j = 0; j < mesh_list[symmtric_part_list[i]]->vertices.size(); j++)
	{
	mesh_list[symmtric_part_list[i]]->vertices[j] = mesh_list[symmtric_part_list[i]]->vertices[j]- second_mesh_center + new_second;
	}
	}
	}*/
}

vec3 ShapeSynthesis::getCenterOfBoundary(TriMesh * mesh, vector<vec3> sample, vector<int> bounday_list)
{
	//vector<NamedPoint> points;
	//for (size_t i = 0; i < mesh->vertices.size(); i++)
	//{
	//points.push_back(NamedPoint(mesh->vertices[i][0], mesh->vertices[i][1], mesh->vertices[i][2], i));
	//}
	//KDTree3<NamedPoint> stree(points.begin(), points.end());
	//vec3 center(0,0,0);
	//for (size_t i = 0; i < bounday_list.size(); i++)
	//{
	//int p_index = bounday_list[i];
	//NamedPoint query(sample[p_index][0],sample[p_index][1],sample[p_index][2]);
	//BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(1);
	//stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);
	//int near_id = stree.getElements()[k_closest_elems[0].getIndex()].id;
	//center += mesh->vertices[near_id];
	//}
	vec3 center(0,0,0);
	/*for (size_t i = 0; i < bounday_list.size(); i++)
	{
		int p_index = bounday_list[i];
		center += sample[p_index];
	}
	center /= bounday_list.size();*/
	for (size_t i = 0; i < bounday_list.size(); i++)
	{
		int p_index = bounday_list[i];
		center += mesh->vertices[p_index];
	}
	center /= bounday_list.size();
	return center;
}