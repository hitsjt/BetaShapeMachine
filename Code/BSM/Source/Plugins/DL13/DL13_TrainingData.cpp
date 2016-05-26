#include "DL13_TrainingData.hpp"

namespace SNL {;
namespace DL13 {;

TrainingData::TrainingData(string const & in_path, float threshold, int limit_number_of_examples_to_read, bool is_binary, 
													 int _number_of_attributes,
													 int _number_of_sparse_points, int _number_of_dense_points)
{
	if (in_path.empty())
		return;
	adjusted_radius = 0.0f;
	std::cout << "Loading training data from " << in_path << "..." << std::endl;
	number_of_training_examples = 0;
	number_of_training_examples_attributes = 0;
	number_of_dense_points = _number_of_dense_points;
	number_of_sparse_points = _number_of_sparse_points;
	number_of_attributes = _number_of_attributes;
	string domain_dir;
	vector<string> all_data_filenames;
	percentage_of_sparse_points_per_part.resize(0);

	boost::filesystem::directory_iterator end_itr, itr; // default construction yields past-the-end
	try 
	{
		itr = boost::filesystem::directory_iterator( in_path + "/sparse/" );
	}
	catch(boost::filesystem::filesystem_error &ex)
	{
		std::cerr << ex.what() << std::endl;
		std::cerr << "Directory " << in_path + "/sparse/" << " not accessible. The domain directory should have a 'sparse' subfolder! " << std::endl;
		return;
	}
	for ( ; itr != end_itr; ++itr )
	{
		all_data_filenames.push_back( itr->path().leaf().string() );
		domain_dir = itr->path().parent_path().parent_path().string();
	}
	for (size_t i = 0; i < all_data_filenames.size(); i++)
	{
		if ((int)data_filenames.size() == limit_number_of_examples_to_read)
			break;

		// 1. OPEN FILES
		//string dense_filename = in_path + "/dense/" + all_data_filenames[i] + "/" + all_data_filenames[i] + ".txt";
		string sparse_filename = in_path	+ "/sparse/" + all_data_filenames[i] + "/" + all_data_filenames[i] + ".txt";
		string attributes_filename = in_path	+ "/sparse/" + all_data_filenames[i] + "/" + all_data_filenames[i] + "_attributes.txt";
		cout << i << " | Parsing " <<  all_data_filenames[i] << "...";
		//ifstream dense_file( dense_filename.c_str(), ios::in | ios::binary );
		ifstream sparse_file( sparse_filename.c_str(), ios::in | ios::binary );
		ifstream attributes_file( attributes_filename.c_str(), ios::in | ios::binary );
		if ( /*!dense_file.good() ||*/ !sparse_file.good() )
		{
			std::cerr << "Files "  << sparse_filename  << " are not found or domain directory structure is corrupted." << std::endl;
			continue;
		}

		// 2. READ number_of_dense_points , number_of_sparse_points
		int num_points_in_dataset;
		//dense_file.read( (char*)(&num_points_in_dataset), sizeof(num_points_in_dataset) );
		//if ( i == 0 )
		//	number_of_dense_points = num_points_in_dataset;
		//else
		//{
		//	if ( num_points_in_dataset != number_of_dense_points )
		//	{
		//		std::cerr << "File format " << dense_filename << " is inconsistent with other files in the dataset." << std::endl;
		//		return;
		//	}
		//}
		sparse_file.read( (char*)(&num_points_in_dataset), sizeof(num_points_in_dataset) );
		if ( !sparse_file.good() || num_points_in_dataset <= 0 )
		{
			std::cerr << " is empty - ignored." << std::endl;
			continue;
		}
		if ( i == 0 )
			number_of_sparse_points = num_points_in_dataset;
		else
		{
			if ( num_points_in_dataset != number_of_sparse_points )
			{
				std::cerr << "File format " << sparse_filename << " is inconsistent with other files in the dataset." << std::endl;
				return;
			}
		}

		// 2. READ number_of_dense_points_in_shape, number_of_sparse_points_in_shape
		//int number_of_dense_points_in_shape;
		//dense_file.read( (char*)(&number_of_dense_points_in_shape), sizeof(number_of_dense_points_in_shape) );
		int number_of_sparse_points_in_shape;
		sparse_file.read( (char*)(&number_of_sparse_points_in_shape), sizeof(number_of_sparse_points_in_shape) );


		//3. READ FIT ERROR
		float fit_error;
		sparse_file.read((char*)(&fit_error), sizeof(fit_error) );
		if (fit_error > threshold)
		{
			cout << " rejected." << endl;
			//dense_file.close();
			sparse_file.close();
			attributes_file.close();
			continue;
		}
		fitting_error.push_back(fit_error);
		//sparse_file.read((char*)(&fit_error), sizeof(fit_error) );


		//4. PREPARE DATA STRUCTURES FOR NEW DATA
		data_filenames.push_back( all_data_filenames[i] );
		//dense_point_data.push_back( vector< vector<float> >() );
		//dense_point_data[ dense_point_data.size()-1].resize( number_of_dense_points );
		//dense_normal_data.push_back( vector< vector<float> >() );
		//dense_normal_data[ dense_normal_data.size()-1].resize( number_of_dense_points );
		//dense_template_id.push_back( vector< short >() );
		//dense_template_id[ dense_template_id.size()-1].resize( number_of_dense_points );
		//dense_part_id.push_back( vector< short >() );
		//dense_part_id[ dense_part_id.size()-1 ].resize( number_of_dense_points );
		//dense_point_distance_error.push_back( vector< float >() );
		//dense_point_distance_error[ dense_point_distance_error.size()-1 ].resize( number_of_dense_points );
		//dense_normal_distance_error.push_back( vector< float >() );
		//dense_normal_distance_error[ dense_normal_distance_error.size()-1 ].resize( number_of_dense_points );

		sparse_point_data.push_back( vector< vector<float> >() );
		sparse_point_data[ sparse_point_data.size()-1].resize( number_of_sparse_points );
		sparse_normal_data.push_back( vector< vector<float> >() );
		sparse_normal_data[ sparse_normal_data.size()-1].resize( number_of_sparse_points );
    sparse_template_id.push_back(vector< short >());
    sparse_template_id[sparse_template_id.size() - 1].resize(number_of_sparse_points, -1);
    sparse_part_id.push_back(vector< short >());
    sparse_part_id[sparse_part_id.size() - 1].resize(number_of_sparse_points, -1);
    sparse_point_distance_error.push_back(vector< float >());
    sparse_point_distance_error[sparse_point_distance_error.size() - 1].resize(number_of_sparse_points, -1.0f);
    sparse_normal_distance_error.push_back(vector< float >());
    sparse_normal_distance_error[sparse_normal_distance_error.size() - 1].resize(number_of_sparse_points, -1.0f);


		//5. READ ATTRIBUTES
		attribute_data.push_back( vector<float>() );

		while( attributes_file.good() )
		{
			float attribute;
			attributes_file >> attribute;
			if ( attributes_file.eof() )
				break;
			attributes_file.ignore(std::numeric_limits<int>::max(), attributes_file.widen('\n'));
			if ( attributes_file.eof() )
				break;

			attribute_data[ attribute_data.size()-1 ].push_back( attribute );
			number_of_training_examples_attributes++;
		}
		if ( number_of_attributes <= 0 )
			number_of_attributes = (int)attribute_data[ attribute_data.size()-1 ].size();
		else
		{
			if ( number_of_attributes != (int)attribute_data[ attribute_data.size()-1 ].size() )
			{
				std::cerr << "File " << attributes_filename << " has inconsistent number of attributes compared to other files in the dataset." << std::endl;
				return;
			}
		}
		attributes_file.close();


		//5. READ DENSE FILE
		//for (int j = 0; j < number_of_dense_points_in_shape; j++)
		//{
		//	float x, y, z, nx, ny, nz;
		//	int template_id, part_id, point_id;
		//	float point_distance;
		//	float normal_distance;

		//	dense_file.read( (char*)(&x), sizeof(x) );
		//	dense_file.read( (char*)(&y), sizeof(y) );
		//	dense_file.read( (char*)(&z), sizeof(z) );
		//	dense_file.read( (char*)(&nx), sizeof(nx) );
		//	dense_file.read( (char*)(&ny), sizeof(ny) );
		//	dense_file.read( (char*)(&nz), sizeof(nz) );
		//	dense_file.read( (char*)(&template_id), sizeof(template_id) );
		//	dense_file.read( (char*)(&part_id), sizeof(part_id) );
		//	dense_file.read( (char*)(&point_id), sizeof(point_id) );
		//	dense_file.read( (char*)(&point_distance), sizeof(point_distance) );
		//	dense_file.read( (char*)(&normal_distance), sizeof(normal_distance) );

		//	dense_point_data[ dense_point_data.size()-1 ][ point_id ].resize(3);
		//	dense_point_data[ dense_point_data.size()-1 ][ point_id ][0] = x;
		//	dense_point_data[ dense_point_data.size()-1 ][ point_id ][1] = y;
		//	dense_point_data[ dense_point_data.size()-1 ][ point_id ][2] = z;
		//	dense_normal_data[ dense_normal_data.size()-1][ point_id ].resize(3);
		//	dense_normal_data[ dense_normal_data.size()-1 ][ point_id ][0] = nx;
		//	dense_normal_data[ dense_normal_data.size()-1 ][ point_id ][1] = ny;
		//	dense_normal_data[ dense_normal_data.size()-1 ][ point_id ][2] = nz;
		//	dense_template_id[ dense_template_id.size()-1][ point_id ] = (short)template_id;
		//	dense_part_id[ dense_part_id.size()-1][ point_id ] = (short)part_id;
		//	dense_point_distance_error[ dense_point_distance_error.size()-1][ point_id ] = point_distance;
		//	dense_normal_distance_error[ dense_normal_distance_error.size()-1][ point_id ] = normal_distance;
		//}

		//5. READ SPARSE FILE
    int previous_part_id = -1;
		for (int j = 0; j < number_of_sparse_points_in_shape; j++)
		{
			float x, y, z, nx, ny, nz;
			int template_id, part_id, point_id;
			float point_distance;
			float normal_distance;

			sparse_file.read( (char*)(&x), sizeof(x) );
			sparse_file.read( (char*)(&y), sizeof(y) );
			sparse_file.read( (char*)(&z), sizeof(z) );
			sparse_file.read( (char*)(&nx), sizeof(nx) );
			sparse_file.read( (char*)(&ny), sizeof(ny) );
			sparse_file.read( (char*)(&nz), sizeof(nz) );
			sparse_file.read( (char*)(&template_id), sizeof(template_id) );
			sparse_file.read( (char*)(&part_id), sizeof(part_id) );
			sparse_file.read( (char*)(&point_id), sizeof(point_id) );
			sparse_file.read( (char*)(&point_distance), sizeof(point_distance) );
			sparse_file.read( (char*)(&normal_distance), sizeof(normal_distance) );

			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ].resize(3);
			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ][0] = x;
			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ][1] = y;
			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ][2] = z;
      sparse_normal_data[ sparse_normal_data.size()-1][ point_id ].resize(3);
			sparse_normal_data[ sparse_normal_data.size()-1 ][ point_id ][0] = nx;
			sparse_normal_data[ sparse_normal_data.size()-1 ][ point_id ][1] = ny;
			sparse_normal_data[ sparse_normal_data.size()-1 ][ point_id ][2] = nz;
			sparse_template_id[ sparse_template_id.size()-1][ point_id ] = (short)template_id;
			sparse_part_id[ sparse_part_id.size()-1][ point_id ] = (short)part_id;
			sparse_point_distance_error[ sparse_point_distance_error.size()-1][ point_id ] = point_distance;
			sparse_normal_distance_error[ sparse_normal_distance_error.size()-1][ point_id ] = normal_distance;

