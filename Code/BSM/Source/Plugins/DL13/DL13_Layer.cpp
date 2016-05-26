#include "DL13_Layer.hpp"

namespace SNL {;
namespace DL13 {;

Layer::~Layer() 
{ 
	for (size_t n = 0; n < nodes.size(); n++)
	{
		nodes[n]->clearNeighborsUnsafeOneWay();
		delete nodes[n];
		nodes[n] = NULL;
	}
	nodes.clear();
} 

float Layer::measureReconstructionError(const std::vector<int>& indices_of_examples_to_use)
{
	float rec_error = 0.0, total_num_instances = 0.0f;
  for (int n = 0; n < (int)nodes.size(); n++)
  {

    if (indices_of_examples_to_use.empty())
    {
      for (int m = 0; m < nodes[n]->V.size(); m++)
      {
        if (nodes[n]->V[m] == FLT_MAX)
          continue;
        else
        {
          rec_error += fabs(nodes[n]->V[m] - nodes[n]->q_mean[m]); // even for binary, do not set to 0/1
          total_num_instances++;
        }
      } // end of loop over training examples
    } // end of if statement
    else
    {
      for (int m = 0; m < indices_of_examples_to_use.size(); m++)
      {
        if (nodes[n]->Vb(m) == FLT_MAX)
          continue;
        else
        {
          rec_error += fabs(nodes[n]->Vb(m) - nodes[n]->q_mean[m]); // even for binary, do not set to 0/1
          total_num_instances++;
        }
      } // end of loop over training examples
    } // end of else statement

  } // end of loop over nodes
	return rec_error / total_num_instances;
}

float Layer::measureReconstructionError(int m)
{
	float rec_error = 0.0, total_num_instances = 0.0f;
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		if ( nodes[n]->V[m] == FLT_MAX)
			continue;
		else
		{
			rec_error += fabs( nodes[n]->V[m] - nodes[n]->q_mean[m] ); // even for binary, do not set to 0/1
			total_num_instances++;
		}
	}
	return rec_error / total_num_instances;
}

SVECTORf Layer::measureEnergy(bool check_out_of_range_values)
{
	SVECTORf uprob = nodes[0]->measureEnergy();
	for (int n = 1; n < (int)nodes.size(); n++)
		uprob += nodes[n]->measureEnergy();

  if (check_out_of_range_values)
  {
    for (int n = 0; n < (int)nodes.size(); n++)
    {
      if (nodes[n]->trimmed)
        uprob.array() -= log(EPSILONf); // energy increased
    }
  }

	return uprob;
}

// PARALLELIZED
void Layer::doInference()
{
	if (is_observed)
		return;

#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
		nodes[n]->doInference();

	is_ready_to_transmit = true;
}

// PARALLELIZED
void Layer::updateExpectations(phase_type phase)
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->updateExpectations(phase);
	}
}

// PARALLELIZED
void Layer::updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight )
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->updateParameters(number_of_training_examples, learning_rate, momentum, reg_type, reg_weight);
	}
}

// PARALLELIZED
void Layer::scaleTrainingData(bool training_data_scaling_already_done)
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->scaleTrainingData(training_data_scaling_already_done);
	}
}

// PARALLELIZED
void Layer::rescale()
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->rescale();
	}
}

// PARALLELIZED
void Layer::unscale()
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->unscale();
	}
}

// PARALLELIZED
void Layer::saveWeights()
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->saveWeights();
	}
}

// PARALLELIZED
void Layer::copyParameters(Layer *source_layer)
{
	if ( source_layer == NULL || source_layer->nodes.size() != nodes.size() || source_layer->type != type )
	{
		std::cerr << "Layer::copyParameters internal error: cannot copy parameters from source layer to target layer, since they are incompatible" << std::endl;
		exit(-1);
	}
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->copyParameters( source_layer->nodes[n] );
	}
}


// PARALLELIZED
void Layer::copyBias(Layer *source_layer, int bias_id)
{
	if ( source_layer == NULL || source_layer->nodes.size() != nodes.size() || source_layer->type != type )
	{
		std::cerr << "Layer::copyBias internal error: cannot copy parameters from source layer to target layer, since they are incompatible" << std::endl;
		exit(-1);
	}
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->copyBias( source_layer->nodes[n], bias_id );
	}
}



// NOT PARALLELIZED [too tittle work]
void Layer::lockParameters()
{
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->lock_parameters = true;
	}
}

