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


  /////////////// ANIMALS ///////////////	
  //options.set("learning_epochs", 30000);
  //options.set("fitting_threshold", 10.0f);
  //training_file = "C:/Users/V/Desktop/BetaShapeMachine/Data/Animals/animals_training_data.bin";
  //boltzmann_file = "C:/Users/V/Desktop/BetaShapeMachine/Data/Animals/animals.bin";
  //training_data_path = "C:/Users/V/Desktop/BetaShapeMachine/Data/Animals/matching";	
  //training_data_path = "E:/data/deep_shape/Results_3_6/matching";	
  //reconstruction_sample_path = "../../../../ShapePriorSegmentationCorrespondences/Data/Animals/scan_matching";
  ///////////////////////////////////////////

  ////////////// BIKES ///////////////
  //options.set("learning_epochs", 120);
  //options.set("fitting_threshold", 0.001f);
  //options.set("num_random_restarts", 0);
  //training_file = "";
  //boltzmann_file = "C:/Users/V/Desktop/BetaShapeMachine/Data/Bikes/group_1/bikes.bin";
  //training_data_path = "C:/Users/V/Desktop/BetaShapeMachine/Data/Bikes/group_1/matching";


  /////////////// CHAIRS ///////////////
  options.set("learning_epochs", 2000);
  options.set("fitting_threshold", 10.0f);
  //training_file = ""; 
  //boltzmann_file = "../../../../Data/chair_gt_new/chair_gt_new_cur_scaling.bin";
  //training_data_path = "../../../../Data/chair_gt_new/matching_FINAL";
  boltzmann_file = "../../../../Data/chair_large/chair0.bin";
  training_data_path = "../../../../Data/chair_large/matching2";
  ///////////////////////////////////////////

  /////////////// SPHERE ///////////////
  //options.set("learning_epochs", 10000);
  //training_file = "";
  //training_data_path = "../../../../Data/Cube_to_Sphere";
  //boltzmann_file = "cube-sphere.bin";	
  //reconstruction_sample_path = "../../../../Data/Cube_to_Sphere";
  ///////////////////////////////////////////

  /////////////// AIRPLANES ///////////////
  //options.set("learning_epochs", 500);
  ////options.set("fitting_threshold", 0.005f);
  //training_file = "";
  //boltzmann_file = "../../../../Data/airplane_gt_new/BIG/airplane0.bin";
  //training_data_path = "../../../../Data/airplane_gt_new/matching_FINAL"; 
  ///////////////////////////////////////////
  ///////////////////////////////////////////


  /////////////// BIKES ///////////////
  //options.set("fitting_threshold", 0.001f);
  //training_file = "";
  //boltzmann_file = "../../../../Data/bike_large/bike3.bin";
  //training_data_path = "../../../../Data/bike_large/matching_3"; 
  ///////////////////////////////////////////

  /////////////// HELICOPTERS ///////////////
  //options.set("fitting_threshold", 0.001f);
  //training_file = "";
  //boltzmann_file = "../../../../Data/helicopters_large/helicopter3.bin";
  //training_data_path = "../../../../Data/helicopters_large/matching_3";
  ///////////////////////////////////////////


  //boltzmann_file = "../../../../Data/helicopters_large/helicopter3.bin";
  //training_data_path = "../../../../Data/helicopters_large/matching_3";

  //boltzmann_file = "../../../../Data/bike_large/bike_large_final.bin";
  //training_data_path = "../../../../Data/bike_large/matching";

  //boltzmann_file = "../../../../Data/chair_large/chair0.bin";
  //training_data_path = "../../../../Data/chair_large/matching";

  //boltzmann_file = "../../../../Data/airplane_gt_new/airplane_gt_new_final.bin";
  //training_data_path = "../../../../Data/airplane_gt_new/matching_FINAL";

  ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel(boltzmann_file, training_file, training_data_path, options);
  //dm->train(boltzmann_file);

  //ShapeDeepGenerativeModel* dm = new ShapeDeepGenerativeModel(boltzmann_file, training_file, training_data_path, options);
  //dm->retrain();
  //dm->geometry_boltzmann_machine->train();
  //dm->structure_boltzmann_machine->layers.clear();
  //dm->structure_boltzmann_machine->connectivity_is_set = false;
  //dm->structure_boltzmann_machine->options.set( "pretrain", true );
  //dm->structure_boltzmann_machine->options.set( "initial_learning_rate", 1e-3 );	
  //dm->structure_boltzmann_machine->options.set( "num_random_restarts", 1 );	
  //dm->structure_boltzmann_machine->options.set( "learning_epochs", 500 );	
  //dm->structure_boltzmann_machine->setTrainingData( *dm->training_data );
  //dm->retrain(boltzmann_file);
  //dm->trainAttributes();
  ////dm->trainDenseLayer();

