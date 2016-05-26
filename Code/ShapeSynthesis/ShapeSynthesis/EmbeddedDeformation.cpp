#include "EmbeddedDeformation.h"


EmbeddedDeformation::EmbeddedDeformation(void)
{
}


EmbeddedDeformation::~EmbeddedDeformation(void)
{
}


EmbeddedDeformation::EmbeddedDeformation(string mesh_name, string c_file, string m_file, string out_mesh)
{
	loadMesh(mesh_name);
	generateNodeSample();
	loadconstraintPoint(c_file);
	loadMovedconstraintPoint(m_file);
	aligmentPoint();
	refineConstraintPoint();
	sampleconstraintPoint();
	buildNodeConnection();
	calculateWeight();
	initialMatrix();
	cout << "begin deformation " << endl;
	deformation();
	cout << "end deformation " << endl;
	outputMesh(out_mesh);
}

EmbeddedDeformation::EmbeddedDeformation(TriMesh* &input_mesh, vector<vec3> &original_point, vector<vec3> moved_point)
{
	mesh = input_mesh;
	constraint_point = original_point;
	moved_constraint_point = moved_point;
	aligmentPoint();
	generateNodeSample();
	//refineConstraintPoint();
	sampleconstraintPoint();
	buildNodeConnection();
	calculateWeight();
	initialMatrix();
	cout << "begin deformation " << endl;
	deformation();
	cout << "end deformation " << endl;
	original_point = constraint_point;
}

void EmbeddedDeformation::loadMesh(string mesh_name)
{
	mesh = TriMesh::read(mesh_name);
	mesh->need_normals();
}

void EmbeddedDeformation::makeControlPointSymmetry(vector<vec3> &point_set)
{
	int current_size = point_set.size();
	for(size_t i = 0; i < current_size ; i++)
	{
		vec3 pos = point_set[i];
		vec3 pos_s(-pos[0],pos[1],pos[2]);
		point_set.push_back(pos_s);
	}
}


