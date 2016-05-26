#include <boost/filesystem.hpp>
#include <stdint.h>
#include <cfloat>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class TrainingData
{
  public:
    int32_t number_of_training_examples, number_of_training_examples_attributes;
    int32_t number_of_dense_points;
    int32_t number_of_sparse_points;
    int32_t number_of_attributes;

    vector<string> data_filenames;
    vector<float> fitting_error;

    vector< vector< vector<float> > >  dense_point_data; // M (#examples x #number_points x 3)
    vector< vector< vector<float> > >  dense_normal_data;
    vector< vector<short> >            dense_template_id;
    vector< vector<short> >            dense_part_id;
    vector< vector<float> >            dense_point_distance_error;
    vector< vector<float> >            dense_normal_distance_error;

    vector< vector< vector<float> > >  sparse_point_data;
    vector< vector< vector<float> > >  sparse_normal_data;
    vector< vector<short> >            sparse_template_id;
    vector< vector<short> >            sparse_part_id;
    vector< vector<float> >            sparse_point_distance_error;
    vector< vector<float> >            sparse_normal_distance_error;

    vector< vector< float > > attribute_data;

    TrainingData(string const & in_path = "", float threshold = FLT_MAX,  bool is_binary = true,
                 int32_t _number_of_attributes = 0, int32_t _number_of_sparse_points = 0, int32_t _number_of_dense_points = 0,
                 int32_t limit_number_of_examples_to_read = INT_MAX);

}; // class TrainingData