#ifdef _MSC_VER
  if (!debug_dm)
  {
    for (int s = 0; s < 30; s++)
      dm->sampleShape(true);
  }
  else
  {
    //for (size_t m = 0; m < 3; m++)
    //{
    //  vector<Point> all_points = dm->showTrainingExample(m, false);
    //  render(all_points);
    //}


    vector< vector<Point> > all_points = dm->reconstructInput(training_data_path, false, 1, true);
    for (size_t m = 0; m < all_points.size(); m++)
    {
      std::cout << m << std::endl;
      render(all_points[m]);
    }

    //vector< vector<float> > values = dm->outputHiddenNodeValues(training_data_path, 3);
    //ofstream names_file("names.txt");
    //ofstream descriptor_file("descriptor.txt");
    //for (size_t m = 0; m < values.size(); m++)
    //{
    //  for (size_t d = 0; d < values[m].size(); d++)
    //  {
    //    descriptor_file << values[m][d] << " ";
    //  }
    //  descriptor_file << std::endl;
    //  names_file << dm->training_data->data_filenames[m] << std::endl;
    //}
    //descriptor_file.close();
    //names_file.close();

    //int point_sample_id = 1;
    //while (true)
    //{
    //  ifstream existing_mesh_sample("point_sample_" + std::to_string(point_sample_id) + ".sparse.asc");
    //  if (!existing_mesh_sample.good())
    //    break;
    //  point_sample_id++;
    //}
    //dm->point_sample_id = point_sample_id;

    //for (int s = 0; s < 500; s++)
    //{
    //  vector<Point> points = dm->sampleShape(false);
    //  //std::cout << dm->sample_unnormalized_probability << std::endl;
    //  if (dm->sample_unnormalized_probability == 0.0f)
    //  {
    //    dm->point_sample_id--;
    //    continue;
    //  }
    //  //render(points);
    //  //if (!accept_result)
    //  //{
    //  //  std::cout << "rejected" << std::endl;
    //  //  dm->point_sample_id--;
    //  //}
    //}

    //vector< vector<Point> > all_points = dm->reconstructInput(reconstruction_sample_path, false, 1, true);

    //vector<float> probs;
    //vector< vector<Point> > all_points = dm->reconstructFromPartialInput(reconstruction_sample_path, false, probs, true);
    //
    //for (size_t m = 0; m < all_points.size(); m++)
    //{
    //  std::cout << probs[m] << std::endl;
    //  render(all_points[m]);
    //}


    //for (size_t m = 0; m < dm->training_data->number_of_training_examples; m++)		
    //{
    //	std::cout <<  dm->training_data->data_filenames[m] << std::endl;
    //	//std::cout << m << " training example" << std::endl;
    //	//render( dm->showTrainingExample(m, false) );
    //	//std::cout << "reconstructTrainingExample" << std::endl;
    //	//render( dm->reconstructTrainingExample(m, false) );			
    //	std::cout << "reconstructInput" << std::endl;
    //	render( all_points[m] );			
    //}



    ///// SPHERE
    //for (int a = 0; a < 10; a++)
    //{
    //	vector<float> attribs(2);
    //	attribs[0] = float(a) / 10.0f;
    //	attribs[1] = (1.0f - attribs[0])*(1.0f - attribs[0]);
    //	render( dm->attribShape( attribs, false ) );
    //}		

    ///// ANIMALS
    //for (int a = 0; a < 8; a++)
    //{
    //	SVECTORf attribs(10);
    //	attribs.fill(.5f);
    //	attribs(0) = float(a) / 10.0f;
    //	attribs(1) = .5f - attribs(0)/2;
    //	render( dm->attribShape( convertEigenVectorToStdVector(attribs), false ) );
    //}			
  }
#endif

  // Cleanup and quit
  DL13_plugin->shutdown();

  return true;
}





