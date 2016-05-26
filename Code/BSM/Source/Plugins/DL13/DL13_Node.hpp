#ifndef __DL13_NODE_HPP
#define __DL13_NODE_HPP

#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_TrainingData.hpp"
#include "DL13_EigenAddons.hpp"
#include "DL13_Layer.hpp"

namespace SNL {;
namespace DL13 {;

class Layer;
class DLNode;


/////////////// class DLEdge ////////////////
class SNL_DL13_API DLEdge
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & type;
		ar & source;
	}
public:
	DLNode *source;
	char type;
	DLEdge(char _type = INVALID_EDGE, DLNode *_source = NULL): source(_source), type(_type) { } 
	virtual ~DLEdge() { };
};




/////////////// class GaussianGaussianDLEdge ////////////////
class SNL_DL13_API GaussianGaussianDLEdge: public DLEdge
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		if ( Archive::is_saving::value && isinv(w) )
		{
			std::cerr << "Internal Error: GaussianGaussianDLEdge::serialize: an edge weight is invalid, cannot serialize" << std::endl;
			return;
		}
		ar & boost::serialization::base_object<DLEdge>(*this);
		ar & w;
	}
public:
	float w;
	float sav_w;
	float old_inc_w;
	float E_POS_w_mean, E_NEG_w_mean;

	GaussianGaussianDLEdge(DLNode *_source = NULL): DLEdge(GAUSSIAN_GAUSSIAN, _source), w(FLT_MAX), sav_w(FLT_MAX), old_inc_w(FLT_MAX), E_POS_w_mean(FLT_MAX), E_NEG_w_mean(FLT_MAX)  { };
};




/////////////// class BetaGaussianDLEdge ////////////////
class SNL_DL13_API BetaGaussianDLEdge: public DLEdge
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		if ( Archive::is_saving::value && ( isinv(wp) || isinv(wn) ) )
		{
			std::cerr << "Internal Error: BetaGaussianDLEdge::serialize: an edge weight is invalid, cannot serialize" << std::endl;
			return;
		}
		ar & boost::serialization::base_object<DLEdge>(*this);
		ar & wp;
		ar & wn;
	}	
public:
	float wp, wn;
	float sav_wp, sav_wn;
	float old_inc_wp, old_inc_wn;
	float E_POS_wp_mean, E_POS_wn_mean, E_NEG_wp_mean, E_NEG_wn_mean;

	BetaGaussianDLEdge(DLNode *_source = NULL): DLEdge(BETA_GAUSSIAN, _source), wp(FLT_MAX), wn(FLT_MAX), sav_wp(FLT_MAX), sav_wn(FLT_MAX), old_inc_wp(FLT_MAX), old_inc_wn(FLT_MAX), 
																							 E_POS_wp_mean(FLT_MAX), E_POS_wn_mean(FLT_MAX), E_NEG_wp_mean(FLT_MAX), E_NEG_wn_mean(FLT_MAX) { };
};



/////////////// class BetaBetaDLEdge ////////////////
class SNL_DL13_API BetaBetaDLEdge: public DLEdge
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		if ( Archive::is_saving::value && ( isinv(w) || isinv(q) || isinv(s) || isinv(t) ) )
		{
			std::cerr << "Internal Error: BetaBetaDLEdge::serialize: an edge weight is invalid - cannot serialize" << std::endl;
			return;
		}
		ar & boost::serialization::base_object<DLEdge>(*this);
		ar & w;
		ar & q;
		ar & s;
		ar & t;
	}	
public:
	float w, q, s, t;
	float sav_w, sav_q, sav_s, sav_t;
	float old_inc_w, old_inc_q, old_inc_s, old_inc_t;
	float E_POS_w_mean, E_POS_q_mean, E_POS_s_mean, E_POS_t_mean, E_NEG_w_mean, E_NEG_q_mean, E_NEG_s_mean, E_NEG_t_mean;

	BetaBetaDLEdge(DLNode *_source = NULL): DLEdge(BETA_BETA, _source), w(FLT_MAX), q(FLT_MAX), s(FLT_MAX), t(FLT_MAX), 
		                                   sav_w(FLT_MAX), sav_q(FLT_MAX), sav_s(FLT_MAX), sav_t(FLT_MAX), 
																			 old_inc_w(FLT_MAX), old_inc_q(FLT_MAX), old_inc_s(FLT_MAX), old_inc_t(FLT_MAX),
																			 E_POS_w_mean(FLT_MAX), E_POS_q_mean(FLT_MAX), E_POS_s_mean(FLT_MAX), E_POS_t_mean(FLT_MAX), 
																			 E_NEG_w_mean(FLT_MAX), E_NEG_q_mean(FLT_MAX), E_NEG_s_mean(FLT_MAX), E_NEG_t_mean(FLT_MAX) { };
};