void EmbeddedDeformation::refineConstraintPoint()
{
	vector<vec3> control_point = constraint_point;
	vector<vec3> control_point_moved = moved_constraint_point;
   vector<vector<int>> laplacian_matrix_control;
	laplacian_matrix_control.clear();
	vector<vec3> laplacian_vector_control; 
	laplacian_vector_control.clear();
	vector<NamedPoint> points;
	for (size_t i = 0; i < control_point.size(); i++)
	{
		points.push_back(NamedPoint(control_point[i][0], control_point[i][1], control_point[i][2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for (size_t i = 0; i < control_point.size(); i++)
	{
		vec3 diff = control_point[i];
		vector<int> near_vertex;
		near_vertex.clear();
		NamedPoint query(control_point[i][0], control_point[i][1], control_point[i][2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(10);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		for (size_t ind = 0; ind< 10; ind++)
		{
			int near_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			if(near_id != i)
			{
				near_vertex.push_back(near_id);
				diff = diff - control_point[near_id]/(float)(10 - 1);
			}
		}
		//cout << near_vertex.size() << endl;
		laplacian_matrix_control.push_back(near_vertex);
		laplacian_vector_control.push_back(diff);
		//cout << diff << endl;
	}
	cout << "finish finding neighbor " << endl;
	std::vector<std::map<int, double> >  LapMat;
	std::vector<std::vector<double> >	  LapB;
	LapB.resize(1);
	for (int iv = 0; iv < control_point.size(); iv++)
	{
		cout << iv << "/" << control_point.size() << "\r";
		vec3 pos_i = control_point[iv];
		Eigen::MatrixXd DMatrix = Eigen::MatrixXd::Constant(3, 7, 0);
		DMatrix(0,0) = laplacian_vector_control[iv][0];
		DMatrix(0,2) = laplacian_vector_control[iv][2];
		DMatrix(0,3) = -laplacian_vector_control[iv][1];
		DMatrix(1,0) = laplacian_vector_control[iv][1];
		DMatrix(1,1) = -laplacian_vector_control[iv][2];
		DMatrix(1,3) = laplacian_vector_control[iv][0];
		DMatrix(2,0) = laplacian_vector_control[iv][2];
		DMatrix(2,1) = laplacian_vector_control[iv][1];
		DMatrix(2,2) = -laplacian_vector_control[iv][0];
		DMatrix(2,6) = 0;
		Eigen::MatrixXd CMatrix = Eigen::MatrixXd::Constant(3*(1 + laplacian_matrix_control[iv].size()), 7, 0);
		CMatrix(0,0) = pos_i[0];
		CMatrix(0,2) = pos_i[2];
		CMatrix(0,3) = -pos_i[1];
		CMatrix(0,4) = 1;
		CMatrix(1,0) = pos_i[1];
		CMatrix(1,1) = -pos_i[2];
		CMatrix(1,3) = pos_i[0];
		CMatrix(1,5) = 1;
		CMatrix(2,0) = pos_i[2];
		CMatrix(2,1) = pos_i[1];
		CMatrix(2,2) = -pos_i[0];
		CMatrix(2,6) = 1;
		for(int j = 0; j <laplacian_matrix_control[iv].size(); j++)
		{
			int index_j = laplacian_matrix_control[iv][j];
			vec3 pos_j = control_point[index_j];
			CMatrix(3*(j+1),0) = pos_j[0];
			CMatrix(3*(j+1),2) = pos_j[2];
			CMatrix(3*(j+1),3) = -pos_j[1];
			CMatrix(3*(j+1),4) = 1;
			CMatrix(3*(j+1)+1,0) = pos_j[1];
			CMatrix(3*(j+1)+1,1) = -pos_j[2];
			CMatrix(3*(j+1)+1,3) = pos_j[0];
			CMatrix(3*(j+1)+1,5) = 1;
			CMatrix(3*(j+1)+2,0) = pos_j[2];
			CMatrix(3*(j+1)+2,1) = pos_j[1];
			CMatrix(3*(j+1)+2,2) = -pos_j[0];
			CMatrix(3*(j+1)+2,6) = 1;
		}
		Eigen::MatrixXd CTC = CMatrix.transpose()*CMatrix;
		Eigen::MatrixXd CTCI = CTC.inverse();
		Eigen::MatrixXd HMatrix = DMatrix*CTCI*(CMatrix.transpose());
		// H = L - D(C^TC)^-1C^T
		Eigen::MatrixXd LMatrix = Eigen::MatrixXd::Constant(3, 3*(1 + laplacian_matrix_control[iv].size()), 0);
		LMatrix(0,0) =  1;
		LMatrix(1,1) =  1;
		LMatrix(2,2) =  1;
		for(int j = 0; j < laplacian_matrix_control[iv].size(); j++)
		{
			LMatrix(0,(j+1)*3)     = -1.0f/ laplacian_matrix_control[iv].size();
			LMatrix(1,(j+1)*3 + 1) = -1.0f/ laplacian_matrix_control[iv].size();
			LMatrix(2,(j+1)*3 + 2) = -1.0f/ laplacian_matrix_control[iv].size();
		}
		HMatrix = LMatrix - HMatrix;
		//cout << HMatrix << endl;
		// convert to Large A
		// for dx
		LapMat.push_back(map<int, double>());
		(LapMat.back())[iv*3] =       HMatrix(0,0);
		(LapMat.back())[iv*3 + 1] =   HMatrix(0,1);
		(LapMat.back())[iv*3 + 2] =   HMatrix(0,2);
		for(int j = 0; j < laplacian_matrix_control[iv].size(); j++)
		{
			int index_j = laplacian_matrix_control[iv][j];
			(LapMat.back())[index_j*3] =       HMatrix(0,(j+1)*3);
			(LapMat.back())[index_j*3 + 1] =   HMatrix(0,(j+1)*3+1);
			(LapMat.back())[index_j*3 + 2] =   HMatrix(0,(j+1)*3+2);
		}
		LapMat.push_back(map<int, double>());
		(LapMat.back())[iv*3] =      HMatrix(1,0);
		(LapMat.back())[iv*3 + 1] =  HMatrix(1,1);
		(LapMat.back())[iv*3 + 2] =  HMatrix(1,2);
		for(int j = 0; j < laplacian_matrix_control[iv].size(); j++)
		{
			int index_j = laplacian_matrix_control[iv][j];
			(LapMat.back())[index_j*3] =      HMatrix(1,(j+1)*3);
			(LapMat.back())[index_j*3 + 1] =  HMatrix(1,(j+1)*3+1);
			(LapMat.back())[index_j*3 + 2] =  HMatrix(1,(j+1)*3+2);
		}
		LapMat.push_back(map<int, double>());
		(LapMat.back())[iv*3] =      HMatrix(2,0);
		(LapMat.back())[iv*3 + 1] =  HMatrix(2,1);
		(LapMat.back())[iv*3 + 2] =  HMatrix(2,2);
		for(int j = 0; j < laplacian_matrix_control[iv].size(); j++)
		{
			int index_j = laplacian_matrix_control[iv][j];
			(LapMat.back())[index_j*3] =      HMatrix(2,(j+1)*3);
			(LapMat.back())[index_j*3 + 1] =  HMatrix(2,(j+1)*3+1);
			(LapMat.back())[index_j*3 + 2] =  HMatrix(2,(j+1)*3+2);
		}
		LapB[0].push_back(0.0f);
		LapB[0].push_back(0.0f);
		LapB[0].push_back(0.0f);
	}
	cout << endl;
	float POSITIONWEIGHT = 1.0f;
	for (int iv = 0; iv < control_point.size(); iv++)
	{
		LapMat.push_back(map<int, double>());
		(LapMat.back())[iv*3] =  1.0f * POSITIONWEIGHT;
		LapMat.push_back(map<int, double>());
		(LapMat.back())[iv*3 + 1] =  1.0f* POSITIONWEIGHT ;
		LapMat.push_back(map<int, double>());
		(LapMat.back())[iv*3 + 2] =  1.0f * POSITIONWEIGHT;
		LapB[0].push_back(control_point_moved[iv][0]* POSITIONWEIGHT);
		LapB[0].push_back(control_point_moved[iv][1]* POSITIONWEIGHT);
		LapB[0].push_back(control_point_moved[iv][2]* POSITIONWEIGHT);
	}
	cout << "begin " << endl;
	int nr_cols = 3*control_point.size();
	cout << nr_cols << endl;
	cout << LapMat.size() << endl;
	LeastSquaresSparseSolver solver;
	solver.Init(LapMat, nr_cols);
	cout << "end intial" << endl;
	vector<vector<double> > eRes;
	solver.Solve(LapB, eRes);
	cout << "end " << endl;
	for (int iv=0; iv< control_point_moved.size(); iv++)
	{
		vec3 pos_i = control_point_moved[iv];
		pos_i[0] = eRes[0][iv*3];
		pos_i[1] = eRes[0][iv*3 + 1];
		pos_i[2] = eRes[0][iv*3 + 2];
		control_point_moved[iv] = pos_i;
		//std::cout << pos_i[0] << " "<< pos_i[1] << " " << pos_i[2] << std::endl;
	}
	moved_constraint_point = control_point_moved;
	
}

void EmbeddedDeformation::generateNodeSample()
{
	vector<ivec3> face_list;
	face_list.clear();
	for(size_t i = 0; i < mesh->faces.size(); i++)
	{
		ivec3 f(mesh->faces[i][0],mesh->faces[i][1],mesh->faces[i][2]);
		face_list.push_back(f);
	}
	SamplePoissonDisk test(face_list, mesh->vertices, mesh->normals);
	vector<Sample> node_sample = test.GetSample(NODESIZE);
	node_point.clear();
	for(size_t i =0; i< node_sample.size(); i++)
	{
		node_point.push_back(node_sample[i].position);
	}
}

void EmbeddedDeformation::loadconstraintPoint(string file_name)
{
	ifstream fin(file_name);
	constraint_point.clear();
	float x,y,z;
	while(fin >> x >> y >> z)
	{
		vec3 pos(x,y,z);
		constraint_point.push_back(pos);
	}
	//makeControlPointSymmetry(constraint_point);
	cout << "load " << constraint_point.size() << " constraint point" << endl;
}

void EmbeddedDeformation::loadMovedconstraintPoint(string file_name)
{
	ifstream fin(file_name);
	moved_constraint_point.clear();
	float x,y,z;
	while(fin >> x >> y >> z)
	{
		vec3 pos(x,y,z);
		moved_constraint_point.push_back(pos);
	}
	//makeControlPointSymmetry(moved_constraint_point);
	cout << "load " <<  moved_constraint_point.size() << "  moved constraint point" << endl;
}

void EmbeddedDeformation::sampleconstraintPoint()
{
	float max_dis = 0.0f;
	for(size_t i = 0; i < constraint_point.size(); i++)
	{
			
			for(size_t j = 0; j < constraint_point.size(); j++)
			{
				if(j != i && dist(constraint_point[i],constraint_point[j]) > max_dis)
				{
					max_dis = dist(constraint_point[i],constraint_point[j]);
				}
			}
	}
	float dis_threat = max_dis * 0.05;
	vector<int> down_sample;
	down_sample.clear();
	float max_def = 0.0f;
	int max_def_index = -1;
	for(size_t i = 0; i < constraint_point.size(); i++)
	{
		if(max_def < dist(constraint_point[i],moved_constraint_point[i]))
		{
			max_def_index = i;
			max_def = dist(constraint_point[i],moved_constraint_point[i]);
		}
	}
	down_sample.push_back(max_def_index);
	for(size_t i = 0; i < constraint_point.size(); i++)
	{
		int is_new = 1;
		for(size_t j = 0; j < down_sample.size(); j++)
		{
			if(dist(constraint_point[i],constraint_point[down_sample[j]]) < dis_threat)
			{
				is_new = 0;
				break;
			}
		}

		if(is_new == 1)
		{				
			down_sample.push_back(i);
		}		
	}
	vector<vec3> c_new;
	c_new.clear();
	vector<vec3> c_moved;
	c_moved.clear();
	for(size_t i = 0; i < down_sample.size(); i++)
	{
		c_new.push_back(constraint_point[down_sample[i]]);
		c_moved.push_back(moved_constraint_point[down_sample[i]]);
	}
	sampled_constraint_point = c_new;
	sampled_moved_constraint_point = c_moved;
	visualPointLine(constraint_point, moved_constraint_point, 0,1, "input.ply");

}

void EmbeddedDeformation::buildNodeConnection()
{
	vetrex_node_connection.clear();
	constrain_node_connection.clear();
	sampled_constrain_node_connection.clear();
	node_connection.clear();
	for(size_t i = 0; i < node_point.size(); i++)
	{
		vector<int> node_ner;
		node_ner.clear();
		node_connection.push_back(node_ner);
	}
	vector<NamedPoint> points;
	for (size_t i = 0; i < node_point.size(); i++)
	{
		points.push_back(NamedPoint(node_point[i][0], node_point[i][1], node_point[i][2], i));
	}
	KDTree3<NamedPoint> stree(points.begin(), points.end());
	for (size_t i = 0; i < mesh->vertices.size(); i++)
	{
		NamedPoint query(mesh->vertices[i][0], mesh->vertices[i][1], mesh->vertices[i][2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(RINGNEIGHBOR);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		vector<int> near_list;
		near_list.clear();
		for(size_t ind = 0; ind < RINGNEIGHBOR; ind++)
		{
			int near_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			near_list.push_back(near_id);
		}
		vetrex_node_connection.push_back(near_list);
		for(size_t ind = 0; ind < near_list.size() - 1; ind++)
		{
			for(size_t j = ind + 1; j < near_list.size() - 1; j++ )
			{
				addNodeNeighbor(near_list[ind], near_list[j]);
				addNodeNeighbor(near_list[j], near_list[ind]);
			}
		}
	}

	for (size_t i = 0; i < constraint_point.size(); i++)
	{
		NamedPoint query(constraint_point[i][0], constraint_point[i][1], constraint_point[i][2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(RINGNEIGHBOR);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		vector<int> near_list;
		near_list.clear();
		for(size_t ind = 0; ind < RINGNEIGHBOR; ind++)
		{
			int near_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			near_list.push_back(near_id);
		}
		constrain_node_connection.push_back(near_list);
		for(size_t ind = 0; ind < near_list.size() - 1; ind++)
		{
			for(size_t j = ind + 1; j < near_list.size() - 1; j++ )
			{
				addNodeNeighbor(near_list[ind], near_list[j]);
				addNodeNeighbor(near_list[j], near_list[ind]);
			}
		}
	}

	for (size_t i = 0; i < sampled_constraint_point.size(); i++)
	{
		NamedPoint query(sampled_constraint_point[i][0], sampled_constraint_point[i][1], sampled_constraint_point[i][2]);
		BoundedSortedArray<PKDTree::Neighbor> k_closest_elems(RINGNEIGHBOR);
		stree.kClosestElements<MetricL2>(query, k_closest_elems, -1);  // -1 means there's no limit on the maximum allowed
		vector<int> near_list;
		near_list.clear();
		for(size_t ind = 0; ind < RINGNEIGHBOR; ind++)
		{
			int near_id = stree.getElements()[k_closest_elems[ind].getIndex()].id;
			near_list.push_back(near_id);
		}
		sampled_constrain_node_connection.push_back(near_list);
		for(size_t ind = 0; ind < near_list.size() - 1; ind++)
		{
			for(size_t j = ind + 1; j < near_list.size() - 1; j++ )
			{
				addNodeNeighbor(near_list[ind], near_list[j]);
				addNodeNeighbor(near_list[j], near_list[ind]);
			}
		}
	}

}

void EmbeddedDeformation::calculateWeight()
{
	weight_vertex.clear();
	vector<float> weight_total;
	weight_total.clear();
	for(size_t i = 0; i < mesh->vertices.size(); i++)
	{
		vector<float> weight_list;
		weight_list.clear();
		float d_max = dist(mesh->vertices[i],node_point[vetrex_node_connection[i][RINGNEIGHBOR - 1]]);
		float total_weight = 0;
		for(size_t j = 0; j < RINGNEIGHBOR - 1; j++)
		{
			//float weight_ji = (1 - dist(mesh->vertices[i],node_point[vetrex_node_connection[i][j]])/d_max)*(1 - dist(mesh->vertices[i],node_point[vetrex_node_connection[i][j]])/d_max);
			float weight_ji = (dist(mesh->vertices[i],node_point[vetrex_node_connection[i][j]])/d_max);
			weight_ji = exp(-weight_ji*weight_ji);
			weight_list.push_back(weight_ji);
			total_weight += weight_ji;
		}
		weight_vertex.push_back(weight_list);
		weight_total.push_back(total_weight);
	}
	// normalize
	for(size_t i = 0; i < mesh->vertices.size(); i++)
	{
		for(size_t j = 0; j < weight_vertex[i].size(); j++)
		{
			weight_vertex[i][j] /= weight_total[i];
		}
	}

	weight_constraint.clear();
	weight_total.clear();
	for(size_t i = 0; i < constraint_point.size(); i++)
	{
		vector<float> weight_list;
		weight_list.clear();
		float d_max = dist(constraint_point[i],node_point[constrain_node_connection[i][RINGNEIGHBOR - 1]]);
		float total_weight = 0;
		for(size_t j = 0; j < RINGNEIGHBOR - 1; j++)
		{
			//float weight_ji = (1 - dist(constraint_point[i],node_point[constrain_node_connection[i][j]])/d_max)*(1 - dist(constraint_point[i],node_point[constrain_node_connection[i][j]])/d_max);
			float weight_ji = (dist(constraint_point[i],node_point[constrain_node_connection[i][j]])/d_max);
			weight_ji = exp(-weight_ji*weight_ji);
			weight_list.push_back(weight_ji);
			total_weight += weight_ji;
		}
		weight_constraint.push_back(weight_list);
		weight_total.push_back(total_weight);
	}

	// normalize
	for(size_t i = 0; i < constraint_point.size(); i++)
	{
		for(size_t j = 0; j < weight_constraint[i].size(); j++)
		{
			weight_constraint[i][j] /= weight_total[i];
		}
	}

	weight_sampled_constraint.clear();
	weight_total.clear();
	for(size_t i = 0; i < sampled_constraint_point.size(); i++)
	{
		vector<float> weight_list;
		weight_list.clear();
		float d_max = dist(sampled_constraint_point[i],node_point[sampled_constrain_node_connection[i][RINGNEIGHBOR - 1]]);
		float total_weight = 0;
		for(size_t j = 0; j < RINGNEIGHBOR - 1; j++)
		{
			//float weight_ji = (1 - dist(constraint_point[i],node_point[constrain_node_connection[i][j]])/d_max)*(1 - dist(constraint_point[i],node_point[constrain_node_connection[i][j]])/d_max);
			float weight_ji = (dist(sampled_constraint_point[i],node_point[sampled_constrain_node_connection[i][j]])/d_max);
			weight_ji = exp(-weight_ji*weight_ji);
			weight_list.push_back(weight_ji);
			total_weight += weight_ji;
		}
		weight_sampled_constraint.push_back(weight_list);
		weight_total.push_back(total_weight);
	}

	// normalize
	for(size_t i = 0; i < sampled_constraint_point.size(); i++)
	{
		for(size_t j = 0; j < weight_sampled_constraint[i].size(); j++)
		{
			weight_sampled_constraint[i][j] /= weight_total[i];
		}
	}
}

void EmbeddedDeformation::addNodeNeighbor(int node_1, int node_2)
{
	int is_new = 1;
	for(size_t j = 0; j < node_connection[node_1].size(); j++)
	{
		if(node_connection[node_1][j] == node_2)
		{
			is_new = 0;
			break;
		}
	}
	if(is_new == 1)
	{
		node_connection[node_1].push_back(node_2);
	}
}

void EmbeddedDeformation::initialMatrix()
{
	trans_matrix_node.clear();
	for(size_t i =0; i < node_point.size(); i++)
	{
		// r = [c0, c3,c6
		//      c1, c4,c7
		//      c2, c5,c8 ]
		vector<float> matrix;
		matrix.resize(12,0);
		matrix[0] = 1.0f;
		matrix[4] = 1.0f;
		matrix[8] = 1.0f;
		trans_matrix_node.push_back(matrix);
	}
}

void EmbeddedDeformation::gaussnewtonMethodNew()
{
	int totalrow = 0;
	for(size_t i = 0; i < node_point.size(); i++)
	{
		totalrow += 6;
	}
	for(size_t i = 0; i < node_point.size(); i++)
	{
		totalrow += node_connection[i].size()* 3;
	}
	for(size_t i = 0; i < constraint_point.size(); i++)
	{
		totalrow +=  3;
	}
	cout << "totalrow " <<" " << totalrow <<  endl;
	Eigen::MatrixXd jacMatrix = Eigen::MatrixXd::Constant(totalrow,12 * node_point.size(), 0);
	Eigen::VectorXd beta = Eigen::VectorXd::Constant(totalrow, 0);
	int current_row = 0;
	for(size_t i = 0; i < node_point.size(); i++)
	{
		jacMatrix(current_row,i*12)     = trans_matrix_node[i][3] * WEIGHTROT;
		jacMatrix(current_row,i*12 + 1) = trans_matrix_node[i][4] * WEIGHTROT;
		jacMatrix(current_row,i*12 + 2) = trans_matrix_node[i][5] * WEIGHTROT;
		jacMatrix(current_row,i*12 + 3) = trans_matrix_node[i][0] * WEIGHTROT;
		jacMatrix(current_row,i*12 + 4) = trans_matrix_node[i][1] * WEIGHTROT;
		jacMatrix(current_row,i*12 + 5) = trans_matrix_node[i][2] * WEIGHTROT;
		float e0 = trans_matrix_node[i][0] * trans_matrix_node[i][3] + trans_matrix_node[i][1] * trans_matrix_node[i][4] + trans_matrix_node[i][2] * trans_matrix_node[i][5];
		beta(current_row) = (e0* WEIGHTROT);
		current_row += 1;
		jacMatrix(current_row,i*12)= trans_matrix_node[i][6]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 1)= trans_matrix_node[i][7]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 2) = trans_matrix_node[i][8]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 6)= trans_matrix_node[i][0]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 7)= trans_matrix_node[i][1]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 8) = trans_matrix_node[i][2]* WEIGHTROT;
		float e1 = trans_matrix_node[i][0] * trans_matrix_node[i][6] + trans_matrix_node[i][1] * trans_matrix_node[i][7] + trans_matrix_node[i][2] * trans_matrix_node[i][8];
		beta(current_row) = (e1* WEIGHTROT);
		current_row += 1;
		jacMatrix(current_row,i*12 + 3) = trans_matrix_node[i][6]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 4)= trans_matrix_node[i][7]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 5) = trans_matrix_node[i][8]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 6) = trans_matrix_node[i][3]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 7)= trans_matrix_node[i][4]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 8)= trans_matrix_node[i][5]* WEIGHTROT;
		float e2 = trans_matrix_node[i][6] * trans_matrix_node[i][3] + trans_matrix_node[i][7] * trans_matrix_node[i][4] + trans_matrix_node[i][8] * trans_matrix_node[i][5];
		beta(current_row) = (e2* WEIGHTROT);
		current_row += 1;
		jacMatrix(current_row,i*12)= 2.0f *trans_matrix_node[i][0]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 1)= 2.0f * trans_matrix_node[i][1]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 2)= 2.0f * trans_matrix_node[i][2]* WEIGHTROT;
		float e3 = trans_matrix_node[i][0] * trans_matrix_node[i][0] + trans_matrix_node[i][1] * trans_matrix_node[i][1] + trans_matrix_node[i][2] * trans_matrix_node[i][2] - 1.0f;
		beta(current_row) = (e3* WEIGHTROT);
		current_row += 1;
		jacMatrix(current_row,i*12 + 3) = 2.0f * trans_matrix_node[i][3]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 4)= 2.0f * trans_matrix_node[i][4]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 5) = 2.0f * trans_matrix_node[i][5]* WEIGHTROT;
		float e4 = trans_matrix_node[i][3] * trans_matrix_node[i][3] + trans_matrix_node[i][4] * trans_matrix_node[i][4] + trans_matrix_node[i][5] * trans_matrix_node[i][5] - 1.0f;
		beta(current_row)  = (e4* WEIGHTROT);
		current_row += 1;
		jacMatrix(current_row,i*12 + 6) = 2.0f * trans_matrix_node[i][6]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 7)= 2.0f * trans_matrix_node[i][7]* WEIGHTROT;
		jacMatrix(current_row,i*12 + 8) =  2.0f * trans_matrix_node[i][8]* WEIGHTROT;
		float e5 = trans_matrix_node[i][6] * trans_matrix_node[i][6] + trans_matrix_node[i][7] * trans_matrix_node[i][7] + trans_matrix_node[i][8] * trans_matrix_node[i][8] - 1.0f;
		beta(current_row) = (e5* WEIGHTROT);
		current_row += 1;

		for(size_t j = 0; j < node_connection[i].size(); j++)
		{
			int near_id = node_connection[i][j];
			vec3 diff_kj = node_point[near_id] - node_point[i];
			jacMatrix(current_row,i*12) = diff_kj[0]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 3)= diff_kj[1]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 6)= diff_kj[2]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 9)= 1* WEIGHTREG;
			jacMatrix(current_row,near_id*12 + 9) = -1* WEIGHTREG;
			float e0 = trans_matrix_node[i][0] * diff_kj[0] + trans_matrix_node[i][3] * diff_kj[1]  +  trans_matrix_node[i][6] * diff_kj[2] - diff_kj[0] + trans_matrix_node[i][9] - trans_matrix_node[near_id][9];
			beta(current_row) = (e0* WEIGHTREG);
			current_row += 1;
			jacMatrix(current_row,i*12 + 1)= diff_kj[0]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 4)= diff_kj[1]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 7)= diff_kj[2]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 10)= 1* WEIGHTREG;
			jacMatrix(current_row,near_id*12 + 10) = -1* WEIGHTREG;
			float e1 = trans_matrix_node[i][1] * diff_kj[0] + trans_matrix_node[i][4] * diff_kj[1]  +  trans_matrix_node[i][7] * diff_kj[2] - diff_kj[1] + trans_matrix_node[i][10] - trans_matrix_node[near_id][10];
			beta(current_row) = (e1* WEIGHTREG);
			current_row += 1;
			jacMatrix(current_row,i*12 + 2) = diff_kj[0]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 5)= diff_kj[1]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 8) = diff_kj[2]* WEIGHTREG;
			jacMatrix(current_row,i*12 + 11) = 1* WEIGHTREG;
			jacMatrix(current_row,near_id*12 + 11) = -1* WEIGHTREG;
			float e2 = trans_matrix_node[i][2] * diff_kj[0] + trans_matrix_node[i][5] * diff_kj[1]  +  trans_matrix_node[i][8] * diff_kj[2] - diff_kj[2] + trans_matrix_node[i][11] - trans_matrix_node[near_id][11];
			beta(current_row) = (e2* WEIGHTREG);
			current_row += 1;
		}
	}
	cout << "end rot and reg " << endl;
	for(size_t i = 0; i < constraint_point.size(); i++)
	{
		float e0 = 0.0f;
		for(size_t j = 0; j < weight_constraint[i].size(); j++)
		{
			float weight_ij = weight_constraint[i][j];
			int near_node = constrain_node_connection[i][j];
			vec3 diff_ij = constraint_point[i] - node_point[near_node];	
			jacMatrix(current_row,near_node*12)  = diff_ij[0]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 3) = diff_ij[1]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 6) = diff_ij[2]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 9)= 1* WEIGHTCON * weight_ij ;
			e0 += (trans_matrix_node[near_node][0] * diff_ij[0] + trans_matrix_node[near_node][3] * diff_ij[1] + trans_matrix_node[near_node][6] * diff_ij[2] + node_point[near_node][0] + trans_matrix_node[near_node][9])*weight_ij;
			//e0 *= weight_ij;
		}
		e0 -= moved_constraint_point[i][0];
		beta(current_row) = (e0* WEIGHTCON);
		current_row += 1;
		float e1 = 0.0f;
		for(size_t j = 0; j < weight_constraint[i].size(); j++)
		{
			float weight_ij = weight_constraint[i][j];
			int near_node = constrain_node_connection[i][j];
			vec3 diff_ij = constraint_point[i] - node_point[near_node];
			jacMatrix(current_row,near_node*12 + 1)= diff_ij[0]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 4) = diff_ij[1]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 7) = diff_ij[2]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 10) = 1* WEIGHTCON * weight_ij ;
			e1 += (trans_matrix_node[near_node][1] * diff_ij[0] + trans_matrix_node[near_node][4] * diff_ij[1] + trans_matrix_node[near_node][7] * diff_ij[2] + node_point[near_node][1] + trans_matrix_node[near_node][10])*weight_ij;
			//e1 *= weight_ij;
		}
		e1 -= moved_constraint_point[i][1];
		beta(current_row) = (e1* WEIGHTCON);
		current_row += 1;
		float e2 = 0.0f;
		for(size_t j = 0; j < weight_constraint[i].size(); j++)
		{
			float weight_ij = weight_constraint[i][j];
			int near_node = constrain_node_connection[i][j];
			vec3 diff_ij = constraint_point[i] - node_point[near_node];
			jacMatrix(current_row,near_node*12 + 2) = diff_ij[0]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 5)= diff_ij[1]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 8) = diff_ij[2]* WEIGHTCON * weight_ij ;
			jacMatrix(current_row,near_node*12 + 11) = 1* WEIGHTCON * weight_ij ;
			e2 += (trans_matrix_node[near_node][2] * diff_ij[0] + trans_matrix_node[near_node][5] * diff_ij[1] + trans_matrix_node[near_node][8] * diff_ij[2] + node_point[near_node][2] + trans_matrix_node[near_node][11])*weight_ij;
			//e2 *= weight_ij;
		}
		e2 -= moved_constraint_point[i][2];
		beta(current_row) = (e2* WEIGHTCON);
		current_row += 1;
	}

	cout << "begin solver " << endl;
	Eigen::MatrixXd CTC = jacMatrix.transpose()*jacMatrix;
	Eigen::MatrixXd CTCI = CTC.inverse();
	//Eigen::MatrixXd HMatrix = DMatrix*CTCI*(CMatrix.transpose());
	Eigen::VectorXd diff = CTCI*jacMatrix.transpose()*beta;
	for (int i = 0; i < trans_matrix_node.size(); i++)
	{
		for(size_t j = 0; j < 12; j++)
		{
			trans_matrix_node[i][j] -= diff[i*12 + j];
			cout << trans_matrix_node[i][j] << " ";
		}
		cout << endl;
	}

}