TrainingData::TrainingData(string const & in_path, float threshold, bool is_binary, int32_t _number_of_attributes,
                           int32_t _number_of_sparse_points, int32_t _number_of_dense_points,
                           int32_t limit_number_of_examples_to_read)
{
  if (in_path.empty())
    return;

  cout << "Loading training data from " << in_path << "..." << endl;
  number_of_training_examples = 0;
  number_of_training_examples_attributes = 0;
  number_of_dense_points = _number_of_dense_points;
  number_of_sparse_points = _number_of_sparse_points;
  number_of_attributes = _number_of_attributes;
  string domain_dir;
  vector<string> all_data_filenames;
  boost::filesystem::directory_iterator end_itr, itr; // default construction yields past-the-end

  try
  {
    itr = boost::filesystem::directory_iterator( in_path + "/dense/" );
  }
  catch (boost::filesystem::filesystem_error & ex)
  {
    cerr << ex.what() << endl;
    cerr << "Directory " << in_path + "/dense/" << " not accessible. The domain directory should have a 'dense' and 'sparse' subfolder! " << endl;
    return;
  }

  for ( ; itr != end_itr; ++itr )
  {
    all_data_filenames.push_back( itr->path().leaf().string() );
    domain_dir = itr->path().parent_path().parent_path().string();
  }

  for (size_t i = 0; i < all_data_filenames.size(); i++)
  {
    if ((int32_t)data_filenames.size() == limit_number_of_examples_to_read)
      break;

    // 1. OPEN FILES
    string dense_filename = in_path + "/dense/" + all_data_filenames[i] + "/" + all_data_filenames[i] + ".txt";
    string sparse_filename = in_path  + "/sparse/" + all_data_filenames[i] + "/" + all_data_filenames[i] + ".txt";
    string attributes_filename = in_path  + "/sparse/" + all_data_filenames[i] + "/" + all_data_filenames[i] + "_attributes.txt";
    cout << i << " | Parsing " <<  all_data_filenames[i] << "...";
    ifstream dense_file( dense_filename.c_str(), ios::in | ios::binary );
    ifstream sparse_file( sparse_filename.c_str(), ios::in | ios::binary );
    ifstream attributes_file( attributes_filename.c_str(), ios::in | ios::binary );

    if ( !dense_file.good() || !sparse_file.good() )
    {
      cerr << "Files " << dense_filename << ", " << sparse_filename  << " are not found or domain directory structure is corrupted." << endl;
      continue;
    }

    // 2. READ number_of_dense_points , number_of_sparse_points
    int32_t num_points_in_dataset;
    dense_file.read( (char *)(&num_points_in_dataset), sizeof(num_points_in_dataset) );

    if ( i == 0 )
      number_of_dense_points = num_points_in_dataset;
    else
    {
      if ( num_points_in_dataset != number_of_dense_points )
      {
        cerr << "File format " << dense_filename << " is inconsistent with other files in the dataset." << endl;
        return;
      }
    }

    sparse_file.read( (char *)(&num_points_in_dataset), sizeof(num_points_in_dataset) );

    if ( i == 0 )
      number_of_sparse_points = num_points_in_dataset;
    else
    {
      if ( num_points_in_dataset != number_of_sparse_points )
      {
        cerr << "File format " << sparse_filename << " is inconsistent with other files in the dataset." << endl;
        return;
      }
    }

    // 2. READ number_of_dense_points_in_shape, number_of_sparse_points_in_shape
    int32_t number_of_dense_points_in_shape;
    dense_file.read( (char *)(&number_of_dense_points_in_shape), sizeof(number_of_dense_points_in_shape) );
    int32_t number_of_sparse_points_in_shape;
    sparse_file.read( (char *)(&number_of_sparse_points_in_shape), sizeof(number_of_sparse_points_in_shape) );
    //3. READ FIT ERROR
    float fit_error;
    dense_file.read((char *)(&fit_error), sizeof(fit_error) );

    if (fit_error > threshold)
    {
      cout << " rejected." << endl;
      dense_file.close();
      sparse_file.close();
      attributes_file.close();
      continue;
    }

    fitting_error.push_back(fit_error);
    sparse_file.read((char *)(&fit_error), sizeof(fit_error) );
    //4. PREPARE DATA STRUCTURES FOR NEW DATA
    data_filenames.push_back( all_data_filenames[i] );
    dense_point_data.push_back( vector< vector<float> >() );
    dense_point_data[ dense_point_data.size() - 1].resize( number_of_dense_points );
    dense_normal_data.push_back( vector< vector<float> >() );
    dense_normal_data[ dense_normal_data.size() - 1].resize( number_of_dense_points );
    dense_template_id.push_back( vector< short >() );
    dense_template_id[ dense_template_id.size() - 1].resize( number_of_dense_points );
    dense_part_id.push_back( vector< short >() );
    dense_part_id[ dense_part_id.size() - 1 ].resize( number_of_dense_points );
    dense_point_distance_error.push_back( vector< float >() );
    dense_point_distance_error[ dense_point_distance_error.size() - 1 ].resize( number_of_dense_points );
    dense_normal_distance_error.push_back( vector< float >() );
    dense_normal_distance_error[ dense_normal_distance_error.size() - 1 ].resize( number_of_dense_points );
    sparse_point_data.push_back( vector< vector<float> >() );
    sparse_point_data[ sparse_point_data.size() - 1].resize( number_of_sparse_points );
    sparse_normal_data.push_back( vector< vector<float> >() );
    sparse_normal_data[ sparse_normal_data.size() - 1].resize( number_of_sparse_points );
    sparse_template_id.push_back( vector< short >() );
    sparse_template_id[ sparse_template_id.size() - 1].resize( number_of_sparse_points );
    sparse_part_id.push_back( vector< short >() );
    sparse_part_id[ sparse_part_id.size() - 1 ].resize( number_of_sparse_points );
    sparse_point_distance_error.push_back( vector< float >() );
    sparse_point_distance_error[ sparse_point_distance_error.size() - 1 ].resize( number_of_sparse_points );
    sparse_normal_distance_error.push_back( vector< float >() );
    sparse_normal_distance_error[ sparse_normal_distance_error.size() - 1 ].resize( number_of_sparse_points );
    //5. READ ATTRIBUTES
    attribute_data.push_back( vector<float>() );

    while ( attributes_file.good() )
    {
      float attribute;
      attributes_file >> attribute;

      if ( attributes_file.eof() )
        break;

      attributes_file.ignore(numeric_limits<int32_t>::max(), attributes_file.widen('\n'));

      if ( attributes_file.eof() )
        break;

      attribute_data[ attribute_data.size() - 1 ].push_back( attribute );
      number_of_training_examples_attributes++;
    }

    if ( number_of_attributes <= 0 )
      number_of_attributes = (int32_t)attribute_data[ attribute_data.size() - 1 ].size();
    else
    {
      if ( number_of_attributes != (int32_t)attribute_data[ attribute_data.size() - 1 ].size() )
      {
        cerr << "File " << attributes_filename << " has inconsistent number of attributes compared to other files in the dataset." << endl;
        return;
      }
    }

    attributes_file.close();

    //5. READ DENSE FILE
    for (int32_t j = 0; j < number_of_dense_points_in_shape; j++)
    {
      float x, y, z, nx, ny, nz;
      int32_t template_id, part_id, point_id;
      float point_distance;
      float normal_distance;
      dense_file.read( (char *)(&x), sizeof(x) );
      dense_file.read( (char *)(&y), sizeof(y) );
      dense_file.read( (char *)(&z), sizeof(z) );
      dense_file.read( (char *)(&nx), sizeof(nx) );
      dense_file.read( (char *)(&ny), sizeof(ny) );
      dense_file.read( (char *)(&nz), sizeof(nz) );
      dense_file.read( (char *)(&template_id), sizeof(template_id) );
      dense_file.read( (char *)(&part_id), sizeof(part_id) );
      dense_file.read( (char *)(&point_id), sizeof(point_id) );
      dense_file.read( (char *)(&point_distance), sizeof(point_distance) );
      dense_file.read( (char *)(&normal_distance), sizeof(normal_distance) );
      dense_point_data[ dense_point_data.size() - 1 ][ point_id ].resize(3);
      dense_point_data[ dense_point_data.size() - 1 ][ point_id ][0] = x;
      dense_point_data[ dense_point_data.size() - 1 ][ point_id ][1] = y;
      dense_point_data[ dense_point_data.size() - 1 ][ point_id ][2] = z;
      dense_normal_data[ dense_normal_data.size() - 1][ point_id ].resize(3);
      dense_normal_data[ dense_normal_data.size() - 1 ][ point_id ][0] = nx;
      dense_normal_data[ dense_normal_data.size() - 1 ][ point_id ][1] = ny;
      dense_normal_data[ dense_normal_data.size() - 1 ][ point_id ][2] = nz;
      dense_template_id[ dense_template_id.size() - 1][ point_id ] = (short)template_id;
      dense_part_id[ dense_part_id.size() - 1][ point_id ] = (short)part_id;
      dense_point_distance_error[ dense_point_distance_error.size() - 1][ point_id ] = point_distance;
      dense_normal_distance_error[ dense_normal_distance_error.size() - 1][ point_id ] = normal_distance;
    }

    //5. READ SPARSE FILE
    for (int32_t j = 0; j < number_of_sparse_points_in_shape; j++)
    {
      float x, y, z, nx, ny, nz;
      int32_t template_id, part_id, point_id;
      float point_distance;
      float normal_distance;
      sparse_file.read( (char *)(&x), sizeof(x) );
      sparse_file.read( (char *)(&y), sizeof(y) );
      sparse_file.read( (char *)(&z), sizeof(z) );
      sparse_file.read( (char *)(&nx), sizeof(nx) );
      sparse_file.read( (char *)(&ny), sizeof(ny) );
      sparse_file.read( (char *)(&nz), sizeof(nz) );
      sparse_file.read( (char *)(&template_id), sizeof(template_id) );
      sparse_file.read( (char *)(&part_id), sizeof(part_id) );
      sparse_file.read( (char *)(&point_id), sizeof(point_id) );
      sparse_file.read( (char *)(&point_distance), sizeof(point_distance) );
      sparse_file.read( (char *)(&normal_distance), sizeof(normal_distance) );
      sparse_point_data[ sparse_point_data.size() - 1 ][ point_id ].resize(3);
      sparse_point_data[ sparse_point_data.size() - 1 ][ point_id ][0] = x;
      sparse_point_data[ sparse_point_data.size() - 1 ][ point_id ][1] = y;
      sparse_point_data[ sparse_point_data.size() - 1 ][ point_id ][2] = z;
      sparse_normal_data[ sparse_normal_data.size() - 1][ point_id ].resize(3);
      sparse_normal_data[ sparse_normal_data.size() - 1 ][ point_id ][0] = nx;
      sparse_normal_data[ sparse_normal_data.size() - 1 ][ point_id ][1] = ny;
      sparse_normal_data[ sparse_normal_data.size() - 1 ][ point_id ][2] = nz;
      sparse_template_id[ sparse_template_id.size() - 1][ point_id ] = (short)template_id;
      sparse_part_id[ sparse_part_id.size() - 1][ point_id ] = (short)part_id;
      sparse_point_distance_error[ sparse_point_distance_error.size() - 1][ point_id ] = point_distance;
      sparse_normal_distance_error[ sparse_normal_distance_error.size() - 1][ point_id ] = normal_distance;
    }

    dense_file.close();
    sparse_file.close();
    cout << " done." <<  endl;
  }

  number_of_training_examples = (int32_t)data_filenames.size();

#if 0
  // CHECK IF ALL POINTS HAVE DATA
  if ( number_of_training_examples > 1 )
  {
    for ( int32_t m = 0; m < number_of_training_examples; m++)
      for (size_t i = 0; i < sparse_point_data[m].size(); i++)
      {
        if ( sparse_point_data[m][i].empty() )
        {
          cout << "TrainingData error (" << data_filenames[m] << "): Sparse point with id: " << i << " has no data" << endl;
          exit(-1);
        }
      }

    for ( int32_t m = 0; m < number_of_training_examples; m++)
      for (size_t i = 0; i < dense_point_data[m].size(); i++)
      {
        if ( dense_point_data[m][i].empty() )
        {
          cout << "TrainingData error (" << data_filenames[m] << "): Dense point with id: " << i << " has no data" << endl;
          exit(-1);
        }
      }
  }
#endif

  // OUTPUT PART SAMPLES
  for (size_t m = 0; m < sparse_point_data.size(); m++)
  {
    cout << all_data_filenames[m] << endl;

    vector<bool> extracted(sparse_point_data[m].size(), false);
    size_t num_extracted = 0;

    while (num_extracted < sparse_point_data[m].size())
    {
      ofstream out;
      string out_path;
      long part_id = -1;

      for (size_t i = 0; i < sparse_point_data[m].size(); i++)
      {
        if (extracted[i])
          continue;

        if (sparse_point_data[m][i].empty())
        {
          extracted[i] = true;
          num_extracted++;
          continue;
        }

        if (part_id < 0)
        {
          part_id = sparse_part_id[m][i];

          ostringstream oss;
          oss << in_path << "/sparse/" << all_data_filenames[m] << "/" << part_id << ".pts";
          out_path = oss.str();

          out.open(out_path.c_str(), ios::binary);
          if (!out)
          {
            cerr << "Could not open " << out_path << " for writing" << endl;
            exit(-1);
          }
        }
        else if (sparse_part_id[m][i] != part_id)
          continue;

        out << sparse_point_data[m][i][0] << ' '
            << sparse_point_data[m][i][1] << ' '
            << sparse_point_data[m][i][2] << ' '
            << sparse_normal_data[m][i][0] << ' '
            << sparse_normal_data[m][i][1] << ' '
            << sparse_normal_data[m][i][2] << ' '
            << i << endl;

        extracted[i] = true;
        num_extracted++;
      }

      cout << "  -- " << out_path << endl;
    }
  }
} // end of constructor TrainingData()

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <dir>" << endl;
    return -1;
  }

  string in_path = argv[1];
  TrainingData tr(in_path);
  return 0;
}