			if ( part_id >= (int)percentage_of_sparse_points_per_part.size() )
			{
				int old_size = percentage_of_sparse_points_per_part.size();
				percentage_of_sparse_points_per_part.conservativeResize( part_id + 1 );
				for (int p = old_size; p <= part_id; p++)
					percentage_of_sparse_points_per_part( p ) = 0.0f;
			}
			percentage_of_sparse_points_per_part( part_id )++;

      //if (part_id < previous_part_id) 
      //  std::cerr << "Warning: File " << sparse_filename << " has points with point or part ids in non-increasing order." << std::endl;
      //previous_part_id = part_id;
		}
		//dense_file.close();
		sparse_file.close();
		cout << " done." <<  endl;
	}

	percentage_of_sparse_points_per_part /= percentage_of_sparse_points_per_part.sum();
	number_of_training_examples = (int)data_filenames.size();

	//// CHECK IF ALL POINTS HAVE DATA
	//if ( limit_number_of_examples_to_read == INT_MAX )
	//{
	//	for (int i = 0; i < number_of_sparse_points; i++)
	//	{
	//		bool has_data = false;
	//		for ( int m = 0; m < number_of_training_examples; m++)
	//			if ( !sparse_point_data[m][i].empty() )
	//				has_data = true;

	//		if (!has_data)
	//		{
	//			std::cout << "TrainingData::TrainingData warning: sparse point with id: " << i << " has no data" << std::endl;
	//			//exit(-1);
	//		}
	//	}	

	//	for (int i = 0; i < number_of_dense_points; i++)
	//	{
	//		bool has_data = false;
	//		for ( int m = 0; m < number_of_training_examples; m++)
	//			if ( !dense_point_data[m][i].empty() )
	//				has_data = true;

	//		if (!has_data)
	//		{
	//			std::cout << "TrainingData::TrainingData error: Dense point with id: " << i << " has no data" << std::endl;
	//			//exit(-1);
	//		}
	//	}
	//}
} // end of constructor TrainingData()



