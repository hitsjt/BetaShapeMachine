#ifndef __DL13_BOLTZMANNMACHINE_HPP
#define __DL13_BOLTZMANNMACHINE_HPP

#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_TrainingData.hpp"
#include "DL13_EigenAddons.hpp"
#include "DL13_Node.hpp"
#include "DL13_Layer.hpp"

namespace SNL {;
namespace DL13 {;

class SNL_DL13_API BoltzmannMachine : public SNL::Network
{
private:
	RAND_GEN rng;

	string name;
	bool dopretrain;	
	int number_of_training_examples;
	int number_of_training_examples_attributes;
	int num_input_dimensions;
	int num_attributes;
	int num_dense_input_dimensions;
	int total_number_of_nodes_created;
	int total_number_of_edges_created;
	bool connectivity_is_set;
	bool init_from_attributes;		
	vector<float> hidden_layer1_part_cum_distribution;
	vector< vector< unsigned short > > nearest_sparse_points_for_each_dense_point;

	int num_mf_iterations;  // no need to save this, internal parameter
	int num_sampling_iterations; // no need to save this, internal parameter
	short max_part_id; // no need to save this, internal parameter
	bool init_marginals; // no need to save this, internal parameter
	bool enable_sampling_with_inference; // no need to save this, internal parameter
	bool training_data_scaling_already_done; // no need to save this, internal parameter

	void saveWeights();
	void restoreSavedWeights();
	void initStructure( bool do_not_set_connectivity = false );
	void clearLayerObservations(Layer *layer);
	void setLayerObservations(Layer *layer, const std::vector<float> & values);	

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar.template register_type<AttributeLayer>();
		ar.template register_type<GaussianLayer>();
		ar.template register_type<BetaLayer>();
		ar.template register_type<BinaryLayer>();
		ar.template register_type<DenseDataLayer>();		

		ar & name;
		ar & dopretrain;
		ar & number_of_training_examples;
		ar & number_of_training_examples_attributes;
		ar & num_input_dimensions;
		ar & num_attributes;
		ar & num_dense_input_dimensions;
		ar & total_number_of_nodes_created;
		ar & total_number_of_edges_created;
		ar & connectivity_is_set;
		ar & init_from_attributes;
		ar & momentum;
		ar & learning_rate;
		ar & options;
		ar & layers;
		ar & alayer;
		ar & dlayer;
		ar & bm_pretrain;
		ar & hidden_layer1_part_cum_distribution;
		ar & nearest_sparse_points_for_each_dense_point;
	}
public:
	SNL::Options	 options;
	float momentum, learning_rate;
	vector<Layer*> layers;
	AttributeLayer *alayer;
	DenseDataLayer *dlayer;
	BoltzmannMachine *bm_pretrain;
	int number_of_observations;

	BoltzmannMachine(const string& _name = "unnamed", const SNL::Options &_options = SNL::Options());
	~BoltzmannMachine();
	void init(SNL::Options const & _options = SNL::Options() );
	void pretrain(SNL::Options const & _options = SNL::Options() );
	void train(SNL::Options const & _options = SNL::Options() );
  void no_stochastic_train(SNL::Options const & _options = SNL::Options());
	void trainDenseDataLayer(SNL::Options const & _options = SNL::Options() );
	void trainAttributeLayer(SNL::Options const & _options = SNL::Options() );
	void setObservation(SNL::Node* node, const std::vector<double> & value);
	void setObservation(SNL::Node* node, float value);
	void clearObservation(SNL::Node* node);
	void clearAllObservations();
	void doInferenceWithoutInit(int layer_id = -1); 
	void doInference(); 
	void doInference( Layer *layer ); 
  SVECTORf measureEnergy(bool check_out_of_range_values = false);
	void sample(); 
	void load(std::string const & in_path);
	void save(std::string const & out_path) const;
	void printStats(std::ostream & os = std::cout) { };
	void doAttribInference();
	void doDenseInference();
	void reconstructTrainingExample(int m);
	void setTrainingData(const TrainingData& training_data);
	void setTrainingData(const Layer* source);
	void setupPretraining(const TrainingData& training_data);
	void clearVisibleLayerObservations(); 
	void clearAttributeLayerObservations();
	void setVisibleLayerObservations(const std::vector<float> & values);
	void setAttributeLayerObservations(const std::vector<float> & values);
	void setMFiterations(int iter);
	float getOutputVisibleNodeValue(int node_id);
	short getOutputVisibleNodePartID(int node_id);
	float getOutputDenseVisibleNodeValue(int node_id);
	short getOutputDenseVisibleNodePartID(int node_id);
	SNL::Node* getVisibleNode(int node_id );
	int getNumberOfUnits();
	int getNumberOfVisibleUnits();
	int getNumberOfDenseVisibleUnits();
}; // class BoltzmannMachine


////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

} // namespace DL13
} // namespace SNL

#endif