// NOT PARALLELIZED [too tittle work]
void Layer::unlockParameters()
{
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->lock_parameters = false;
	}
}


// PARALLELIZED
void Layer::updatePriors()
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->updatePriors();
	}
}


// PARALLELIZED
void Layer::saveEdgeWeights(bool clear)
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->saveEdgeWeights(clear);
	}
}


// PARALLELIZED
void Layer::restoreSavedWeights()
{
#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->restoreSavedWeights();
	}
}


// PARALLELIZED
void Layer::initMarginals(int num_data)
{
	if (is_observed)
		return;

	is_ready_to_transmit = false;

#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->initMarginals(num_data);
	}
}

// DO NOT PARALLELIZE - sampling here
void Layer::sample(RAND_GEN& rng)
{
	is_ready_to_transmit = true;

	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->sample(rng);
	}
}


// DO NOT PARALLELIZE - sampling here
void Layer::condSample(RAND_GEN& rng)
{
	is_ready_to_transmit = true;

	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->condSample(rng);
	}
}

// DO NOT PARALLELIZE - sampling here
void BinaryLayer::sampleAndDiscretize(RAND_GEN& rng)
{
  is_ready_to_transmit = true;

  for (int n = 0; n < (int)nodes.size(); n++)
  {
    ((BinaryNode*)nodes[n])->sampleAndDiscretize(rng);
  }
}

// PARALLELIZED
void Layer::setObservations( const std::vector<float> & values, bool rescale_value )
{
	is_observed = true;
	is_ready_to_transmit = true;

#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->setObservation( values[n], rescale_value );
	}		
}

// PARALLELIZED
void Layer::setObservationsFromTrainingExamples(bool use_dropout, const std::vector<int>& indices_of_examples_to_use)
{ 
	is_observed = true;
	is_ready_to_transmit = true;

  int k;
  int num_examples_to_use;
  SVECTORf rand_example_selection;
  SVECTORf invalid_values;

#pragma omp parallel for private(k, num_examples_to_use, rand_example_selection, invalid_values)
  for (int n = 0; n < (int)nodes.size(); n++)
  {
    if (indices_of_examples_to_use.empty())
    {
      num_examples_to_use = (int)nodes[n]->V.size();
      nodes[n]->Vb = nodes[n]->V;

      if (use_dropout)
      {
        invalid_values = SVECTORf(num_examples_to_use);
        invalid_values.fill(FLT_MAX);
        rand_example_selection = SVECTORf::Random(num_examples_to_use); // returns -1...1
        nodes[n]->Vb = (rand_example_selection.array() > -0.9f).select(nodes[n]->Vb, invalid_values);
      }

      nodes[n]->setObservation(nodes[n]->Vb);
    }
    else
    {
      num_examples_to_use = (int)indices_of_examples_to_use.size();
      nodes[n]->Vb.resize(num_examples_to_use);
      for (k = 0; k < num_examples_to_use; k++)
        nodes[n]->Vb(k) = nodes[n]->V(indices_of_examples_to_use[k]);

      if (use_dropout)
      {
        invalid_values = SVECTORf(num_examples_to_use);
        invalid_values.fill(FLT_MAX);
        rand_example_selection = SVECTORf::Random(num_examples_to_use); // returns -1...1
        nodes[n]->Vb = (rand_example_selection.array() > -0.9f).select(nodes[n]->Vb, invalid_values);
      }

      nodes[n]->setObservation(nodes[n]->Vb);
    }
  }
};

// PARALLELIZED
void Layer::setObservationsFromCurrentMeans() 
{ 
	is_observed = true;
	is_ready_to_transmit = true;

#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->setObservation( nodes[n]->q_mean );
	}		
};

// PARALLELIZED
void Layer::clearObservations()
{
	is_observed = false;
	is_ready_to_transmit = false;

#pragma omp parallel for
	for (int n = 0; n < (int)nodes.size(); n++)
	{
		nodes[n]->clearObservation();
	}		
}


// PARALLELIZED
void Layer::init(bool do_not_init_parameters)
{
	// DO NOT PARALLELIZE THIS LOOP, I SUSPECT THERE IS A RACE CONDITION IN rand
	for (int n = 0; n <(int) nodes.size(); n++)
	{
		nodes[n]->init(do_not_init_parameters);
	}

	if ( !do_not_init_parameters )
	{
		smoothParameters(10);
	}
}