void TrainingData::populateSpatialNeighbors(const float radius)
{
	spatial_neighbors_ids.clear();
	spatial_neighbors_weights.clear();
	spatial_neighbors_candidates.clear();
	adjusted_radius = radius;
	while ( internal_populateSpatialNeighbors(adjusted_radius) < 20.0f )
	{
		std::cout << "Too few avg neighbors. Increasing radius of search..." << std::endl;
		adjusted_radius *= 1.5f;
	}
}


float TrainingData::internal_populateSpatialNeighbors(const float radius)
{
	std::cout << "Finding spatial neighbors for each sparse point..."; 
	spatial_neighbors_ids.resize( number_of_sparse_points );
	spatial_neighbors_weights.resize( number_of_sparse_points );
	spatial_neighbors_candidates.resize( number_of_sparse_points );
	float avg_number_neighbors = 0.0f;

	int j, m;
	map<int, bool>::iterator ij;
	float ndist = 0.0f, dist = 0.0f;
	float num_examples_existing_for_pair = 0.0f;
	float min_dist = 0.0f;
	float closest_weight = 1.0f;
	int closest_id = -1; 
	float total_weight = 0.0f;

#pragma omp parallel for private ( j, m, dist, min_dist, closest_id ) 
	for (int i = 0; i < number_of_sparse_points; i++)
	{
		min_dist = FLT_MAX;
		closest_id = -1;

		for (j = 0; j < number_of_sparse_points; j++)
		{
			if ( i == j)
				continue;
			for ( m = 0; m < number_of_training_examples; m++)
			{
				if ( sparse_point_data[m][i].empty() || sparse_point_data[m][j].empty() )
					continue;
				if ( sparse_part_id[m][i] != sparse_part_id[m][j] )
					continue;
				dist = ( sparse_point_data[m][i][0] - sparse_point_data[m][j][0] ) * ( sparse_point_data[m][i][0] - sparse_point_data[m][j][0] );
				dist += ( sparse_point_data[m][i][1] - sparse_point_data[m][j][1] ) * ( sparse_point_data[m][i][1] - sparse_point_data[m][j][1] );
				dist += ( sparse_point_data[m][i][2] - sparse_point_data[m][j][2] ) * ( sparse_point_data[m][i][2] - sparse_point_data[m][j][2] );

				if ( dist < min_dist )
				{
					min_dist = dist;
					closest_id = j;
				}

				if ( dist < radius * radius )
					spatial_neighbors_candidates[i][(int)j] = true;
			}
		}

		spatial_neighbors_candidates[i][closest_id] = true;
	}

#pragma omp parallel for private ( ij, j, m, dist, ndist, min_dist, closest_weight, total_weight, closest_id, num_examples_existing_for_pair )
	for (int i = 0; i < number_of_sparse_points; i++)
	{
		min_dist = FLT_MAX;
		closest_weight = 1.0f;
		closest_id = -1;

		for (map<int, bool>::iterator ij = spatial_neighbors_candidates[i].begin(); ij != spatial_neighbors_candidates[i].end(); ++ij)
		{
			j = (*ij).first;
			ndist = 0.0f;
			dist = 0.0f;
			num_examples_existing_for_pair = 0.0f;
			for (m = 0; m < number_of_training_examples; m++)
			{
				if (sparse_point_data[m][i].empty() || sparse_point_data[m][j].empty())
					continue;
				if (sparse_part_id[m][i] != sparse_part_id[m][j])
					continue;
				num_examples_existing_for_pair++;
				ndist += (sparse_normal_data[m][i][0] * sparse_normal_data[m][j][0]);
				ndist += (sparse_normal_data[m][i][1] * sparse_normal_data[m][j][1]);
				ndist += (sparse_normal_data[m][i][2] * sparse_normal_data[m][j][2]);
				dist += (sparse_point_data[m][i][0] - sparse_point_data[m][j][0]) * (sparse_point_data[m][i][0] - sparse_point_data[m][j][0]);
				dist += (sparse_point_data[m][i][1] - sparse_point_data[m][j][1]) * (sparse_point_data[m][i][1] - sparse_point_data[m][j][1]);
				dist += (sparse_point_data[m][i][2] - sparse_point_data[m][j][2]) * (sparse_point_data[m][i][2] - sparse_point_data[m][j][2]);
			}
			ndist /= num_examples_existing_for_pair;
			dist = dist / num_examples_existing_for_pair;
			float weight = exp(-dist / (radius * radius)) * exp(ndist / .5f - 2.0f);

			if (dist < min_dist)
			{
				min_dist = dist;
				closest_id = j;
				closest_weight = weight;
			}

			if (dist > radius * radius || ndist < 0.0f || isnan(weight) || isinf(weight) )
				continue;

			spatial_neighbors_ids[i].push_back( j );
			spatial_neighbors_weights[i].push_back( weight );		
		} // end of loop over spatial_neighbors_candidates[i]


		spatial_neighbors_candidates[i].clear();

		if ( spatial_neighbors_ids[i].empty() )
		{
			spatial_neighbors_ids[i].push_back( closest_id );
			spatial_neighbors_weights[i].push_back( closest_weight );
		}

		total_weight = EPSILONf;
		for (j = 0; j < (int)spatial_neighbors_weights[i].size(); j++)
			total_weight += spatial_neighbors_weights[i][j];
		for (j = 0; j < (int)spatial_neighbors_weights[i].size(); j++)
			spatial_neighbors_weights[i][j] /= total_weight;

#pragma omp atomic
		avg_number_neighbors += float( spatial_neighbors_ids[i].size() );

		//ofstream tmp("tmp.txt");
		//std::cout << spatial_neighbors_ids[i].size() << " " << spatial_neighbors_weights[i].size() << std::endl;
		//for (int j = 0; j < spatial_neighbors_weights[i].size(); j++)
		//{
		//	tmp << spatial_neighbors_ids[i][j] << std::endl;
		//}
		//for (int j = 0; j < spatial_neighbors_weights[i].size(); j++)
		//{
		//	tmp << spatial_neighbors_weights[i][j] << std::endl;
		//}
		//tmp.close();
		//system("pause");
	}

	std::cout << "Avg #neighbors per point: " << avg_number_neighbors/float(number_of_sparse_points) << ". Done." << std::endl; 
	return avg_number_neighbors/float(number_of_sparse_points);
}


