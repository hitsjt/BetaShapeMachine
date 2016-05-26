#ifndef __DL13_LAYER_HPP
#define __DL13_LAYER_HPP

#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_TrainingData.hpp"
#include "DL13_EigenAddons.hpp"
#include "DL13_Node.hpp"
#include "DL13_BackPropagation.hpp"
#include "DL13_Logistic_Regression.hpp"


namespace SNL {;
namespace DL13 {;

class DLNode;
class BetaNode;
class GaussianNode;
class BinaryNode;

class SNL_DL13_API Layer
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar.template register_type<BetaNode>();
		ar.template register_type<GaussianNode>();
		ar.template register_type<BinaryNode>();
		ar & nodes;
		ar & id;
		ar & is_hidden;
		ar & type;
		ar & is_observed;
		ar & above_layer;
		ar & below_layer;
	}
public:
	vector<DLNode*> nodes;
	int id;
	bool is_hidden;
	variable_type type;
	bool is_observed;
	bool is_ready_to_transmit;
	Layer *above_layer;
	Layer *below_layer;	

	Layer(int _num_nodes = 0, bool _is_hidden = false, variable_type _type = INVALID_VARIABLE, 
				int _id = -1, Layer *_above_layer = NULL, Layer *_below_layer = NULL): 
				id(_id), is_hidden(_is_hidden), type(_type),  
				is_observed(false), is_ready_to_transmit(false), above_layer(_above_layer), below_layer(_below_layer) { };

  float measureReconstructionError(const std::vector<int>& indices_of_examples_to_use = std::vector<int>());
	float measureReconstructionError(int m);
  SVECTORf measureEnergy(bool check_out_of_range_values = false);
	void updateExpectations(phase_type phase);
	void updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight );
	void init(bool do_not_init_parameters);
	void smoothParameters(int number_of_iterations);
	void initMarginals(int num_data);
	void sample(RAND_GEN& rng);
	void condSample(RAND_GEN& rng);
	void saveWeights();
	void copyParameters(Layer *source_layer);
	void copyBias(Layer *source_layer, int bias_id);
	void lockParameters();
	void unlockParameters();
	void updatePriors();
	void saveEdgeWeights(bool);
	void restoreSavedWeights();
  void setObservationsFromTrainingExamples(bool use_dropout = false, const std::vector<int>& indices_of_examples_to_use = std::vector<int>() );
	void setObservationsFromCurrentMeans();
	void exportEdgeWeightsIntoTempFile();
	virtual ~Layer();

	virtual void doInference();
	virtual void scaleTrainingData(bool training_data_scaling_already_done);
	virtual void rescale();
	virtual void unscale();
	virtual void setObservations(  const std::vector<float> & values, bool rescale_value = false );
	virtual void clearObservations( );

}; // class Layer


class SNL_DL13_API GaussianLayer : public Layer
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Layer>(*this);
	}
public:
	GaussianLayer(int _num_nodes = 0, bool _is_hidden = false, int _id = -1, Layer *_above_layer = NULL, Layer *_below_layer = NULL);
	~GaussianLayer() { }
	void doInference() { Layer::doInference(); }
	void scaleTrainingData(bool training_data_scaling_already_done) { Layer::scaleTrainingData(training_data_scaling_already_done); }
	void rescale() { Layer::rescale(); };
	void unscale() { Layer::unscale(); };
	void setObservations(  const std::vector<float> & values, bool rescale_value = false )  { Layer::setObservations(values, rescale_value); };
	void clearObservations( ) { Layer::clearObservations(); };
}; // class GaussianLayer




class SNL_DL13_API BetaLayer : public Layer
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Layer>(*this);
	}
public:
	BetaLayer(int _num_nodes = 0, bool _is_double_beta = false, bool _is_hidden = false, int _id = -1, Layer *_above_layer = NULL, Layer *_below_layer = NULL);
	~BetaLayer() { }
	void doInference() { Layer::doInference(); }
	void scaleTrainingData(bool training_data_scaling_already_done) { Layer::scaleTrainingData(training_data_scaling_already_done); }
	void rescale() { Layer::rescale(); };
	void unscale() { Layer::unscale(); };
	void setObservations(  const std::vector<float> & values, bool rescale_value = false )  { Layer::setObservations(values, rescale_value); };
	void clearObservations( ) { Layer::clearObservations(); };
}; // class BetaLayer