// PARALLELIZED
void Layer::smoothParameters(int number_of_iterations)
{
		//if (id==1) { exportEdgeWeightsIntoTempFile(); system("pause"); }
		for (int it = 0; it < number_of_iterations; it++)
		{
			saveEdgeWeights(false);
#pragma omp parallel for
			for (int n = 0; n < (int)nodes.size(); n++)
			{
				nodes[n]->smoothParameters();
			}
		}
		saveEdgeWeights(true);
		//if (id==1) { exportEdgeWeightsIntoTempFile(); system("pause"); }
}






// DO NOT PARALLELIZE - used only for debugging
void Layer::exportEdgeWeightsIntoTempFile()
{	
	Layer *visible_layer = nodes[0]->owned_edges.begin()->first->layer;

	for (size_t n = 0; n < nodes.size(); n++)
	{
		ostringstream ss;
		ss <<  "tmp_edges_" << n << ".txt";
		std::cout << "Exporting edge weights in " << ss.str() << std::endl;
		ofstream tmp_edges_file( ss.str() );
		for( size_t v = 0; v < visible_layer->nodes.size(); v++ )
		{
			boost::unordered_map<DLNode*, DLEdge*>::const_iterator it = nodes[n]->owned_edges.find( visible_layer->nodes[v] );
			// let it crash if it does not exist
			if ( it->second->type == GAUSSIAN_GAUSSIAN )
			{
				tmp_edges_file << ((GaussianGaussianDLEdge*)it->second)->w << std::endl;
			}
			else if ( it->second->type == BETA_GAUSSIAN )
			{
				tmp_edges_file << ((BetaGaussianDLEdge*)it->second)->wp << " ";
				tmp_edges_file << ((BetaGaussianDLEdge*)it->second)->wn << std::endl;
			}
			else if ( it->second->type == BETA_BETA )
			{
				tmp_edges_file << ((BetaBetaDLEdge*)it->second)->w << " ";
				tmp_edges_file << ((BetaBetaDLEdge*)it->second)->q << " ";
				tmp_edges_file << ((BetaBetaDLEdge*)it->second)->s << " ";
				tmp_edges_file << ((BetaBetaDLEdge*)it->second)->t << std::endl;
			}
		}
		tmp_edges_file.close();
	}
}

GaussianLayer::GaussianLayer(int _num_nodes, bool _is_hidden, int _id, Layer *_above_layer, Layer *_below_layer): 
	Layer(_num_nodes, _is_hidden, GAUSSIAN, _id, _above_layer, _below_layer) 
{
	if (_id == -1 || _num_nodes == 0)
		return;
	if (_is_hidden)
		std::cout << "=> Creating a hidden layer of " << _num_nodes << " Gaussian nodes (id=" << _id << ")..." << std::endl;
	else
		std::cout << "=> Creating a visible layer of " << _num_nodes << " Gaussian nodes (id=" << _id << ")..." << std::endl;

	nodes.resize( _num_nodes );
	for (int n = 0; n < _num_nodes; n++)
	{
		nodes[n] = new GaussianNode(this, (long)n);
	}
}

BetaLayer::BetaLayer(int _num_nodes, bool _is_double_beta, bool _is_hidden, int _id, Layer *_above_layer, Layer *_below_layer) :
	Layer(_num_nodes, _is_hidden, BETA, _id, _above_layer, _below_layer) 
{
	if (_id == -1 || _num_nodes == 0)
		return;
	if (_is_hidden)
    if (_is_double_beta)
		  std::cout << "=> Creating a hidden layer of " << _num_nodes << " double Beta nodes (id=" << _id << ")..." << std::endl;
    else
      std::cout << "=> Creating a hidden layer of " << _num_nodes << " Beta nodes (id=" << _id << ")..." << std::endl;
	else
    if (_is_double_beta)
		  std::cout << "=> Creating a visible layer of " << _num_nodes << " double Beta nodes (id=" << _id << ")..." << std::endl;
    else
      std::cout << "=> Creating a visible layer of " << _num_nodes << " Beta nodes (id=" << _id << ")..." << std::endl;

	nodes.resize( _num_nodes );
	for (int n = 0; n < _num_nodes; n++)
	{
		nodes[n] = new BetaNode(this, (long)n, _is_double_beta);
	}
}

