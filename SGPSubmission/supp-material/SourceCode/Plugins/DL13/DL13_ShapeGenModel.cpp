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


#include "DL13_ShapeGenModel.hpp"

namespace SNL {;
namespace DL13 {;

ShapeDeepGenerativeModel::ShapeDeepGenerativeModel(const string &load_boltzmann_file_path, const string &load_training_file_path,  const string &training_data_path, const SNL::Options &_options )
{
	Eigen::initParallel();
	Eigen::setNbThreads(1);
	int tid = 0;
#ifndef _DEBUG
#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		if (tid == 0)
			std::cout << "Will use " << omp_get_num_threads() << " threads across " << omp_get_num_procs() << " available processors." << std::endl;
	}
#endif

	std::cout << "+++ BSM v1.2 +++" << std::endl;


	sample_unnormalized_probability = 0.0f;
	point_sample_id = 1;
	point_attrib_id = 1;
	geometry_learning_options.merge(_options);
	structure_learning_options.merge(_options);
	geometry_learning_options.set("visible_layer_type", "DoubleBeta"); 
	geometry_learning_options.set("hidden_layer_type", "Binary");
	structure_learning_options.set("visible_layer_type", "Binary");
	structure_learning_options.set("hidden_layer_type", "Binary");			
	structure_learning_options.set("learning_epochs", _options.get("learning_epochs", 50000) / 4 );
	structure_learning_options.set("dense_mapping_type", "none");
	structure_learning_options.set("do_not_reconstruct_input_structure", true);
	geometry_boltzmann_machine = new BoltzmannMachine("geometry_boltzmann_machine", geometry_learning_options);
	structure_boltzmann_machine = new BoltzmannMachine("structure_boltzmann_machine", structure_learning_options);

	mesh_constructor = new MeshConstructor(this);
	training_data = NULL;

	if ( load_boltzmann_file_path != "" )
	{
		geometry_boltzmann_machine->load( load_boltzmann_file_path );
		structure_boltzmann_machine->load( load_boltzmann_file_path.substr(0, load_boltzmann_file_path.size()-4) + "_structure.bin");
		geometry_boltzmann_machine->options.merge(_options);
		structure_boltzmann_machine->options.merge(_options);
	}

	if ( load_training_file_path != "" )
	{
		training_data = new TrainingData();
		if ( !training_data->load(load_training_file_path) )
		{
			delete training_data;
			training_data = NULL;
		}
	}

	if ( (training_data == NULL) && (training_data_path != "") )
	{
		training_data = new TrainingData(training_data_path, _options.get("fitting_threshold", 100.0f) );
		training_data->findPartCentroids();
		training_data->populateSpatialNeighbors();
		training_data->findPartReflectiveSymmetries();
		training_data->findDenseToSparseAssociations(100);			
		if ( load_training_file_path != "" )
			training_data->save(load_training_file_path);		
	}