/////////////// class BinaryBinaryDLEdge ////////////////
class SNL_DL13_API BinaryBinaryDLEdge: public DLEdge
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		if ( Archive::is_saving::value && isinv(w) )
		{
			std::cerr << "Internal Error: BinaryBinaryDLEdge::serialize: an edge weight is invalid, cannot serialize" << std::endl;
			return;
		}
		ar & boost::serialization::base_object<DLEdge>(*this);
		ar & w;
	}
public:
	float w;
	float sav_w;
	float old_inc_w;
	float E_POS_w_mean, E_NEG_w_mean;

	BinaryBinaryDLEdge(DLNode *_source = NULL): DLEdge(BINARY_BINARY, _source), w(FLT_MAX), sav_w(FLT_MAX), old_inc_w(FLT_MAX), E_POS_w_mean(FLT_MAX), E_NEG_w_mean(FLT_MAX)  { };
};



/////////////// class BinaryGaussianDLEdge ////////////////
class SNL_DL13_API BinaryGaussianDLEdge: public DLEdge
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		if ( Archive::is_saving::value && isinv(w) )
		{
			std::cerr << "Internal Error: BinaryGaussianDLEdge::serialize: an edge weight is invalid, cannot serialize" << std::endl;
			return;
		}
		ar & boost::serialization::base_object<DLEdge>(*this);
		ar & w;
	}
public:
	float w;
	float sav_w;
	float old_inc_w;
	float E_POS_w_mean, E_NEG_w_mean;

	BinaryGaussianDLEdge(DLNode *_source = NULL): DLEdge(BINARY_GAUSSIAN, _source), w(FLT_MAX), sav_w(FLT_MAX), old_inc_w(FLT_MAX), E_POS_w_mean(FLT_MAX), E_NEG_w_mean(FLT_MAX)  { };
};



/////////////// class BinaryBetaDLEdge ////////////////
class SNL_DL13_API BinaryBetaDLEdge: public DLEdge
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		if ( Archive::is_saving::value && ( isinv(wp) || isinv(wn) ) )
		{
			std::cerr << "Internal Error: BinaryBetaDLEdge::serialize: an edge weight is invalid, cannot serialize" << std::endl;
			return;
		}
		ar & boost::serialization::base_object<DLEdge>(*this);
		ar & wp;
		ar & wn;
	}	
public:
	float wp, wn;
	float sav_wp, sav_wn;
	float old_inc_wp, old_inc_wn;
	float E_POS_wp_mean, E_POS_wn_mean, E_NEG_wp_mean, E_NEG_wn_mean;

	BinaryBetaDLEdge(DLNode *_source = NULL): DLEdge(BINARY_BETA, _source), wp(FLT_MAX), wn(FLT_MAX), sav_wp(FLT_MAX), sav_wn(FLT_MAX), old_inc_wp(FLT_MAX), old_inc_wn(FLT_MAX), 
																						E_POS_wp_mean(FLT_MAX), E_POS_wn_mean(FLT_MAX), E_NEG_wp_mean(FLT_MAX), E_NEG_wn_mean(FLT_MAX) { };
};




/////////////// class BinaryDoubleBetaDLEdge ////////////////
class SNL_DL13_API BinaryDoubleBetaDLEdge : public DLEdge
{
private:
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    if (Archive::is_saving::value && (isinv(wp) || isinv(wn) || isinv(qp) || isinv(qn) ) )
    {
      std::cerr << "Internal Error: BinaryDoubleBetaDLEdge::serialize: an edge weight is invalid, cannot serialize" << std::endl;
      return;
    }
    ar & boost::serialization::base_object<DLEdge>(*this);
    ar & wp;
    ar & wn;
    ar & qp;
    ar & qn;
  }