void TrainingData::findDenseToSparseAssociations(int num_nearest)
{	
	return;

//	std::cout << "Finding spatial sparse neighbors for each dense point..."; 	
//	num_nearest = min( num_nearest, number_of_sparse_points );
//	nearest_sparse_points_for_each_dense_point.resize( number_of_dense_points );
//
//	vector< float > dense_sparse_point_distances;
//	vector< float > dense_sparse_point_instances;
//	boost::iterator_range<boost::counting_iterator<int> > count_range;
//	vector<int> index_list;
//	int k, m, j;
//	float ndist = 0.0f, dist = 0.0f;
//
//#pragma omp parallel for private ( dense_sparse_point_distances, dense_sparse_point_instances, count_range, index_list, k, m, j, ndist, dist ) 
//	for (int i = 0; i < number_of_dense_points; i++)
//	{
//		dense_sparse_point_distances.clear();
//		dense_sparse_point_distances.resize( number_of_sparse_points, 0.0f );
//		dense_sparse_point_instances.clear();
//		dense_sparse_point_instances.resize( number_of_sparse_points, EPSILONf );
//
//		for ( m = 0; m < number_of_training_examples; m++ )
//		{
//			if ( dense_point_data[m][i].empty() )
//				continue;
//
//			for ( j = 0; j < number_of_sparse_points; j++ )
//			{
//				if ( dense_part_id[m][i] != sparse_part_id[m][j] || dense_sparse_point_distances[j] == FLT_MAX )
//				{
//					dense_sparse_point_distances[j] = FLT_MAX;
//					continue;
//				}
//				if ( sparse_point_data[m][j].empty() )
//				{
//					dense_sparse_point_distances[j] = FLT_MAX;
//					continue;
//				}
//				ndist = 0.0f;
//				dist = 0.0f;
//				//ndist += ( dense_normal_data[m][i][0] * sparse_normal_data[m][j][0] );
//				//ndist += ( dense_normal_data[m][i][1] * sparse_normal_data[m][j][1] );
//				//ndist += ( dense_normal_data[m][i][2] * sparse_normal_data[m][j][2] );
//				dist += ( dense_point_data[m][i][0] - sparse_point_data[m][j][0] ) * ( dense_point_data[m][i][0] - sparse_point_data[m][j][0] );
//				dist += ( dense_point_data[m][i][1] - sparse_point_data[m][j][1] ) * ( dense_point_data[m][i][1] - sparse_point_data[m][j][1] );
//				dist += ( dense_point_data[m][i][2] - sparse_point_data[m][j][2] ) * ( dense_point_data[m][i][2] - sparse_point_data[m][j][2] );
//				dense_sparse_point_distances[j] += dist; /*( 1.0f - exp( ndist / .5f - 2.0f ) ) * */
//				dense_sparse_point_instances[j]++;
//			}
//		}
//
//		for ( j = 0; j < number_of_sparse_points; j++ )
//			dense_sparse_point_distances[j] /= dense_sparse_point_instances[j];
//
//		nearest_sparse_points_for_each_dense_point[i].resize( num_nearest );
//		count_range = boost::counting_range(0, (int)dense_sparse_point_distances.size() );
//		index_list = vector<int>(count_range.begin(), count_range.end());
//		std::sort( index_list.begin(), index_list.end(), SortOrder<float>(&dense_sparse_point_distances) );
//		for (k = 0; k < num_nearest; k++)
//			nearest_sparse_points_for_each_dense_point[i][k] = (short)index_list[k];
//
//		//////if ( i == 50000 )
//		//////{
//		//////	for (k = 0; k < num_nearest; k++)
//		//////		std::cout << nearest_sparse_points_for_each_dense_point[i][k] << " ";
//		//////}
//	}
//
//	std::cout << "Done." << std::endl;
}