BinaryLayer::BinaryLayer(int _num_nodes, bool _is_hidden, int _id, Layer *_above_layer, Layer *_below_layer): 
	Layer(_num_nodes, _is_hidden, BINARY, _id, _above_layer, _below_layer) 
{
	if (_id == -1 || _num_nodes == 0)
		return;
	if (_is_hidden)
		std::cout << "=> Creating a hidden layer of " << _num_nodes << " binary nodes (id=" << _id << ")..." << std::endl;
	else
		std::cout << "=> Creating a visible layer of " << _num_nodes << " binary nodes (id=" << _id << ")..." << std::endl;

	nodes.resize( _num_nodes );
	for (int n = 0; n < _num_nodes; n++)
	{
		nodes[n] = new BinaryNode(this, (long)n);
	}
}

AttributeLayer::AttributeLayer(int _num_nodes,  int _num_training_examples, int _id ): Layer(_num_nodes, false, DETERMINICTIC, _id) 
{
	if (_id == -1 || _num_nodes == 0)
		return;
	std::cout << "=> Creating an attribute layer of " << _num_nodes << " variables (id=" << _id << ")..." << std::endl;

	attribute_mapping_type = "";
	A.resize( _num_training_examples, _num_nodes );
	A_props.resize(A.cols());
}


void AttributeLayer::scaleTrainingData(bool training_data_scaling_already_done)
{
	for (int n = 0; n < A.cols(); n++)
	{
		SVECTORf V = A.col(n);		
		if ( !training_data_scaling_already_done )
			A_props[n].getBasicRandomVariableProperties( removeElements(V, FLT_MAX) );
		//A_props[n].standardize( v );
		//A.col(n) = v;
		float dscale = 2.0f * (A_props[n].max - A_props[n].min) + EPSILONf;
		A.col(n) = (V.array() != FLT_MAX).select( (V.array() - A_props[n].min + dscale / 4.0f) / dscale, V); // scale then in the [.25 .75] interval
	}
}

void AttributeLayer::setObservations(  const std::vector<float> & values, bool rescale_value )
{
	is_observed = true;
	AO = convertStdVectorToEigenVector(values);
	if ( rescale_value )
		rescale();
}

void AttributeLayer::clearObservations(  )
{
	is_observed = false;
	AO.resize(0);
}

void AttributeLayer::connect(Layer *layer)
{
	std::cout << "=> Connecting attribute layer to layer " << layer->id << std::endl;
	neighboring_layers.push_back(layer);
	size_t total_num_neighboring_nodes = 0;
	for (size_t l = 0; l < neighboring_layers.size(); l++)
		total_num_neighboring_nodes += neighboring_layers[l]->nodes.size();

	X.resize( A.rows(), total_num_neighboring_nodes );
}

void AttributeLayer::updateTrainingData()
{
	int i = 0;
	for (size_t l = 0; l < neighboring_layers.size(); l++)
	{
		for (size_t n = 0; n < neighboring_layers[l]->nodes.size(); n++)
		{
			X.col(i++) = neighboring_layers[l]->nodes[n]->q_mean;
		}
	}
}

void AttributeLayer::rescale()
{
	for (int n = 0; n < AO.size(); n++)
	{
		if (!A_props[n].valid)
		{
			std::cerr << "Internal error: AttributeLayer::rescale was called before mean/std of attributes are computed." << std::endl;
			exit(-1);
		}
		//A_props[n].standardize( AO(n) );
		float dscale = 2.0f * (A_props[n].max - A_props[n].min) + EPSILONf;
		AO(n) = (AO(n) - A_props[n].min + dscale / 4.0f) / dscale; // scale then in the [.25 .75] interval
	}
}

void AttributeLayer::unscale()
{
	// not needed
}


void AttributeLayer::updateParameters(const string& _attribute_mapping_type)
{
	attribute_mapping_type = _attribute_mapping_type;
	SMATRIXf AC = removeRows(A, FLT_MAX);
	SMATRIXf XC = removeRowsAccordingToOtherMatrix(X, A, FLT_MAX);

	if ( neighboring_layers[0]->type == BINARY )
	{
		//XC = round( XC ); // Should we binarize trainig input? Seems to work even without binarizing it.
		lr = LogisticRegression(AC, XC, false);
		lr.train();
	}
	else if ( attribute_mapping_type == "linear_regression" )
	{
		//SMATRIXf AC_bias( AC.rows(), 2*AC.cols()+1);
		//AC_bias << AC.array().log(), (1.0f-AC.array()).log(), SVECTORf::Ones(AC.rows(), 1);
		//SMATRIXf AC_bias( AC.rows(), AC.cols()+1);
		//AC_bias << AC.array().log(), SVECTORf::Ones(AC.rows(), 1);
		SMATRIXf AC_bias( AC.rows(), AC.cols()+1 );
		AC_bias << AC, SVECTORf::Ones( AC.rows(), 1);
		bp.W = AC_bias.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve( XC );
		std::cout << "[error: " << ( AC_bias * bp.W  - XC ).cwiseAbs().sum() / float(XC.size()) << "]" << std::endl;
	}
	else if ( attribute_mapping_type == "backpropagation" )
	{
		//SNL::Options options;
		//options.set("learning_epochs", 1000);
		//bp = BackPropagation(AC, XC, false, options);
		bp = BackPropagation(AC, XC, false);
		bp.train();
	}
	else
	{
		std::cerr << "Internal error: AttributeLayer::updateParameters: specified method " << attribute_mapping_type
			<< " to map attributes to hidden layers is not supported." << std::endl;
		exit(-1);
	}
}

