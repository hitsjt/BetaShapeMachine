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

#include "DL13_BoltzmannMachine.hpp"

namespace SNL {
namespace DL13 {

BoltzmannMachine::BoltzmannMachine(const string& _name, const SNL::Options &_options) : rng((const uint32_t)time(0))
{
  options.set("num_hidden_layers", 3);
  options.set("learning_epochs", 50000);
  options.set("use_dropout", false);
  options.set("num_random_restarts", 1);
  options.set("num_iter_activate_momentum_control", 100);
  options.set("initial_learning_rate", 1e-3f);
  options.set("regularization_type", (int)LS1L1);
  options.set("regularization_weight", 1e-3f);
  options.set("visible_layer_type", "DoubleBeta");
  options.set("hidden_layer_type", "Binary");
  options.set("decreasing_factor_for_number_of_hidden_nodes", 10.0f);
  options.set("use_part_based_connectivity", true);
  options.set("attribute_mapping_type", "linear_regression");
  //options.set("dense_mapping_type", "linear_regression");	
  options.set("dense_mapping_type", "none");
  options.set("num_neighbors_for_dense_mapping", 16);
  options.set("pretrain", true);
  options.set("override_num_hidden_nodes", 0);
  options.set("enable_sampling_with_inference", true);
  options.set("batch_size_proportion_of_dataset", 1.0f);
  options.merge(_options);	 // overwrite default options

  name = _name;
  number_of_training_examples = 0;
  number_of_training_examples_attributes = 0;
  number_of_observations = 0;
  num_input_dimensions = -1;
  num_attributes = -1;
  num_dense_input_dimensions = -1;
  total_number_of_nodes_created = 0;
  total_number_of_edges_created = 0;
  connectivity_is_set = false;
  init_from_attributes = false;
  momentum = 0.0f;
  max_part_id = 0;
  learning_rate = options.get("initial_learning_rate", 1e-3f);
  alayer = NULL;
  dlayer = NULL;
  bm_pretrain = NULL;
  dopretrain = false; 
  init_marginals = true;
  enable_sampling_with_inference = options.get("enable_sampling_with_inference", true);
  training_data_scaling_already_done = false;
  num_mf_iterations = 2; // options.get("num_hidden_layers", 1); 
  num_sampling_iterations = 1; // options.get("num_hidden_layers", 1);
}


BoltzmannMachine::~BoltzmannMachine()
{
  for (size_t l = 0; l < layers.size(); l++)
  {
    delete layers[l];
  }

  if (alayer != NULL)
    delete alayer;
  if (dlayer != NULL)
    delete dlayer;

};

void BoltzmannMachine::load(std::string const & in_path)
{
  std::cout << "Reading " << in_path << " for loading Boltzmann Machine...";
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

void BoltzmannMachine::save(std::string const & out_path) const
{
  //return;
  std::cout << "Writing " << out_path << " for storing Boltzmann Machine...";
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


void BoltzmannMachine::setTrainingData(const TrainingData& training_data)
{
  if (training_data.number_of_training_examples == 0)
  {
    std::cerr << "setTrainingSparseVisibleData: Cannot Initialize the Boltzmann Machine with emptry training data! " << std::endl;
    return;
  }

  std::cout << "Setting up Boltzmann Machine " << name << " based on the provided training data..." << std::endl;
  if (number_of_training_examples > 0)
    training_data_scaling_already_done = true;


  number_of_training_examples = training_data.number_of_training_examples;
  number_of_training_examples_attributes = training_data.number_of_training_examples_attributes;
  num_input_dimensions = training_data.number_of_sparse_points * 3;
  num_attributes = training_data.number_of_attributes;
  num_dense_input_dimensions = training_data.number_of_dense_points * 3;

  // 1. Initialize all nodes in the model
  initStructure(true);

  // 2. set-up training data for the nodes of the visible layer
  for (int n = 0; n < training_data.number_of_sparse_points; n++)
  {
    layers[0]->nodes[3 * n]->V.resize(training_data.number_of_training_examples);
    layers[0]->nodes[3 * n]->V.fill(FLT_MAX);
    layers[0]->nodes[3 * n + 1]->V.resize(training_data.number_of_training_examples);
    layers[0]->nodes[3 * n + 1]->V.fill(FLT_MAX);
    layers[0]->nodes[3 * n + 2]->V.resize(training_data.number_of_training_examples);
    layers[0]->nodes[3 * n + 2]->V.fill(FLT_MAX);

    for (int m = 0; m < training_data.number_of_training_examples; m++)
    {
      if (!training_data.sparse_point_data[m][n].empty())
      {
        layers[0]->nodes[3 * n]->part_id = training_data.sparse_part_id[m][n];
        layers[0]->nodes[3 * n + 1]->part_id = training_data.sparse_part_id[m][n];
        layers[0]->nodes[3 * n + 2]->part_id = training_data.sparse_part_id[m][n];
        max_part_id = max(layers[0]->nodes[3 * n]->part_id, max_part_id);

        if (options.get("visible_layer_type", "") == "Binary")
        {
          layers[0]->nodes[3 * n]->V(m) = 1.0f;
          if (!training_data.symmetry_type.empty())
          {
            layers[0]->nodes[3 * n + 1]->V(m) = (float)(training_data.symmetry_type[m][n] == 1);
            layers[0]->nodes[3 * n + 2]->V(m) = (float)(training_data.symmetry_type[m][n] == -1);
          }
          else
          {
            layers[0]->nodes[3 * n + 1]->V(m) = 0.0f;
            layers[0]->nodes[3 * n + 2]->V(m) = 0.0f;
          }
        }
        else
        {
          layers[0]->nodes[3 * n]->V(m) = training_data.sparse_point_data[m][n][0];
          layers[0]->nodes[3 * n + 1]->V(m) = training_data.sparse_point_data[m][n][1];
          layers[0]->nodes[3 * n + 2]->V(m) = training_data.sparse_point_data[m][n][2];
        }
      }
      else
      {
        if (options.get("visible_layer_type", "") == "Binary")
        {
          layers[0]->nodes[3 * n]->V(m) = 0.0f;
          layers[0]->nodes[3 * n + 1]->V(m) = 0.0f;
          layers[0]->nodes[3 * n + 2]->V(m) = 0.0f;
        }
      }
    }

    if (!training_data.spatial_neighbors_ids.empty())
    {
      for (size_t nj = 0; nj < training_data.spatial_neighbors_ids[n].size(); nj++)
      {
        layers[0]->nodes[3 * n]->spatial_neighbors.push_back(layers[0]->nodes[3 * training_data.spatial_neighbors_ids[n][nj]]);
        layers[0]->nodes[3 * n]->spatial_neighbors_weights.push_back(training_data.spatial_neighbors_weights[n][nj]);
        layers[0]->nodes[3 * n + 1]->spatial_neighbors.push_back(layers[0]->nodes[3 * training_data.spatial_neighbors_ids[n][nj] + 1]);
        layers[0]->nodes[3 * n + 1]->spatial_neighbors_weights.push_back(training_data.spatial_neighbors_weights[n][nj]);
        layers[0]->nodes[3 * n + 2]->spatial_neighbors.push_back(layers[0]->nodes[3 * training_data.spatial_neighbors_ids[n][nj] + 2]);
        layers[0]->nodes[3 * n + 2]->spatial_neighbors_weights.push_back(training_data.spatial_neighbors_weights[n][nj]);
      }
    }
  }
  //SVECTORf _hidden_layer1_part_cum_distribution = .5f * cumsum( training_data.percentage_of_sparse_points_per_part ) * (float)layers[1]->nodes.size();
  SVECTORf _hidden_layer1_part_cum_distribution = cumsum(training_data.percentage_of_sparse_points_per_part) * (float)layers[1]->nodes.size();
  _hidden_layer1_part_cum_distribution = ceiling(_hidden_layer1_part_cum_distribution);
  hidden_layer1_part_cum_distribution = convertEigenVectorToStdVector(_hidden_layer1_part_cum_distribution);

  std::cout << "Each labeled part in the shape will be allocated the following number of hidden nodes [printing the cumulative distribution]: " << std::endl;
  std::cout << _hidden_layer1_part_cum_distribution << std::endl;

  //std::cout << training_data.percentage_of_sparse_points_per_part << std::endl;
  //std::cout << hidden_layer1_part_cum_distribution << std::endl; system("pause");

  // 3. set-up training data for the attribute layer		
  if (alayer != NULL)
  {
    if (alayer->A.size() == 0)
      alayer->A.resize(number_of_training_examples, num_attributes);
    for (int n = 0; n < training_data.number_of_attributes; n++)
    {
      for (int m = 0; m < training_data.number_of_training_examples; m++)
      {
        if (!training_data.attribute_data[m].empty())
          alayer->A(m, n) = training_data.attribute_data[m][n];
        else
          alayer->A(m, n) = FLT_MAX;
      }
    }
  }

  // 4. set-up training data for the deterministic layer	
  if (dlayer != NULL)
  {
    if (dlayer->Y.size() == 0)
      dlayer->Y.resize(number_of_training_examples, num_dense_input_dimensions);
    dlayer->Y.fill(FLT_MAX);
    for (int n = 0; n < training_data.number_of_dense_points; n++)
    {
      for (int m = 0; m < training_data.number_of_training_examples; m++)
      {
        if (!training_data.dense_point_data[m][n].empty())
        {
          dlayer->Y(m, 3 * n) = training_data.dense_point_data[m][n][0];
          dlayer->Y(m, 3 * n + 1) = training_data.dense_point_data[m][n][1];
          dlayer->Y(m, 3 * n + 2) = training_data.dense_point_data[m][n][2];
        }
      }
    }
    // 5. set-up connection information for the dense layer
    nearest_sparse_points_for_each_dense_point = training_data.nearest_sparse_points_for_each_dense_point;
  }

  // 6. set-up model structure 
  initStructure(false);

  // 7. rescale observed data and attributes depending if they are Gaussians or beta
  std::cout << "Re-scaling the training data...";
  if (training_data_scaling_already_done)
    std::cout << "(based on previously computed scaling parameters)...";
  layers[0]->scaleTrainingData(training_data_scaling_already_done);
  if (alayer != NULL)
    alayer->scaleTrainingData(training_data_scaling_already_done);
  if (dlayer != NULL)
    dlayer->scaleTrainingData(training_data_scaling_already_done); // SHOULD BE LAST
  std::cout << "Done." << std::endl;

  training_data_scaling_already_done = true;

  // 8. pre-training preparation
  setupPretraining(training_data);
}

void BoltzmannMachine::setupPretraining(const TrainingData& training_data)
{
  if (options.get("pretrain", true) && layers.size() > 2)
  {
    dopretrain = true;
    SNL::Options pretrain_options;
    pretrain_options.merge(options);
    pretrain_options.set("num_hidden_layers", 1);
    pretrain_options.set("attribute_mapping_type", "none");
    pretrain_options.set("dense_mapping_type", "none");
    bm_pretrain = new BoltzmannMachine("pretrain-0-1", pretrain_options);
    std::cout << "Setting up Boltzmann Machine for pretraining..." << std::endl;
    bm_pretrain->setTrainingData(training_data);
    bm_pretrain->enable_sampling_with_inference = false;
  }
}

void BoltzmannMachine::setTrainingData(const Layer* source)
{
  std::cout << "=> Setting up pretraining Boltzmann Machine..." << std::endl;
  number_of_training_examples = (int)source->nodes[0]->q_mean.size();
  num_input_dimensions = (int)source->nodes.size();

  // 1. Initialize all nodes in the model
  initStructure(true);

  // 2. set-up training data for the nodes of the visible layer
  for (int n = 0; n < num_input_dimensions; n++)
  {
    layers[0]->nodes[n]->V.resize(source->nodes[n]->q_mean.size());

    if (options.get("visible_layer_type", "") == "Binary")
    {
      for (int m = 0; m < source->nodes[n]->q_mean.size(); m++)
        layers[0]->nodes[n]->V(m) = source->nodes[n]->q_mean(m); //>= .5f; 
    }
    else
    {
      for (int m = 0; m < source->nodes[n]->q_mean.size(); m++)
        layers[0]->nodes[n]->V(m) = source->nodes[n]->q_mean(m);
    }
  }

  // 6. set-up model structure 
  initStructure(false);
}

void BoltzmannMachine::init(SNL::Options const & _options)
{
  std::cerr << "Warning: calling BoltzmannMachine::init() directly does not serve any purpose - it does not do anything. You always need to call setTrainingData or load." << std::endl;
  //	options.merge(_options);
  initStructure();
}

void BoltzmannMachine::initStructure(bool do_not_set_connectivity)
{
  if (num_input_dimensions <= 0)
  {
    std::cerr << "BoltzmannMachine::initStructure: Cannot initialize machine without having the information about the input dimensionality - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  }

  // 1. create layers [need to clear layers, before calling init, if you want to rebuild machine]
  if (layers.empty())
  {
    std::cout << "=> Setting up the layers..." << std::endl;
    layers.resize(1 + options.get("num_hidden_layers", 1), NULL);

    total_number_of_nodes_created += num_input_dimensions;
    if (options.get("visible_layer_type", "") == "Gaussian")
      layers[0] = new GaussianLayer(num_input_dimensions, false, 0);
    else if (options.get("visible_layer_type", "") == "Beta")
      layers[0] = new BetaLayer(num_input_dimensions, false, false, 0);
    else if (options.get("visible_layer_type", "") == "DoubleBeta")
      layers[0] = new BetaLayer(num_input_dimensions, true, false, 0);
    else if (options.get("visible_layer_type", "") == "Binary")
      layers[0] = new BinaryLayer(num_input_dimensions, false, 0);
    else
    {
      std::cout << "Fatal error: visible layer of type " << options.get("visible_layer_type", "") << " is not supported!" << std::endl;
      exit(-1);
    }

    float decreasing_ratio = options.get("decreasing_factor_for_number_of_hidden_nodes", 10.0f);
    for (size_t l = 1; l < layers.size(); l++)
    {
      int number_of_hidden_nodes_to_create = (int)ceil( float(layers[l - 1]->nodes.size()) / (decreasing_ratio / pow(2, (float)l - 1.0) ) );
      if (options.get("override_num_hidden_nodes", 0) != 0)
        number_of_hidden_nodes_to_create = options.get("override_num_hidden_nodes", 0);

      if (number_of_hidden_nodes_to_create <= 3 && l >= 2)
      {
        std::cout << "=> Layer " << l << " has too few hidden nodes. This layer will be deleted" << std::endl;
        break;
      }
      total_number_of_nodes_created += number_of_hidden_nodes_to_create;

      if (options.get("hidden_layer_type", "") == "Gaussian")
        layers[l] = new GaussianLayer(number_of_hidden_nodes_to_create, true, (int)l);
      else if (options.get("hidden_layer_type", "") == "Beta")
        layers[l] = new BetaLayer(number_of_hidden_nodes_to_create, false, true, (int)l);
      else if (options.get("hidden_layer_type", "") == "DoubleBeta")
        layers[l] = new BetaLayer(number_of_hidden_nodes_to_create, true, true, (int)l);
      else if (options.get("hidden_layer_type", "") == "Binary")
        layers[l] = new BinaryLayer(number_of_hidden_nodes_to_create, true, (int)l);
      else
      {
        std::cout << "Fatal error: hidden layer of type " << options.get("hidden_layer_type", "") << " is not supported!" << std::endl;
        exit(-1);
      }
    }

    if (options.get("attribute_mapping_type", "") != "none" && num_attributes != 0 && number_of_training_examples_attributes != 0)
      alayer = new AttributeLayer(num_attributes, number_of_training_examples, (int)layers.size());
    if (options.get("dense_mapping_type", "") != "none" && num_dense_input_dimensions != 0)
      dlayer = new DenseDataLayer(num_dense_input_dimensions, number_of_training_examples, (int)layers.size() + 1);
  }

  for (size_t l = 1; l < layers.size(); l++)
  {
    if (layers[l] == NULL)
    {
      layers.resize(l);
      break;
    }
  }
  if (do_not_set_connectivity || connectivity_is_set)
    return;

  // 2. create connectivity between layers for the machine given the training data
  if (options.get("use_part_based_connectivity", true))
  {
    std::cout << "=> Connecting layer 1 with layer 0 (visible layer) based on part information of visible layer" << std::endl;
    layers[0]->above_layer = layers[1];
    layers[1]->below_layer = layers[0];

    short current_part_id = 0;
    for (size_t n = 0; n < layers[1]->nodes.size(); n++)
    {
      while (n == hidden_layer1_part_cum_distribution[current_part_id])
        current_part_id++;
      layers[1]->nodes[n]->part_id = current_part_id;

      for (size_t n2 = 0; n2 < layers[0]->nodes.size(); n2++)
      {        
        if (layers[0]->nodes[n2]->part_id == current_part_id)
          total_number_of_edges_created += layers[1]->nodes[n]->connect(layers[0]->nodes[n2]);
      }

      //if ( current_part_id <= max_part_id )
      //{
      //	for (size_t n2 = 0; n2 < layers[0]->nodes.size(); n2++)
      //	{
      //		if ( layers[0]->nodes[n2]->part_id == current_part_id )
      //			total_number_of_edges_created += layers[1]->nodes[n]->connect( layers[0]->nodes[n2] );
      //	}
      //}
      //else
      //{
      //	for (size_t n2 = 0; n2 < layers[0]->nodes.size(); n2++)
      //		total_number_of_edges_created += layers[1]->nodes[n]->connect( layers[0]->nodes[n2] );
      //}
    }

    for (size_t l = 2; l < layers.size(); l++)
    {
      std::cout << "=> Connecting layer " << l << " with layer " << l - 1 << "..." << std::endl;
      layers[l - 1]->above_layer = layers[l];
      layers[l]->below_layer = layers[l - 1];

      for (size_t n = 0; n < layers[l]->nodes.size(); n++)
      {
        for (size_t n2 = 0; n2 < layers[l - 1]->nodes.size(); n2++)
        {
          total_number_of_edges_created += layers[l]->nodes[n]->connect(layers[l - 1]->nodes[n2]);
        }
      }
    }
  } // end of use_part_based_connectivity == true
  else
  {
    for (size_t l = 1; l < layers.size(); l++)
    {
      std::cout << "=> Connecting layer " << l << " with layer " << l - 1 << "..." << std::endl;
      layers[l - 1]->above_layer = layers[l];
      layers[l]->below_layer = layers[l - 1];

      for (size_t n = 0; n < layers[l]->nodes.size(); n++)
      {
        for (size_t n2 = 0; n2 < layers[l - 1]->nodes.size(); n2++)
        {
          total_number_of_edges_created += layers[l]->nodes[n]->connect(layers[l - 1]->nodes[n2]);
        }
      }
    }
  }  // end of use_part_based_connectivity == true


  // 3. create connectivity for deterministic layers in the netwoork
  if (alayer != NULL)
    alayer->connect(layers[layers.size() - 1]);

  if (dlayer != NULL)
  {
    std::cout << "=> Connecting dense layer to the visible layer..." << std::endl;;
    for (size_t i = 0; i < nearest_sparse_points_for_each_dense_point.size(); i++)
    {
      for (size_t j = 0; j < nearest_sparse_points_for_each_dense_point[i].size(); j++)
      {
        dlayer->sparse_to_dense_node_connections[3 * i].push_back(layers[0]->nodes[3 * nearest_sparse_points_for_each_dense_point[i][j]]);
        dlayer->sparse_to_dense_node_connections[3 * i + 1].push_back(layers[0]->nodes[3 * nearest_sparse_points_for_each_dense_point[i][j] + 1]);
        dlayer->sparse_to_dense_node_connections[3 * i + 2].push_back(layers[0]->nodes[3 * nearest_sparse_points_for_each_dense_point[i][j] + 2]);
      }
    }
  }

  connectivity_is_set = true;
  std::cout << total_number_of_nodes_created << " nodes created, " << total_number_of_edges_created << " edges created." << " Boltzmann structure is now initialized." << std::endl;
}



void BoltzmannMachine::pretrain(SNL::Options const & _options)
{
  BoltzmannMachine *prev_bm = bm_pretrain, *bm = bm_pretrain;
  std::cout << "=> Pretraining layers 0-1..." << std::endl;
  bm_pretrain->train();
  this->layers[0]->copyParameters(bm_pretrain->layers[0]);
  this->layers[1]->copyParameters(bm_pretrain->layers[1]);
  this->learning_rate = max(bm_pretrain->learning_rate, options.get("initial_learning_rate", 1e-3f));

  for (size_t l = 1; l < layers.size() - 1; l++)
  {
    std::cout << "=> Pretraining layers " << l << " " << l + 1 << "..." << std::endl;
    prev_bm = bm;

    SNL::Options pretrain_options;
    pretrain_options.merge(options);
    pretrain_options.set("num_hidden_layers", 1);
    pretrain_options.set("attribute_mapping_type", "none");
    pretrain_options.set("dense_mapping_type", "none");
    pretrain_options.set("visible_layer_type", this->options.get("hidden_layer_type", "")); // pretraining hidden layers 
    pretrain_options.set("hidden_layer_type", this->options.get("hidden_layer_type", ""));
    pretrain_options.set("use_part_based_connectivity", false);

    if (this->options.get("regularization_type", (int)L1) == LNONE)
      pretrain_options.set("regularization_type", (int)LNONE);
    if (this->options.get("regularization_type", (int)L1) == L1 || this->options.get("regularization_type", (int)L1) == LS1L1)
      pretrain_options.set("regularization_type", (int)L1);
    if (this->options.get("regularization_type", (int)L1) == L2 || this->options.get("regularization_type", (int)L1) == LS2L2)
      pretrain_options.set("regularization_type", (int)L2);

    pretrain_options.set("override_num_hidden_nodes", layers[l + 1]->nodes.size());
    bm = new BoltzmannMachine("pretrain_" + std::to_string(l) + "-" + std::to_string(l + 1), pretrain_options);
    //if (l != layers.size()-2)
    bm->enable_sampling_with_inference = false;

    prev_bm->layers[0]->setObservationsFromTrainingExamples();
    prev_bm->doInference();
    bm->setTrainingData(prev_bm->layers[1]);
    delete prev_bm;
    bm->train();
    this->layers[l]->copyBias(bm->layers[0], 1);
    this->layers[l + 1]->copyParameters(bm->layers[1]);
  }

  bm_pretrain = NULL;
  delete bm;
}



void BoltzmannMachine::train(SNL::Options const & _options)
{
  if (!connectivity_is_set || layers.empty())
  {
    std::cerr << "BoltzmannMachine::train: Cannot train machine without layers or connections - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  }
  if (layers[0]->nodes[0]->V.size() == 0)
  {
    std::cerr << "BoltzmannMachine::train: There is no training data set for learning. If you used 'load', you must call 'setTrainingData' after 'load'. " << std::endl;
    return;
  }
  if (options.get("visible_layer_type", "") == "Gaussian")
  {
    options.set("attribute_mapping_type", "linear_regression");
    options.set("dense_mapping_type", "linear_regression");
  }
  options.merge(_options);

  if (options.get("batch_size_proportion_of_dataset", 1.0f) == 1.0f)
  {
    no_stochastic_train();
    return;
  }

  number_of_observations = number_of_training_examples;
  int batch_size_proportion_of_dataset = (int)ceil( options.get("batch_size_proportion_of_dataset", .1f) * (float)number_of_training_examples );
  if (batch_size_proportion_of_dataset <= 10)
  {
    std::cout << "Too small training dataset. No minibatches will be used." << std::endl;
    batch_size_proportion_of_dataset = number_of_training_examples;
  }
  regularization_type reg_type = (regularization_type)options.get("regularization_type", (int)LNONE);
  float reg_weight = options.get("regularization_weight", 0.0f);
  int num_iter_activate_momentum_control = options.get("num_iter_activate_momentum_control", 1000);  
  bool use_dropout = options.get("use_dropout", false);

  if (dlayer != NULL)
    if (dlayer->bps.empty())
      trainDenseDataLayer();
  
  for (size_t l = 0; l < layers.size(); l++)
    layers[l]->init(false);

  if (dopretrain)
  {
    std::cout << "=== PRETRAINING MODE ===" << std::endl;
    pretrain();
    std::cout << "=== PRETRAINING DONE ===" << std::endl;
  }
  

  std::cout << "stochastic gradient mode / enable_sampling_with_inference: " << enable_sampling_with_inference << std::endl;
  float prev_rec_error = FLT_MAX, rec_error = FLT_MAX, min_rec_error = FLT_MAX;
  for (int iter = 0; iter < options.get("learning_epochs", INT_MAX); )
  {
    // prepare batches
    std::vector<int> training_example_indices(number_of_training_examples);
    std::iota(std::begin(training_example_indices), std::end(training_example_indices), 0);
    std::random_shuffle(training_example_indices.begin(), training_example_indices.end());

    for (int tid = 0; tid < number_of_training_examples; tid += batch_size_proportion_of_dataset)
    {
		std::vector<int> batch_training_example_indices;
		if (tid + batch_size_proportion_of_dataset >= number_of_training_examples)
			batch_training_example_indices = std::vector<int>(training_example_indices.begin() + tid, training_example_indices.begin() + number_of_training_examples);
		else
			batch_training_example_indices = std::vector<int>(training_example_indices.begin() + tid, training_example_indices.begin() + tid + batch_size_proportion_of_dataset);

      number_of_observations = (int)batch_training_example_indices.size();

      // positive phase
      layers[0]->setObservationsFromTrainingExamples( use_dropout, batch_training_example_indices);
      doInference();
      for (int l = 0; l < (int)layers.size(); l++)
      {
        layers[l]->updateExpectations(POSITIVE_PHASE);
      }
      layers[0]->clearObservations(); // in case inference was run from a training example, clear it - every time you need to set it

      // negative phase
      if (enable_sampling_with_inference)
      {
        layers[layers.size() - 1]->condSample(rng);
        for (int l = int(layers.size()) - 2; l >= 0; l--)
          layers[l]->initMarginals(number_of_observations);
        for (int l = int(layers.size()) - 2; l >= 0; l--)
          layers[l]->doInference();
      }
      else
      {
        doInference(layers[0]);
      }

      layers[0]->setObservationsFromCurrentMeans();
      doInference();
      for (int l = 0; l < (int)layers.size(); l++)
      {
        layers[l]->updateExpectations(NEGATIVE_PHASE);
      }
      layers[0]->clearObservations(); // in case inference was run from a training example, clear it - every time you need to set it

      
      // update parameters from this minibatch
      for (int l = 0; l < (int)layers.size(); l++)
      {
        if (l <= 1)
          layers[l]->updateParameters(number_of_observations, learning_rate, momentum, reg_type, reg_weight);
        else
        {
          if (this->options.get("regularization_type", (int)L1) == L1 || this->options.get("regularization_type", (int)L1) == LS1L1)
            layers[l]->updateParameters(number_of_observations, learning_rate, momentum, L1, reg_weight);
          if (this->options.get("regularization_type", (int)L1) == L2 || this->options.get("regularization_type", (int)L1) == LS2L2)
            layers[l]->updateParameters(number_of_observations, learning_rate, momentum, L2, reg_weight);
        }
      }
    } // end of loop over batches

	iter++;

    // measure current reconstruction error
    number_of_observations = number_of_training_examples;
    layers[0]->setObservationsFromTrainingExamples();
    doInference();
    layers[0]->clearObservations(); // in case inference was run from a training example, clear it - every time you need to set it
    doInference(layers[0]);
    prev_rec_error = rec_error;
    rec_error = layers[0]->measureReconstructionError();
    layers[0]->clearObservations(); // in case inference was run from a training example, clear it - every time you need to set it

    // update learning rate with bold driver and momentum
    if (isinf(rec_error) || isnan(rec_error) || rec_error > 1.5f * prev_rec_error || rec_error > 1.5f * min_rec_error)
    {
      std::cout << "=> Exploded... restoring parameters and auto-fixing learning" << std::endl;
      restoreSavedWeights();
      for (size_t l = 0; l < layers.size(); l++)
        layers[l]->init(true);
      rec_error = min_rec_error;
      learning_rate *= 0.5f;
    }
    else if (rec_error > prev_rec_error)
      learning_rate *= 0.9f;
    else
      learning_rate *= 1.1f;

    if (options.get("visible_layer_type", "") == "Binary")
      learning_rate = min(learning_rate, 1.0f);
    else
      learning_rate = min(learning_rate, 0.1f);

    if (iter >= num_iter_activate_momentum_control)
    {
      float new_momentum = 1.0f - 1.0f / (1.0f + ((float)iter / float(num_iter_activate_momentum_control)));
      if (new_momentum >= momentum)
        momentum = new_momentum;
    }

    // check termination condition and check and check if the current parameters are best before updating them
    if (iter % 100 == 0)
      std::cout << "=> Learning iteration " << iter << ": current error=" << rec_error << ", learning rate=" << learning_rate << ", momentum=" << momentum << std::endl;
    if (rec_error < min_rec_error)
    {
      min_rec_error = rec_error;
      std::cout << "=>=> Best iteration " << iter << ": current error=" << rec_error << ", learning rate=" << learning_rate << ", momentum=" << momentum << std::endl;
      saveWeights();
    }
    if (learning_rate < EPSILONf || rec_error < EPSILONf)
      break;

  }  // end of loop over iteratins

  number_of_observations = number_of_training_examples;
  restoreSavedWeights();
  layers[0]->setObservationsFromTrainingExamples();
  doInference();
  layers[0]->clearObservations();
  for (int l = 1; l < (int)layers.size(); l++)
    layers[l]->updatePriors();
  options.set("pretrain", false);
  dopretrain = false;

  if (alayer == NULL)
  {
    std::cerr << "Training is now complete." << std::endl;
    return;
  }

  alayer->updateTrainingData();
  //alayer->updateParameters(options.get("attribute_mapping_type", "linear_regression")	);
  trainAttributeLayer();

  std::cout << "Training is now complete." << std::endl;
}





///// train without stochastic gradient descent and greedy initialization (probably useless)
void BoltzmannMachine::no_stochastic_train(SNL::Options const & _options)
{
  number_of_observations = number_of_training_examples;
  if (dlayer != NULL)
    if (dlayer->bps.empty())
      trainDenseDataLayer();

  int num_iter_activate_momentum_control = options.get("num_iter_activate_momentum_control", 1000);
  for (size_t l = 0; l < layers.size(); l++)
  {
    layers[l]->init(true);
  }

  if (dopretrain)
  {
    std::cout << "=== PRETRAINING MODE ===" << std::endl;
    pretrain();
    std::cout << "=== PRETRAINING DONE ===" << std::endl;
  }

  if ( options.get("num_random_restarts", 1) >= 1 && !dopretrain)
  {
    // initialize with random weights
    std::cout << "=> Initializing model parameters with random restarts..." << std::endl;
    float min_rec_error = FLT_MAX;
    for (int r = 1; r <= options.get("num_random_restarts", 1); r++)
    {
      if ( (r-1) % 100 == 0)
        std::cout << "=> Random restart: " << r << std::endl;

      for (size_t l = 0; l < layers.size(); l++)
        layers[l]->init(false);

      layers[0]->setObservationsFromTrainingExamples();
      doInference();
      layers[0]->clearObservations(); // in case inference was run from a training example, clear it - every time you need to set it
      doInference(layers[0]);
      float rec_error = layers[0]->measureReconstructionError();

      if (rec_error < min_rec_error)
      {
        min_rec_error = rec_error;
        std::cout << "=>=> Best initialization so far with reconstruction error: " << rec_error << std::endl;
        saveWeights();
      }
    }
    restoreSavedWeights();
    options.set("greedy_initialization", false);
    momentum = 0.0f;
  }

  regularization_type reg_type = (regularization_type)options.get("regularization_type", (int)LNONE);
  float reg_weight = options.get("regularization_weight", 0.0f);
  float prev_rec_error = FLT_MAX, rec_error = FLT_MAX, min_rec_error = FLT_MAX;
  bool use_dropout = options.get("use_dropout", false);

  std::cout << "deterministic gradient descent / enable_sampling_with_inference: " << enable_sampling_with_inference << std::endl;

  for (int iter = 0; iter < options.get("learning_epochs", INT_MAX); iter++)
  {
    // positive phase
    layers[0]->setObservationsFromTrainingExamples( use_dropout );
    doInference();
    for (int l = 0; l < (int)layers.size(); l++)
    {
      layers[l]->updateExpectations(POSITIVE_PHASE);
    }
    layers[0]->clearObservations(); // in case inference was run from a training example, clear it - every time you need to set it

    // negative phase (+update reconstruction error)
    if (enable_sampling_with_inference)
    {
      layers[layers.size() - 1]->condSample(rng);
      for (int l = int(layers.size()) - 2; l >= 0; l--)
        layers[l]->initMarginals(number_of_observations);
      for (int l = int(layers.size()) - 2; l >= 0; l--)
        layers[l]->doInference();
    }
    else
    {
      doInference(layers[0]);
    }

    prev_rec_error = rec_error;
    rec_error = layers[0]->measureReconstructionError();
    layers[0]->setObservationsFromCurrentMeans();
    doInference();
    for (int l = 0; l < (int)layers.size(); l++)
    {
      layers[l]->updateExpectations(NEGATIVE_PHASE);
    }
    layers[0]->clearObservations(); // in case inference was run from a training example, clear it - every time you need to set it

    // update learning rate and momentum 
    if (isinf(rec_error) || isnan(rec_error) || rec_error > 1.1f * prev_rec_error || rec_error > 1.1f * min_rec_error)
    {
      std::cout << "=> Exploded... restoring parameters and auto-fixing learning" << std::endl;
      restoreSavedWeights();
      for (size_t l = 0; l < layers.size(); l++)
        layers[l]->init(true);
      rec_error = min_rec_error;
      learning_rate *= 0.5f;
    }
    else if (rec_error > prev_rec_error)
      learning_rate *= 0.9f;
    else
      learning_rate *= 1.1f;

    if (options.get("visible_layer_type", "") == "Binary")
    {
      learning_rate = min(learning_rate, 1.0f);
    }
    else
    {
      learning_rate = min(learning_rate, 0.1f);
    }

    if (iter >= num_iter_activate_momentum_control)
    {
      float new_momentum = 1.0f - 1.0f / (1.0f + ((float)iter / float(num_iter_activate_momentum_control)));
      if (new_momentum >= momentum)
        momentum = new_momentum;
    }

    // check termination condition and check and check if the current parameters are best before updating them
    if (iter % 100 == 0)
      std::cout << "=> Learning iteration " << iter << ": current error=" << rec_error << ", learning rate=" << learning_rate << ", momentum=" << momentum << std::endl;
    if (rec_error < min_rec_error)
    {
      min_rec_error = rec_error;
      std::cout << "=>=> Best iteration " << iter << ": current error=" << rec_error << ", learning rate=" << learning_rate << ", momentum=" << momentum << std::endl;
      saveWeights();
    }
    if (learning_rate < EPSILONf || rec_error < EPSILONf)
      break;

    // update parameters for next iteration
    for (int l = 0; l < (int)layers.size(); l++)
    {
      if (l <= 1)
        layers[l]->updateParameters(number_of_training_examples, learning_rate, momentum, reg_type, reg_weight);
      else
      {
        if (this->options.get("regularization_type", (int)L1) == L1 || this->options.get("regularization_type", (int)L1) == LS1L1)
          layers[l]->updateParameters(number_of_training_examples, learning_rate, momentum, L1, reg_weight);
        if (this->options.get("regularization_type", (int)L1) == L2 || this->options.get("regularization_type", (int)L1) == LS2L2)
          layers[l]->updateParameters(number_of_training_examples, learning_rate, momentum, L2, reg_weight);
      }
    }
  }
  restoreSavedWeights();
  layers[0]->setObservationsFromTrainingExamples();
  doInference();
  layers[0]->clearObservations();
  for (int l = 1; l < (int)layers.size(); l++)
    layers[l]->updatePriors();
  options.set("pretrain", false);
  dopretrain = false;

  if (alayer == NULL)
  {
    std::cerr << "Training is now complete." << std::endl;
    return;
  }

  alayer->updateTrainingData();
  //alayer->updateParameters(options.get("attribute_mapping_type", "linear_regression")	);
  trainAttributeLayer();

  std::cout << "Training is now complete." << std::endl;
}



void BoltzmannMachine::trainAttributeLayer(SNL::Options const & _options)
{
  if (!connectivity_is_set || layers.empty())
  {
    std::cerr << "BoltzmannMachine::trainAttributeLayer: Cannot train machine without layers or connections - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  }
  if (alayer == NULL)
  {
    std::cerr << "BoltzmannMachine::trainAttributeLayer: There are no attributes set for learning!]" << std::endl;
    return;
  }
  if (alayer->A.size() == 0 || alayer->X.size() == 0)
  {
    std::cerr << "BoltzmannMachine::trainAttributeLayer: There is no training data set for learning. If you used 'load', the saved boltzmann machine was not trained with attributes" << std::endl;
    return;
  }

  options.merge(_options);
  number_of_observations = number_of_training_examples;
  std::cout << "=> Mapping attribute layer to the hidden layer connected to it..." << std::endl;
  alayer->updateParameters(options.get("attribute_mapping_type", "linear_regression"));
  std::cout << "Done." << std::endl;
}



void BoltzmannMachine::trainDenseDataLayer(SNL::Options const & _options)
{
  if (!connectivity_is_set || layers.empty())
  {
    std::cerr << "BoltzmannMachine::trainDenseDataLayer: Cannot train machine without layers or connections - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  }
  if (dlayer == NULL)
  {
    std::cerr << "BoltzmannMachine::trainDenseDataLayer: There is no dense layer set for learning!" << std::endl;
    return;
  }
  if (dlayer->Y.size() == 0 && dlayer->bps.empty())
  {
    std::cout << "No training data set for learning dense point cloud representations. Skipping dense layer learning." << std::endl;
    return;
  }
  if (dlayer->Y.size() == 0 && !dlayer->bps.empty())
  {
    std::cout << "No training data set for learning dense point cloud representations. Training data for the dense layer were deleted last time the model was trained. The reason is that this training data take really too much space. To re-train, you have to call setTrainingData again." << std::endl;
    return;
  }

  options.merge(_options);
  std::cout << "=> Mapping dense layer to the visible layer connected to it..." << std::endl;
  dlayer->updateParameters(options.get("dense_mapping_type", "linear_regression"), options.get("num_neighbors_for_dense_mapping", 3));
  dlayer->Y.resize(0, 0); // clear the huge matrix
  std::cout << "Done." << std::endl;
}


void BoltzmannMachine::doInference(Layer *layer)
{
  if (!connectivity_is_set || layers.empty())
  {
    std::cerr << "BoltzmannMachine::doInference: Cannot performance inference on a machine without layers or connections - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  }

  layer->initMarginals(number_of_observations);
  layer->doInference();
  //layer->unscale(); 
}


void BoltzmannMachine::doInferenceWithoutInit(int layer_id)
{
  init_marginals = false;
  if (layer_id == -1) // do inference in all layers
    doInference();
  else
    doInference(layers[layer_id]);
  layers[0]->unscale();
  init_marginals = true;
}

//void BoltzmannMachine::doInferenceWithoutInit(float evidence_weight)
//{
//  init_marginals = false;
//  vector<float> old_q_mean(layers[0]->nodes.size());
//  for (size_t n = 0; n < layers[0]->nodes.size(); n++)
//    old_q_mean[n] = layers[0]->nodes[n]->q_mean(0);
//
//  doInference();
//
//  for (size_t n = 0; n < layers[0]->nodes.size(); n++)
//    layers[0]->nodes[n]->q_mean(0) = (1.0f - evidence_weight) * layers[0]->nodes[n]->q_mean(0) + evidence_weight * old_q_mean[n];
//
//  layers[0]->unscale();
//  init_marginals = true;
//}

void BoltzmannMachine::doInference()
{
  if (!connectivity_is_set || layers.empty())
  {
    std::cerr << "BoltzmannMachine::doInference: Cannot performance inference on a machine without layers or connections - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  } 

  if (init_marginals)
    for (int l = 0; l < (int)layers.size(); l++)
      layers[l]->initMarginals(number_of_observations);

  if (!init_from_attributes)
  {
    for (int i = 0; i < num_mf_iterations; i++)
    {
      for (int l = 0; l < (int)layers.size(); l++)
        layers[l]->doInference();
    } 
  } 
  else
  {
    alayer->doInference();
    for (int i = 0; i < num_mf_iterations; i++)
    {
      for (int l = int(layers.size()) - 1; l >= 0; l--)
        layers[l]->doInference();
    }
  }

  layers[0]->unscale();

}


void BoltzmannMachine::doAttribInference()
{
  std::cout << "Running attribute-based inference...";
  if (alayer == NULL || !alayer->is_observed)
  {
    std::cerr << "BoltzmannMachine::doAttribInference cannot run inference with attributes, if setLayerObservations for attributes is not called first" << std::endl;
    return;
  }
  init_from_attributes = true;
  number_of_observations = 1;
  doInference();
  init_from_attributes = false;
  std::cout << "Done." << std::endl;
}

void BoltzmannMachine::doDenseInference()
{
  std::cout << "Running dense layer-based inference...";
  if (dlayer == NULL || dlayer->bps.empty())
  {
    std::cerr << "BoltzmannMachine::doDenseInference cannot run without training the dense layer first" << std::endl;
    return;
  }
  bool is_visible_layer_ready = true;
  for (size_t n = 0; n < layers[0]->nodes.size(); n++)
    if (layers[0]->nodes[n]->q_mean.size() == 0)
      is_visible_layer_ready = false;
  if (!is_visible_layer_ready)
  {
    std::cerr << "BoltzmannMachine::doDenseInference requires inference on the visible layer first (call doInference, doAttribInference or sample first" << std::endl;
    return;
  }

  dlayer->doInference();
  dlayer->unscale();
  std::cout << "Done." << std::endl;
}

SVECTORf BoltzmannMachine::measureEnergy(bool check_out_of_range_values)
{
  SVECTORf uprob = layers[0]->measureEnergy(check_out_of_range_values);

  for (size_t l = 1; l < layers.size(); l++)
    uprob += layers[l]->measureEnergy(check_out_of_range_values);

  return uprob;
}

void BoltzmannMachine::sample()
{
  if (!connectivity_is_set || layers.empty())
  {
    std::cerr << "BoltzmannMachine::sample: Cannot sample machine without layers or connections - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  }
  number_of_observations = 1;
  std::cout << "Taking a sample...";
  for (int l = 0; l < (int)layers.size(); l++)
    layers[l]->initMarginals(number_of_observations);

  boost::random::uniform_real_distribution<float> rand(0.0f, 1.0f);
  if ( rand(rng) <= .5f )
    layers[layers.size() - 1]->sample(rng);
  else
  {   
    if (layers[layers.size() - 1]->type == BINARY) // from time to time, sample extremes
    {
      std::cout << " [Sampling extremes] ";
      ((BinaryLayer*)layers[layers.size() - 1])->sampleAndDiscretize(rng);
    }
    else
      layers[layers.size() - 1]->sample(rng);
  }

  for (int l = int(layers.size()) - 2; l >= 0; l--)
    layers[l]->doInference();

  for (int i = 0; i < num_sampling_iterations - 1; i++)
  {
    for (int l = int(layers.size()) - 1; l >= 0; l--)
      layers[l]->doInference();
  }

  layers[0]->unscale();

  std::cout << "Done." << std::endl;
}


void BoltzmannMachine::reconstructTrainingExample(int m)
{
  if (!connectivity_is_set || layers.empty())
  {
    std::cerr << "BoltzmannMachine::reconstructTrainingExample: Cannot train machine without layers or connections - need to call 'setTrainingData' or 'load' first" << std::endl;
    return;
  }
  if (layers[0]->nodes[0]->V.size() == 0)
  {
    std::cerr << "BoltzmannMachine::reconstructTrainingExample: There is no training data set for learning. If you used 'load', you must call 'setTrainingData' after 'load'. " << std::endl;
    return;
  }

  for (int l = 0; l < (int)layers.size(); l++)
    layers[l]->initMarginals(number_of_observations);

  number_of_observations = number_of_training_examples;
  layers[0]->setObservationsFromTrainingExamples();
  doInference();
  layers[0]->clearObservations();

  //layers[0]->initMarginals(number_of_observations);
  //layers[1]->initMarginals(number_of_observations);
  //doInference( layers[1] );

  doInference(layers[0]);
  for (size_t n = 0; n < layers[0]->nodes.size(); n++)
  {
    layers[0]->nodes[n]->q_mean(0) = layers[0]->nodes[n]->q_mean(m);
    layers[0]->nodes[n]->log_q_mean(0) = layers[0]->nodes[n]->log_q_mean(m);
    layers[0]->nodes[n]->log_one_minus_q_mean(0) = layers[0]->nodes[n]->log_one_minus_q_mean(m);
  }
  layers[0]->unscale();
}


void BoltzmannMachine::setObservation(SNL::Node* node, const std::vector<double> & value)
{
  number_of_observations = 1;
  ((DLNode*)node)->setObservation((float)value[0], true);
}

void BoltzmannMachine::setObservation(SNL::Node* node, float value)
{
  number_of_observations = 1;
  ((DLNode*)node)->setObservation(value, true);
}

void BoltzmannMachine::setLayerObservations(Layer *layer, const std::vector<float> & values)
{
  number_of_observations = 1;
  layer->setObservations(values, true);
}

void BoltzmannMachine::clearObservation(SNL::Node* node)
{
  ((DLNode*)node)->clearObservation();
}

void BoltzmannMachine::clearLayerObservations(Layer* layer)
{
  layer->clearObservations();
};


void BoltzmannMachine::clearAllObservations()
{
  number_of_observations = 0;
  for (size_t l = 0; l < layers.size(); l++)
  {
    layers[l]->clearObservations();
  }
  if (alayer != NULL)
    alayer->clearObservations();
};


void BoltzmannMachine::saveWeights()
{
  for (size_t l = 0; l < layers.size(); l++)
  {
    layers[l]->saveWeights();
  }
}

void BoltzmannMachine::restoreSavedWeights()
{
  for (size_t l = 0; l < layers.size(); l++)
  {
    layers[l]->restoreSavedWeights();
  }
}


void BoltzmannMachine::clearVisibleLayerObservations()
{
  if (layers.empty())
  {
    std::cerr << " BoltzmannMachine::clearVisibleLayerObservations() cannot run since the machine is not initialized (setTrainingData or load was not called) " << std::endl;
    return;
  }
  clearLayerObservations(layers[0]);
}

void BoltzmannMachine::clearAttributeLayerObservations()
{
  if (alayer == NULL)
  {
    std::cerr << " BoltzmannMachine::clearAttributeLayerObservations() cannot run since the machine is not initialized (setTrainingData or load was not called) " << std::endl;
    return;
  }
  clearLayerObservations(alayer);
}

void BoltzmannMachine::setVisibleLayerObservations(const std::vector<float> & values)
{
  std::cout << "Setting observations on the visible layer...";
  if (layers.empty())
  {
    std::cerr << " BoltzmannMachine::setVisibleLayerObservations() cannot run since the machine is not initialized (setTrainingData or load was not called) " << std::endl;
    return;
  }
  setLayerObservations(layers[0], values);
  std::cout << "Done." << std::endl;
}

void BoltzmannMachine::setAttributeLayerObservations(const std::vector<float> & values)
{
  std::cout << "Setting observations on the attribute layer...";
  if (alayer == NULL)
  {
    std::cerr << " BoltzmannMachine::setAttributeLayerObservations() cannot run since the machine is not initialized (setTrainingData or load was not called) " << std::endl;
    return;
  }
  setLayerObservations(alayer, values);
  std::cout << "Done." << std::endl;
};



float BoltzmannMachine::getOutputVisibleNodeValue(int node_id)
{
  if (layers.empty())
  {
    std::cerr << " BoltzmannMachine::getOutputVisibleNodeValue() cannot run since the machine is not initialized (setTrainingData or load was not called) " << std::endl;
    return FLT_MAX;
  }
  return layers[0]->nodes[node_id]->out_mean;
}

short BoltzmannMachine::getOutputVisibleNodePartID(int node_id)
{
  if (layers.empty())
  {
    std::cerr << " BoltzmannMachine::getOutputVisibleNodePartID() cannot run since the machine is not initialized (setTrainingData or load was not called) " << std::endl;
    return -1;
  }
  return layers[0]->nodes[node_id]->part_id;
}

SNL::Node* BoltzmannMachine::getVisibleNode(int node_id)
{
  if (layers.empty())
  {
    std::cerr << " BoltzmannMachine::getVisibleNode() cannot run since the machine is not initialized (setTrainingData or load was not called) " << std::endl;
    return NULL;
  }
  return layers[0]->nodes[node_id];
}

float BoltzmannMachine::getOutputDenseVisibleNodeValue(int node_id)
{
  if (dlayer == NULL)
  {
    std::cerr << " BoltzmannMachine::getOutputDenseVisibleNodeValue() cannot run since the machine's dense layer is not initialized" << std::endl;
    return FLT_MAX;
  }
  return dlayer->out(node_id);
}

short BoltzmannMachine::getOutputDenseVisibleNodePartID(int node_id)
{
  if (dlayer == NULL)
  {
    std::cerr << " BoltzmannMachine::getOutputDenseVisibleNodePartID() cannot run since the machine's dense layer is not initialized" << std::endl;
    return -1;
  }
  return dlayer->sparse_to_dense_node_connections[node_id][0]->part_id;
}


int BoltzmannMachine::getNumberOfUnits()
{
  int num_units = 0;
  for (int l = 0; l < (int)layers.size(); l++)
    num_units += (int)layers[l]->nodes.size();
  return num_units;
}

int BoltzmannMachine::getNumberOfVisibleUnits()
{
  return num_input_dimensions;
}

int BoltzmannMachine::getNumberOfDenseVisibleUnits()
{
  if (dlayer != NULL)
    return num_dense_input_dimensions;
  else
    return 0;
}

void BoltzmannMachine::setMFiterations(int iter)
{
  num_mf_iterations = iter;
}


} // namespace DL13
} // namespace SNL

//
//for (int n = 0; n < layers[layers.size() - 1]->nodes.size(); n++)
//{
//  if (layers[layers.size() - 1]->nodes[n]->type == BETA)
//  {
//    std::cout << "BETA: ";
//    std::cout << ((BetaNode*)layers[layers.size() - 1]->nodes[n])->p_a << " ";
//    std::cout << ((BetaNode*)layers[layers.size() - 1]->nodes[n])->p_b << " ";
//    std::cout << layers[layers.size() - 1]->nodes[n]->q_mean << std::endl;
//  }
//  else
//  {
//    std::cout << ((BinaryNode*)layers[layers.size() - 1]->nodes[n])->p_b << " ";
//    std::cout << layers[layers.size() - 1]->nodes[n]->q_mean << std::endl;
//  }
//}
//std::cout << "----" << std::endl;