void TrainingData::findPartCentroids()
{	
	std::cout << "Finding part centroids..."; 		
	int total_number_of_part_labels = (int)percentage_of_sparse_points_per_part.size();
	part_centroids.resize( number_of_training_examples );

	for ( int m = 0; m < number_of_training_examples; m++ )
	{
		vector< float > number_of_points_per_part( total_number_of_part_labels, 0.0f );
		part_centroids[m].resize( total_number_of_part_labels );
		for ( int p = 0; p < total_number_of_part_labels; p++ )
			part_centroids[m][p].resize(3, FLT_MAX);

		for ( int j = 0; j < number_of_sparse_points; j++ )
		{
			if ( sparse_point_data[m][j].empty() )
				continue;

			int p = (int)sparse_part_id[m][j];
			if ( part_centroids[m][p][0] == FLT_MAX)
			{
				part_centroids[m][p][0] = 0.0f;
				part_centroids[m][p][1] = 0.0f;
				part_centroids[m][p][2] = 0.0f;
			}
			number_of_points_per_part[p]++;
			part_centroids[m][p][0] += sparse_point_data[m][j][0];
			part_centroids[m][p][1] += sparse_point_data[m][j][1];
			part_centroids[m][p][2] += sparse_point_data[m][j][2];
		}

		for ( int p = 0; p < total_number_of_part_labels; p++ )
		{
			part_centroids[m][p][0] /= number_of_points_per_part[p];
			part_centroids[m][p][1] /= number_of_points_per_part[p];
			part_centroids[m][p][2] /= number_of_points_per_part[p];
		}
	}	

	std::cout << "Done." << std::endl;
}