public:
  float wp, wn, qp, qn;
  float sav_wp, sav_wn, sav_qp, sav_qn;
  float old_inc_wp, old_inc_wn, old_inc_qp, old_inc_qn;
  float E_POS_wp_mean, E_POS_wn_mean, E_NEG_wp_mean, E_NEG_wn_mean, E_POS_qp_mean, E_POS_qn_mean, E_NEG_qp_mean, E_NEG_qn_mean;

  BinaryDoubleBetaDLEdge(DLNode *_source = NULL) : DLEdge(BINARY_DOUBLEBETA, _source), wp(FLT_MAX), wn(FLT_MAX), sav_wp(FLT_MAX), sav_wn(FLT_MAX), old_inc_wp(FLT_MAX), old_inc_wn(FLT_MAX),
    E_POS_wp_mean(FLT_MAX), E_POS_wn_mean(FLT_MAX), E_NEG_wp_mean(FLT_MAX), E_NEG_wn_mean(FLT_MAX) { };
};


/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////

/////////////////////////////////////////////
/////////////// class DLNode ////////////////
/////////////////////////////////////////////
class SNL_DL13_API DLNode : public SNL::Node
{
private:
	//std::vector<float> _V;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar.template register_type<GaussianGaussianDLEdge>();
		ar.template register_type<BetaGaussianDLEdge>();
		ar.template register_type<BetaBetaDLEdge>();
		ar.template register_type<BinaryBinaryDLEdge>();
		ar.template register_type<BinaryGaussianDLEdge>();
		ar.template register_type<BinaryBetaDLEdge>();
    ar.template register_type<BinaryDoubleBetaDLEdge>();
		ar & boost::serialization::base_object<SNL::Node>(*this);
		ar & prop;
		ar & all_edges;
		ar & update_edges;
		ar & update_neighbors;
		ar & owned_edges;
		ar & spatial_neighbors;
		ar & spatial_neighbors_weights;
		ar & layer;
		ar & part_id;
		//if ( Archive::is_saving::value )
		//{
		//	_V = convertEigenVectorToStdVector(V);
		//}
		//ar & _V;
		//if ( !Archive::is_saving::value )
		//{
		//	V = convertStdVectorToEigenVector(_V);
		//}
	}
public:
	bool trimmed; // do not save
	RandomVariableProperties<float> prop;
	vector<DLEdge*> all_edges;					 // used in inference
	vector<DLEdge*> update_edges;				 // used in learning
	vector<DLNode*> update_neighbors;		 // used in learning
	UNORDERED_MAP<DLNode*, DLEdge*> owned_edges; // used in learning (redundant, but much faster for spatial smoothing)
	vector<DLNode*> spatial_neighbors;   // used in learning
	vector<float>   spatial_neighbors_weights;   // used in learning
	Layer*				  layer;
	short						part_id;
	SVECTORf				V;
  SVECTORf				Vb;                 // this is used for batch training
	SVECTORf				log_q_mean;
	SVECTORf				log_one_minus_q_mean;
	// Note: q_mean is set by setMarginal [initialize all q_mean to FLT_MAX, thus if q_mean(0) if FLT_MAX, it must be ignored]
	// setObservation(s) [set to observed values, if [rescale_value is false [training] and V is FLT_MAX] *OR* a value is FLT_MAX, q_mean is 0 [ignore observation]]
	// doInference computes q_mean
	SVECTORf				q_mean; 	
	float						out_mean;
	bool						is_observed;
	bool						lock_parameters;

	DLNode(int _type = INVALID_VARIABLE, Layer* _layer = NULL, long _id = -1): 
		Node(_type, _id, false), trimmed(false), layer(_layer), part_id(-1), out_mean(FLT_MAX), is_observed(false), lock_parameters(false) { };
	virtual bool isDiscrete() const = 0;
	bool isContinuous() const { return true; }
	int getType() const {return type; }
	long getID() const {return -1L;}
	string getName() const {return "";}
	size_t dim() const {return 1;}

	int connect(DLNode*);
	void setObservation(const float value, bool rescale_value = false);
	void setObservation(const SVECTORf& values, bool rescale_value = false);
	void clearObservation();
	void initMarginals(int num_data);
	void smoothParameters();

	virtual void doInference() = 0;
	virtual void condSample(RAND_GEN& rng) = 0;
	virtual void sample(RAND_GEN& rng) = 0;
	virtual void updatePriors() = 0;
	virtual void saveWeights() = 0;
	virtual void copyParameters(DLNode *source_node) = 0;
	virtual void copyBias(DLNode *source_node, int bias_id) = 0;
	virtual void saveEdgeWeights(bool) = 0;
	virtual void restoreSavedWeights() = 0;
	virtual void scaleTrainingData(bool training_data_scaling_already_done) = 0;
	virtual void rescale() = 0;
	virtual void unscale() = 0;
	virtual void init(bool do_not_init_parameters) = 0;
	virtual SVECTORf measureEnergy() = 0;
	virtual void updateExpectations(phase_type phase) = 0;
	virtual void updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight ) = 0;

	~DLNode();
}; // class DLNode