	if ( training_data != NULL )
	{
		geometry_boltzmann_machine->setTrainingData(*training_data);
		structure_boltzmann_machine->setTrainingData(*training_data);
	}

}

void ShapeDeepGenerativeModel::train(const string &save_boltzmann_file_path, const SNL::Options &_options )
{
	geometry_boltzmann_machine->options.merge(_options);
	structure_boltzmann_machine->options.merge(_options);
	geometry_learning_options.merge(_options);
	structure_learning_options.merge(_options);

	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	std::cout << "***** Training GEOMETRY Boltzmann Machine *****" << std::endl;
  geometry_boltzmann_machine->train();
	std::cout << "*****Training STRUCTURE Boltzmann Machine *****" << std::endl;
  structure_boltzmann_machine->train();
	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start;
	std::cout << "***** Finished training at " << elapsed_seconds.count() << " seconds *****" << std::endl;

	if ( save_boltzmann_file_path != "" )
	{
		geometry_boltzmann_machine->save( save_boltzmann_file_path );
		structure_boltzmann_machine->save( save_boltzmann_file_path.substr(0, save_boltzmann_file_path.size()-4) + "_structure.bin");
	}
}

void ShapeDeepGenerativeModel::retrain(const string &save_boltzmann_file_path, const SNL::Options &_options )
{
	geometry_boltzmann_machine->options.merge(_options);
	geometry_learning_options.merge(_options);
	geometry_boltzmann_machine->options.set( "greedy_initialization", true );
	geometry_boltzmann_machine->options.set( "pretrain", true );
	geometry_boltzmann_machine->setupPretraining(*training_data);
	geometry_boltzmann_machine->momentum = 0.0f;
	geometry_boltzmann_machine->learning_rate = structure_boltzmann_machine->options.get( "initial_learning_rate", 1e-3f );

	structure_boltzmann_machine->options.merge(_options);
	structure_learning_options.merge(_options);
	structure_boltzmann_machine->options.set( "greedy_initialization", true );
	structure_boltzmann_machine->options.set( "pretrain", true );
	structure_boltzmann_machine->setupPretraining(*training_data);
	structure_boltzmann_machine->momentum = 0.0f;
	structure_boltzmann_machine->learning_rate = structure_boltzmann_machine->options.get( "initial_learning_rate", 1e-3f );


	boost::timer t;
	std::cout << "***** Training GEOMETRY Boltzmann Machine *****" << std::endl;
	geometry_boltzmann_machine->train();
	std::cout << "*****Training STRUCTURE Boltzmann Machine *****" << std::endl;
	structure_boltzmann_machine->train();
	std::cout << "***** Finished training at " << t.elapsed() << " seconds *****" << std::endl;

	if ( save_boltzmann_file_path != "" )
	{
		geometry_boltzmann_machine->save( save_boltzmann_file_path );
		structure_boltzmann_machine->save( save_boltzmann_file_path.substr(0, save_boltzmann_file_path.size()-4) + "_structure.bin");
	}
}

void ShapeDeepGenerativeModel::trainAttributes(const string &save_boltzmann_file_path, const SNL::Options &_options )
{
	geometry_boltzmann_machine->options.merge(_options);
	structure_boltzmann_machine->options.merge(_options);
	geometry_learning_options.merge(_options);
	structure_learning_options.merge(_options);

	boost::timer t;
	geometry_boltzmann_machine->trainAttributeLayer();
	structure_boltzmann_machine->trainAttributeLayer();	
	std::cout << "[Finished attribute inference at " << t.elapsed() << " seconds]" << std::endl;

	if ( save_boltzmann_file_path != "" )
	{
		geometry_boltzmann_machine->save( save_boltzmann_file_path );
		structure_boltzmann_machine->save( save_boltzmann_file_path.substr(0, save_boltzmann_file_path.size()-4) + "_structure.bin");
	}
}

void ShapeDeepGenerativeModel::trainDenseLayer(const string &save_boltzmann_file_path, const SNL::Options &_options )
{
	geometry_learning_options.merge(_options);
	geometry_boltzmann_machine->options.merge(_options);

	boost::timer t;
	geometry_boltzmann_machine->trainDenseDataLayer();
	std::cout << "[Finished dense layer inference at " << t.elapsed() << " seconds]" << std::endl;

	if ( save_boltzmann_file_path != "" )
		geometry_boltzmann_machine->save( save_boltzmann_file_path );
}


vector<Point> ShapeDeepGenerativeModel::sampleShape(bool need_dense_result)
{
	boost::timer t;
	structure_boltzmann_machine->clearAllObservations();
	geometry_boltzmann_machine->clearAllObservations();	
	structure_boltzmann_machine->sample();
	geometry_boltzmann_machine->sample();
	nullifyMissingPoints();
  getUnnormalizedLogProbability();
	std::cout << "[Sampling finished at " << t.elapsed() << " seconds]" << std::endl;

	if ( !need_dense_result )
	{		
		createSparsePointCloud();
		//if ( mesh_constructor->findNumberOfConnectedComponentsInTheSparsePointCloud() > 1 )
		//	sample_unnormalized_probability = 0.0f;
		//if ( !mesh_constructor->checkIfPartsAgreeWithSymmetricBits() )
		//	sample_unnormalized_probability = 0.0f;
		mesh_constructor->createMesh( "point_sample_" + std::to_string( point_sample_id ) );		
    point_sample_id++;
		return removeInvalidSparsePoints();
	}
	else
	{		
		createDensePointCloud();
		mesh_constructor->createMesh( "point_dsample_" + std::to_string( point_sample_id ) );		
    point_sample_id++;
		return removeInvalidDensePoints();
	}
}

vector<Point> ShapeDeepGenerativeModel::reconstructTrainingExample(int m, bool need_dense_result)
{
	boost::timer t;	
	structure_boltzmann_machine->clearAllObservations();
	geometry_boltzmann_machine->clearAllObservations();
	structure_boltzmann_machine->reconstructTrainingExample(m);	
	geometry_boltzmann_machine->reconstructTrainingExample(m);	
	nullifyMissingPoints();
  getUnnormalizedLogProbability();
	std::cout << "[Reconstruction finished at " << t.elapsed() << " seconds]" << std::endl;

	if ( !need_dense_result )
	{
		createSparsePointCloud();
		mesh_constructor->createMesh( "point_rec_" + std::to_string( m ) );		
		return removeInvalidSparsePoints();
	}
	else
	{
		createDensePointCloud();
		mesh_constructor->createMesh( "point_drec_" + std::to_string( m ) );		
		return removeInvalidDensePoints();
	}
}

vector<Point> ShapeDeepGenerativeModel::showTrainingExample(int m, bool need_dense_result)
{
	structure_boltzmann_machine->clearAllObservations();
	geometry_boltzmann_machine->clearAllObservations();	
	structure_boltzmann_machine->layers[0]->setObservationsFromTrainingExamples();
	geometry_boltzmann_machine->layers[0]->setObservationsFromTrainingExamples();	
	for (size_t n = 0; n < geometry_boltzmann_machine->layers[0]->nodes.size(); n++)
	{
		structure_boltzmann_machine->layers[0]->nodes[n]->q_mean(0) = structure_boltzmann_machine->layers[0]->nodes[n]->q_mean(m);
		geometry_boltzmann_machine->layers[0]->nodes[n]->q_mean(0) = geometry_boltzmann_machine->layers[0]->nodes[n]->q_mean(m);		
	}
	structure_boltzmann_machine->layers[0]->unscale();
	geometry_boltzmann_machine->layers[0]->unscale();
  getUnnormalizedLogProbability();

	if ( !need_dense_result )
	{
		createSparsePointCloud();
		mesh_constructor->createMesh( "point_tr_" + std::to_string( m ) );
		return removeInvalidSparsePoints();
	}
	else
	{
		createDensePointCloud();
		mesh_constructor->createMesh( "point_dtr_" + std::to_string( m ) );		
		return removeInvalidDensePoints();
	}
}

vector< vector<Point> > ShapeDeepGenerativeModel::reconstructInput(std::string const & in_path, bool need_dense_result, int num_iterations, bool smooth_result)
{
	vector<float> probs;
	return reconstructInput(in_path, need_dense_result, num_iterations, probs, smooth_result, true);
}

vector< vector<Point> > ShapeDeepGenerativeModel::reconstructFromPartialInput(std::string const & in_path, bool need_dense_result, vector<float>& probs, bool smooth_result)
{
	structure_learning_options.set("do_not_reconstruct_input_structure", false);
  vector< vector<Point> > pts = reconstructInput(in_path, need_dense_result, 1, probs, smooth_result, false);
	structure_learning_options.set("do_not_reconstruct_input_structure", true);
	return pts;
}

vector< vector<Point> > ShapeDeepGenerativeModel::reconstructInput(std::string const & in_path, bool need_dense_result, int num_iterations, vector<float>& probs, bool smooth_result, bool skip_prob)
{
	boost::timer t;	
	TrainingData input_data(in_path, FLT_MAX);
  vector< vector<Point> > all_points;

  if (input_data.number_of_sparse_points != geometry_boltzmann_machine->getNumberOfVisibleUnits()/3)
  {
    std::cerr << "Input shapes have inconsistent number of points with the loaded Boltzmann machine" << std::endl;
    std::cerr << input_data.number_of_sparse_points << std::endl; 
    std::cerr << geometry_boltzmann_machine->getNumberOfVisibleUnits()/3 << std::endl;
    return all_points;
  }

	for (int mi = 0; mi < input_data.number_of_training_examples; mi++)
	{
		std::cout << "Reconstructing: " << input_data.data_filenames[mi] << std::endl;

		// 1st pass: set all observations
		structure_boltzmann_machine->clearAllObservations();	
		geometry_boltzmann_machine->clearAllObservations();		
		for (int n = 0; n < input_data.number_of_sparse_points; n++)
		{
			if ( !input_data.sparse_point_data[mi][n].empty() )
			{
				geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->layers[0]->nodes[3 * n], input_data.sparse_point_data[mi][n][0] );
				geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->layers[0]->nodes[3 * n + 1], input_data.sparse_point_data[mi][n][1] );
				geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->layers[0]->nodes[3 * n + 2], input_data.sparse_point_data[mi][n][2] );

				if ( geometry_boltzmann_machine->layers[0]->nodes[3 * n]->trimmed || // possible outlier
					geometry_boltzmann_machine->layers[0]->nodes[3 * n + 1]->trimmed ||
					geometry_boltzmann_machine->layers[0]->nodes[3 * n + 2]->trimmed )
				{
					geometry_boltzmann_machine->clearObservation( geometry_boltzmann_machine->layers[0]->nodes[3 * n] );
					geometry_boltzmann_machine->clearObservation( geometry_boltzmann_machine->layers[0]->nodes[3 * n + 1] );
					geometry_boltzmann_machine->clearObservation( geometry_boltzmann_machine->layers[0]->nodes[3 * n + 2] );
					continue;
				}

				structure_boltzmann_machine->setObservation( structure_boltzmann_machine->layers[0]->nodes[3 * n], 1.0f );
				//////////structure_boltzmann_machine->setObservation( structure_boltzmann_machine->layers[0]->nodes[3 * n + 1], 1.0f ); // symmetries are unobserved
				//////////structure_boltzmann_machine->setObservation( structure_boltzmann_machine->layers[0]->nodes[3 * n + 2], 1.0f );
			}
			else
			{
				if ( structure_learning_options.get("do_not_reconstruct_input_structure", false) )
					structure_boltzmann_machine->setObservation( structure_boltzmann_machine->layers[0]->nodes[3 * n], 0.0f );
			}
		}
		//structure_boltzmann_machine->setMFiterations(num_iterations);
		//geometry_boltzmann_machine->setMFiterations(num_iterations);
		structure_boltzmann_machine->doInference();
		geometry_boltzmann_machine->doInference(); 

		//// 2nd pass: can correct observations
		for (int n = 0; n < input_data.number_of_sparse_points; n++)
		{
			geometry_boltzmann_machine->layers[0]->nodes[3 * n]->is_observed = false;
			geometry_boltzmann_machine->layers[0]->nodes[3 * n + 1]->is_observed = false;
			geometry_boltzmann_machine->layers[0]->nodes[3 * n + 2]->is_observed = false;
			if ( !structure_learning_options.get("do_not_reconstruct_input_structure", false) )
			{
				structure_boltzmann_machine->layers[0]->nodes[3 * n]->is_observed = false;
				structure_boltzmann_machine->layers[0]->nodes[3 * n + 1]->is_observed = false;
				structure_boltzmann_machine->layers[0]->nodes[3 * n + 2]->is_observed = false;
			} 
		}
		if ( !structure_learning_options.get("do_not_reconstruct_input_structure", false) )
			structure_boltzmann_machine->doInferenceWithoutInit(0);
		geometry_boltzmann_machine->doInferenceWithoutInit(0);
		nullifyMissingPoints();

		std::cout << "[Input Reconstruction finished at " << t.elapsed() << " seconds]" << std::endl;

		if ( !need_dense_result )
		{
			createSparsePointCloud();			
			if (smooth_result)
        if (!structure_learning_options.get("do_not_reconstruct_input_structure", false)) // rec
				  reInitializeSparsePoints(mesh_constructor->smoothSparsePoints(3));
        else
          reInitializeSparsePoints(mesh_constructor->smoothSparsePoints(1));
			all_points.push_back(removeInvalidSparsePoints());
			mesh_constructor->createMesh( "point_input_rec" + std::to_string( mi )  );		
		}
		else
		{
			createDensePointCloud();
			all_points.push_back( removeInvalidDensePoints() );
			mesh_constructor->createMesh( "point_input_drec" + std::to_string( mi )  );		
		}		

    if (skip_prob)
      continue;

    // estimate probability (roughly in the presense of missing data)
    structure_boltzmann_machine->clearAllObservations();
    geometry_boltzmann_machine->clearAllObservations(); 
    for (int n = 0; n < input_data.number_of_sparse_points; n++)
    {
      if (!input_data.sparse_point_data[mi][n].empty())
      {
        geometry_boltzmann_machine->setObservation(geometry_boltzmann_machine->layers[0]->nodes[3 * n], input_data.sparse_point_data[mi][n][0]);
        geometry_boltzmann_machine->setObservation(geometry_boltzmann_machine->layers[0]->nodes[3 * n + 1], input_data.sparse_point_data[mi][n][1]);
        geometry_boltzmann_machine->setObservation(geometry_boltzmann_machine->layers[0]->nodes[3 * n + 2], input_data.sparse_point_data[mi][n][2]);
        structure_boltzmann_machine->setObservation(structure_boltzmann_machine->layers[0]->nodes[3 * n], 1.0f);
      }
      else
      {
        if (structure_learning_options.get("do_not_reconstruct_input_structure", false))
          structure_boltzmann_machine->setObservation(structure_boltzmann_machine->layers[0]->nodes[3 * n], 0.0f);
      }
    }
    //structure_boltzmann_machine->setMFiterations(num_iterations);
    //geometry_boltzmann_machine->setMFiterations(num_iterations);
    structure_boltzmann_machine->doInference();
    geometry_boltzmann_machine->doInference();
    if (num_iterations == 1) // make sure that all nodes have values
    {
      geometry_boltzmann_machine->doInferenceWithoutInit(0);
      structure_boltzmann_machine->doInferenceWithoutInit(0);
    }
    nullifyMissingPoints();
    getUnnormalizedLogProbability(true);
    probs.push_back(sample_unnormalized_probability);

	} // end of loop over input data shapes


  std::cout << "Done." << std::endl;
	return all_points;
}

