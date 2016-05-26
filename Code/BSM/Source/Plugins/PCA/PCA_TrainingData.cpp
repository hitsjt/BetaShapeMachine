#include "PCA_TrainingData.hpp"

namespace SNL {;
namespace PCA {;

TrainingData::TrainingData(string const & in_path, float threshold, int limit_number_of_examples_to_read, bool is_binary, 
													 int _number_of_attributes,
													 int _number_of_sparse_points, int _number_of_dense_points)
{
	if (in_path.empty())
		return;
	std::cout << "Loading training data from " << in_path << "..." << std::endl;
	number_of_training_examples = 0;
	number_of_training_examples_attributes = 0;
	number_of_dense_points = _number_of_dense_points;
	number_of_sparse_points = _number_of_sparse_points;
	number_of_attributes = _number_of_attributes;
	string domain_dir;
	vector<string> all_data_filenames;
	number_of_sparse_points_per_part.resize(0);

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
		sparse_template_id.push_back( vector< short >() );
		sparse_template_id[ sparse_template_id.size()-1].resize( number_of_sparse_points, -1 );
		sparse_part_id.push_back( vector< short >() );
		sparse_part_id[ sparse_part_id.size()-1 ].resize( number_of_sparse_points, -1 );
		sparse_point_distance_error.push_back( vector< float >() );
		sparse_point_distance_error[ sparse_point_distance_error.size()-1 ].resize( number_of_sparse_points, -1.0f );
		sparse_normal_distance_error.push_back( vector< float >() );
		sparse_normal_distance_error[ sparse_normal_distance_error.size()-1 ].resize( number_of_sparse_points, -1.0f );


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
    SCVECTORf number_of_sparse_points_per_part_in_this_shape = number_of_sparse_points_per_part;
    number_of_sparse_points_per_part_in_this_shape.fill(0.0f);
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

			if ( part_id >= (int)number_of_sparse_points_per_part.size() )
			{
				int old_size = number_of_sparse_points_per_part.size();
				number_of_sparse_points_per_part.conservativeResize( part_id + 1 );
				for (int p = old_size; p <= part_id; p++)
					number_of_sparse_points_per_part( p ) = 0.0f;
        
        number_of_sparse_points_per_part_in_this_shape.conservativeResize(part_id + 1);
        for (int p = old_size; p <= part_id; p++)
          number_of_sparse_points_per_part_in_this_shape(p) = 0.0f;
			}

      number_of_sparse_points_per_part_in_this_shape(part_id)++;
		}
		//dense_file.close();

    for (int p = 0; p < number_of_sparse_points_per_part.size(); p++)
      number_of_sparse_points_per_part(p) = max(number_of_sparse_points_per_part(p), number_of_sparse_points_per_part_in_this_shape(p));

		sparse_file.close();
		cout << " done." <<  endl;
	}

	number_of_training_examples = (int)data_filenames.size();

} // end of constructor TrainingData()



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
	int total_number_of_part_labels = (int)number_of_sparse_points_per_part.size();
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
} // end of namespace PCA