void EmbeddedDeformation::gaussnewtonMethod()
{
	std::vector<std::map<int, double> >  LapMat;
	std::vector<std::vector<double> >	  LapB;
	LapB.resize(1);

	for(size_t i = 0; i < node_point.size(); i++)
	{
		// Erot (c1.c2)^2 + (c1.c3)^2 + (c2.c3)^2 + (c1.c1 - 1 )^2 + (c2.c2 - 1 )^2 + (c3.c3 - 1 )^2
		LapMat.push_back(map<int, double>());
		(LapMat.back())[i*12] =     trans_matrix_node[i][3] * WEIGHTROT;
		(LapMat.back())[i*12 + 1] = trans_matrix_node[i][4]* WEIGHTROT;
		(LapMat.back())[i*12 + 2] = trans_matrix_node[i][5]* WEIGHTROT;
		(LapMat.back())[i*12 + 3] = trans_matrix_node[i][0]* WEIGHTROT;
		(LapMat.back())[i*12 + 4] = trans_matrix_node[i][1]* WEIGHTROT;
		(LapMat.back())[i*12+ 5] = trans_matrix_node[i][2]* WEIGHTROT;
		float e0 = trans_matrix_node[i][0] * trans_matrix_node[i][3] + trans_matrix_node[i][1] * trans_matrix_node[i][4] + trans_matrix_node[i][2] * trans_matrix_node[i][5];
		LapB[0].push_back(e0* WEIGHTROT);
		LapMat.push_back(map<int, double>());
		(LapMat.back())[i*12 ] = trans_matrix_node[i][6]* WEIGHTROT;
		(LapMat.back())[i*12 + 1] = trans_matrix_node[i][7]* WEIGHTROT;
		(LapMat.back())[i*12 + 2] = trans_matrix_node[i][8]* WEIGHTROT;
		(LapMat.back())[i*12 + 6] = trans_matrix_node[i][0]* WEIGHTROT;
		(LapMat.back())[i*12 + 7] = trans_matrix_node[i][1]* WEIGHTROT;
		(LapMat.back())[i*12+ 8] = trans_matrix_node[i][2]* WEIGHTROT;
		float e1 = trans_matrix_node[i][0] * trans_matrix_node[i][6] + trans_matrix_node[i][1] * trans_matrix_node[i][7] + trans_matrix_node[i][2] * trans_matrix_node[i][8];
		LapB[0].push_back(e1* WEIGHTROT);
		LapMat.push_back(map<int, double>());
		(LapMat.back())[i*12 + 3] = trans_matrix_node[i][6]* WEIGHTROT;
		(LapMat.back())[i*12 + 4] = trans_matrix_node[i][7]* WEIGHTROT;
		(LapMat.back())[i*12 + 5] = trans_matrix_node[i][8]* WEIGHTROT;
		(LapMat.back())[i*12 + 6] = trans_matrix_node[i][3]* WEIGHTROT;
		(LapMat.back())[i*12 + 7] = trans_matrix_node[i][4]* WEIGHTROT;
		(LapMat.back())[i*12+ 8] = trans_matrix_node[i][5]* WEIGHTROT;
		float e2 = trans_matrix_node[i][6] * trans_matrix_node[i][3] + trans_matrix_node[i][7] * trans_matrix_node[i][4] + trans_matrix_node[i][8] * trans_matrix_node[i][5];
		LapB[0].push_back(e2* WEIGHTROT);
		LapMat.push_back(map<int, double>());
		(LapMat.back())[i*12] = 2.0f *trans_matrix_node[i][0]* WEIGHTROT;
		(LapMat.back())[i*12 + 1] = 2.0f * trans_matrix_node[i][1]* WEIGHTROT;
		(LapMat.back())[i*12 + 2] = 2.0f * trans_matrix_node[i][2]* WEIGHTROT;
		float e3 = trans_matrix_node[i][0] * trans_matrix_node[i][0] + trans_matrix_node[i][1] * trans_matrix_node[i][1] + trans_matrix_node[i][2] * trans_matrix_node[i][2] - 1.0f;
		LapB[0].push_back(e3* WEIGHTROT);
		LapMat.push_back(map<int, double>());
		(LapMat.back())[i*12 + 3] = 2.0f * trans_matrix_node[i][3]* WEIGHTROT;
		(LapMat.back())[i*12 + 4] = 2.0f * trans_matrix_node[i][4]* WEIGHTROT;
		(LapMat.back())[i*12 + 5] = 2.0f * trans_matrix_node[i][5]* WEIGHTROT;
		float e4 = trans_matrix_node[i][3] * trans_matrix_node[i][3] + trans_matrix_node[i][4] * trans_matrix_node[i][4] + trans_matrix_node[i][5] * trans_matrix_node[i][5] - 1.0f;
		LapB[0].push_back(e4* WEIGHTROT);
		LapMat.push_back(map<int, double>());
		(LapMat.back())[i*12 + 6] = 2.0f * trans_matrix_node[i][6]* WEIGHTROT;
		(LapMat.back())[i*12 + 7] = 2.0f * trans_matrix_node[i][7]* WEIGHTROT;
		(LapMat.back())[i*12 + 8] = 2.0f * trans_matrix_node[i][8]* WEIGHTROT;
		float e5 = trans_matrix_node[i][6] * trans_matrix_node[i][6] + trans_matrix_node[i][7] * trans_matrix_node[i][7] + trans_matrix_node[i][8] * trans_matrix_node[i][8] - 1.0f;
		LapB[0].push_back(e5* WEIGHTROT);

		//Ereg
		for(size_t j = 0; j < node_connection[i].size(); j++)
		{
			int near_id = node_connection[i][j];
			vec3 diff_kj = node_point[near_id] - node_point[i];
			LapMat.push_back(map<int, double>());
			(LapMat.back())[i*12] = diff_kj[0]* WEIGHTREG;
			(LapMat.back())[i*12 + 3] = diff_kj[1]* WEIGHTREG;
			(LapMat.back())[i*12 + 6] = diff_kj[2]* WEIGHTREG;
			(LapMat.back())[i*12 + 9] = 1* WEIGHTREG;
			(LapMat.back())[near_id*12 + 9] = -1* WEIGHTREG;
			float e0 = trans_matrix_node[i][0] * diff_kj[0] + trans_matrix_node[i][3] * diff_kj[1]  +  trans_matrix_node[i][6] * diff_kj[2] - diff_kj[0] + trans_matrix_node[i][9] - trans_matrix_node[near_id][9];
			LapB[0].push_back(e0* WEIGHTREG);
			LapMat.push_back(map<int, double>());
			(LapMat.back())[i*12 + 1] = diff_kj[0]* WEIGHTREG;
			(LapMat.back())[i*12 + 4] = diff_kj[1]* WEIGHTREG;
			(LapMat.back())[i*12 + 7] = diff_kj[2]* WEIGHTREG;
			(LapMat.back())[i*12 + 10] = 1* WEIGHTREG;
			(LapMat.back())[near_id*12 + 10] = -1* WEIGHTREG;
			float e1 = trans_matrix_node[i][1] * diff_kj[0] + trans_matrix_node[i][4] * diff_kj[1]  +  trans_matrix_node[i][7] * diff_kj[2] - diff_kj[1] + trans_matrix_node[i][10] - trans_matrix_node[near_id][10];
			LapB[0].push_back(e1* WEIGHTREG);
			LapMat.push_back(map<int, double>());
			(LapMat.back())[i*12 + 2] = diff_kj[0]* WEIGHTREG;
			(LapMat.back())[i*12 + 5] = diff_kj[1]* WEIGHTREG;
			(LapMat.back())[i*12 + 8] = diff_kj[2]* WEIGHTREG;
			(LapMat.back())[i*12 + 11] = 1* WEIGHTREG;
			(LapMat.back())[near_id*12 + 11] = -1* WEIGHTREG;
			float e2 = trans_matrix_node[i][2] * diff_kj[0] + trans_matrix_node[i][5] * diff_kj[1]  +  trans_matrix_node[i][8] * diff_kj[2] - diff_kj[2] + trans_matrix_node[i][11] - trans_matrix_node[near_id][11];
			LapB[0].push_back(e2* WEIGHTREG);
		}
	}

	for(size_t i = 0; i < sampled_constraint_point.size(); i++)
	{
		LapMat.push_back(map<int, double>());
		float e0 = 0.0f;
		for(size_t j = 0; j < weight_sampled_constraint[i].size(); j++)
		{
			float weight_ij = weight_sampled_constraint[i][j];
			int near_node = sampled_constrain_node_connection[i][j];
			vec3 diff_ij = sampled_constraint_point[i] - node_point[near_node];
			(LapMat.back())[near_node*12 ] = diff_ij[0]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 3] = diff_ij[1]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 6] = diff_ij[2]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 9] = 1* WEIGHTCON * weight_ij ;
			e0 += (trans_matrix_node[near_node][0] * diff_ij[0] + trans_matrix_node[near_node][3] * diff_ij[1] + trans_matrix_node[near_node][6] * diff_ij[2] + node_point[near_node][0] + trans_matrix_node[near_node][9])*weight_ij;
			//e0 *= weight_ij;
		}
		e0 -= sampled_moved_constraint_point[i][0];
		LapB[0].push_back(e0* WEIGHTCON);

		LapMat.push_back(map<int, double>());
		float e1 = 0.0f;
		for(size_t j = 0; j < weight_sampled_constraint[i].size(); j++)
		{
			float weight_ij = weight_sampled_constraint[i][j];
			int near_node = sampled_constrain_node_connection[i][j];
			vec3 diff_ij = sampled_constraint_point[i] - node_point[near_node];
			(LapMat.back())[near_node*12 + 1] = diff_ij[0]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 4] = diff_ij[1]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 7] = diff_ij[2]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 10] = 1* WEIGHTCON * weight_ij ;
			e1 += (trans_matrix_node[near_node][1] * diff_ij[0] + trans_matrix_node[near_node][4] * diff_ij[1] + trans_matrix_node[near_node][7] * diff_ij[2] + node_point[near_node][1] + trans_matrix_node[near_node][10])*weight_ij;
			//e1 *= weight_ij;
		}
		e1 -= sampled_moved_constraint_point[i][1];
		LapB[0].push_back(e1* WEIGHTCON);
		LapMat.push_back(map<int, double>());
		float e2 = 0.0f;
		for(size_t j = 0; j < weight_sampled_constraint[i].size(); j++)
		{
			float weight_ij = weight_sampled_constraint[i][j];
			int near_node = sampled_constrain_node_connection[i][j];
			vec3 diff_ij = sampled_constraint_point[i] - node_point[near_node];
			(LapMat.back())[near_node*12 + 2] = diff_ij[0]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 5] = diff_ij[1]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 8] = diff_ij[2]* WEIGHTCON * weight_ij ;
			(LapMat.back())[near_node*12 + 11] = 1* WEIGHTCON * weight_ij ;
			e2 += (trans_matrix_node[near_node][2] * diff_ij[0] + trans_matrix_node[near_node][5] * diff_ij[1] + trans_matrix_node[near_node][8] * diff_ij[2] + node_point[near_node][2] + trans_matrix_node[near_node][11])*weight_ij;
			//e2 *= weight_ij;
		}
		e2 -= sampled_moved_constraint_point[i][2];
		LapB[0].push_back(e2* WEIGHTCON);
	}


	int nr_cols =  12 * node_point.size();
	LeastSquaresSparseSolver solver;
	solver.Init(LapMat, nr_cols);
	vector<vector<double> > eRes;
	solver.Solve(LapB, eRes);

	for (int i = 0; i < trans_matrix_node.size(); i++)
	{
		for(size_t j = 0; j < 12; j++)
		{
			trans_matrix_node[i][j] -= eRes[0][i*12 + j];
		}
	}

}