vector< float > ShapeDeepGenerativeModel::getLogProbabilityForAlignment(std::string const & in_path)
 {
   boost::timer t;
   TrainingData input_data(in_path, FLT_MAX);
   vector< float > probs;

   if (input_data.number_of_sparse_points != geometry_boltzmann_machine->getNumberOfVisibleUnits() / 3)
   {
     std::cerr << "Input shapes have inconsistent number of points with the loaded Boltzmann machine" << std::endl;
     std::cerr << input_data.number_of_sparse_points << std::endl;
     std::cerr << geometry_boltzmann_machine->getNumberOfVisibleUnits() / 3 << std::endl;
     return probs;
   }

   for (int mi = 0; mi < input_data.number_of_training_examples; mi++)
   {
     std::cout << "Getting prob for: " << input_data.data_filenames[mi] << std::endl;

     for (int n = 0; n < input_data.number_of_sparse_points; n++)
     {
       if (!input_data.sparse_point_data[mi][n].empty())
       {          
          geometry_boltzmann_machine->setObservation(geometry_boltzmann_machine->layers[0]->nodes[3 * n], input_data.sparse_point_data[mi][n][0]);
          geometry_boltzmann_machine->setObservation(geometry_boltzmann_machine->layers[0]->nodes[3 * n + 1], input_data.sparse_point_data[mi][n][1]);
          geometry_boltzmann_machine->setObservation(geometry_boltzmann_machine->layers[0]->nodes[3 * n + 2], input_data.sparse_point_data[mi][n][2]);
          structure_boltzmann_machine->setObservation(structure_boltzmann_machine->layers[0]->nodes[3 * n], 1.0f);
       }
       else
       {
        structure_boltzmann_machine->setObservation(structure_boltzmann_machine->layers[0]->nodes[3 * n], 0.0f);
       }
     }
     geometry_boltzmann_machine->doInference();
     structure_boltzmann_machine->doInference();
     nullifyMissingPoints();
     float prob = getUnnormalizedLogProbability(true);
     probs.push_back(prob);
   } // end of loop over input data shapes


   std::cout << "Done." << std::endl;
   return probs;
 }

