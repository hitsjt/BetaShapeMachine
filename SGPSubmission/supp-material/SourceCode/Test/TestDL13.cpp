//============================================================================
//
// This file is part of the Beta Shape Machine (BSM) project.
//
// Copyright (c) 2014-15 - Evangelos Kalogerakis (author of the code) / UMass-Amherst
//
// BSM is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// BSM is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with BSM.  If not, see <http://www.gnu.org/licenses/>.
//
//============================================================================

#include "TestSNL.hpp"
#include "../Plugins/DL13/DL13_BoltzmannMachine.hpp"
#include "../Plugins/DL13/DL13_Plugin.hpp"
#include "../Plugins/DL13/DL13_Common.hpp"
#include "../Plugins/DL13/DL13_TrainingData.hpp"
#include "../Plugins/DL13/DL13_MeshConstructor.hpp"
#include "../Plugins/DL13/DL13_EigenAddons.hpp"
#include "../Plugins/DL13/DL13_Logistic_Regression.hpp"
#include "../Plugins/DL13/DL13_ShapeGenModel.hpp"

extern int render(vector< SNL::DL13::Point > _points);
extern bool accept_result;

using namespace DL13;

bool
testDL13(int argc, char * argv[])
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
  vector<Point> points;
#ifdef _MSC_VER
  render(points); // this prevents a crash for some reason 
#endif
  bool debug_dm = true;

  string training_file = "";
  string boltzmann_file = "";
  string training_data_path = "";
  string reconstruction_sample_path = "";
  SNL::Options options;
  ///////////////////////////////////////

  /////////////// CHAIRS ///////////////
  training_file = ""; 
  boltzmann_file = "../../../../Data/chair_large/chair_large.bin";
  training_data_path = "../../../../Data/chair_large/matching_FINAL";
  ///////////////////////////////////////////
  

  ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel( "", training_file, training_data_path, options );
  dm->train(boltzmann_file);

  //ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel(boltzmann_file, training_file, training_data_path, options);
  //dm->retrain();
  //dm->geometry_boltzmann_machine->train();
  //dm->structure_boltzmann_machine->layers.clear();
  //dm->structure_boltzmann_machine->connectivity_is_set = false;
  //dm->structure_boltzmann_machine->options.set( "pretrain", true );
  //dm->structure_boltzmann_machine->options.set( "initial_learning_rate", 1e-3 );	
  //dm->structure_boltzmann_machine->options.set( "num_random_restarts", 1 );	
  //dm->structure_boltzmann_machine->options.set( "learning_epochs", 10000 );	
  //dm->structure_boltzmann_machine->setTrainingData( *dm->training_data );
  //dm->retrain(boltzmann_file);
  //dm->trainAttributes();
  ////dm->trainDenseLayer();

    for (int s = 0; s < 250; s++)
      dm->sampleShape(true);	

  // Cleanup and quit
  DL13_plugin->shutdown();

  return true;
}