void EmbeddedDeformation::aligmentPoint()
{
	vec3 center_control(0,0,0);
	vec3 center_mesh(0,0,0);
	for(size_t i = 0 ; i < constraint_point.size(); i++)
	{
		center_mesh += constraint_point[i];
	}
	center_mesh /= constraint_point.size();
    vec3 scale(0,0,0);
	for(size_t i = 0 ; i < constraint_point.size(); i++)
	{
		vec3 pos_diff = constraint_point[i] - center_mesh;
		scale[0] += pos_diff[0]*pos_diff[0];
		scale[1] += pos_diff[1]*pos_diff[1];
		scale[2] += pos_diff[2]*pos_diff[2];
	}
	for(size_t i = 0; i < moved_constraint_point.size(); i++)
	{
		center_control += moved_constraint_point[i];
	}
	center_control /= moved_constraint_point.size();
	vec3 scale_m(0,0,0);
	for(size_t i = 0; i < moved_constraint_point.size(); i++)
	{
		vec3 pos_diff = moved_constraint_point[i] - center_control;
		scale_m[0] += pos_diff[0]*pos_diff[0];
		scale_m[1] += pos_diff[1]*pos_diff[1];
		scale_m[2] += pos_diff[2]*pos_diff[2];
	}
	// move mesh and control point
	for(size_t i = 0; i < moved_constraint_point.size(); i++)
	{
		moved_constraint_point[i] = moved_constraint_point[i] - center_control;
		moved_constraint_point[i][0] *= sqrt(scale[0]/scale_m[0]);
		moved_constraint_point[i][1] *= sqrt(scale[1]/scale_m[1]);
		moved_constraint_point[i][2] *= sqrt(scale[2]/scale_m[2]);
		moved_constraint_point[i] += center_mesh;
	}
	/*for(size_t i = 0 ; i < constraint_point.size(); i++)
	{
		constraint_point[i] = constraint_point[i] - center_mesh;
		constraint_point[i][0] *= sqrt(scale_m[0]/scale[0]);
		constraint_point[i][1] *= sqrt(scale_m[1]/scale[1]);
		constraint_point[i][2] *= sqrt(scale_m[2]/scale[2]);
		constraint_point[i] += center_control;
	}

	for(size_t i = 0 ; i < mesh->vertices.size(); i++)
	{
		mesh->vertices[i] = mesh->vertices[i] - center_mesh;
		mesh->vertices[i][0] *= sqrt(scale_m[0]/scale[0]);
		mesh->vertices[i][1] *= sqrt(scale_m[1]/scale[1]);
		mesh->vertices[i][2] *= sqrt(scale_m[2]/scale[2]);
		mesh->vertices[i] += center_control;
	}*/
}