vector<Point> ShapeDeepGenerativeModel::attribShape(const vector<float>& attrib_values, bool need_dense_result)
{
	boost::timer t;
	structure_boltzmann_machine->clearAllObservations();	
	structure_boltzmann_machine->setAttributeLayerObservations( attrib_values );
	structure_boltzmann_machine->doAttribInference();
	geometry_boltzmann_machine->clearAllObservations();
	geometry_boltzmann_machine->setAttributeLayerObservations( attrib_values );
	geometry_boltzmann_machine->doAttribInference();
	nullifyMissingPoints();
  getUnnormalizedLogProbability();
	std::cout << "[Attribute Inference finished at " << t.elapsed() << " seconds]" << std::endl;

	if ( !need_dense_result )
	{
		createSparsePointCloud();
		mesh_constructor->createMesh( "point_attrib_" + std::to_string( point_attrib_id ) );		
    point_attrib_id++;
		return removeInvalidSparsePoints();
	}
	else
	{		
		createDensePointCloud();
		mesh_constructor->createMesh( "point_dattrib_" + std::to_string( point_attrib_id ) );		
    point_attrib_id++;
		return removeInvalidDensePoints();
	}
}


void ShapeDeepGenerativeModel::nullifyMissingPoints()
{
	for (int i = 0; i < geometry_boltzmann_machine->getNumberOfVisibleUnits(); i+=3)
	{
		if ( structure_boltzmann_machine->getOutputVisibleNodeValue(i) == 0.0f )
		{
			geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->getVisibleNode(i), FLT_MAX );
			geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->getVisibleNode(i+1), FLT_MAX );
			geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->getVisibleNode(i+2), FLT_MAX );
		}
	}
}

