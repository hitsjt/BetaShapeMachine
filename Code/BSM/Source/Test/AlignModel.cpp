#include "TestSNL.hpp"
#include "../Plugins/DL13/DL13_BoltzmannMachine.hpp"
#include "../Plugins/DL13/DL13_Plugin.hpp"
#include "../Plugins/DL13/DL13_Common.hpp"
#include "../Plugins/DL13/DL13_TrainingData.hpp"
#include "../Plugins/DL13/DL13_MeshConstructor.hpp"
#include "../Plugins/DL13/DL13_EigenAddons.hpp"
#include "../Plugins/DL13/DL13_Logistic_Regression.hpp"
#include "../Plugins/DL13/DL13_ShapeGenModel.hpp"

using namespace DL13;

bool
alignModel(int argc, char * argv[])
{
  // Get the path containing the executable
  string bin_path = parent(argv[0]);

  // Try to load the DL13 plugin from the same parent directory as the executable
#ifdef _MSC_VER
#if !defined(NDEBUG) || defined(_DEBUG)
  string plugin_path = bin_path + "\\..\\Debug\\SNLPluginDL13d";
#else
  string plugin_path = bin_path + "\\..\\Release\\SNLPluginDL13";
#endif
#else
#if !defined(NDEBUG) || defined(_DEBUG)
  string plugin_path = getFullPath(bin_path, "libSNLPluginDL13d");
#else
  string plugin_path = getFullPath(bin_path, "libSNLPluginDL13");
#endif
#endif

  cout << "Loading plugin: " << plugin_path << endl;
  SNL::Plugin * DL13_plugin = SNL::PluginManager::load(plugin_path);

  // Start up the plugin
  DL13_plugin->startup();

  //==========================================================================================================================
  // TESTS BEGIN
  //==========================================================================================================================	

  /////////////// GENERAL ///////////////
  // run: -align-dl13 ../../../../Data/chair_gt_new/chair0.bin ../../../../Data/chair_gt_new/wrong_alignment
  vector<Point> points;
  bool debug_dm = true;

  string boltzmann_file = string( argv[2] );
  string align_model_data_path = string( argv[3] );

  ///////////////////////////////////////////
  ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel(boltzmann_file, "", align_model_data_path);
  std::cout << dm->getLogProbabilityForAlignment(align_model_data_path).at(0);

  // Cleanup and quit
  DL13_plugin->shutdown();

  return true;
}