void EmbeddedDeformation::deformation()
{
	for(size_t i = 0; i < 5 ; i++)
	{
		cout << "ite " << i << endl;
		gaussnewtonMethod();
		//gaussnewtonMethodNew();
	}
	cout << "end optimization" << endl;
	for(size_t i = 0 ; i < mesh->vertices.size(); i++)
	{
		vec3 pos = mesh->vertices[i];
		float p_x = 0.0f;
		float p_y = 0.0f;
		float p_z = 0.0f;
		//cout << i << endl;
		for(size_t j = 0; j < weight_vertex[i].size(); j++)
		{
			float weight_ij = weight_vertex[i][j];
			int near_node = vetrex_node_connection[i][j];
			vec3 diff_ij = pos - node_point[near_node];
			//cout << near_node <<" ";
			p_x += (trans_matrix_node[near_node][0] * diff_ij[0] + trans_matrix_node[near_node][3] * diff_ij[1] + trans_matrix_node[near_node][6] * diff_ij[2] + node_point[near_node][0] + trans_matrix_node[near_node][9]) * weight_ij;
			p_y += (trans_matrix_node[near_node][1] * diff_ij[0] + trans_matrix_node[near_node][4] * diff_ij[1] + trans_matrix_node[near_node][7] * diff_ij[2] + node_point[near_node][1] + trans_matrix_node[near_node][10])* weight_ij;
			p_z += (trans_matrix_node[near_node][2] * diff_ij[0] + trans_matrix_node[near_node][5] * diff_ij[1] + trans_matrix_node[near_node][8] * diff_ij[2] + node_point[near_node][2] + trans_matrix_node[near_node][11]) * weight_ij;
		}
		//cout << endl;
		mesh->vertices[i][0] = p_x;
		mesh->vertices[i][1] = p_y;
		mesh->vertices[i][2] = p_z;
	}

	for(size_t i = 0 ; i < constraint_point.size(); i++)
	{
		vec3 pos = constraint_point[i];
		float p_x = 0.0f;
		float p_y = 0.0f;
		float p_z = 0.0f;
		//cout << i << endl;
		for(size_t j = 0; j < weight_constraint[i].size(); j++)
		{
			float weight_ij = weight_constraint[i][j];
			int near_node = constrain_node_connection[i][j];
			vec3 diff_ij = pos - node_point[near_node];
			//cout << near_node <<" ";
			p_x += (trans_matrix_node[near_node][0] * diff_ij[0] + trans_matrix_node[near_node][3] * diff_ij[1] + trans_matrix_node[near_node][6] * diff_ij[2] + node_point[near_node][0] + trans_matrix_node[near_node][9]) * weight_ij;
			p_y += (trans_matrix_node[near_node][1] * diff_ij[0] + trans_matrix_node[near_node][4] * diff_ij[1] + trans_matrix_node[near_node][7] * diff_ij[2] + node_point[near_node][1] + trans_matrix_node[near_node][10])* weight_ij;
			p_z += (trans_matrix_node[near_node][2] * diff_ij[0] + trans_matrix_node[near_node][5] * diff_ij[1] + trans_matrix_node[near_node][8] * diff_ij[2] + node_point[near_node][2] + trans_matrix_node[near_node][11]) * weight_ij;
		}
		//cout << endl;
		constraint_point[i][0] = p_x;
		constraint_point[i][1] = p_y;
		constraint_point[i][2] = p_z;
		//cout << p_x << " "<< p_y << " " << p_z << endl;
	}
	//cout << "end " << constraint_point[0] << endl;
}