float ShapeDeepGenerativeModel::getUnnormalizedLogProbability(bool check_out_of_range_values)
{
  sample_unnormalized_probability = -geometry_boltzmann_machine->measureEnergy(check_out_of_range_values)(0)
                                    -structure_boltzmann_machine->measureEnergy(check_out_of_range_values).array()(0);

  float num_active_units_in_geometry_boltzmann_machine = (float)geometry_boltzmann_machine->getNumberOfUnits();
  float num_active_units_in_structure_boltzmann_machine = (float)structure_boltzmann_machine->getNumberOfUnits();

  for (int i = 0; i < structure_boltzmann_machine->getNumberOfVisibleUnits(); i += 3)
  {
  	if ( structure_boltzmann_machine->getOutputVisibleNodeValue(i) == 0.0f )
  		num_active_units_in_geometry_boltzmann_machine -= 3.0f;
  }

  sample_unnormalized_probability = sample_unnormalized_probability / num_active_units_in_geometry_boltzmann_machine;

  return sample_unnormalized_probability;
}

void ShapeDeepGenerativeModel::createSparsePointCloud()
{
	sparse_points.clear();
	sparse_points.reserve( geometry_boltzmann_machine->getNumberOfVisibleUnits() / 3 );

	for (int i = 0; i < geometry_boltzmann_machine->getNumberOfVisibleUnits(); i+=3)
	{
		if ( structure_boltzmann_machine->getOutputVisibleNodeValue(i) == 0.0f )
		{
      sparse_points.push_back(Point(FLT_MAX, FLT_MAX, FLT_MAX, -1, -1));
			continue;
		}

    sparse_points.push_back(Point(geometry_boltzmann_machine->getOutputVisibleNodeValue(i),
			geometry_boltzmann_machine->getOutputVisibleNodeValue(i+1),  
			geometry_boltzmann_machine->getOutputVisibleNodeValue(i+2),
			i/3,
			geometry_boltzmann_machine->getOutputVisibleNodePartID(i), 
			structure_boltzmann_machine->getOutputVisibleNodeValue(i+1),
			structure_boltzmann_machine->getOutputVisibleNodeValue(i+2)
			) );
	}
}