void TrainingData::findPartReflectiveSymmetries()
{	
	if ( adjusted_radius == 0.0f )
	{
		std::cout << "Need to run populateSpatialNeighbors() first" << std::endl;
		return;
	}
	std::cout << "Finding part reflective symmetries...";
	int total_number_of_part_labels = (int)percentage_of_sparse_points_per_part.size();
	symmetry_type.resize( number_of_training_examples );

	int m, p, j, j2;
	vector< int > part_point_ids;
	bool is_symmetric = false;
	int number_of_self_symmetric_points = 0;
	float dist_to_neighboring_compatible_point = 0.0f;
	float min_dist = FLT_MAX;
	bool has_self_symmetric_point = false;
	float ndist = 0.0f;
	float dist = 0.0f;
	float tmp = 0.0f;

#pragma omp parallel for private ( m, p, j, j2, part_point_ids, is_symmetric, number_of_self_symmetric_points, dist_to_neighboring_compatible_point, min_dist, has_self_symmetric_point, ndist, dist, tmp ) 
	for ( m = 0; m < number_of_training_examples; m++ )
	{
		symmetry_type[m].resize( sparse_point_data[m].size(), 0 );
		
		for ( p = 0; p < total_number_of_part_labels; p++)
		{
			part_point_ids.clear();
			is_symmetric = false;
			number_of_self_symmetric_points = 0;

			for ( j = 0; j < number_of_sparse_points; j++ )
			{
				if ( sparse_point_data[m][j].empty() )
					continue;
				if ( sparse_part_id[m][j] != p )
					continue;
				part_point_ids.push_back( j );
			}
			
			dist_to_neighboring_compatible_point = 0.0f;
			for ( j = 0; j < (int)part_point_ids.size(); j++ )
			{
				// assume reflection over x-axis
				min_dist = FLT_MAX;
				has_self_symmetric_point = false;

				for ( j2 = 0; j2 < number_of_sparse_points; j2++ )
				{
					if (j2 == part_point_ids[j])
						continue;
					if ( sparse_point_data[m][j2].empty() )
						continue;

					ndist = 0.0f;
					dist = 0.0f;
					ndist += ( -sparse_normal_data[m][ part_point_ids[j] ][0] * sparse_normal_data[m][ j2 ][0] );
					ndist += ( sparse_normal_data[m][ part_point_ids[j] ][1] * sparse_normal_data[m][ j2 ][1] );
					ndist += ( sparse_normal_data[m][ part_point_ids[j] ][2] * sparse_normal_data[m][ j2 ][2] );
					if (ndist < 0.0f)
						dist = FLT_MAX;
					else
					{
						tmp = ( -sparse_point_data[m][ part_point_ids[j] ][0] - sparse_point_data[m][ j2 ][0] );
						dist += tmp*tmp;
						tmp = ( sparse_point_data[m][ part_point_ids[j] ][1] - sparse_point_data[m][ j2 ][1] );
						dist += tmp*tmp;
						tmp = ( sparse_point_data[m][ part_point_ids[j] ][2] - sparse_point_data[m][ j2 ][2] );
						dist += tmp*tmp;
					}
					if ( dist < min_dist )
					{
						if ( sparse_part_id[m][j2] == p )
							has_self_symmetric_point = true;
						else
							has_self_symmetric_point = false;
						min_dist = dist;
					}
				} // end of loop for potentially symmetric points of part
				
				dist_to_neighboring_compatible_point += min_dist;
				number_of_self_symmetric_points += (int) has_self_symmetric_point;

			} //end of loop over points of part

			dist_to_neighboring_compatible_point /= ( (float)part_point_ids.size() + 1.0f);
			if ( part_point_ids.size() > 0 )
				if ( dist_to_neighboring_compatible_point < adjusted_radius * adjusted_radius )
					is_symmetric = true;			

			if (is_symmetric)
			{
				for ( j = 0; j < (int)part_point_ids.size(); j++ )
				{
					symmetry_type[m][ part_point_ids[j] ] = 1;
				}
				if (number_of_self_symmetric_points > int(part_point_ids.size())/2)
				{
					for ( j = 0; j < (int)part_point_ids.size(); j++ )
					{
						symmetry_type[m][ part_point_ids[j] ] = -1;
					}
				}
			}
			//std::cout << m << "-" << p << ": is_symmetric:" << is_symmetric << ", self-symmetry:" << (number_of_self_symmetric_points > int(part_point_ids.size())/2) << std::endl;
		} // end of loop over parts

	}	// end of loop over training examples

	std::cout << "Done." << std::endl;
}



bool TrainingData::load(std::string const & in_path)
{
	std::cout << "Reading " << in_path << " for loading training data directly...";
	ifstream in( in_path.c_str(), ios::in | ios::binary );
	if ( !in.good() )
	{
		std::cerr << "Failed. Cannot open file for reading." << std::endl;
		return false;
	}
	boost::archive::binary_iarchive ia(in);
	ia >> *this;
	in.close();
	std::cout << "Done." << std::endl;
	return true;
}