class SNL_DL13_API BinaryLayer : public Layer
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<Layer>(*this);
	}
public:
	BinaryLayer(int _num_nodes = 0, bool _is_hidden = false, int _id = -1, Layer *_above_layer = NULL, Layer *_below_layer = NULL);
	~BinaryLayer() { }
	void doInference() { Layer::doInference(); }
	void scaleTrainingData(bool training_data_scaling_already_done) { Layer::scaleTrainingData(training_data_scaling_already_done); }
	void rescale() { Layer::rescale(); };
	void unscale() { Layer::unscale(); };
  void sampleAndDiscretize(RAND_GEN& rng);
	void setObservations(  const std::vector<float> & values, bool rescale_value = false )  { Layer::setObservations(values, rescale_value); };
	void clearObservations( ) { Layer::clearObservations(); };
}; // class BetaLayer

class SNL_DL13_API AttributeLayer : public DL13::Layer
{
private:	
	vector<Layer*> neighboring_layers;
	string attribute_mapping_type;
	vector< RandomVariableProperties<float> > A_props;
	BackPropagation bp;
	LogisticRegression lr;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		vector< vector< float > > _A;
		vector< vector< float > > _X;

		if ( Archive::is_saving::value )
		{
			_A = convertEigenMatrixToStdVectorVector(A);
			_X = convertEigenMatrixToStdVectorVector(X);
		}
		
		ar & neighboring_layers;
		ar & attribute_mapping_type;
		ar & _A;
		ar & _X;
		ar & A_props;
		ar & bp;
		ar & lr;
		ar & boost::serialization::base_object<Layer>(*this);

		if ( !Archive::is_saving::value )
		{
			A = convertStdVectorVectorToEigenMatrix(_A);
			X = convertStdVectorVectorToEigenMatrix(_X);
		}
	}
public:
	SMATRIXf A; // training data #examples x #number of attributes for A
	SMATRIXf X; // training data #examples x #number of hidden nodes connected to this layer	
	SVECTORf AO; // observed attribute vector

	void connect(Layer *l);
	void updateTrainingData();
	void updateParameters(const string& _attribute_mapping_type);
	AttributeLayer(int _num_nodes = 0, int _num_training_examples = 0, int _id = -1);
	~AttributeLayer() { }

	void doInference();
	void scaleTrainingData(bool training_data_scaling_already_done);
	void rescale();
	void unscale();
	void setObservations(  const std::vector<float> & values, bool rescale_value = false );
	void clearObservations() ;

}; // class AttributeLayer




class SNL_DL13_API DenseDataLayer : public DL13::Layer
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		vector< vector< float > > _Y;

		if ( Archive::is_saving::value )
		{
			_Y = convertEigenMatrixToStdVectorVector(Y);
		}

		ar & boost::serialization::base_object<Layer>(*this);
		ar & D_props;
		ar & dense_mapping_type;
		ar & num_neighbors_to_consider;
		ar & bps;
		ar & sparse_to_dense_node_connections;		
		ar & _Y;

		if ( !Archive::is_saving::value )
		{
			Y = convertStdVectorVectorToEigenMatrix(_Y);
		}

	}

	vector< RandomVariableProperties<float> > D_props;
	string dense_mapping_type;	
public:
	size_t num_neighbors_to_consider;
	vector<BackPropagation> bps; // stored model
	vector< vector<DLNode*> > sparse_to_dense_node_connections;
	SMATRIXf Y; // training data output: #examples x #number of nodes
	SVECTORf out; // output: #examples x #number of nodes

	void updateParameters(const string& _dense_mapping_type, size_t num_neighbors_to_consider);
	DenseDataLayer(int _num_nodes = 0, int _num_training_examples = 0, int _id = -1);
	~DenseDataLayer() { }

	void doInference();
	void scaleTrainingData(bool training_data_scaling_already_done);
	void rescale();
	void unscale();
	void setObservations(  const std::vector<float> & values, bool rescale_value = false );
	void clearObservations();
}; // class DenseDataLayer


}
}

#endif