void ShapeDeepGenerativeModel::createDensePointCloud()
{
	dense_points.clear();
	dense_points.reserve( training_data->number_of_dense_points );

	createSparsePointCloud();
	if ( geometry_boltzmann_machine->dlayer != NULL )
		geometry_boltzmann_machine->doDenseInference();

	for (int i = 0; i < geometry_boltzmann_machine->getNumberOfDenseVisibleUnits(); i+=3)
	{
		if ( isinv( geometry_boltzmann_machine->getOutputDenseVisibleNodeValue(i) ) )
		{
      dense_points.push_back(Point(FLT_MAX, FLT_MAX, FLT_MAX, -1, -1));
			continue;
		}		
    dense_points.push_back(Point(geometry_boltzmann_machine->getOutputDenseVisibleNodeValue(i),
			geometry_boltzmann_machine->getOutputDenseVisibleNodeValue(i+1),  
			geometry_boltzmann_machine->getOutputDenseVisibleNodeValue(i+2),
			i/3,
			geometry_boltzmann_machine->getOutputDenseVisibleNodePartID(i) 
			) );
	}
}

vector<Point> ShapeDeepGenerativeModel::removeInvalidSparsePoints()
{
  vector<Point> valid_points;
	valid_points.reserve( sparse_points.size() );

	for (size_t i = 0; i < sparse_points.size(); i++) 
	{
		if ( isinv( sparse_points[i].p[0]  ) )
			continue;

		valid_points.push_back( sparse_points[i] );
	}

	return valid_points;
}