/////////////////////////////////////////////
/////////////// class BinaryNode ////////////////
/////////////////////////////////////////////
class SNL_DL13_API BinaryNode : public DLNode
{
private:
	float sav_b[2];
	float old_inc_b;
	float E_POS_b_mean, E_NEG_b_mean;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<DLNode>(*this);
		ar & b;
		ar & p_b;
	}	
public:
	float b[2]; 
	float p_b;

	BinaryNode(Layer* _layer = NULL, long _id = -1):   DLNode(BINARY, _layer, _id),  old_inc_b(FLT_MAX),
													   E_POS_b_mean(FLT_MAX), E_NEG_b_mean(FLT_MAX), p_b(FLT_MAX)
													  { b[0] = FLT_MAX; b[1] = FLT_MAX; sav_b[0] = FLT_MAX; sav_b[1] = FLT_MAX; };
	bool isDiscrete() const { return true; }
	void doInference();
	void condSample(RAND_GEN& rng);
	void sample(RAND_GEN& rng);
  void sampleAndDiscretize(RAND_GEN& rng);
	void updatePriors();
	void saveWeights();
	void copyParameters(DLNode *source_node);
	void copyBias(DLNode *source_node, int bias_id);
	void saveEdgeWeights(bool);
	void restoreSavedWeights();
	SVECTORf measureEnergy();
	void updateExpectations(phase_type phase);	
	void updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight );
	void scaleTrainingData(bool training_data_scaling_already_done) { };
	void rescale() { };
	void unscale();
	void init(bool do_not_init_parameters);  
}; // class BinaryNode



/////////////////////////////////////////////
/////////////// class GaussianNode ////////////////
/////////////////////////////////////////////

class SNL_DL13_API GaussianNode : public DLNode
{
private:
	float sav_b[2], sav_s;
	float old_inc_b, old_inc_s;
	float E_POS_s_mean, E_POS_b_mean, E_NEG_s_mean, E_NEG_b_mean;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<DLNode>(*this);
		ar & is_connected_to_beta;
		ar & b;
		ar & s;
		ar & p_b;
		ar & p_s;		
	}	
public:
	bool is_connected_to_beta;
	float b[2], s; 
	float p_b, p_s; 
	SVECTORf	q_std; 

	GaussianNode(Layer* _layer = NULL, long _id = -1): DLNode(GAUSSIAN, _layer, _id),  sav_s(FLT_MAX),
																										 old_inc_b(FLT_MAX), old_inc_s(FLT_MAX), 
																										 E_POS_s_mean(FLT_MAX), E_POS_b_mean(FLT_MAX), E_NEG_s_mean(FLT_MAX), E_NEG_b_mean(FLT_MAX),																										 
																									   is_connected_to_beta(false),
																										 s(FLT_MAX),
																										p_b(FLT_MAX), p_s(FLT_MAX)
																										{ b[0] = FLT_MAX; b[1] = FLT_MAX; sav_b[0] = FLT_MAX; sav_b[1] = FLT_MAX; };
	bool isDiscrete() const { return false; }
	void doInference();
	void condSample(RAND_GEN& rng);
	void sample(RAND_GEN& rng);
	void updatePriors();
	void saveWeights();
	void copyParameters(DLNode *source_node);
	void copyBias(DLNode *source_node, int bias_id);
	void saveEdgeWeights(bool);
	void restoreSavedWeights();
	SVECTORf measureEnergy();
	void updateExpectations(phase_type phase);
	void updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight );
	void scaleTrainingData(bool training_data_scaling_already_done);
	void rescale();
	void unscale();
	void init(bool do_not_init_parameters);
}; // class GaussianNode



/////////////////////////////////////////////
/////////////// class BetaNode ////////////////
/////////////////////////////////////////////