void AttributeLayer::doInference()
{
	SVECTORf res;

	if ( neighboring_layers[0]->type == BINARY )
	{
		res = lr.predict(AO);
	}
	else if ( attribute_mapping_type == "linear_regression" )
	{
		//SVECTORf AO_bias(2*AO.size()+1);
		//AO_bias << AO.array().log(), (1.0f-AO.array()).log(), 1.0f;
		//SVECTORf AO_bias(AO.size()+1);
		//AO_bias << AO.array().log(), 1.0f;
		SVECTORf AO_bias(AO.size()+1);
		AO_bias << AO, 1;
		res = bp.W.transpose() * AO_bias;		
	}
	else if ( attribute_mapping_type == "backpropagation" )
	{
		res = bp.predict(AO);
	}
	else
	{
		std::cerr << "Internal error: AttributeLayer::doInference: cannot apply inference on this layer since it has not been trained with " << attribute_mapping_type << std::endl;
		exit(-1);
	}

	int i = 0;
	for (size_t l = 0; l < neighboring_layers.size(); l++)
		for (size_t n = 0; n < neighboring_layers[l]->nodes.size(); n++)
			neighboring_layers[l]->nodes[n]->setObservation( res(i++) );
}




////////////////////////////////////////////////
///////////////////////////////////////////////
////////////// DENSE LAYER ///////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

DenseDataLayer::DenseDataLayer(int _num_nodes, int _num_training_examples, int _id): Layer(_num_nodes, false, DETERMINICTIC, _id) 
{
	if (_id == -1 || _num_nodes == 0)
		return;
	std::cout << "=> Creating a dense point representation layer of " << _num_nodes << " variables (id=" << _id << ")..." << std::endl;

	dense_mapping_type = "";
	is_observed = true;
	Y.resize( _num_training_examples, _num_nodes );
	D_props.resize( _num_nodes );
	sparse_to_dense_node_connections.resize( _num_nodes );
	num_neighbors_to_consider = 0;
}


void DenseDataLayer::rescale()
{
// not needed
}

void DenseDataLayer::unscale()
{
	for (int n = 0; n < out.size(); n++)
	{
		if (!D_props[n].valid)
		{
			std::cerr << "Internal error: DenseDataLayer::unscale was called before mean/std of dense layer nodes are computed." << std::endl;
			exit(-1);
		}
		float dscale = 2.0f * (D_props[n].max - D_props[n].min) + EPSILONf;
		if ( !isinv(out(n)) )
			out(n) = out(n) * dscale + D_props[n].min - dscale / 4.0f;
	}
}

void DenseDataLayer::clearObservations( )
{
	// not needed (always observed)
}


void DenseDataLayer::setObservations( const std::vector<float> & values, bool rescale_value )
{
	// not needed (always observed)
}


void DenseDataLayer::scaleTrainingData(bool training_data_scaling_already_done)
{
	for (int n = 0; n < Y.cols(); n++)
	{
		SVECTORf V = Y.col(n);
		if ( !training_data_scaling_already_done )
			D_props[n].getBasicRandomVariableProperties( removeElements(V, FLT_MAX) );
		float dscale = 2.0f * (D_props[n].max - D_props[n].min) + EPSILONf;
		Y.col(n) = (V.array() != FLT_MAX).select( (V.array() - D_props[n].min + dscale / 4.0f) / dscale, V); // scale then in the [.25 .75] interval
	}
}