void EmbeddedDeformation::visualNodeGraph(string ply_name)
{
	ofstream fout(ply_name);
	int total_edge = 0;
	for(size_t i = 0; i < node_connection.size(); i++)
	{
		//cout <<  node_connection[i].size() << endl;
		total_edge += node_connection[i].size();
	}
	fout << "ply" << endl;
	fout << "format ascii 1.0" << endl;
	fout << "element vertex " << node_point.size()<< endl;
	fout << "property float32 x" << endl;
	fout << "property float32 y" << endl;
	fout << "property float32 z" << endl;
	fout << "property float32 nx" << endl;
	fout << "property float32 ny" << endl;
	fout << "property float32 nz" << endl;
	fout << "property uchar red" << endl;
	fout << "property uchar green" << endl;
	fout << "property uchar blue" << endl;
	fout << "element edge " << total_edge << endl;
	fout << "property int vertex1 " <<endl;
	fout << "property int vertex2 " <<endl;
	fout << "element face 0 " << endl;
	fout << "property list uint8 int32 vertex_index" << endl;
	fout << "end_header" << endl;
	for (int iv=0; iv< node_point.size(); iv++)
	{
		ivec3 color(255,0,0);
		fout << node_point[iv][0] << " " << node_point[iv][1] << " " <<node_point[iv][2] << " ";
		fout << 1 << " " << 0 << " " << 0 << " ";
		fout << color[0] << " " << color[1] << " " << color[2] << endl;
	}
	for(size_t i = 0; i < node_connection.size(); i++)
	{
		for(size_t j = 0; j < node_connection[i].size(); j++)
		{
			fout << i << " " << node_connection[i][j] << endl;
		}
	}
}

