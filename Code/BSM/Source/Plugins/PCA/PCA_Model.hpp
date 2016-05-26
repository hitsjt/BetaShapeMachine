#ifndef __PCA_MODEL_HPP
#define __PCA_MODEL_HPP

#include "PCA_Common.hpp"
#include "PCA_EigenAddons.hpp"
#include "PCA_TrainingData.hpp"
#include "PCA_Part.hpp"
#include "../../Options.hpp"
#include "../DL13/DL13_Point.hpp"

namespace SNL {;
namespace PCA {;

class PCAPart;

class SNL_PCA_API PCAModel
{
private:
  SNL::Options options;
  TrainingData *training_data;
  vector<PCAPart*> parts;
  int number_of_sparse_points;

  vector< SNL::DL13::Point > sparse_points; // do not save
  vector<point>		 part_centroids; // do not save
  vector<string>  nearest_part_filename_per_sparse_point; // do not save

  void findPartCentroids();
  void findNearestParts();


  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & number_of_sparse_points;
    ar & options;
    ar & parts;
  }
public:  
  PCAModel(): training_data(NULL) { };
  PCAModel(const string &load_boltzmann_file_path, const string &load_training_file_path, const string &training_data_path, const SNL::Options &_options);
  ~PCAModel();

  void load(std::string const & in_path);
  void save(std::string const & out_path) const;

  void train(const string &save_model_file_path);
  vector< vector< SNL::DL13::Point > > reconstructInput(std::string const & in_path, bool need_dense_result, int num_iterations = 1, bool smooth_result = false);
  vector< vector< SNL::DL13::Point > > outputTrainingExamples(std::string const & in_path);
};


} // end of namespace PCA
} // end of namespace SNL

#endif