class SNL_DL13_API BetaNode : public DLNode
{
private:  
	float sav_a[2], sav_b[2];
	float old_inc_a, old_inc_b;
	float E_POS_a_mean, E_POS_b_mean, E_NEG_a_mean, E_NEG_b_mean;	

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<DLNode>(*this);
    ar & is_double_beta;
		ar & a;
		ar & b;
		ar & p_a;
		ar & p_b;
	}	
public:  
	SVECTORf	q_nominator, q_denominator; 
  bool is_double_beta;
	float a[2], b[2];
	float p_a, p_b;

	BetaNode(Layer* _layer = NULL, long _id = -1, bool _is_double_beta = false): DLNode(BETA, _layer, _id), 
																								 old_inc_a(FLT_MAX), old_inc_b(FLT_MAX), 
																								 E_POS_a_mean(FLT_MAX), E_POS_b_mean(FLT_MAX), E_NEG_a_mean(FLT_MAX), E_NEG_b_mean(FLT_MAX),
                                                 is_double_beta(_is_double_beta),
																								 p_a(FLT_MAX), p_b(FLT_MAX)
																								 {     
																									 a[0] = FLT_MAX; a[1] = FLT_MAX; b[0] = FLT_MAX; b[1] = FLT_MAX; 
																									 sav_a[0] = FLT_MAX; sav_a[1] = FLT_MAX;
																									 sav_b[0] = FLT_MAX; sav_b[1] = FLT_MAX;
																								 };
	bool isDiscrete() const { return false; }
	void doInference();
	void condSample(RAND_GEN& rng);
	void sample(RAND_GEN& rng);
	void updatePriors();
	void saveWeights();
	void copyParameters(DLNode *source_node);
	void copyBias(DLNode *source_node, int bias_id);
	void saveEdgeWeights(bool);
	void restoreSavedWeights();
	SVECTORf measureEnergy();
	void updateExpectations(phase_type phase);
	void updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight );
	void scaleTrainingData(bool training_data_scaling_already_done);
	void rescale();
	void unscale();
	void init(bool do_not_init_parameters);
}; // class BetaNode






}
}

#endif



//
//class SNL_DL13_API AttributeDLEdge: public DLEdge
//{
//private:
//	friend class boost::serialization::access;
//	template<class Archive>
//	void serialize(Archive & ar, const unsigned int version)
//	{
//		// serialize base class information
//		if ( Archive::is_saving::value && isnan(w) )
//		{
//			std::cerr << "Internal Error: AttributeDLEdge::serialize: an edge weight is NaN, cannot serialize" << std::endl;
//			return;
//		}
//		ar & boost::serialization::base_object<DLEdge>(*this);
//		ar & w;
//	}
//public:
//	AttributeDLEdge(): DLEdge(DETERMINISTIC_EDGE), w(FLT_MAX)  { };
//	float w;
//};


//
//
//class SNL_DL13_API AttributeNode : public DLNode
//{
//private:
//	friend class boost::serialization::access;
//	template<class Archive>
//	void serialize(Archive & ar, const unsigned int version)
//	{
//		if ( Archive::is_saving::value && (isnan(b)) )
//		{
//			std::cerr << "Internal Error: AttributeNode parameters are NaN - cannot serialize" << std::endl;
//			return;
//		}
//		ar & boost::serialization::base_object<DLNode>(*this);
//		ar & b;
//	}	
//public:
//	float b; // bias
//	AttributeNode(Layer* _layer = NULL): DLNode(DETERMINISTIC, _layer), b(0.0), s(1.0) {};
//	bool isDiscrete() const { return false; }
//	void doInference() { std::cout << "Warning: inference cannot be executed for a deterministic attribute node. " << std::endl; };
//	void saveWeights() { std::cout << "Warning: saveWeights cannot be executed for a deterministic attribute node. " << std::endl; };
//	void restoreSavedWeights() { std::cout << "Warning: restoreSavedWeights cannot be executed for a deterministic attribute node. " << std::endl; };
//	void updateExpectations(phase_type phase, int m) { std::cout << "Warning: updateExpectations cannot be executed for a deterministic attribute node. " << std::endl; };;
//	void updateParameters(float learning_rate, float momentum, const string& reg_type, float reg_weight );
//	void rescale();
//	void init(int number_of_training_examples, bool do_not_init_parameters);
//};