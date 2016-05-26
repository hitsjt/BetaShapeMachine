#include "PCA_Common.hpp"
#include "PCA_Model.hpp"
#include "PCA_Part.hpp"

namespace SNL {;
namespace PCA {;

PCAModel::PCAModel(const string &load_pca_file_path, const string &load_training_file_path, const string &training_data_path, const SNL::Options &_options)
{
  options.set("keep_variance_percentage", 0.9f);
  options.merge(_options);
  training_data = NULL;

  if (load_training_file_path != "")
  {
    training_data = new TrainingData();
    if (!training_data->load(load_training_file_path))
    {
      delete training_data;
      training_data = NULL;
    }
  }

  if ( (training_data == NULL) && (training_data_path != "") )
  {
    training_data = new TrainingData(training_data_path, options.get("fitting_threshold", 100.0f));
    training_data->findPartCentroids();
    if (load_training_file_path != "")
      training_data->save(load_training_file_path);
  }

  if (load_pca_file_path != "")
  {
    load(load_pca_file_path);
  }
}

PCAModel::~PCAModel()
{
  if (training_data != NULL)
  {
    delete training_data;
  }

  for (int p = 0; p < parts.size(); p++)
    delete parts[p];
}

void PCAModel::train(const string &save_model_file_path)
{
  if (training_data == NULL)
  {
    std::cerr << "No training data to learn the PCA model!";
    return;
  }
  number_of_sparse_points = training_data->number_of_sparse_points;
 
  for (int p = 0; p < training_data->number_of_sparse_points_per_part.size(); p++)
  {
    std::cout << "Processing part " << p << " for training PCA model...";

    PCAPart* part = new PCAPart();
    vector<int> point_ids;
    bool point_ids_is_empty = true;
    point_ids.reserve(number_of_sparse_points);
    parts.push_back(part);

    SMATRIXf data(training_data->number_of_training_examples, 3 * (int)training_data->number_of_sparse_points_per_part(p));
    data.fill(FLT_MAX);

    for (int m = 0; m < training_data->number_of_training_examples; m++)
    {
      int current_pos_in_data = 0;

      for (int n = 0; n < number_of_sparse_points; n++)
      {
        // point not belonging to this part or not existing
        if (training_data->sparse_part_id[m][n] != p)
          continue;

        // point belonging to this part - is it empty?
        if (!training_data->sparse_point_data[m][n].empty())
        {
          data(m, current_pos_in_data++ ) = training_data->sparse_point_data[m][n][0];
          data(m, current_pos_in_data++ ) = training_data->sparse_point_data[m][n][1];
          data(m, current_pos_in_data++ ) = training_data->sparse_point_data[m][n][2];
        }

        if (point_ids_is_empty)
          point_ids.push_back(n);          
      } // end of loop over points

      if (point_ids_is_empty && !point_ids.empty()) // got filled from this example - done with point_ids
        point_ids_is_empty = false;
    }  // end of loop over examples

    data = removeRows(data, FLT_MAX);
    part->setPointIds(point_ids);
    part->train(data, options.get("keep_variance_percentage", 0.9f));
    std::cout << "Done.";
  } // end of loop over parts

  save(save_model_file_path);
}


vector< vector< SNL::DL13::Point > > PCAModel::reconstructInput(std::string const & in_path, bool need_dense_result, int num_iterations, bool smooth_result)
{
  boost::timer t;
  TrainingData input_data(in_path, FLT_MAX);
  vector< vector< SNL::DL13::Point > > all_points;

  if (parts.empty())
  {
    std::cerr << "Cannot run reconstruct without a learned PCA model";
    return all_points;
  }

  if (input_data.number_of_sparse_points != number_of_sparse_points)
  {
    std::cerr << "Input shapes have inconsistent number of points with the loaded PCA model" << std::endl;
    std::cerr << input_data.number_of_sparse_points << std::endl;
    std::cerr << number_of_sparse_points << std::endl;
    return all_points;
  }

  for (int mi = 0; mi < input_data.number_of_training_examples; mi++)
  {
    sparse_points.clear();
    std::cout << "Reconstructing: " << input_data.data_filenames[mi]  << "... ";
    for (int p = 0; p < training_data->number_of_sparse_points_per_part.size(); p++)
    {
      std::cout << "Part " << p << "... ";
      SMATRIXf data(1, 3 * (int)training_data->number_of_sparse_points_per_part(p));
      data.fill(FLT_MAX);
      int current_pos_in_data = 0;

      for (int n = 0; n < number_of_sparse_points; n++)
      {
        // point not belonging to this part or not existing
        if (input_data.sparse_part_id[mi][n] != p)
          continue;

        // point belonging to this part - is it empty?
        if (!input_data.sparse_point_data[mi][n].empty())
        {
          data(0, current_pos_in_data++) = input_data.sparse_point_data[mi][n][0];
          data(0, current_pos_in_data++) = input_data.sparse_point_data[mi][n][1];
          data(0, current_pos_in_data++) = input_data.sparse_point_data[mi][n][2];
        }

      } // end of loop over points
      data = removeRows(data, FLT_MAX);
      if ( (data.rows() == 0) || (data.size() == 0) )
      {
        std::cout << "No data for this part. ";
      }
      else
      {
        SMATRIXf R = parts[p]->reconstruct(data);

        for (int n = 0; n < R.cols(); n += 3)
          sparse_points.push_back(SNL::DL13::Point(R(0, n), R(0, n + 1), R(0, n + 2), parts[p]->getPointId(n / 3), p));

        std::cout << "OK. ";
      }

    } // end of loop over parts

    all_points.push_back(sparse_points);
    std::cout << "Done.\n[Input Reconstruction finished at " << t.elapsed() << " seconds]" << std::endl;

    // extract data
    if (training_data != NULL)
      findNearestParts();

    string out_path = "mesh_input_pcarec" + std::to_string(mi);    
    ofstream out(out_path + ".sparse.xyz");
    for (int i = 0; i < (int)sparse_points.size(); i++)
    {
      out << sparse_points[i].p[0] << " " << sparse_points[i].p[1] << " " << sparse_points[i].p[2] << " ";
      if (training_data != NULL)
        out << sparse_points[i].id << " " << sparse_points[i].part_id << " " << nearest_part_filename_per_sparse_point[i] << " ";
      else
        out << sparse_points[i].id << " " << sparse_points[i].part_id << " " << "null" << " ";
      out << sparse_points[i].has_symmetric_part << " " << sparse_points[i].is_self_symmetric << std::endl;
    }
    out.close();


  } // end of loop over given examples
  
  std::cout << "Done." << std::endl;
  return all_points;

}




void PCAModel::findPartCentroids()
{
  std::cout << "=> Finding part centroids" << std::endl;
  part_centroids.clear();
  vector<float> number_of_points_per_part(training_data->number_of_sparse_points_per_part.size(), 0.0f);

  for (int p = 0; p < (int)number_of_points_per_part.size(); p++)
  {
    point c(FLT_MAX, FLT_MAX, FLT_MAX);
    part_centroids.push_back(c);
  }

  for (int i = 0; i < (int)sparse_points.size(); i++)
  {
    int p = sparse_points[i].part_id;
    if (isinv(part_centroids[p][0]))
      part_centroids[p] = point(0.0f, 0.0f, 0.0f);
    number_of_points_per_part[p]++;
    part_centroids[p] += sparse_points[i].p;
  }

  for (int p = 0; p < (int)part_centroids.size(); p++)
  {
    part_centroids[p] /= number_of_points_per_part[p];
  }
}


void PCAModel::findNearestParts()
{
  std::cout << "=> Finding closest parts from database" << std::endl;
  findPartCentroids();
  nearest_part_filename_per_sparse_point.clear();
  nearest_part_filename_per_sparse_point.resize(sparse_points.size(), "");

  vector<float> nearest_dist_to_parts(part_centroids.size(), FLT_MAX);
  vector<int> nearest_dist_to_part_ids(part_centroids.size(), -1);

  for (int m = 0; m < (int)training_data->number_of_training_examples; m++)
  {
    vector<float> dist_to_parts(part_centroids.size(), FLT_MAX);

    for (size_t i = 0; i < sparse_points.size(); i++)
    {
      if (isinv(sparse_points[i].p[0]) || training_data->sparse_point_data[m][i].empty())
        continue;
      int p = sparse_points[i].part_id;
      if (isinv(dist_to_parts[p]))
        dist_to_parts[p] = 0.0f;
      vec local_sparse_point_position = sparse_points[i].p - part_centroids[p];
      vec local_training_data_sparse_point_position(0.0f, 0.0f, 0.0f);
      local_training_data_sparse_point_position[0] = training_data->sparse_point_data[m][i][0] - training_data->part_centroids[m][p][0];
      local_training_data_sparse_point_position[1] = training_data->sparse_point_data[m][i][1] - training_data->part_centroids[m][p][1];
      local_training_data_sparse_point_position[2] = training_data->sparse_point_data[m][i][2] - training_data->part_centroids[m][p][2];
      dist_to_parts[p] += len2(local_training_data_sparse_point_position - local_sparse_point_position);
    }

    for (int p = 0; p < (int)part_centroids.size(); p++)
    {
      if (dist_to_parts[p] < nearest_dist_to_parts[p])
      {
        nearest_dist_to_parts[p] = dist_to_parts[p];
        nearest_dist_to_part_ids[p] = m;
      }
    }
  }

  for (size_t i = 0; i < sparse_points.size(); i++)
    nearest_part_filename_per_sparse_point[i] = training_data->data_filenames[nearest_dist_to_part_ids[sparse_points[i].part_id]];
}


vector< vector< SNL::DL13::Point > > PCAModel::outputTrainingExamples(std::string const & in_path)
{
	TrainingData input_data(in_path, FLT_MAX);
	vector< vector< SNL::DL13::Point > > all_points;

	for (int mi = 0; mi < input_data.number_of_training_examples; mi++)
	{
		sparse_points.clear();
		for (int p = 0; p < input_data.number_of_sparse_points; p++)
		{
			if (!input_data.sparse_point_data[mi][p].empty())
				sparse_points.push_back(SNL::DL13::Point(input_data.sparse_point_data[mi][p][0], 
														 input_data.sparse_point_data[mi][p][1], 
														 input_data.sparse_point_data[mi][p][2], p, input_data.sparse_part_id[mi][p] ) );
		}

		all_points.push_back( sparse_points );
	} // end of loop over given examples
	
	std::cout << "Done." << std::endl;
	return all_points;


}


void PCAModel::load(std::string const & in_path)
{
  std::cout << "Reading " << in_path << " for loading PCA model...";
  ifstream in(in_path.c_str(), ios::in | ios::binary);
  if (!in.good())
  {
    std::cerr << "Failed. Cannot open file for reading." << std::endl;
    return;
  }
  //boost::archive::text_iarchive ia(in);
  boost::archive::binary_iarchive ia(in);
  ia >> *this;
  in.close();
  std::cout << "Done." << std::endl;
}

void PCAModel::save(std::string const & out_path) const
{
  //return;
  std::cout << "Writing " << out_path << " for storing PCA model...";
  ofstream out(out_path.c_str(), ios::out | ios::binary);
  if (!out.good())
  {
    std::cerr << "Failed. Cannot open file for writing." << std::endl;
    return;
  }
  //boost::archive::text_oarchive oa(out);
  boost::archive::binary_oarchive oa(out);
  oa << *this;
  out.close();
  std::cout << "Done." << std::endl;
}



} // end of namespace PCA
} // end of namespace SNL