void TrainingData::save(std::string const & out_path) const
{
	if ( out_path.empty() )
		return;
	std::cout << "Writing " << out_path << " for storing training data directly...";
	ofstream out( out_path.c_str(), ios::out | ios::binary );
	if ( !out.good() )
	{
		std::cerr << "Failed. Cannot open file for writing." << std::endl;
		return;
	}
	boost::archive::binary_oarchive oa(out);
	oa << *this;
	out.close();
	std::cout << "Done." << std::endl;
}

}// end of namespace SNL
} // end of namespace DL13









//if (!is_binary)
//{
//	// read each model filename
//	for (size_t i = 0; i < all_data_filenames.size(); i++)
//	{
//		if (data_filenames.size() == limit_number_of_examples_to_read)
//			break;
//		string dense_filename = in_path + "/dense/" + all_data_filenames[i] + "/" + all_data_filenames[i] + "_matching.txt";
//		string sparse_filename = in_path	+ "/sparse/" + all_data_filenames[i] + "/" + all_data_filenames[i] + "_matching.txt";
//		string attributes_filename = in_path	+ "/sparse/" + all_data_filenames[i] + "/" + all_data_filenames[i] + "_attributes.txt";
//		cout << i << " | Parsing " <<  all_data_filenames[i] << "...";

//		ifstream dense_file( dense_filename.c_str() );
//		ifstream sparse_file( sparse_filename.c_str() );
//		ifstream attributes_file( attributes_filename.c_str() );
//		if ( !dense_file.good() || !sparse_file.good() )
//		{
//			std::cerr << "Files " << dense_filename << ", " << sparse_filename  << " are not found or domain directory structure is corrupted." << std::endl;
//			continue;
//		}
//		float fit_error;
//		dense_file >> fit_error;
//		if (fit_error > threshold)
//		{
//			cout << " rejected." << endl;
//			dense_file.close();
//			sparse_file.close();
//			attributes_file.close();
//			continue;
//		}
//		if ( number_of_attributes > 0 && !attributes_file.good() )
//		{
//			std::cerr << "Attributes file: " << attributes_filename  << " was not found - ignoring this model." << std::endl;
//			continue;
//		}
//		fitting_error.push_back(fit_error);
//		sparse_file >> fit_error;

//		data_filenames.push_back( all_data_filenames[i] );

//		dense_point_data.push_back( vector< vector<float> >() );
//		dense_point_data[ dense_point_data.size()-1].resize( number_of_dense_points );
//		dense_normal_data.push_back( vector< vector<float> >() );
//		dense_normal_data[ dense_normal_data.size()-1].resize( number_of_dense_points );
//		dense_template_id.push_back( vector< short >() );
//		dense_template_id[ dense_template_id.size()-1].resize( number_of_dense_points );
//		dense_part_id.push_back( vector< short >() );
//		dense_part_id[ dense_part_id.size()-1 ].resize( number_of_dense_points );
//		dense_point_distance_error.push_back( vector< float >() );
//		dense_point_distance_error[ dense_point_distance_error.size()-1 ].resize( number_of_dense_points );
//		dense_normal_distance_error.push_back( vector< float >() );
//		dense_normal_distance_error[ dense_normal_distance_error.size()-1 ].resize( number_of_dense_points );

//		sparse_point_data.push_back( vector< vector<float> >() );
//		sparse_point_data[ sparse_point_data.size()-1].resize( number_of_sparse_points );
//		sparse_normal_data.push_back( vector< vector<float> >() );
//		sparse_normal_data[ sparse_normal_data.size()-1].resize( number_of_sparse_points );
//		sparse_template_id.push_back( vector< short >() );
//		sparse_template_id[ sparse_template_id.size()-1].resize( number_of_sparse_points );
//		sparse_part_id.push_back( vector< short >() );
//		sparse_part_id[ sparse_part_id.size()-1 ].resize( number_of_sparse_points );
//		sparse_point_distance_error.push_back( vector< float >() );
//		sparse_point_distance_error[ sparse_point_distance_error.size()-1 ].resize( number_of_sparse_points );
//		sparse_normal_distance_error.push_back( vector< float >() );
//		sparse_normal_distance_error[ sparse_normal_distance_error.size()-1 ].resize( number_of_sparse_points );

//		if ( number_of_attributes > 0 )
//		{
//			attribute_data.push_back( vector<float>() );
//			attribute_data[ attribute_data.size()-1].resize( number_of_attributes );
//			for (int a = 0; a < number_of_attributes; a++)
//				attributes_file >> attribute_data[ attribute_data.size()-1 ][a];
//			attributes_file.close();
//			number_of_training_examples_attributes++;
//		}			

//		size_t id = 0;
//		size_t line = 2;