//TrainingData* training_data = new TrainingData();
//ofstream tmp("4.txt");
//training_data->load("chairs_T4_training_data.bin");
//for (int i = 0; i < training_data->spatial_neighbors_ids.size(); i++)
//{
//	for (int j = 0; j < training_data->spatial_neighbors_ids[i].size(); j++)
//	{
//		tmp << training_data->spatial_neighbors_ids[i][j] << " " <<  training_data->spatial_neighbors_weights[i][j] << "  ";
//	}
//	tmp << std::endl;
//}
//tmp.close();
//return true;

//TrainingData* training_data = new TrainingData();
//ofstream tmp("4sparsetodense.txt");
//training_data->load("chairs_T4_training_data.bin");
//for (int i = 0; i < training_data->nearest_sparse_points_for_each_dense_point.size(); i++)
//{
//	for (int j = 0; j < training_data->nearest_sparse_points_for_each_dense_point[i].size(); j++)
//	{
//		tmp << training_data->nearest_sparse_points_for_each_dense_point[i][j] << "  ";
//	}
//	tmp << std::endl;
//}
//tmp.close();
//return true;


//TrainingData training_data("../../../Data/Cube_to_Sphere", 1000.0f, 98, 98, 2, false); 
//for (size_t m = 0; m < training_data.number_of_training_examples; m++)
//{
//	vector<point> points;
//	for (int i = 0; i < training_data.sparse_point_data[m].size(); i++)
//	{
//		points.push_back( point( training_data.sparse_point_data[m][i][0], training_data.sparse_point_data[m][i][1], training_data.sparse_point_data[m][i][2]  ) );
//	}
//	render(points);
//}


//ofstream tmp("tmp.txt");
//for (size_t m = 0; m < training_data->number_of_training_examples; m++)
//{
//	if ( !training_data->sparse_point_data[m][100].empty() )
//		tmp << training_data->attribute_data[m][100] << " " << training_data->sparse_point_data[m][100][0] << std::endl;
//}
//tmp.close();


//bm->load("chairs_T4.bin");
//TrainingData* training_data = new TrainingData();
//training_data->load("chairs_T4_training_data.bin");
//bm->setTrainingData( *training_data );
//bm->options.set("dense_mapping_type", "backpropagation");	
//bm->options.set("attribute_mapping_type", "backpropagation");	
//bm->trainDenseDataLayer();
//bm->trainAttributeLayer();

//for (int n = 0; n < 50; n++)
//{
//	training_data.sparse_point_data[0][n].clear();
//	training_data.dense_point_data[0][n].clear();
//	training_data.sparse_point_data[5][n].clear();
//	training_data.dense_point_data[5][n].clear();
//	//training_data.attribute_data[0].clear();
//	//training_data.attribute_data[5].clear();
//}
//training_data.populateSpatialNeighbors();
//training_data.findDenseToSparseAssociations(100);


//ofstream tmp("tmp.txt");
//for (size_t m = 0; m < training_data.number_of_training_examples; m++)
//{
//	for (size_t n = 0; n < training_data.number_of_sparse_points; n++)
//	{
//		tmp << !training_data.sparse_point_data[m][n].empty() << " ";
//	}
//	tmp << std::endl;
//}
//tmp.close();

/*LogisticRegression tr;
tr.test();
return true;*/


//BoltzmannMachine *bm = (BoltzmannMachine*)nw;
//bm->load("bm-chairs-pretrain-1.bin");

//ofstream tmp("tmp.txt");
//for (size_t m = 0; m < bm->layers[0]->nodes[0]->V.size(); m++)
//{
//	for (size_t n = 0; n < bm->layers[0]->nodes.size(); n++)
//	{		
//		tmp <<  bm->layers[0]->nodes[n]->V(m) << " ";
//	}
//	tmp <<  std::endl;
//}
//system("pause");

//bm->options.set("greedy_initialization", true);
//bm->train();


//ShapeDeepGenerativeModel* ddm = new ShapeDeepGenerativeModel( "C:/Users/V/Desktop/animals_BINARY-BETA.bin", "animals_training_data.bin" );
////for (int s = 0; s < 10; s++)
////	render( ddm->sampleShape(false) );
//render( ddm->reconstructTrainingExample(0, false) );

//return true;