vector<Point> ShapeDeepGenerativeModel::removeInvalidDensePoints()
{
  vector<Point> valid_points;
	valid_points.reserve( dense_points.size() );

	for (size_t i = 0; i < dense_points.size(); i++) 
	{
		if ( isinv( dense_points[i].p[0]  ) )
			continue;

		valid_points.push_back( dense_points[i] );
	}

	return valid_points;
}

void ShapeDeepGenerativeModel::reInitializeSparsePoints(const vector<Point>& points)
{
	int j = 0;
	for (size_t i = 0; i < sparse_points.size(); i++)
	{
		if (isinv(sparse_points[i].p[0]))
			continue;

		sparse_points[i].p = points[j++].p;
	}
}


void ShapeDeepGenerativeModel::saveSparsePointCloud(std::string const & out_path)
{
	ofstream out(out_path.c_str());
	for (size_t i = 0; i < sparse_points.size(); i++)
	{
		if ( isinv( sparse_points[i].p[0] ) )
			continue;
		out << sparse_points[i].p[0] << " " << sparse_points[i].p[1] << " " << sparse_points[i].p[2] << std::endl;
	}
	out.close();
}

void ShapeDeepGenerativeModel::saveDensePointCloud(std::string const & out_path)
{
	ofstream out(out_path.c_str());
	for (size_t i = 0; i < dense_points.size(); i++)
	{
		if ( isinv( dense_points[i].p[0] ) )
			continue;
		out << dense_points[i].p[0] << " " << dense_points[i].p[1] << " " << dense_points[i].p[2];
	}
	out.close();
}

ShapeDeepGenerativeModel::~ShapeDeepGenerativeModel()
{
	delete geometry_boltzmann_machine;
	delete structure_boltzmann_machine;
	delete mesh_constructor;

	if ( training_data != NULL )
		delete training_data;
}

}
}





//if ( geometry_boltzmann_machine->getOutputVisibleNodePartID(i) == 1 || 
//	   geometry_boltzmann_machine->getOutputVisibleNodePartID(i) == 2 || geometry_boltzmann_machine->getOutputVisibleNodePartID(i) >= 9 )
//{
//	geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->getVisibleNode(i), FLT_MAX );
//	geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->getVisibleNode(i+1), FLT_MAX );
//	geometry_boltzmann_machine->setObservation( geometry_boltzmann_machine->getVisibleNode(i+2), FLT_MAX );
//	sparse_points.push_back( point( FLT_MAX, FLT_MAX, FLT_MAX ) );
//	continue;
//}



//// DEL
//for (int n = 0; n < 50; n++)
//{
//	training_data->sparse_point_data[0][n].clear();
//	training_data->dense_point_data[0][n].clear();
//}
////