void EmbeddedDeformation::outputMesh(string mesh_name)
{
	//mesh->write(mesh_name);
	ofstream fout(mesh_name);
	for(size_t i = 0; i < mesh->vertices.size(); i++)
	{
		fout <<"v " <<  mesh->vertices[i][0] << " " << mesh->vertices[i][1] <<" " << mesh->vertices[i][2] <<" " << 1 << " " << 0 <<" "<< 0 << endl;
	}
	for(size_t i = 0; i < mesh->faces.size(); i++)
	{
		fout <<"f " <<  mesh->faces[i][0] + 1 << " " << mesh->faces[i][1]+ 1 <<" " << mesh->faces[i][2]+ 1 << endl;
	}
}

void EmbeddedDeformation::visualPointLine(vector<vec3> polit_list1, vector<vec3> polit_list2, int color_type1, int color_type2,string file_name)
{
	ofstream fout(file_name);
	fout << "ply" << endl;
	fout << "format ascii 1.0" << endl;
	fout << "element vertex " << polit_list1.size() + polit_list2.size()<< endl;
	fout << "property float32 x" << endl;
	fout << "property float32 y" << endl;
	fout << "property float32 z" << endl;
	fout << "property float32 nx" << endl;
	fout << "property float32 ny" << endl;
	fout << "property float32 nz" << endl;
	fout << "property uchar red" << endl;
	fout << "property uchar green" << endl;
	fout << "property uchar blue" << endl;
	fout << "element edge " << polit_list1.size() << endl;
    fout << "property int vertex1 " <<endl;
    fout << "property int vertex2 " <<endl;
    fout << "element face 0 " << endl;
	fout << "property list uint8 int32 vertex_index" << endl;
	fout << "end_header" << endl;
	for (int iv=0; iv< polit_list1.size(); iv++)
	{
		ivec3 color(255,0,0);
		if(color_type1 == 1)
		{
			color[0] = 0;
			color[1] = 255;
		}
		if(color_type1 == 2)
		{
			color[0] = 0;
			color[2] = 255;
		}
		//color = template_sample_color[i];
		fout << polit_list1[iv][0] << " " << polit_list1[iv][1] << " " << polit_list1[iv][2] << " ";
		fout << 1 << " " << 0 << " " << 0 << " ";
		fout << color[0] << " " << color[1] << " " << color[2] << endl;
	}

	for (int iv=0; iv< polit_list2.size(); iv++)
	{
		ivec3 color(255,0,0);
		if(color_type2 == 1)
		{
			color[0] = 0;
			color[1] = 255;
		}
		if(color_type2 == 2)
		{
			color[0] = 0;
			color[2] = 255;
		}
		//color = template_sample_color[i];
		fout << polit_list2[iv][0] << " " << polit_list2[iv][1] << " " << polit_list2[iv][2] << " ";
		fout << 1 << " " << 0 << " " << 0 << " ";
		fout << color[0] << " " << color[1] << " " << color[2] << endl;
	}

	for (int iv=0; iv< polit_list2.size(); iv++)
	{
		fout << iv << " " << iv + polit_list2.size() << endl;
	}
}