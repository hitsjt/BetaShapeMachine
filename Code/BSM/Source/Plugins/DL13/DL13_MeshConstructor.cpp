#include "DL13_MeshConstructor.hpp"

namespace SNL {;
namespace DL13 {;



void MeshConstructor::createMesh(const std::string & out_path)
{
	valid_sparse_points = dm->removeInvalidSparsePoints();
	valid_dense_points = dm->removeInvalidDensePoints();

	if (dm->training_data != NULL)
		findNearestParts();

	//if ( !valid_dense_points.empty() )
	//{
	//	computeNormals();
	//	if (dm->training_data != NULL)
	//		orientNormals();
	//	consistentlyOrientNormals();
	//	//smoothDensePoints();
	//}

	if (out_path == "")
		return;

	//ofstream out( out_path + ".pts" );
	//for (int i = 0; i < valid_dense_points.size(); i++)
	//{
	//	if ( component_ids[i] == -1 )
	//		continue;
	//	out << valid_dense_points[i].p[0] << " " << valid_dense_points[i].p[1] << " " << valid_dense_points[i].p[2];
	//	out << " " << confidence_normals[i]*dense_normals[i][0] << " " << confidence_normals[i]*dense_normals[i][1] << " " << confidence_normals[i]*dense_normals[i][2] << std::endl;
	//}
	//out.close();

	//ofstream out2( out_path + ".asc" );
	//for (int i = 0; i < valid_dense_points.size(); i++)
	//{
	//	out2 << valid_dense_points[i].p[0] << " " << valid_dense_points[i].p[1] << " " << valid_dense_points[i].p[2] << " ";
	//	out2 << valid_dense_points[i].id << " " << valid_dense_points[i].part_id << " " << nearest_part_filename_per_dense_point[i] << std::endl;
	//}
	//out2.close();

  ofstream out3(out_path + ".sparse.asc"); 
  out3 << dm->sample_unnormalized_probability << std::endl;
	for (int i = 0; i < (int)valid_sparse_points.size(); i++)
	{
		//if ( valid_sparse_points[i].has_symmetric_part |  valid_sparse_points[i].is_self_symmetric )
		//	if ( valid_sparse_points[i].p[0] < 0.0f )
		//		continue;
    out3 << valid_sparse_points[i].p[0] << " " << valid_sparse_points[i].p[1] << " " << valid_sparse_points[i].p[2] << " ";
    if (dm->training_data != NULL)
      out3 << valid_sparse_points[i].id << " " << valid_sparse_points[i].part_id << " " << nearest_part_filename_per_sparse_point[i] << " ";
    else
      out3 << valid_sparse_points[i].id << " " << valid_sparse_points[i].part_id << " " << "null" << " ";
    out3 << valid_sparse_points[i].has_symmetric_part << " " << valid_sparse_points[i].is_self_symmetric << std::endl;
	}
	out3.close();

	//string command = "PoissonRecon.x64 --verbose --in " + out_path + ".pts --out " + out_path + " --depth 12 --solverDivide 12 --nonManifold --accuracy 0.00001 2>&1";

	//FILE* pipe = popen(command.c_str(), "r");
	//char buffer[128];
	//while(!feof(pipe)) 
	//{
	//	if(fgets(buffer, 128, pipe) != NULL)
	//	{
	//		std::cout << buffer;
	//		std::cout.flush();
	//	}
	//}
	//pclose(pipe);
}




void MeshConstructor::findPartCentroidsAndSymmetries()
{
	std::cout << "=> Finding part centroids" << std::endl;
	part_centroids.clear();
	vector<float> number_of_points_per_part( dm->training_data->percentage_of_sparse_points_per_part.size(), 0.0f );
	vector<float> number_of_symmetric_points_per_part( dm->training_data->percentage_of_sparse_points_per_part.size(), 0.0f );
	vector<float> number_of_self_symmetric_points_per_part( dm->training_data->percentage_of_sparse_points_per_part.size(), 0.0f );
	for (int p = 0; p < (int)number_of_points_per_part.size(); p++)
	{
		point c(FLT_MAX, FLT_MAX, FLT_MAX);
		part_centroids.push_back(c);
	}

	for (int i = 0; i < (int)valid_sparse_points.size(); i++)
	{
		int p = valid_sparse_points[i].part_id;
		if ( isinv( part_centroids[p][0] ) )
			part_centroids[p] = point(0.0f, 0.0f, 0.0f);
		number_of_points_per_part[p]++;
		number_of_symmetric_points_per_part[p] += (float)valid_sparse_points[i].has_symmetric_part;
		number_of_self_symmetric_points_per_part[p] += (float)valid_sparse_points[i].is_self_symmetric;
		part_centroids[p] += valid_sparse_points[i].p;
	}

	for (int p = 0; p < (int)part_centroids.size(); p++)
	{
		part_centroids[p] /= number_of_points_per_part[p];

		if ( number_of_symmetric_points_per_part[p] > number_of_points_per_part[p] / 2.0f )
		{
			for (int i = 0; i < (int)valid_sparse_points.size(); i++)
				if ( valid_sparse_points[i].part_id == p )
					valid_sparse_points[i].has_symmetric_part = true;
		}
		else
		{
			for (int i = 0; i < (int)valid_sparse_points.size(); i++)
				if ( valid_sparse_points[i].part_id == p )
					valid_sparse_points[i].has_symmetric_part = false;
		}

		if ( number_of_self_symmetric_points_per_part[p] > number_of_points_per_part[p] / 2.0f )
		{
			for (int i = 0; i < (int)valid_sparse_points.size(); i++)
				if ( valid_sparse_points[i].part_id == p )
					valid_sparse_points[i].is_self_symmetric = true;
		}
		else
		{
			for (int i = 0; i < (int)valid_sparse_points.size(); i++)
				if ( valid_sparse_points[i].part_id == p )
					valid_sparse_points[i].is_self_symmetric = false;
		}


	}
}


void MeshConstructor::findNearestParts()
{		
	std::cout << "=> Finding closest parts from database" << std::endl;
	findPartCentroidsAndSymmetries();
	nearest_part_filename_per_sparse_point.clear();
	nearest_part_filename_per_sparse_point.resize( valid_sparse_points.size(), "" );
	nearest_part_filename_per_dense_point.clear();
	nearest_part_filename_per_dense_point.resize( valid_dense_points.size(), "" );
	
  // SCALE ALIGNMENT
  vector< vector< vec > > scale_parts_nom(dm->training_data->number_of_training_examples);
  vector< vector< vec > > scale_parts_denom(dm->training_data->number_of_training_examples);

  for (int m = 0; m < (int)dm->training_data->number_of_training_examples; m++)
  {
    scale_parts_nom[m].resize(part_centroids.size());
    scale_parts_denom[m].resize(part_centroids.size());
    for (int p = 0; p < part_centroids.size(); p++)
    {
      scale_parts_nom[m][p] = vec(FLT_MAX, FLT_MAX, FLT_MAX);
      scale_parts_denom[m][p] = vec(FLT_MAX, FLT_MAX, FLT_MAX);
    }

    for (int i = 0; i < (int)dm->sparse_points.size(); i++)
    {
      if (isinv(dm->sparse_points[i].p[0]) || dm->training_data->sparse_point_data[m][i].empty())
        continue;
      int p = dm->sparse_points[i].part_id;
      if (isinv(scale_parts_nom[m][p][0]))
      {
        scale_parts_nom[m][p] = vec(0.0f, 0.0f, 0.0f);
        scale_parts_denom[m][p] = vec(0.0f, 0.0f, 0.0f);
      }
      vec local_sparse_point_position = dm->sparse_points[i].p - part_centroids[p];

      vec local_training_data_sparse_point_position(0.0f, 0.0f, 0.0f);
      for (int d = 0; d < 3; d++)
      {
        local_training_data_sparse_point_position[d] = dm->training_data->sparse_point_data[m][i][d] - dm->training_data->part_centroids[m][p][d];
        scale_parts_nom[m][p][d] += local_sparse_point_position[d] * local_sparse_point_position[d];
        scale_parts_denom[m][p][d] += local_training_data_sparse_point_position[d] * local_training_data_sparse_point_position[d];
      }
    } // end of loop over points 

    for (int p = 0; p < part_centroids.size(); p++)
      for (int d = 0; d < 3; d++)
        scale_parts_nom[m][p][d] = sqrt( scale_parts_nom[m][p][d] / (scale_parts_denom[m][p][d] + EPSILONf) );
  } // end of loop over training examples



  // CENTROID ALIGNMENT
  vector<float> nearest_dist_to_parts(part_centroids.size(), FLT_MAX);
  vector<int> nearest_dist_to_part_ids(part_centroids.size(), -1);

  for (int m = 0; m < (int)dm->training_data->number_of_training_examples; m++)
  {
    vector<float> dist_to_parts(part_centroids.size(), FLT_MAX);

    for (size_t i = 0; i < dm->sparse_points.size(); i++)
    {
      if (isinv(dm->sparse_points[i].p[0]) || dm->training_data->sparse_point_data[m][i].empty())
        continue;
      int p = dm->sparse_points[i].part_id;
      if (isinv(dist_to_parts[p]))
        dist_to_parts[p] = 0.0f;
      vec local_sparse_point_position = dm->sparse_points[i].p - part_centroids[p];
      vec local_training_data_sparse_point_position(0.0f, 0.0f, 0.0f);
      for (int d = 0; d < 3; d++)
      {
        local_training_data_sparse_point_position[d] = dm->training_data->sparse_point_data[m][i][d] - dm->training_data->part_centroids[m][p][d];
        local_training_data_sparse_point_position[d] *= scale_parts_nom[m][p][d];
      }

      dist_to_parts[p] += len(local_training_data_sparse_point_position - local_sparse_point_position);
    } // end of loop over points 

    for (int p = 0; p < (int)part_centroids.size(); p++)
    {
      if (dist_to_parts[p] < nearest_dist_to_parts[p])
      {
        nearest_dist_to_parts[p] = dist_to_parts[p];
        nearest_dist_to_part_ids[p] = m;
      }
    }
  } // end of loop over training examples

	for (size_t i = 0; i < valid_sparse_points.size(); i++)
		nearest_part_filename_per_sparse_point[i] = dm->training_data->data_filenames[ nearest_dist_to_part_ids[ valid_sparse_points[i].part_id ] ];
	
	for (size_t i = 0; i < valid_dense_points.size(); i++)
		nearest_part_filename_per_dense_point[i] = dm->training_data->data_filenames[ nearest_dist_to_part_ids[ valid_dense_points[i].part_id ] ];
}




int MeshConstructor::findNumberOfConnectedComponentsInTheSparsePointCloud()
{
	valid_sparse_points = dm->removeInvalidSparsePoints();
	sparse_point_neighbors.clear();
	sparse_point_neighbors.resize(valid_sparse_points.size());

	//1. Find nearest points for each point
	float avg_dist = 0.0f;
	float total_num_neighbors = 0.0f;
	vector<Thea::NamedPoint> points;
	for (size_t i = 0; i < valid_sparse_points.size(); i++)
		points.push_back(Thea::NamedPoint(valid_sparse_points[i].p[0], valid_sparse_points[i].p[1], valid_sparse_points[i].p[2], i));
	Thea::PKDTree stree(points.begin(), points.end());
	for (size_t i = 0; i < valid_sparse_points.size(); i++)
	{
		Thea::NamedPoint query(valid_sparse_points[i].p[0], valid_sparse_points[i].p[1], valid_sparse_points[i].p[2]);
		Thea::BoundedSortedArray<Thea::PKDTree::Neighbor> k_closest_elems(20);
		stree.kClosestElements<Thea::MetricL2>(query, k_closest_elems);  // -1 means there's no limit on the maximum allowed

		for (int kn = 0; kn < k_closest_elems.size(); kn++)
		{
			Thea::NamedPoint kpoint = stree.getElements()[k_closest_elems[kn].getIndex()];
			if (kpoint.id != i)
			{
				avg_dist += (kpoint.position - query.position).length();
				total_num_neighbors++;
				sparse_point_neighbors[i].push_back(kpoint.id);
			}
		}
	}
	avg_dist /= total_num_neighbors;

	//2. find connected components
	vector< vector<size_t> > components;
	component_ids.clear();
	component_ids.resize(valid_sparse_points.size(), -1);

	for (size_t i = 0; i < valid_sparse_points.size(); i++)
	{
		if (component_ids[i] >= 0)
			continue;

		queue<size_t> bfs_front;
		bfs_front.push(i);
		vector<size_t> visited_points;

		while (!bfs_front.empty())
		{
			size_t front_i = bfs_front.front();
			bfs_front.pop();
			visited_points.push_back(front_i);

			for (int kn = 0; kn < (int)sparse_point_neighbors[front_i].size(); kn++)
			{
				size_t nearest_point_id = sparse_point_neighbors[front_i][kn];
				if (component_ids[nearest_point_id] >= 0)
					continue;

				if (dist(valid_sparse_points[front_i].p, valid_sparse_points[nearest_point_id].p) > 2.0f * avg_dist)
					continue;

				component_ids[nearest_point_id] = (int)components.size();
				bfs_front.push(nearest_point_id);
			}
		} // end of component

		components.push_back(visited_points);
	} // end of for loop

  std::cout << "#components: " << components.size() << std::endl;

	return (int)components.size();
}


bool MeshConstructor::checkIfPartsAgreeWithSymmetricBits()
{
  valid_sparse_points = dm->removeInvalidSparsePoints();

  for (int p = 0; p < (int)dm->training_data->percentage_of_sparse_points_per_part.size(); p++)
  {
    float symmetric_distance = 0.0f;
    float number_of_points_per_part = 0.0f;
    float	number_of_symmetric_points_per_part = 0.0f;

    for (size_t i = 0; i < valid_sparse_points.size(); i++)
    {
      if (valid_sparse_points[i].part_id != p)
        continue;

      number_of_points_per_part++;
      number_of_symmetric_points_per_part += (float)valid_sparse_points[i].has_symmetric_part;

      float min_dist = FLT_MAX;
      for (size_t j2 = 0; j2 < valid_sparse_points.size(); j2++)
      {
        float dist = 0.0f, tmp = 0.0f;
        tmp = (-valid_sparse_points[i].p[0] - valid_sparse_points[j2].p[0]);
        dist += tmp * tmp;
        tmp = (valid_sparse_points[i].p[1] - valid_sparse_points[j2].p[1]);
        dist += tmp * tmp;
        tmp = (valid_sparse_points[i].p[2] - valid_sparse_points[j2].p[2]);
        dist += tmp * tmp;

        if (dist < min_dist)
          min_dist = dist;
      } // end of loop for potentially symmetric points of part

      symmetric_distance += min_dist;
    } // end of loop over points of part

    symmetric_distance /= (number_of_points_per_part + 1.0f);

    std::cout << p << " symmetry: " << symmetric_distance << " " << dm->training_data->adjusted_radius * dm->training_data->adjusted_radius << std::endl;

    if (symmetric_distance > .05f * dm->training_data->adjusted_radius * dm->training_data->adjusted_radius) // no symmetry
      if (number_of_symmetric_points_per_part > number_of_points_per_part / 2.0f) // symmetry bit indicates symmetry though
        return false;
  } // end of loop over parts

  return true;
}


vector<Point> MeshConstructor::smoothSparsePoints(int smoothing_amount_mult)
{
  std::cout << "=> Smoothing Points" << std::endl;
  valid_sparse_points = dm->removeInvalidSparsePoints();
  sparse_point_neighbors.clear();
  sparse_point_neighbors.resize(valid_sparse_points.size());
  int num_neighbors = 25 * smoothing_amount_mult;

  vector<Thea::NamedPoint> points;
  for (size_t i = 0; i < valid_sparse_points.size(); i++)
    points.push_back(Thea::NamedPoint(valid_sparse_points[i].p[0], valid_sparse_points[i].p[1], valid_sparse_points[i].p[2], i));
  Thea::PKDTree stree(points.begin(), points.end());

  for (size_t i = 0; i < valid_sparse_points.size(); i++)
  {
    Thea::NamedPoint query(valid_sparse_points[i].p[0], valid_sparse_points[i].p[1], valid_sparse_points[i].p[2]);
    Thea::BoundedSortedArray<Thea::PKDTree::Neighbor> k_closest_elems(num_neighbors);
    stree.kClosestElements<Thea::MetricL2>(query, k_closest_elems, -1);

    for (int kn = 0; kn < k_closest_elems.size(); kn++)
    {
      Thea::NamedPoint kpoint = stree.getElements()[k_closest_elems[kn].getIndex()];
      if (kpoint.id != i)
        sparse_point_neighbors[i].push_back(kpoint.id);
    }
  }

  for (int smooth_iter = 0; smooth_iter < 3 * smoothing_amount_mult; smooth_iter++)
  {
    vector<Point>  corrected_valid_sparse_points = valid_sparse_points;

    for (size_t i = 0; i < valid_sparse_points.size(); i++)
    {
      vec laplacian(0.0f, 0.0f, 0.0f);
      float total_w = 0.0f;

      for (int kn = 0; kn < (int)sparse_point_neighbors[i].size(); kn++)
      {
        size_t nearest_point_id = sparse_point_neighbors[i][kn];
        laplacian += valid_sparse_points[nearest_point_id].p;
        total_w++;
      }
      laplacian = laplacian / total_w - valid_sparse_points[i].p;
      corrected_valid_sparse_points[i].p = valid_sparse_points[i].p + .4f * laplacian;
    }

    valid_sparse_points = corrected_valid_sparse_points;

    for (size_t i = 0; i < valid_sparse_points.size(); i++)
    {
      vec laplacian(0.0f, 0.0f, 0.0f);
      float total_w = 0.0f;

      for (int kn = 0; kn < (int)sparse_point_neighbors[i].size(); kn++)
      {
        size_t nearest_point_id = sparse_point_neighbors[i][kn];
        laplacian += valid_sparse_points[nearest_point_id].p;
        total_w++;
      }
      laplacian = laplacian / total_w - valid_sparse_points[i].p;
      corrected_valid_sparse_points[i].p = valid_sparse_points[i].p - .5f * laplacian;
    }

    valid_sparse_points = corrected_valid_sparse_points;
  }

  return valid_sparse_points;
}



//
//void MeshConstructor::smoothDensePoints()
//{
//	std::cout << "=> Smoothing Points" << std::endl;
//
//	for (int smooth_iter = 0; smooth_iter < 10; smooth_iter++)
//	{
//		vector<Point>  corrected_valid_dense_points = valid_dense_points;
//
//		for (size_t i = 0; i < valid_dense_points.size(); i++)
//		{
//			if (component_ids[i] == -1)
//				continue;
//
//			point new_point = valid_dense_points[i].p;
//			float total_w = 1.0f;
//
//			for (int kn = 0; kn < (int)dense_point_neighbors[i].size(); kn++)
//			{
//				size_t nearest_point_id = dense_point_neighbors[i][kn];
//				if (component_ids[nearest_point_id] == -1)
//					continue;
//				new_point += valid_dense_points[nearest_point_id].p;
//				total_w++;
//			}
//
//			corrected_valid_dense_points[i].p = new_point / total_w;
//		}
//
//		valid_dense_points = corrected_valid_dense_points;
//	}
//
//}


//void MeshConstructor::computeNormals()
//{
//	num_neighbors_for_normal_estimation = 50;
//	//(int) dm->geometry_boltzmann_machine->dlayer->num_neighbors_to_consider;		
//	//	(int) ( dm->geometry_boltzmann_machine->dlayer->num_neighbors_to_consider * dm->geometry_boltzmann_machine->dlayer->num_neighbors_to_consider );
//	std::cout << "=> Computing normals" << std::endl;
//	dense_normals.clear();
//	dense_normals.resize(valid_dense_points.size());
//	confidence_normals.clear();
//	confidence_normals.resize(valid_dense_points.size());
//	dense_point_neighbors.clear();
//	dense_point_neighbors.resize(valid_dense_points.size());
//	component_ids.clear();
//	component_ids.resize(valid_dense_points.size(), -1);
//
//	vector<Thea::NamedPoint> points;
//	for (size_t i = 0; i < valid_dense_points.size(); i++)
//		points.push_back(Thea::NamedPoint(valid_dense_points[i].p[0], valid_dense_points[i].p[1], valid_dense_points[i].p[2], i));
//	Thea::PKDTree stree(points.begin(), points.end());
//
//	for (size_t i = 0; i < valid_dense_points.size(); i++)
//	{
//		SMATRIXf local_covariance_matrix(3, 3);
//		local_covariance_matrix.fill(0.0f);
//		SVECTORf centroid(3);
//		centroid.fill(0.0f);
//		float total_w = 0.0f;
//
//		Thea::NamedPoint query(valid_dense_points[i].p[0], valid_dense_points[i].p[1], valid_dense_points[i].p[2]);
//		SMATRIXf q = query.convertToEigenVector();
//		Thea::BoundedSortedArray<Thea::PKDTree::Neighbor> k_closest_elems(num_neighbors_for_normal_estimation);
//		stree.kClosestElements<Thea::MetricL2>(query, k_closest_elems, .05f);  // -1 means there's no limit on the maximum allowed
//
//		for (int kn = 0; kn < k_closest_elems.size(); kn++)
//		{
//			Thea::NamedPoint kpoint = stree.getElements()[k_closest_elems[kn].getIndex()];
//			SMATRIXf v = kpoint.convertToEigenVector();
//			float w = 1.0f; //exp( - (v - q).squaredNorm() / 0.001f );
//			centroid += w * v;
//			total_w += w;
//			if (kpoint.id != i)
//				dense_point_neighbors[i].push_back(kpoint.id);
//		}
//		centroid /= total_w;
//
//		for (int kn = 0; kn < k_closest_elems.size(); kn++)
//		{
//			Thea::NamedPoint kpoint = stree.getElements()[k_closest_elems[kn].getIndex()];
//			SMATRIXf v = kpoint.convertToEigenVector();
//			float w = 1.0f; //exp( - (v - q).squaredNorm() / 0.001f );
//			v = v - centroid;
//			local_covariance_matrix += w * v * v.transpose();
//		}
//		local_covariance_matrix /= total_w;
//		Eigen::SelfAdjointEigenSolver<SMATRIXf> eigensolver(local_covariance_matrix);
//		SVECTORf n = eigensolver.eigenvectors().col(0);
//		dense_normals[i][0] = n(0);
//		dense_normals[i][1] = n(1);
//		dense_normals[i][2] = n(2);
//		dense_normals[i] = normalize(dense_normals[i]);
//		confidence_normals[i] = 1.0f; // 1.0f - eigensolver.eigenvalues()[0] / ( eigensolver.eigenvalues()[0] + eigensolver.eigenvalues()[1] + eigensolver.eigenvalues()[2] );
//	}
//}
//
//void MeshConstructor::orientNormals()
//{
//	if (dm->training_data->nearest_sparse_points_for_each_dense_point.empty())
//	{
//		std::cerr << "MeshConstructor::orientNormals cannot orient normals without setting first the spatial neighbors in training data (run findDenseToSparseAssociations)" << std::endl;
//		return;
//	}
//
//	num_sparse_neighbors_for_patch_similarity_for_normal_orientation = (int)dm->geometry_boltzmann_machine->dlayer->num_neighbors_to_consider * 10;
//
//	std::cout << "=> Orienting normals based on patch similarity" << std::endl;
//
//	int ii = 0; // index for valid points / normals
//	for (size_t i = 0; i < dm->dense_points.size(); i++)
//	{
//		if (isinv(dm->dense_points[i].p[0]))
//			continue;
//
//		int nearest_example = 0;
//		float min_dist = FLT_MAX;
//		for (int m = 0; m < (int)dm->training_data->number_of_training_examples; m++)
//		{
//			if (dm->training_data->dense_point_data[m][i].empty())
//				continue;
//
//			float dist = 0.0f;
//
//			for (int ij = 0; ij < std::min(num_sparse_neighbors_for_patch_similarity_for_normal_orientation, (int)dm->training_data->nearest_sparse_points_for_each_dense_point[i].size()); ij++)
//			{
//				int sparse_id = dm->training_data->nearest_sparse_points_for_each_dense_point[i][ij];
//				float distx = dm->sparse_points[sparse_id].p[0] - dm->training_data->sparse_point_data[m][sparse_id][0];
//				float disty = dm->sparse_points[sparse_id].p[1] - dm->training_data->sparse_point_data[m][sparse_id][1];
//				float distz = dm->sparse_points[sparse_id].p[2] - dm->training_data->sparse_point_data[m][sparse_id][2];
//				dist += distx*distx + disty*disty + distz*distz;
//			}
//			if (dist < min_dist)
//			{
//				nearest_example = m;
//				min_dist = dist;
//			}
//		}
//
//		vec nm = vec(dm->training_data->dense_normal_data[nearest_example][i][0],
//			dm->training_data->dense_normal_data[nearest_example][i][1],
//			dm->training_data->dense_normal_data[nearest_example][i][2]);
//		if ((nm DOT dense_normals[ii]) < 0.0f)
//			dense_normals[ii] = -dense_normals[ii];
//		ii++;
//
//	}
//}
//
//
//
//void MeshConstructor::consistentlyOrientNormals()
//{
//	std::cout << "=> Orienting normals with consistency checks" << std::endl;
//
//	vector< vector<size_t> > components;
//
//	for (size_t i = 0; i < valid_dense_points.size(); i++)
//	{
//		if (component_ids[i] >= 0)
//			continue;
//
//		queue<size_t> bfs_front;
//		bfs_front.push(i);
//		vector<size_t> visited_points;
//
//		while (!bfs_front.empty())
//		{
//			size_t front_i = bfs_front.front();
//			bfs_front.pop();
//			visited_points.push_back(front_i);
//
//			for (int kn = 0; kn < (int)dense_point_neighbors[front_i].size(); kn++)
//			{
//				size_t nearest_point_id = dense_point_neighbors[front_i][kn];
//				if (component_ids[nearest_point_id] >= 0)
//					continue;
//				if (fabs(dense_normals[nearest_point_id] DOT dense_normals[front_i]) < 0.9f)
//					continue;
//				if ((dense_normals[nearest_point_id] DOT dense_normals[front_i]) < 0.0f)
//					continue;
//
//				component_ids[nearest_point_id] = (int)components.size();
//				bfs_front.push(nearest_point_id);
//			}
//		} // end of component
//
//		components.push_back(visited_points);
//	} // end of for loop
//
//	size_t largest_component_size = 0;
//	size_t largest_component_id = 0;
//	for (int k = 0; k < (int)components.size(); k++)
//	{
//		if (components[k].size() > largest_component_size)
//		{
//			largest_component_size = components[k].size();
//			largest_component_id = k;
//		}
//	}
//
//
//	size_t previous_largest_component_size = 0;
//	while (true)
//	{
//		if (largest_component_size == previous_largest_component_size)
//			break;
//
//		previous_largest_component_size = largest_component_size;
//
//		for (size_t i = 0; i < largest_component_size; i++)
//		{
//			size_t front_i = components[largest_component_id][i];
//			for (int kn = 0; kn < (int)dense_point_neighbors[front_i].size(); kn++)
//			{
//				size_t nearest_point_id = dense_point_neighbors[front_i][kn];
//				if (component_ids[nearest_point_id] != (int)largest_component_id)
//				{
//					if (fabs(dense_normals[nearest_point_id] DOT dense_normals[front_i]) < 0.9f)
//						continue;
//					if ((dense_normals[nearest_point_id] DOT dense_normals[front_i]) < 0.0f)
//						dense_normals[nearest_point_id] = -dense_normals[nearest_point_id];
//					components[largest_component_id].push_back(nearest_point_id);
//					component_ids[nearest_point_id] = (int)largest_component_id;
//				}
//			}
//		}
//
//		largest_component_size = components[largest_component_id].size();
//	}
//
//	for (size_t i = 0; i < valid_dense_points.size(); i++)
//	{
//		if (component_ids[i] != (int)largest_component_id)
//			component_ids[i] = -1;
//	}
//
//}


}
}