//		while ( true )
//		{
//			float x, y, z, nx, ny, nz;
//			float point_distance;
//			float normal_distance;
//			size_t template_id, part_id, point_id;
//			dense_file >> x >> y >> z >> nx >> ny >> nz >> template_id 
//				>> part_id >> point_id >> point_distance >> normal_distance;
//			if (dense_file.eof())
//				break;
//			//if (point_id+2 != line )
//			//{
//			//	cerr << "internal error: points are not ordered in this file" << endl;
//			//	exit(-1);
//			//}
//			line++;

//			dense_point_data[ dense_point_data.size()-1 ][ point_id ].resize(3);
//			dense_point_data[ dense_point_data.size()-1 ][ point_id ][0] = x;
//			dense_point_data[ dense_point_data.size()-1 ][ point_id ][1] = y;
//			dense_point_data[ dense_point_data.size()-1 ][ point_id ][2] = z;
//			dense_normal_data[ dense_normal_data.size()-1][ point_id ].resize(3);
//			dense_normal_data[ dense_normal_data.size()-1 ][ point_id ][0] = nx;
//			dense_normal_data[ dense_normal_data.size()-1 ][ point_id ][1] = ny;
//			dense_normal_data[ dense_normal_data.size()-1 ][ point_id ][2] = nz;
//			dense_template_id[ dense_template_id.size()-1][ point_id ] = (short)template_id;
//			dense_part_id[ dense_part_id.size()-1][ point_id ] = (short)part_id;
//			dense_point_distance_error[ dense_point_distance_error.size()-1][ point_id ] = point_distance;
//			dense_normal_distance_error[ dense_normal_distance_error.size()-1][ point_id ] = normal_distance;
//		}

//		id = 0;
//		line = 2;
//		while( true )
//		{
//			float x, y, z, nx, ny, nz;
//			float point_distance;
//			float normal_distance;
//			size_t template_id, part_id, point_id;
//			sparse_file >> x >> y >> z >> nx >> ny >> nz >> template_id 
//				>> part_id >> point_id >> point_distance >> normal_distance;
//			if (sparse_file.eof())
//				break;
//			//if (point_id+2 != line )
//			//{
//			//	cerr << "internal error: points are not ordered in this file" << endl;
//			//	exit(-1);
//			//}
//			line++;

//			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ].resize(3);
//			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ][0] = x;
//			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ][1] = y;
//			sparse_point_data[ sparse_point_data.size()-1 ][ point_id ][2] = z;
//			sparse_normal_data[ sparse_normal_data.size()-1][ point_id ].resize(3);
//			sparse_normal_data[ sparse_normal_data.size()-1 ][ point_id ][0] = nx;
//			sparse_normal_data[ sparse_normal_data.size()-1 ][ point_id ][1] = ny;
//			sparse_normal_data[ sparse_normal_data.size()-1 ][ point_id ][2] = nz;
//			sparse_template_id[ sparse_template_id.size()-1][ point_id ] = (short)template_id;
//			sparse_part_id[ sparse_part_id.size()-1][ point_id ] = (short)part_id;
//			sparse_point_distance_error[ sparse_point_distance_error.size()-1][ point_id ] = point_distance;
//			sparse_normal_distance_error[ sparse_normal_distance_error.size()-1][ point_id ] = normal_distance;

//			if ( part_id >= (int)percentage_of_sparse_points_per_part.size() )
//				percentage_of_sparse_points_per_part.conservativeResize( percentage_of_sparse_points_per_part.size() + 1 );
//			percentage_of_sparse_points_per_part( part_id )++;
//		}

//		dense_file.close();
//		sparse_file.close();
//		cout << " done." <<  endl;

//		//std::cout << sparse_point_data[ sparse_point_data.size()-1 ][ number_of_sparse_points-1 ][2] << std::endl;
//		//std::cout << sparse_normal_data[ sparse_normal_data.size()-1 ][ number_of_sparse_points-1 ][2] << std::endl;
//		//std::cout << sparse_template_id[ sparse_template_id.size()-1 ][ number_of_sparse_points-1 ] << std::endl;
//		//std::cout << sparse_part_id[ sparse_part_id.size()-1 ][ number_of_sparse_points-1 ] << std::endl;
//		//std::cout << sparse_point_distance_error[ sparse_point_distance_error.size()-1 ][ number_of_sparse_points-1 ] << std::endl;
//		//std::cout << sparse_normal_distance_error[ sparse_template_id.size()-1 ][ number_of_sparse_points-1 ] << std::endl;

//		//std::cout << dense_point_data[ dense_point_data.size()-1 ][ number_of_dense_points-1 ][2] << std::endl;
//		//std::cout << dense_normal_data[ dense_normal_data.size()-1 ][ number_of_dense_points-1 ][2] << std::endl;
//		//std::cout << dense_template_id[ dense_template_id.size()-1 ][ number_of_dense_points-1 ] << std::endl;
//		//std::cout << dense_part_id[ dense_part_id.size()-1 ][ number_of_dense_points-1 ] << std::endl;
//		//std::cout << dense_point_distance_error[ dense_point_distance_error.size()-1 ][ number_of_dense_points-1 ] << std::endl;
//		//std::cout << dense_normal_distance_error[ dense_template_id.size()-1 ][ number_of_dense_points-1 ] << std::endl;
//	}
//} // end of text-based format sparsing
//else
//{