void DenseDataLayer::updateParameters(const string& _dense_mapping_type, size_t _num_neighbors_to_consider)
{
	dense_mapping_type = _dense_mapping_type;
	num_neighbors_to_consider = _num_neighbors_to_consider;
	bps.resize( Y.cols() );
	
	SMATRIXf X, XC_bias, XC, YT;
	SVECTORf YC;
	int m, j;

#pragma omp parallel for private(X, XC_bias, XC, YT, YC, m, j)
	for (int i = 0; i < Y.cols(); i++)
	{
		X.resize( Y.rows(), std::min(num_neighbors_to_consider, sparse_to_dense_node_connections[i].size()) );

		for (m = 0; m < Y.rows(); m++)
		{
			for (j = 0; j < (int)std::min(num_neighbors_to_consider, sparse_to_dense_node_connections[i].size()); j++)
			{
				X(m, j) = sparse_to_dense_node_connections[i][j]->V[m];
			}
		}

				
		YT = Y.col(i);
		XC = removeRowsAccordingToOtherMatrix(X, YT, FLT_MAX);
		YC = Y.col(i);
		YC = removeElements(YC, FLT_MAX);

		if ( dense_mapping_type == "linear_regression" )
		{
			//XC_bias.resize( XC.rows(), 2*XC.cols()+1);
			//XC_bias << XC.array().log(), (1.0f-XC.array()).log(), SVECTORf::Ones(XC.rows(), 1);
			//XC_bias.resize( XC.rows(), XC.cols()+1);
			//XC_bias << XC.array().log(),  SVECTORf::Ones(XC.rows(), 1);
			XC_bias.resize( XC.rows(), XC.cols()+1);
			XC_bias << XC, SVECTORf::Ones(XC.rows(), 1);			
			bps[i].W = XC_bias.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve( YC );
			//bps[i].W = (XC_bias.transpose() * XC_bias).inverse() * XC_bias.transpose() * Y.col(i);
			//std::cout << std::endl << "=>=> Training model for dense layer node " << i << " [error: " << ( XC_bias * bps[i].W  - Y.col(i) ).cwiseAbs().sum() / float(Y.size()) << "]";
			std::cout << " [" << i << " - error: " << ( XC_bias * bps[i].W  - YC ).cwiseAbs().sum() / float(YC.size()) << "] ";
		}
		else if ( dense_mapping_type == "backpropagation" )
		{
			SNL::Options options;
			options.set("learning_epochs", 1000);
			bps[i] = BackPropagation(XC, YC, true, options);
			std::cout << " [" << i << " - error: " << bps[i].train() << "] ";
		}
		else
		{
			std::cerr << "Internal error: DenseDataLayer::updateParameters: specified method " << dense_mapping_type
				<< " to map the dense to the visible layer is not supported." << std::endl;
			exit(-1);
		}
	}
}

void DenseDataLayer::doInference()
{
	out.resize( bps.size() );
	int j;
	SVECTORf X;
	SVECTORf X_bias;
	bool is_invalid = false;

#pragma omp parallel for private(j, X, X_bias, is_invalid)
	for (int i = 0; i < out.size(); i++)
	{
		is_invalid = false;
		X.resize( std::min(num_neighbors_to_consider, sparse_to_dense_node_connections[i].size())  );
		for (j = 0; j < (int)std::min(num_neighbors_to_consider, sparse_to_dense_node_connections[i].size()); j++)
		{
			X(j) = sparse_to_dense_node_connections[i][j]->q_mean(0);
			if ( isinv(X(j)) || (X(j) == sparse_to_dense_node_connections[i][j]->log_q_mean(0)) )
				is_invalid = true;
		}

		if (is_invalid)
		{
			out(i) = FLT_MAX;
			continue;
		}

		if ( dense_mapping_type == "linear_regression" )
		{
			//X_bias.resize( 2*X.size()+1);
			//X_bias << X.array().log(), (1.0f-X.array()).log(), 1.0f;
			//X_bias.resize( X.size()+1);
			//X_bias << X.array().log(), 1.0f;
			X_bias.resize( X.size()+1 );
			X_bias << X, 1.0f;
			out(i) = ( bps[i].W.transpose() * X_bias ).value();
		}
		else if ( dense_mapping_type == "backpropagation" )
		{
			out(i) = bps[i].predict(X).value();
		}
		else
		{
			std::cerr << "Internal error: DenseDataLayer::doInference: cannot apply inference on this layer since it has not been trained with " << dense_mapping_type << std::endl;
			exit(-1);
		}		
	}
}




}
}

