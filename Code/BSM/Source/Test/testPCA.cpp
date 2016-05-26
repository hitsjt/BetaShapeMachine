#include "TestSNL.hpp"
#include "../Plugins/DL13/DL13_ShapeGenModel.hpp"

#include "../Plugins/PCA/PCA_Model.hpp"
#include "../Plugins/PCA/PCA_TrainingData.hpp"


extern int render(vector< SNL::DL13::Point > _points);

using namespace DL13;
using namespace PCA;

bool
testPCA(int argc, char * argv[])
{
  // Get the path containing the executable
  string bin_path = parent(argv[0]);

  // Try to load the DL13 plugin from the same parent directory as the executable
#ifdef _MSC_VER
#if !defined(NDEBUG) || defined(_DEBUG)
  string plugin_path = bin_path + "\\..\\Debug\\SNLPluginPCAd";
#else
  string plugin_path = bin_path + "\\..\\Release\\SNLPluginPCA";
#endif
#else
#if !defined(NDEBUG) || defined(_DEBUG)
  string plugin_path = getFullPath(bin_path, "libSNLPluginPCAd");
#else
  string plugin_path = getFullPath(bin_path, "libSNLPluginPCA");
#endif
#endif

  cout << "Loading plugin: " << plugin_path << endl;
  SNL::Plugin * PCA_plugin = SNL::PluginManager::load(plugin_path);

  // Start up the plugin
  PCA_plugin->startup();

  //==========================================================================================================================
  // TESTS BEGIN
  //==========================================================================================================================	

  /////////////// GENERAL ///////////////
  vector<Point> points;
#ifdef _MSC_VER
  render(points); // this prevents a crash for some reason 
#endif
  bool debug_dm = true;

  string training_file = "";
  string pca_file = "";
  string training_data_path = "";
  string reconstruction_sample_path = "";
  SNL::Options options;
  ///////////////////////////////////////

  /////////////// SPHERE ///////////////
  //training_file = "";
  //training_data_path = "../../../../Data/Cube_to_Sphere";
  //pca_file = "cube-sphere-pca.bin";
  //reconstruction_sample_path = "../../../../Data/Cube_to_Sphere";
  ///////////////////////////////////////////


  /////////////// CHAIRS ///////////////
  training_file = "";
  training_data_path = "../../../../Data/chair_gt_new/matching_0";
  pca_file = "chair.bin";
  reconstruction_sample_path = "../../../../Data/chair_gt/rec";
  ///////////////////////////////////////////

  // save
  //PCAModel* pm = new PCAModel("", training_file, training_data_path, options);
  //pm->train(pca_file);

  // load
  PCAModel* pm = new PCAModel(pca_file, training_file, training_data_path, options);


#ifdef _MSC_VER
  vector< vector< SNL::DL13::Point > > all_points = pm->reconstructInput(training_data_path, false);
  vector< vector< SNL::DL13::Point > > all_train_points = pm->outputTrainingExamples(training_data_path);

  for (size_t m = 0; m < all_points.size(); m++)
  {
	render(all_train_points[m]);
    render(all_points[m]);
  }

#endif

  // Cleanup and quit
  delete pm;
  PCA_plugin->shutdown();

  return true;
}



