#include "DL13_Node.hpp"

namespace SNL {;
namespace DL13 {;

DLNode::~DLNode()
{
	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		delete it->second;
		owned_edges[it->first] = NULL;
	}
	owned_edges.clear();	
}

int DLNode::connect(DLNode* node)
{
	if ( type == INVALID_VARIABLE || layer == NULL)
	{
		std::cerr << "Internal error: DLNode::connect was called for an invalid variable type." << std::endl;
		exit(-1);
	}
	DLEdge *edge;
	if (this->type == GAUSSIAN && node->type == GAUSSIAN)
	{
		GaussianGaussianDLEdge *gedge = new GaussianGaussianDLEdge(this);
		edge = gedge;
	}
	else if ( (this->type == BETA && node->type == GAUSSIAN) || (node->type == BETA && this->type == GAUSSIAN) )
	{
		((GaussianNode*)node)->is_connected_to_beta = true;
		BetaGaussianDLEdge *gedge = new BetaGaussianDLEdge(this);
		edge = gedge;
	}
	else if (this->type == BETA && node->type == BETA)
	{
		BetaBetaDLEdge *gedge = new BetaBetaDLEdge(this);
		edge = gedge;
	}
	else if (this->type == BINARY && node->type == BINARY)
	{
		BinaryBinaryDLEdge *gedge = new BinaryBinaryDLEdge(this);
		edge = gedge;
	}
	else if ( (this->type == BINARY && node->type == GAUSSIAN) || (node->type == GAUSSIAN && this->type == BINARY) )
	{
		BinaryGaussianDLEdge *gedge = new BinaryGaussianDLEdge(this);
		edge = gedge;
	}
	else if ( (this->type == BINARY && node->type == BETA) || (node->type == BETA && this->type == BINARY) )
	{
    bool double_beta = false;
    if (node->type == BETA)
      double_beta = ((BetaNode*)node)->is_double_beta;
    if (this->type == BETA)
      double_beta = ((BetaNode*)this)->is_double_beta;
    
    if (double_beta)
    {
      BinaryDoubleBetaDLEdge *gedge = new BinaryDoubleBetaDLEdge(this);
      edge = gedge;
    }     
    else
    {
      BinaryBetaDLEdge *gedge = new BinaryBetaDLEdge(this);
      edge = gedge;
    }		
	}


	if (this->layer == node->layer)
	{
		this->addSiblingNoCheck(node);
		//this->sibling_edges.push_back(edge);
		//node->sibling_edges.push_back(edge);
		this->all_edges.push_back(edge);
		node->all_edges.push_back(edge);
		owned_edges[node] = edge;
		this->update_edges.push_back(edge);
		this->update_neighbors.push_back(node);
	}
	else
	{
		if (this->layer->id > node->layer->id)
		{
			this->addChildNoCheck(node);
			//this->children_edges.push_back(edge);
			//node->parent_edges.push_back(edge);
			this->all_edges.push_back(edge);
			node->all_edges.push_back(edge);
			owned_edges[node] = edge;
			this->update_edges.push_back(edge);
			this->update_neighbors.push_back(node);
		}
		else
		{
			std::cout << "Reminder: When you call DLNode::connect between nodes of different layers, node->connect(node2) connects 'node2' as a child of 'node')" << std::endl;
			this->addParentNoCheck(node);
			//node->children_edges.push_back(edge);
			//this->parent_edges.push_back(edge);
			this->all_edges.push_back(edge);
			node->all_edges.push_back(edge);
			node->owned_edges[this] = edge;
			node->update_edges.push_back(edge);
			node->update_neighbors.push_back(this);
		}
	}

	return 1;
}


void DLNode::setObservation(const float value, bool rescale_value)
{
	is_observed = true;
	trimmed = false;
	q_mean.resize(1);
	q_mean(0) = value;
	if ( rescale_value )
		rescale();

	if (type == GAUSSIAN)
	{
		if ( ((GaussianNode*)this)->is_connected_to_beta )
		{
      float tmp = q_mean(0);
			q_mean(0) = (q_mean(0)<EPSILONf)? EPSILONf : q_mean(0);
      if (q_mean(0) != tmp && value != FLT_MAX)
        trimmed = true;
		}
	}
	else if (type == BETA)
	{
		float tmp = q_mean(0);
		q_mean(0) = (q_mean(0)<EPSILONf)? EPSILONf : q_mean(0);
		q_mean(0) = (q_mean(0)>1.0f-EPSILONf)? 1.0f-EPSILONf : q_mean(0);
    if (q_mean(0) != tmp && value != FLT_MAX)
			trimmed = true;
	}
	//else if (type == BINARY)
	//{
	//	q_mean(0) = q_mean(0) >= .5;
	//}

	log_q_mean.resize(1);
	log_one_minus_q_mean.resize(1);
	log_q_mean(0) = log( q_mean(0) );
	log_one_minus_q_mean(0) = log( 1.0f - q_mean(0) );

	if (value == FLT_MAX)
	{
		q_mean(0) = 0.0f;     // note: zero imputations on missing data
		log_q_mean(0) = 0.0f;
		log_one_minus_q_mean(0) = 0.0f;
	}
  
}

// rescale_value=false means this function is called while training internally
// it is supposed to make 0 the values for which the training examples were FLT_MAX
void DLNode::setObservation(const SVECTORf& values, bool rescale_value)
{
	is_observed = true;
	trimmed = false;
	q_mean = values;
	if ( rescale_value )
		rescale();

	if (type == GAUSSIAN)
	{
		if ( ((GaussianNode*)this)->is_connected_to_beta )
			limit( q_mean, EPSILONf, FLT_MAX );
	}
	else if (type == BETA)
	{
		limit( q_mean, EPSILONf, 1.0f - EPSILONf );
	}
	//else if (type == BINARY)
	//{
	//	SVECTORf Z = SVECTORf::Zero( values.size() );
	//	SVECTORf O = SVECTORf::Ones( values.size() );
	//	q_mean = ( q_mean.array() >= .5 ).select( O, Z );
	//}
	log_q_mean = q_mean.array().log();
	log_one_minus_q_mean = ( 1.0f - q_mean.array() ).log();

	SVECTORf Z = SVECTORf::Zero( values.size() );
	q_mean = ( values.array() == FLT_MAX ).select( Z, q_mean );   // note: zero imputations on missing data
	log_q_mean = ( values.array() == FLT_MAX ).select( Z, log_q_mean );
	log_one_minus_q_mean = ( values.array() == FLT_MAX ).select( Z, log_one_minus_q_mean );
	if (!rescale_value) // not very elegant, this is important for setObservationsFromCurrentMeans
	{
		q_mean = (  Vb.array() == FLT_MAX ).select( Z, q_mean );
		log_q_mean = ( Vb.array() == FLT_MAX ).select( Z, log_q_mean );
		log_one_minus_q_mean = ( Vb.array() == FLT_MAX ).select( Z, log_one_minus_q_mean );
	}
}

void DLNode::clearObservation()
{
	is_observed = false;
	trimmed = false;
	q_mean.resize(0);
	log_q_mean.resize(0);
	log_one_minus_q_mean.resize(0);
	out_mean = FLT_MAX;
}

void DLNode::initMarginals(int num_data)
{
	if (is_observed)
		return;
	trimmed = false;
	q_mean.resize(num_data);
	log_q_mean.resize(num_data);
	log_one_minus_q_mean.resize(num_data);
	q_mean.fill(FLT_MAX);
	log_q_mean.fill(FLT_MAX);
	log_one_minus_q_mean.fill(FLT_MAX);
}


void DLNode::smoothParameters()
{
	//for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];

		switch( dledge->type )
		{
		case GAUSSIAN_GAUSSIAN:
			{
				GaussianGaussianDLEdge* gupdate_edge = (GaussianGaussianDLEdge*)dledge;
				GaussianNode* gupdate_neighbor = (GaussianNode*)update_neighbors[e];
				float total_weight = 1.0f;
				for (size_t es = 0; es < gupdate_neighbor->spatial_neighbors.size(); es++)
				{
					GaussianGaussianDLEdge* gneighbor_update_edge = (GaussianGaussianDLEdge*)owned_edges[ gupdate_neighbor->spatial_neighbors[es] ];
					float weight = gupdate_neighbor->spatial_neighbors_weights[es];
					gupdate_edge->w += weight * gneighbor_update_edge->old_inc_w;
					total_weight += weight;
				}
				gupdate_edge->w /= total_weight;
				break;
			}
		case BETA_GAUSSIAN:
			{
				BetaGaussianDLEdge* gupdate_edge = (BetaGaussianDLEdge*)dledge;
				GaussianNode* gupdate_neighbor = (GaussianNode*)update_neighbors[e];
				float total_weight = 1.0f;
				for (size_t es = 0; es < gupdate_neighbor->spatial_neighbors.size(); es++)
				{
					BetaGaussianDLEdge* gneighbor_update_edge = (BetaGaussianDLEdge*)owned_edges[ gupdate_neighbor->spatial_neighbors[es] ];
					float weight = gupdate_neighbor->spatial_neighbors_weights[es];
					gupdate_edge->wp += weight * gneighbor_update_edge->old_inc_wp;
					gupdate_edge->wn += weight * gneighbor_update_edge->old_inc_wn;
					total_weight += weight;
				}
				gupdate_edge->wp /= total_weight;
				gupdate_edge->wn /= total_weight;
				break;
			}
		case BETA_BETA:
			{
				BetaBetaDLEdge* gupdate_edge = (BetaBetaDLEdge*)dledge;
				BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
				float total_weight = 1.0f;
				for (size_t es = 0; es < gupdate_neighbor->spatial_neighbors.size(); es++)
				{
					BetaBetaDLEdge* gneighbor_update_edge = (BetaBetaDLEdge*)owned_edges[ gupdate_neighbor->spatial_neighbors[es] ];
					float weight = gupdate_neighbor->spatial_neighbors_weights[es];
					gupdate_edge->q += weight * gneighbor_update_edge->old_inc_q;
					gupdate_edge->s += weight * gneighbor_update_edge->old_inc_s;
					gupdate_edge->t += weight * gneighbor_update_edge->old_inc_t;
					gupdate_edge->w += weight * gneighbor_update_edge->old_inc_w;
					total_weight += weight;
				}
				gupdate_edge->q /= total_weight;
				gupdate_edge->s /= total_weight;
				gupdate_edge->t /= total_weight;
				gupdate_edge->w /= total_weight;
				break;
			}
		case BINARY_BINARY:
			{
				BinaryBinaryDLEdge* gupdate_edge = (BinaryBinaryDLEdge*)dledge;
				BinaryNode* gupdate_neighbor = (BinaryNode*)update_neighbors[e];
				float total_weight = 1.0f;
				for (size_t es = 0; es < gupdate_neighbor->spatial_neighbors.size(); es++)
				{
					BinaryBinaryDLEdge* gneighbor_update_edge = (BinaryBinaryDLEdge*)owned_edges[ gupdate_neighbor->spatial_neighbors[es] ];
					float weight = gupdate_neighbor->spatial_neighbors_weights[es];
					gupdate_edge->w += weight * gneighbor_update_edge->old_inc_w;
					total_weight += weight;
				}
				gupdate_edge->w /= total_weight;
				break;
			}
		case BINARY_GAUSSIAN:
			{
				BinaryGaussianDLEdge* gupdate_edge = (BinaryGaussianDLEdge*)dledge;
				GaussianNode* gupdate_neighbor = (GaussianNode*)update_neighbors[e];
				float total_weight = 1.0f;
				for (size_t es = 0; es < gupdate_neighbor->spatial_neighbors.size(); es++)
				{
					BinaryGaussianDLEdge* gneighbor_update_edge = (BinaryGaussianDLEdge*)owned_edges[ gupdate_neighbor->spatial_neighbors[es] ];
					float weight = gupdate_neighbor->spatial_neighbors_weights[es];
					gupdate_edge->w += weight * gneighbor_update_edge->old_inc_w;
					total_weight += weight;
				}
				gupdate_edge->w /= total_weight;
				break;
			}
		case BINARY_BETA:
			{
				BinaryBetaDLEdge* gupdate_edge = (BinaryBetaDLEdge*)dledge;
				BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
				float total_weight = 1.0f;
				for (size_t es = 0; es < gupdate_neighbor->spatial_neighbors.size(); es++)
				{
					BinaryBetaDLEdge* gneighbor_update_edge = (BinaryBetaDLEdge*)owned_edges[ gupdate_neighbor->spatial_neighbors[es] ];
					float weight = gupdate_neighbor->spatial_neighbors_weights[es];
					gupdate_edge->wp += weight * gneighbor_update_edge->old_inc_wp;
					gupdate_edge->wn += weight * gneighbor_update_edge->old_inc_wn;
					total_weight += weight;
				}
				gupdate_edge->wp /= total_weight;
				gupdate_edge->wn /= total_weight;
				break;
			}
    case BINARY_DOUBLEBETA:
    {
      BinaryDoubleBetaDLEdge* gupdate_edge = (BinaryDoubleBetaDLEdge*)dledge;
      BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
      float total_weight = 1.0f;
      for (size_t es = 0; es < gupdate_neighbor->spatial_neighbors.size(); es++)
      {
        BinaryDoubleBetaDLEdge* gneighbor_update_edge = (BinaryDoubleBetaDLEdge*)owned_edges[gupdate_neighbor->spatial_neighbors[es]];
        float weight = gupdate_neighbor->spatial_neighbors_weights[es];
        gupdate_edge->wp += weight * gneighbor_update_edge->old_inc_wp;
        gupdate_edge->wn += weight * gneighbor_update_edge->old_inc_wn;
        gupdate_edge->qp += weight * gneighbor_update_edge->old_inc_qp;
        gupdate_edge->qn += weight * gneighbor_update_edge->old_inc_qn;
        total_weight += weight;
      }
      gupdate_edge->wp /= total_weight;
      gupdate_edge->wn /= total_weight;
      gupdate_edge->qp /= total_weight;
      gupdate_edge->qn /= total_weight;
      break;
    }
		default:
			std::cerr << "Internal error: DLNode::smoothParameters supports parameter spatial smoothing only for Gaussian-Gaussian, Beta[hidden]-Gaussian, or Beta-Beta edges" << std::endl;
			exit(-1);
		} // end of switch statement
	}
}


/////////// GAUSSIAN NODE FUNCTIONS ////////////////

void GaussianNode::doInference()
{
	if ( is_observed )
		return;
	bool ready = false;
	if ( layer->above_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit )
			ready = true;
	if ( layer->below_layer != NULL )
		if ( layer->below_layer->is_ready_to_transmit )
			ready = true;
	if (!ready)
		return;	

	q_mean.fill(0.0f);

	for (size_t e = 0; e < all_edges.size(); e++)
	{
		DLEdge* dledge = all_edges[e];

		switch(dledge->type)
		{
		case GAUSSIAN_GAUSSIAN:
			{
				GaussianNode *neighbor = (GaussianNode*)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				GaussianGaussianDLEdge *edge = (GaussianGaussianDLEdge*)dledge;
				q_mean += s * edge->w * ( neighbor->q_mean / neighbor->s );
				break;
			}
		case BETA_GAUSSIAN:
			{
				BetaNode *neighbor = (BetaNode*)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				BetaGaussianDLEdge *edge = (BetaGaussianDLEdge*)dledge;
				q_mean += s * ( edge->wp * neighbor->log_q_mean + edge->wn * neighbor->log_one_minus_q_mean );
				break;
			}
		case BINARY_GAUSSIAN:
			{
				BinaryNode *neighbor = (BinaryNode*)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				BinaryGaussianDLEdge *edge = (BinaryGaussianDLEdge*)dledge;
				q_mean += s * ( edge->w * neighbor->q_mean );
				break;
			}
		default:
			std::cerr << "Internal error: GaussianNode::doInference supports inference updates only from Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}

	if ( layer->above_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit)
			q_mean = q_mean.array() + b[1];

	if ( layer->below_layer != NULL )
		if ( layer->below_layer->is_ready_to_transmit )
			q_mean = q_mean.array() + b[0];

	if ( layer->above_layer != NULL && layer->below_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit && layer->below_layer->is_ready_to_transmit )
			q_mean = .5f * q_mean;

	if ( is_connected_to_beta )
		limit( q_mean, EPSILONf, FLT_MAX );

	q_std = q_mean;
	q_std.fill(s);
}

void GaussianNode::updatePriors()
{
	// updatePriors is used only for hidden nodes, so if q_mean(m)=log_q_mean(m) [invalid], don't worry
	p_b = q_mean.mean();
	p_s = stddev( q_mean, p_b );
}

void GaussianNode::sample(RAND_GEN& rng)
{
	for (int m = 0; m < q_mean.size(); m++)
	{
		boost::normal_distribution<float> norm_dist(p_b, p_s);		
		q_mean(m) = norm_dist(rng);
	}
	if ( is_connected_to_beta )
		limit( q_mean, EPSILONf, FLT_MAX );
}

void GaussianNode::condSample(RAND_GEN& rng)
{	
	for (int m = 0; m < q_mean.size(); m++)
	{
		boost::normal_distribution<float> norm_dist(q_mean(m), q_std(m));		
		q_mean(m) = norm_dist(rng);
	}
	if ( is_connected_to_beta )
		limit( q_mean, EPSILONf, FLT_MAX );
}



SVECTORf GaussianNode::measureEnergy()
{
	float sqr_s = s * s;
	SVECTORf uprob = SVECTORf::Zero( q_mean.size() );

	if ( layer->above_layer != NULL && layer->below_layer == NULL)
		uprob.array() += ( q_mean.array() - b[1] ).square() / (2.0f * sqr_s);
		
	if ( layer->below_layer != NULL && layer->above_layer == NULL )
		uprob.array() += ( q_mean.array() - b[0] ).square() / (2.0f * sqr_s);

	if ( layer->above_layer != NULL && layer->below_layer != NULL )
		uprob.array() += ( q_mean.array() - (b[1] + b[0])*.5f ).square() / (2.0f * sqr_s);

	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge* dledge = update_edges[e];

		if ( dledge->type == GAUSSIAN_GAUSSIAN )
		{
			GaussianGaussianDLEdge* gupdate_edge = (GaussianGaussianDLEdge*)dledge;
			GaussianNode* gupdate_neighbor = (GaussianNode*)update_neighbors[e];
			uprob.array() -= gupdate_edge->w * ( q_mean.array() / s ) * ( gupdate_neighbor->q_mean.array() / gupdate_neighbor->s );
		}
		else if ( dledge->type == BETA_GAUSSIAN )
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)dledge;
			BetaNode *gupdate_neighbor = (BetaNode*)update_neighbors[e];
			uprob.array() -= gupdate_edge->wp * ( q_mean.array() / s ) * gupdate_neighbor->log_q_mean.array();
			uprob.array() -= gupdate_edge->wn * ( q_mean.array() / s ) * gupdate_neighbor->log_one_minus_q_mean.array();
		}
		else
		{
			std::cerr << "Internal error: GaussianNode::measureEnergy supports expectation updates only between Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}

	return uprob;
}


void GaussianNode::updateExpectations(phase_type phase)
{
	float sqr_s = s * s;
	float cub_s = sqr_s * s;
	SVECTORf q_mean_div_sqr_s = q_mean / sqr_s;
	SVECTORf q_mean_div_s = q_mean / s;
	
	SVECTORf q_mean_minus_b = q_mean;
	if ( layer->below_layer == NULL )
		q_mean_minus_b = q_mean_minus_b.array() - b[1];
	else
		q_mean_minus_b = q_mean_minus_b.array() - b[0];

	if ( phase == POSITIVE_PHASE )
	{
		E_POS_s_mean = ( q_mean_minus_b.array().square() / cub_s ).mean();
		E_POS_b_mean = ( q_mean_minus_b / sqr_s ).mean();
	}
	else
	{
		E_NEG_s_mean = ( q_mean_minus_b.array().square() / cub_s ).mean();
		E_NEG_b_mean = ( q_mean_minus_b / sqr_s ).mean();
	}

	for (size_t e = 0; e < all_edges.size(); e++)
	{
		DLEdge* dledge = all_edges[e];

		if (dledge->type == GAUSSIAN_GAUSSIAN)
		{
			GaussianNode *neighbor = (GaussianNode*)neighbors[e];			
			GaussianGaussianDLEdge *edge = (GaussianGaussianDLEdge*)dledge;

			if ( phase == POSITIVE_PHASE )
				E_POS_s_mean -= ( q_mean_div_sqr_s.array() * edge->w * ( neighbor->q_mean.array() / neighbor->s ) ).mean();
			else
				E_NEG_s_mean -= ( q_mean_div_sqr_s.array() * edge->w * ( neighbor->q_mean.array() / neighbor->s ) ).mean();
		}
		else if (dledge->type == BETA_GAUSSIAN)
		{
			BetaNode *neighbor = (BetaNode*)neighbors[e];
			BetaGaussianDLEdge *edge = (BetaGaussianDLEdge*)dledge;

			if ( phase == POSITIVE_PHASE )
				E_POS_s_mean -= ( q_mean_div_sqr_s.array() * ( edge->wp * neighbor->log_q_mean.array() + edge->wn * neighbor->log_one_minus_q_mean.array() ) ).mean();
			else
				E_NEG_s_mean -= ( q_mean_div_sqr_s.array() * ( edge->wp * neighbor->log_q_mean.array() + edge->wn * neighbor->log_one_minus_q_mean.array() ) ).mean();
		}
		else if (dledge->type == BINARY_GAUSSIAN)
		{
			BinaryNode *neighbor = (BinaryNode*)neighbors[e];
			BinaryGaussianDLEdge *edge = (BinaryGaussianDLEdge*)dledge;

			if ( phase == POSITIVE_PHASE )
				E_POS_s_mean -= ( q_mean_div_sqr_s.array() * edge->w * neighbor->q_mean.array() ).mean();
			else
				E_NEG_s_mean -= ( q_mean_div_sqr_s.array() * edge->w * neighbor->q_mean.array() ).mean();
		}
		else
		{
			std::cerr << "Internal error: GaussianNode::updateExpectations supports expectation updates only between Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}

	if (lock_parameters)
		return;

	// Update expectations only for CHILDREN and SIBLING edges
	//for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge* dledge = update_edges[e];

		if ( dledge->type == GAUSSIAN_GAUSSIAN )
		{
			GaussianGaussianDLEdge* gupdate_edge = (GaussianGaussianDLEdge*)dledge;
			GaussianNode* gupdate_neighbor = (GaussianNode*)update_neighbors[e];
			if ( phase == POSITIVE_PHASE )
				gupdate_edge->E_POS_w_mean = ( q_mean_div_s.array() * ( gupdate_neighbor->q_mean.array() / gupdate_neighbor->s ) ).mean();
			else
				gupdate_edge->E_NEG_w_mean = ( q_mean_div_s.array() * ( gupdate_neighbor->q_mean.array() / gupdate_neighbor->s ) ).mean();
		}
		else if ( dledge->type == BETA_GAUSSIAN )
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)dledge;
			BetaNode *gupdate_neighbor = (BetaNode*)update_neighbors[e];
			if ( phase == POSITIVE_PHASE )
			{
				gupdate_edge->E_POS_wp_mean = ( q_mean_div_s.array() * gupdate_neighbor->log_q_mean.array() ).mean();
				gupdate_edge->E_POS_wn_mean = ( q_mean_div_s.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
			}
			else
			{
				gupdate_edge->E_NEG_wp_mean = ( q_mean_div_s.array() * gupdate_neighbor->log_q_mean.array() ).mean();
				gupdate_edge->E_NEG_wn_mean = ( q_mean_div_s.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
			}
		}
		else
		{
			std::cerr << "Internal error: GaussianNode::updateExpectations supports expectation updates only between Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void GaussianNode::updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight )
{
	float grad_b = (E_POS_b_mean - E_NEG_b_mean);
	float grad_s = (E_POS_s_mean - E_NEG_s_mean);
	float inc_b = momentum * old_inc_b + learning_rate * 1.0f * grad_b; // update bias faster
	float inc_s = momentum * old_inc_s + learning_rate * 1.0f * grad_s;   // update variances slower
	
	inc_s = std::max( inc_s, EPSILONf - s);
	s += inc_s;

	if ( layer->below_layer == NULL )
		b[1] += inc_b;
	else
		b[0] += inc_b;

	old_inc_b = inc_b;
	old_inc_s = inc_s;

	if (lock_parameters)
		return;

	// Update parameters only for CHILDREN and SIBLING edges
	//for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];

		if (dledge->type == GAUSSIAN_GAUSSIAN )
		{
			GaussianGaussianDLEdge* gupdate_edge = (GaussianGaussianDLEdge*)dledge;

			float grad_w = (gupdate_edge->E_POS_w_mean - gupdate_edge->E_NEG_w_mean);
			float inc_w = momentum * gupdate_edge->old_inc_w + learning_rate * grad_w;

			switch( reg_type )
			{
			case L1:
				{
					inc_w -= learning_rate * reg_weight * sgn( gupdate_edge->w );
					break;
				}
			case L2:
				{
					inc_w -= learning_rate * reg_weight * gupdate_edge->w;
					break;
				}
			case LS1L1:
			case LS2L2:
			case LS1:
			case LS2:
				{
					DLNode *dlneighbor = update_neighbors[e];
					for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
					{
						GaussianGaussianDLEdge* gnupdate_edge = (GaussianGaussianDLEdge*)owned_edges[ dlneighbor->spatial_neighbors[es] ];
						if ( reg_type == LS2 )
							inc_w -= learning_rate * reg_weight * dlneighbor->spatial_neighbors_weights[es] * ( gupdate_edge->w - gnupdate_edge->w );
						else
							inc_w -= learning_rate * reg_weight * dlneighbor->spatial_neighbors_weights[es] * sgn( gupdate_edge->w - gnupdate_edge->w );						
					}

					if (reg_type == LS1L1)
						inc_w -= learning_rate * reg_weight * sgn(gupdate_edge->w);
					if (reg_type == LS2L2)
						inc_w -= learning_rate * reg_weight * gupdate_edge->w;

					break;
				}
			case LNONE:
				break;
			default:
				std::cerr << "Internal error: GaussianNode::updateParameters: unknown regularization type" << std::endl;
				exit(-1);
			}

			gupdate_edge->w += inc_w;
			gupdate_edge->old_inc_w = inc_w;
		}
		else if (dledge->type == BETA_GAUSSIAN )
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)dledge;

			float grad_wp = (gupdate_edge->E_POS_wp_mean - gupdate_edge->E_NEG_wp_mean);
			float grad_wn = (gupdate_edge->E_POS_wn_mean - gupdate_edge->E_NEG_wn_mean);
			float inc_wp = momentum * gupdate_edge->old_inc_wp + learning_rate * grad_wp;
			float inc_wn = momentum * gupdate_edge->old_inc_wn + learning_rate * grad_wn;

			switch( reg_type )
			{
			case L1:
				{
					inc_wp -= learning_rate * reg_weight * sgn( gupdate_edge->wp );
					inc_wn -= learning_rate * reg_weight * sgn( gupdate_edge->wn );
					break;
				}
			case L2:
				{
					inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
					inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
					break;
				}
			case LS1L1:
			case LS2L2:
			case LS1:
			case LS2:
				{
					DLNode *dlneighbor = update_neighbors[e];
					for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
					{
						float weight = reg_weight * dlneighbor->spatial_neighbors_weights[es];
						BetaGaussianDLEdge* gnupdate_edge = (BetaGaussianDLEdge*)owned_edges[ dlneighbor->spatial_neighbors[es] ];
						if (reg_type == LS2)
						{
							inc_wp -= learning_rate * weight * ( gupdate_edge->wp - gnupdate_edge->wp );
							inc_wn -= learning_rate * weight * ( gupdate_edge->wn - gnupdate_edge->wn );
						}
						else
						{
							inc_wp -= learning_rate * weight * sgn( gupdate_edge->wp - gnupdate_edge->wp );
							inc_wn -= learning_rate * weight * sgn( gupdate_edge->wn - gnupdate_edge->wn );
						}
					}

					if (reg_type == LS1L1)
					{
						inc_wp -= learning_rate * reg_weight * sgn(gupdate_edge->wp);
						inc_wn -= learning_rate * reg_weight * sgn(gupdate_edge->wn);
					}
					if (reg_type == LS2L2)
					{
						inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
						inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
					}

					break;
				}
			case LNONE:
				break;
			default:
				std::cerr << "Internal error: GaussianNode::updateParameters: unknown regularization type" << std::endl;
				exit(-1);
			} // end of switch statement

			inc_wp = std::max( inc_wp, EPSILONf - gupdate_edge->wp);
			inc_wn = std::max( inc_wn, EPSILONf - gupdate_edge->wn);
			//inc_wp = std::min( inc_wp, 1.0f-EPSILONf - gupdate_edge->wp);
			//inc_wn = std::min( inc_wn, 1.0f-EPSILONf - gupdate_edge->wn);
			gupdate_edge->wp += inc_wp;
			gupdate_edge->wn += inc_wn;
			gupdate_edge->old_inc_wp = inc_wp;
			gupdate_edge->old_inc_wn = inc_wn;
		}
		else
		{
			std::cerr << "Internal error: GaussianNode::updateParameters supports parameter updates only between Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void GaussianNode::init(bool do_not_init_parameters)
{
	old_inc_b = 0.0f;
	old_inc_s = 0.0f;
	E_POS_b_mean = 0.0f;
	E_NEG_b_mean = 0.0f;
	E_POS_s_mean = 0.0f;
	E_NEG_s_mean = 0.0f;

	// initialize CHILDREN and SIBLING edges.
	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == GAUSSIAN_GAUSSIAN )
		{
			GaussianGaussianDLEdge* gupdate_edge = (GaussianGaussianDLEdge*)it->second;
			gupdate_edge->old_inc_w = 0.0f;
			gupdate_edge->E_POS_w_mean = 0.0f;
			gupdate_edge->E_NEG_w_mean = 0.0f;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)it->second;
			gupdate_edge->old_inc_wp = 0.0f;
			gupdate_edge->old_inc_wn = 0.0f;
			gupdate_edge->E_POS_wp_mean = 0.0f;
			gupdate_edge->E_NEG_wp_mean = 0.0f;
			gupdate_edge->E_POS_wn_mean = 0.0f;
			gupdate_edge->E_NEG_wn_mean = 0.0f;
		}
		else
		{
			std::cerr << "Internal error: GaussianNode::init supports initialization of weights between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}

	if (do_not_init_parameters)
		return;

	if ( isinv(s) )
		s = 1.0f;

	if ( layer->below_layer == NULL )
	{
		if ( isinv(b[1]) )
		{
			if (is_connected_to_beta)
				b[1] = (float)parents.size() * .1f;
			else
				b[1] = 0.0f;
		}
	}
	else
	{
		if ( isinv(b[0]) )
		{
			if (is_connected_to_beta)
				b[0] = (float)parents.size() * .1f;
			else
				b[0] = 0.0f;
		}
	}

	// initialize CHILDREN and SIBLING edges.
	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == GAUSSIAN_GAUSSIAN )
		{
			GaussianGaussianDLEdge* gupdate_edge = (GaussianGaussianDLEdge*)it->second;

			if (it->first->layer != this->layer)
				gupdate_edge->w = unifRand(-.1f, .1f);
			else
				gupdate_edge->w = 0.0f;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)it->second;

			gupdate_edge->wp = unifRand(EPSILONf, .01f);
			gupdate_edge->wn = unifRand(EPSILONf, .01f);
		}
		else
		{
			std::cerr << "Internal error: GaussianNode::init supports initialization of weights between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void GaussianNode::scaleTrainingData(bool training_data_scaling_already_done)
{
	if (!training_data_scaling_already_done)
		prop.getBasicRandomVariableProperties( removeElements(V, FLT_MAX) );

	if ( !is_connected_to_beta )
	{
		V = (V.array() != FLT_MAX).select(  (V.array() - prop.mean) / (prop.std + EPSILONf), V); // scale then in the [.25 .75] interval
	}
	else
	{
		float dscale = 2.0f * (prop.max - prop.min) + EPSILONf;
		V = (V.array() != FLT_MAX).select( (V.array() - prop.min + dscale / 4.0f) / dscale, V); // scale then in the [.25 .75] interval
	}
}

void GaussianNode::rescale()
{
	if (!prop.valid)
	{
		std::cerr << "Internal error: GaussianNode::rescale was called before mean/std is computed." << std::endl;
		exit(-1);
	}
	if ( !is_connected_to_beta )
	{
		q_mean = (q_mean.array() != FLT_MAX).select(  (q_mean.array() - prop.mean) / (prop.std + EPSILONf), q_mean); // scale then in the [.25 .75] interval
	}
	else
	{
		float dscale = 2.0f * (prop.max - prop.min) + EPSILONf;
		q_mean = (q_mean.array() != FLT_MAX).select( (q_mean.array() - prop.min + dscale / 4.0f) / dscale, q_mean); // scale then in the [.25 .75] interval
	}
}

void GaussianNode::unscale()
{
	out_mean = q_mean(0);
	if (!prop.valid)
		return;

	if ( !is_connected_to_beta )
	{
		prop.unstandardize(out_mean);
	}
	else
	{
		float dscale = 2.0f * (prop.max - prop.min) + EPSILONf;
		out_mean = out_mean * dscale + prop.min - dscale / 4.0f;	
	}
}

void GaussianNode::saveWeights()
{
	sav_b[0] = b[0];
	sav_b[1] = b[1];
	sav_s = s;

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == GAUSSIAN_GAUSSIAN)
		{
			((GaussianGaussianDLEdge*)it->second)->sav_w = ((GaussianGaussianDLEdge*)it->second)->w;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it->second)->sav_wp = ((BetaGaussianDLEdge*)it->second)->wp;
			((BetaGaussianDLEdge*)it->second)->sav_wn = ((BetaGaussianDLEdge*)it->second)->wn;
		}
		else
		{
			std::cerr << "GaussianNode::saveWeights supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void GaussianNode::saveEdgeWeights(bool clear)
{
	if (clear)
	{
		for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
		{
			if (it->second->type == GAUSSIAN_GAUSSIAN)
			{
				((GaussianGaussianDLEdge*)it->second)->old_inc_w = 0.0f;
			}
			else if (it->second->type == BETA_GAUSSIAN)
			{
				((BetaGaussianDLEdge*)it->second)->old_inc_wp = 0.0f;
				((BetaGaussianDLEdge*)it->second)->old_inc_wn = 0.0f;
			}
			else
			{
				std::cerr << "GaussianNode::saveEdgeWeights supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
				exit(-1);
			}
		}
		return;
	}

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == GAUSSIAN_GAUSSIAN)
		{
			((GaussianGaussianDLEdge*)it->second)->old_inc_w = ((GaussianGaussianDLEdge*)it->second)->w;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it->second)->old_inc_wp = ((BetaGaussianDLEdge*)it->second)->wp;
			((BetaGaussianDLEdge*)it->second)->old_inc_wn = ((BetaGaussianDLEdge*)it->second)->wn;
		}
		else
		{
			std::cerr << "GaussianNode::saveEdgeWeights supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void GaussianNode::restoreSavedWeights()
{
	b[0] = sav_b[0];
	b[1] = sav_b[1];
	s = sav_s;

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == GAUSSIAN_GAUSSIAN)
		{
			((GaussianGaussianDLEdge*)it->second)->w = ((GaussianGaussianDLEdge*)it->second)->sav_w;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it->second)->wp = ((BetaGaussianDLEdge*)it->second)->sav_wp;
			((BetaGaussianDLEdge*)it->second)->wn = ((BetaGaussianDLEdge*)it->second)->sav_wn;
		}
		else
		{
			std::cerr << "GaussianNode::saveWeights supports edge weight restoring between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void GaussianNode::copyParameters(DLNode *source_node)
{
	GaussianNode *gsource_node = (GaussianNode*)source_node;
	b[0] = gsource_node->b[0];
	b[1] = gsource_node->b[1];
	s = gsource_node->s;

	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge* it = update_edges[e];
		DLEdge* git = gsource_node->update_edges[e];

		if (it->type == GAUSSIAN_GAUSSIAN)
		{
			((GaussianGaussianDLEdge*)it)->w = ((GaussianGaussianDLEdge*)git)->w;
		}
		else if (it->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it)->wp = ((BetaGaussianDLEdge*)git)->wp;
			((BetaGaussianDLEdge*)it)->wn = ((BetaGaussianDLEdge*)git)->wn;
		}
		else
		{
			std::cerr << "GaussianNode::copyParameters supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void GaussianNode::copyBias(DLNode *source_node, int bias_id)
{
	GaussianNode *gsource_node = (GaussianNode*)source_node;
	b[bias_id] = gsource_node->b[bias_id];
}



/////////// BETA NODE FUNCTIONS ////////////////



void BetaNode::doInference()
{
	if ( is_observed )
		return;
	bool ready = false;
	if ( layer->above_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit )
			ready = true;
	if ( layer->below_layer != NULL )
		if ( layer->below_layer->is_ready_to_transmit )
			ready = true;
	if (!ready)
		return;	

	q_nominator = q_mean;
	q_denominator = q_mean;
	q_nominator.fill(0.0f);
	q_denominator.fill(0.0f);

	for (size_t e = 0; e < all_edges.size(); e++)
	{
		DLEdge* dledge = all_edges[e];

		switch( dledge->type )
		{
		case BETA_BETA:
			{
				BetaNode *neighbor = (BetaNode*)neighbors[e];
				if (isinv(neighbor->log_q_mean(0)))
					continue;

				BetaBetaDLEdge *edge = (BetaBetaDLEdge*)dledge;
				if (edge->source == this)
				{
					q_nominator -= edge->w * neighbor->log_q_mean + edge->s * neighbor->log_one_minus_q_mean;
					q_denominator -= edge->q * neighbor->log_q_mean + edge->t * neighbor->log_one_minus_q_mean;
				}
				else
				{
					q_nominator -= edge->w * neighbor->log_q_mean + edge->q * neighbor->log_one_minus_q_mean;
					q_denominator -= edge->s * neighbor->log_q_mean + edge->t * neighbor->log_one_minus_q_mean;
				}
				break;
			}
		case BETA_GAUSSIAN:
			{
				GaussianNode *neighbor = (GaussianNode*)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				BetaGaussianDLEdge *edge = (BetaGaussianDLEdge*)dledge;
				q_nominator += edge->wp * ( neighbor->q_mean / neighbor->s );
				q_denominator += edge->wn * ( neighbor->q_mean / neighbor->s );
				break;
			}
		case BINARY_BETA:
			{
				BinaryNode *neighbor = (BinaryNode*)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				BinaryBetaDLEdge *edge = (BinaryBetaDLEdge*)dledge;
				q_nominator += edge->wp * neighbor->q_mean;
				q_denominator += edge->wn * neighbor->q_mean;
				break;
			}
    case BINARY_DOUBLEBETA:
    {
      BinaryNode *neighbor = (BinaryNode*)neighbors[e];
      if (isinv(neighbor->q_mean(0)))
        continue;
      BinaryDoubleBetaDLEdge *edge = (BinaryDoubleBetaDLEdge*)dledge;
      q_nominator.array() += edge->wp * neighbor->q_mean.array();
      q_nominator.array() += edge->qp * (1.0f - neighbor->q_mean.array());
      q_denominator.array() += edge->wn * neighbor->q_mean.array();
      q_denominator.array() += edge->qn * (1.0f - neighbor->q_mean.array());
      break;
    }
		default:
			std::cerr << "Internal error: BetaNode::doInference supports inference updates only from Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}

  if (layer->above_layer != NULL)
  {
    if (layer->above_layer->is_ready_to_transmit)
    {
      q_nominator = q_nominator.array() + a[1];
      q_denominator = q_denominator.array() + b[1];
    }
  }

  if (layer->below_layer != NULL)
  {
    if (layer->below_layer->is_ready_to_transmit)
    {
      q_nominator = q_nominator.array() + a[0];
      q_denominator = q_denominator.array() + b[0];
    }
  }

	if ( layer->above_layer != NULL && layer->below_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit && layer->below_layer->is_ready_to_transmit )
		{
			q_nominator = .5f * q_nominator;
			q_denominator = .5f * q_denominator;
		}

	q_mean = q_nominator.array() / (q_nominator.array() + q_denominator.array() );
	limit( q_mean, EPSILONf, 1.0f - EPSILONf );
	log_q_mean = q_mean.array().log();
	log_one_minus_q_mean = ( 1.0f - q_mean.array() ).log();
}

void BetaNode::updatePriors()
{
	// updatePriors is used only for hidden nodes, so if q_mean(m)=log_q_mean(m) [invalid], don't worry
	// argh, this should probably be converted to MLE, which is not closed-form
	float m = q_mean.mean();
	float s = variance(q_mean, m);
	s = min( s, m * (1.0f - m) );
	p_a = m * ( -1.0f + (m * (1.0f - m)) / s );
	p_b = (1.0f - m ) * ( -1.0f + (m * (1.0f - m)) / s );
}


void BetaNode::sample(RAND_GEN& rng)
{
	for (int m = 0; m < q_mean.size(); m++)
	{
		boost::gamma_distribution<double> gamma_dist1( std::max(p_a, EPSILONf), 1.0f);
		boost::gamma_distribution<double> gamma_dist2( std::max(p_b, EPSILONf), 1.0f);
		float x = (float)gamma_dist1(rng);
		float y = (float)gamma_dist2(rng);	
		if ( (x < EPSILONf) && (y < EPSILONf) ) // bernoulli
		{
			float p = p_a / (p_a + p_b);
			q_mean(m) = float( unifRand(0.0f, 1.0f) > p );
		}
		else
		{
			q_mean(m) =  x / (x+y+EPSILONf);
		}
		q_mean(m) = (q_mean(m)<EPSILONf)? EPSILONf : q_mean(m);
		q_mean(m) = (q_mean(m)>1.0f-EPSILONf)? 1.0f-EPSILONf : q_mean(m);
		log_q_mean(m) = log( q_mean(m) );
		log_one_minus_q_mean(m) = log( 1.0f - q_mean(m) );
	}
}

void BetaNode::condSample(RAND_GEN& rng)
{
	for (int m = 0; m < q_mean.size(); m++)
	{
		boost::gamma_distribution<double> gamma_dist1( std::max(q_nominator(m), EPSILONf), 1.0f);
		boost::gamma_distribution<double> gamma_dist2( std::max(q_denominator(m), EPSILONf), 1.0f);
		float x = (float)gamma_dist1(rng);
		float y = (float)gamma_dist2(rng);	
		if ( (x < EPSILONf) && (y < EPSILONf) ) // bernoulli
		{
			float p = q_nominator(m) / (q_nominator(m) + q_denominator(m));
			q_mean(m) = float( unifRand(0.0f, 1.0f) > p );
		}
		else
		{
			q_mean(m) =  x / (x+y+EPSILONf);
		}
		q_mean(m) = (q_mean(m)<EPSILONf)? EPSILONf : q_mean(m);
		q_mean(m) = (q_mean(m)>1.0f-EPSILONf)? 1.0f-EPSILONf : q_mean(m);
		log_q_mean(m) = log( q_mean(m) );
		log_one_minus_q_mean(m) = log( 1.0f - q_mean(m) );
	}
}



SVECTORf BetaNode::measureEnergy()
{	
	SVECTORf uprob = SVECTORf::Zero( q_mean.size() );

  if (layer->above_layer != NULL)
  {
    uprob.array() -= log_q_mean.array() * a[1];
    uprob.array() -= log_one_minus_q_mean.array() * b[1];
  }

  if (layer->below_layer != NULL)
  {
    uprob.array() -= log_q_mean.array() * a[0];
    uprob.array() -= log_one_minus_q_mean.array() * b[0];
  }

  if (layer->above_layer != NULL && layer->below_layer != NULL)
    uprob.array() = .5f * uprob.array();

	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];

		if (dledge->type == BETA_BETA )
		{
			BetaBetaDLEdge* gupdate_edge = (BetaBetaDLEdge*)dledge;
			BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
			uprob.array() += gupdate_edge->w * log_q_mean.array() * gupdate_neighbor->log_q_mean.array();
			uprob.array() += gupdate_edge->q * log_one_minus_q_mean.array() * gupdate_neighbor->log_q_mean.array();
			uprob.array() += gupdate_edge->s * log_q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array();
			uprob.array() += gupdate_edge->t * log_one_minus_q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array();
		}
		else if (dledge->type == BETA_GAUSSIAN)
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)dledge;
			GaussianNode *gupdate_neighbor = (GaussianNode*)update_neighbors[e];
			uprob.array() -= gupdate_edge->wp * log_q_mean.array() * (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s);
			uprob.array() -= gupdate_edge->wn * log_one_minus_q_mean.array() * (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s);
		}
		else
		{
			std::cerr << "Internal error: BetaNode::measureEnergy supports expectation updates only between Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}

	return uprob;
}

void BetaNode::updateExpectations(phase_type phase)
{
	if ( phase == POSITIVE_PHASE )
	{
		E_POS_a_mean = log_q_mean.mean();
		E_POS_b_mean = log_one_minus_q_mean.mean();
	}
	else
	{
		E_NEG_a_mean = log_q_mean.mean();
		E_NEG_b_mean = log_one_minus_q_mean.mean();
	}

	if (lock_parameters)
		return;

	// Update expectations only for CHILDREN and SIBLING edges
	//for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];

		if (dledge->type == BETA_BETA )
		{
			BetaBetaDLEdge* gupdate_edge = (BetaBetaDLEdge*)dledge;
			BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
			if ( phase == POSITIVE_PHASE )
			{
				gupdate_edge->E_POS_w_mean = -( log_q_mean.array() * gupdate_neighbor->log_q_mean.array() ).mean();
				gupdate_edge->E_POS_q_mean = -( log_one_minus_q_mean.array() * gupdate_neighbor->log_q_mean.array() ).mean();
				gupdate_edge->E_POS_s_mean = -( log_q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
				gupdate_edge->E_POS_t_mean = -( log_one_minus_q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
			}
			else
			{
				gupdate_edge->E_NEG_w_mean = -( log_q_mean.array() * gupdate_neighbor->log_q_mean.array() ).mean();
				gupdate_edge->E_NEG_q_mean = -( log_one_minus_q_mean.array() * gupdate_neighbor->log_q_mean.array() ).mean();
				gupdate_edge->E_NEG_s_mean = -( log_q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
				gupdate_edge->E_NEG_t_mean = -( log_one_minus_q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
			}
		}
		else if (dledge->type == BETA_GAUSSIAN)
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)dledge;
			GaussianNode *gupdate_neighbor = (GaussianNode*)update_neighbors[e];
			if ( phase == POSITIVE_PHASE )
			{
				gupdate_edge->E_POS_wp_mean = ( (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s) * log_q_mean.array() ).mean();
				gupdate_edge->E_POS_wn_mean = ( (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s) * log_one_minus_q_mean.array() ).mean();
			}
			else
			{
				gupdate_edge->E_NEG_wp_mean = ( (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s) * log_q_mean.array() ).mean();
				gupdate_edge->E_NEG_wn_mean = ( (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s) * log_one_minus_q_mean.array() ).mean();
			}
		}
		else
		{
			std::cerr << "Internal error: BetaNode::updateExpectations supports expectation updates only between Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void BetaNode::updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight )
{
  if (!is_double_beta) // note: a, b are not updated in binary beta
  {
    float grad_a = (E_POS_a_mean - E_NEG_a_mean);
    float grad_b = (E_POS_b_mean - E_NEG_b_mean);
    float inc_a = momentum * old_inc_a + learning_rate * .001f * grad_a; // update a much slower
    float inc_b = momentum * old_inc_b + learning_rate * .001f * grad_b; // update b much slower


    if (layer->below_layer == NULL)
    {
      //inc_a = std::max( inc_a, EPSILONf - a[1]);
      //inc_b = std::max( inc_b, EPSILONf - b[1]);
      a[1] += inc_a;
      b[1] += inc_b;
    }
    else
    {
      //inc_a = std::max( inc_a, EPSILONf - a[0]);
      //inc_b = std::max( inc_b, EPSILONf - b[0]);
      a[0] += inc_a;
      b[0] += inc_b;
    }

    old_inc_a = inc_a;
    old_inc_b = inc_b;
  }

	if (lock_parameters)
		return;

	// Update parameters only for CHILDREN and SIBLING edges
	//for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];	

		if (dledge->type == BETA_BETA )
		{
			BetaBetaDLEdge* gupdate_edge = (BetaBetaDLEdge*)dledge;

			float grad_w = (gupdate_edge->E_POS_w_mean - gupdate_edge->E_NEG_w_mean);
			float grad_q = (gupdate_edge->E_POS_q_mean - gupdate_edge->E_NEG_q_mean);
			float grad_s = (gupdate_edge->E_POS_s_mean - gupdate_edge->E_NEG_s_mean);
			float grad_t = (gupdate_edge->E_POS_t_mean - gupdate_edge->E_NEG_t_mean);
			float inc_w = momentum * gupdate_edge->old_inc_w + learning_rate * grad_w;
			float inc_q = momentum * gupdate_edge->old_inc_q + learning_rate * grad_q;
			float inc_s = momentum * gupdate_edge->old_inc_s + learning_rate * .1f * grad_s;
			float inc_t = momentum * gupdate_edge->old_inc_t + learning_rate * .1f * grad_t;


			switch( reg_type )
			{
			case L1:
				{
					inc_w -= learning_rate * reg_weight * sgn( gupdate_edge->w );
					inc_q -= learning_rate * reg_weight * sgn( gupdate_edge->q );
					inc_s -= learning_rate * reg_weight * sgn( gupdate_edge->s );
					inc_t -= learning_rate * reg_weight * sgn( gupdate_edge->t );
					break;
				}
			case L2:
				{
					inc_w -= learning_rate * reg_weight * gupdate_edge->w;
					inc_q -= learning_rate * reg_weight * gupdate_edge->q;
					inc_s -= learning_rate * reg_weight * gupdate_edge->s;
					inc_t -= learning_rate * reg_weight * gupdate_edge->t;
					break;
				}
			case LS1L1:
			case LS2L2:
			case LS1:
			case LS2:
				{
					DLNode *dlneighbor = update_neighbors[e];
					for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
					{						
						BetaBetaDLEdge* gnupdate_edge = (BetaBetaDLEdge*)owned_edges[ dlneighbor->spatial_neighbors[es] ];
						float weight = reg_weight * dlneighbor->spatial_neighbors_weights[es];
						if (reg_type == LS2)
						{
							inc_w -= learning_rate * weight * ( gupdate_edge->w - gnupdate_edge->w );
							inc_q -= learning_rate * weight * ( gupdate_edge->q - gnupdate_edge->q );
							inc_s -= learning_rate * weight * ( gupdate_edge->s - gnupdate_edge->s );
							inc_t -= learning_rate * weight * ( gupdate_edge->t - gnupdate_edge->t );
						}
						else
						{
							inc_w -= learning_rate * weight * sgn( gupdate_edge->w - gnupdate_edge->w );
							inc_q -= learning_rate * weight * sgn( gupdate_edge->q - gnupdate_edge->q );
							inc_s -= learning_rate * weight * sgn( gupdate_edge->s - gnupdate_edge->s );
							inc_t -= learning_rate * weight * sgn( gupdate_edge->t - gnupdate_edge->t );
						}
					}

					if (reg_type == LS1L1)
					{
						inc_w -= learning_rate * reg_weight * sgn(gupdate_edge->w);
						inc_q -= learning_rate * reg_weight * sgn(gupdate_edge->q);
						inc_s -= learning_rate * reg_weight * sgn(gupdate_edge->s);
						inc_t -= learning_rate * reg_weight * sgn(gupdate_edge->t);
					}
					if (reg_type == LS2L2)
					{
						inc_w -= learning_rate * reg_weight * gupdate_edge->w;
						inc_q -= learning_rate * reg_weight * gupdate_edge->q;
						inc_s -= learning_rate * reg_weight * gupdate_edge->s;
						inc_t -= learning_rate * reg_weight * gupdate_edge->t;
					}

					break;
				}
			case LNONE:
				break;
			default:
				std::cerr << "Internal error: BetaNode::updateParameters: unknown regularization type" << std::endl;
				exit(-1);
			} // end of switch statement

			inc_w = std::max( inc_w, EPSILONf - gupdate_edge->w);
			inc_q = std::max( inc_q, EPSILONf - gupdate_edge->q);
			inc_s = std::max( inc_s, EPSILONf - gupdate_edge->s);
			inc_t = std::max( inc_t, EPSILONf - gupdate_edge->t);
			gupdate_edge->w += inc_w;
			gupdate_edge->q += inc_q;
			gupdate_edge->s += inc_s;
			gupdate_edge->t += inc_t;
			//gupdate_edge->w = (gupdate_edge->w<EPSILONf)? EPSILONf : gupdate_edge->w;
			//gupdate_edge->q = (gupdate_edge->q<EPSILONf)? EPSILONf : gupdate_edge->q;
			//gupdate_edge->s = (gupdate_edge->s<EPSILONf)? EPSILONf : gupdate_edge->s;
			//gupdate_edge->t = (gupdate_edge->t<EPSILONf)? EPSILONf : gupdate_edge->t;
			gupdate_edge->old_inc_w = inc_w;
			gupdate_edge->old_inc_q = inc_q;
			gupdate_edge->old_inc_s = inc_s;
			gupdate_edge->old_inc_t = inc_t;
		}
		else if (dledge->type == BETA_GAUSSIAN)
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)dledge;

			float grad_wp = (gupdate_edge->E_POS_wp_mean - gupdate_edge->E_NEG_wp_mean);
			float grad_wn = (gupdate_edge->E_POS_wn_mean - gupdate_edge->E_NEG_wn_mean);
			float inc_wp = momentum * gupdate_edge->old_inc_wp + learning_rate * grad_wp;
			float inc_wn = momentum * gupdate_edge->old_inc_wn + learning_rate * grad_wn;

			switch( reg_type )
			{
			case L1:
				{
					inc_wp -= learning_rate * reg_weight * sgn( gupdate_edge->wp );
					inc_wn -= learning_rate * reg_weight * sgn( gupdate_edge->wn );
					break;
				}
			case L2:
				{
					inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
					inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
					break;
				}
			case LS1L1:
			case LS2L2:
			case LS1:
			case LS2:
				{
					DLNode *dlneighbor = update_neighbors[e];					
					for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
					{						
						BetaGaussianDLEdge* gnupdate_edge = (BetaGaussianDLEdge*)owned_edges[ dlneighbor->spatial_neighbors[es] ];
						float weight = reg_weight * dlneighbor->spatial_neighbors_weights[es];
						if (reg_type == LS2)
						{
							inc_wp -= learning_rate * weight * ( gupdate_edge->wp - gnupdate_edge->wp );
							inc_wn -= learning_rate * weight * ( gupdate_edge->wn - gnupdate_edge->wn );
						}
						else
						{
							inc_wp -= learning_rate * weight * sgn( gupdate_edge->wp - gnupdate_edge->wp );
							inc_wn -= learning_rate * weight * sgn( gupdate_edge->wn - gnupdate_edge->wn );
						}
					}

					if (reg_type == LS1L1)
					{
						inc_wp -= learning_rate * reg_weight * sgn(gupdate_edge->wp);
						inc_wn -= learning_rate * reg_weight * sgn(gupdate_edge->wn);
					}
					if (reg_type == LS2L2)
					{
						inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
						inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
					}

					break;
				}
			case LNONE:
				break;
			default:
				std::cerr << "Internal error: BetaNode::updateParameters: unknown regularization type" << std::endl;
				exit(-1);
			} // end of switch statement

			inc_wp = std::max( inc_wp, EPSILONf - gupdate_edge->wp);
			inc_wn = std::max( inc_wn, EPSILONf - gupdate_edge->wn);
			//inc_wp = std::min( inc_wp, 1.0f-EPSILONf - gupdate_edge->wp);
			//inc_wn = std::min( inc_wn, 1.0f-EPSILONf - gupdate_edge->wn);
			gupdate_edge->wp += inc_wp;
			gupdate_edge->wn += inc_wn;
			gupdate_edge->old_inc_wp = inc_wp;
			gupdate_edge->old_inc_wn = inc_wn;
		}
		else
		{
			std::cerr << "Internal error: BetaNode::updateParameters supports parameter updates only between Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void BetaNode::init(bool do_not_init_parameters)
{
  old_inc_a = 0.0f;
  old_inc_b = 0.0f;
  E_POS_a_mean = 0.0f;
  E_NEG_a_mean = 0.0f;
  E_POS_b_mean = 0.0f;
  E_NEG_b_mean = 0.0f;

  // initialize CHILDREN and SIBLING edges.
  for (UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it)
  {
    if (it->second->type == BETA_BETA)
    {
      BetaBetaDLEdge* gupdate_edge = (BetaBetaDLEdge*)it->second;
      gupdate_edge->old_inc_w = 0.0f;
      gupdate_edge->old_inc_q = 0.0f;
      gupdate_edge->old_inc_s = 0.0f;
      gupdate_edge->old_inc_t = 0.0f;
      gupdate_edge->E_POS_w_mean = 0.0f;
      gupdate_edge->E_NEG_w_mean = 0.0f;
      gupdate_edge->E_POS_q_mean = 0.0f;
      gupdate_edge->E_NEG_q_mean = 0.0f;
      gupdate_edge->E_POS_s_mean = 0.0f;
      gupdate_edge->E_NEG_s_mean = 0.0f;
      gupdate_edge->E_POS_t_mean = 0.0f;
      gupdate_edge->E_NEG_t_mean = 0.0f;
    }
    else if (it->second->type == BETA_GAUSSIAN)
    {
      BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)it->second;
      gupdate_edge->old_inc_wp = 0.0f;
      gupdate_edge->old_inc_wn = 0.0f;
      gupdate_edge->E_POS_wp_mean = 0.0f;
      gupdate_edge->E_NEG_wp_mean = 0.0f;
      gupdate_edge->E_POS_wn_mean = 0.0f;
      gupdate_edge->E_NEG_wn_mean = 0.0f;
    }
    else
    {
      std::cerr << "Internal error: BetaNode::init supports initialization of weights between only Gaussian/Beta nodes" << std::endl;
      exit(-1);
    }
  }

  if (do_not_init_parameters)
    return;

    if (layer->below_layer == NULL)
    {
      if (isinv(a[1]))
      {
        a[1] = 1.0f;
        b[1] = 1.0f;
      }
    }
    else
    {
      if (isinv(a[0]))
      {
        a[0] = 1.0f; 
        b[0] = 1.0f;
      }
    }

	// initialize CHILDREN and SIBLING edges.
	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == BETA_BETA )
		{
			BetaBetaDLEdge* gupdate_edge = (BetaBetaDLEdge*)it->second;
			//BetaNode* gupdate_neighbor = (BetaNode*)it->first;
			if (it->first->layer != this->layer)
			{
				gupdate_edge->w = unifRand(EPSILONf, .01f);
				gupdate_edge->q = unifRand(EPSILONf, .01f);
				gupdate_edge->s = unifRand(EPSILONf, .01f);
				gupdate_edge->t = unifRand(EPSILONf, .01f);
			}
			else
			{
				gupdate_edge->w = EPSILONf;
				gupdate_edge->q = EPSILONf;
				gupdate_edge->s = EPSILONf;
				gupdate_edge->t = EPSILONf;
			}
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			BetaGaussianDLEdge *gupdate_edge = (BetaGaussianDLEdge*)it->second;
			gupdate_edge->wp = unifRand(EPSILONf, .01f);
			gupdate_edge->wn = unifRand(EPSILONf, .01f);
		}
		else
		{
			std::cerr << "Internal error: BetaNode::init supports initialization of weights between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void BetaNode::scaleTrainingData(bool training_data_scaling_already_done)
{
	if (!training_data_scaling_already_done)
		prop.getBasicRandomVariableProperties( removeElements(V, FLT_MAX) );
	float dscale = 2.0f * (prop.max - prop.min) + EPSILONf;
	V = (V.array() != FLT_MAX).select( (V.array() - prop.min + dscale / 4.0f) / dscale, V); // scale then in the [.25 .75] interval
}

void BetaNode::rescale()
{
	if (!prop.valid)
	{
		std::cerr << "Internal error: BetaNode::rescale was called before mean/std is computed." << std::endl;
		exit(-1);
	}
	float dscale = 2.0f * (prop.max - prop.min) + EPSILONf;
	q_mean = (q_mean.array() != FLT_MAX).select( (q_mean.array() - prop.min + dscale / 4.0f) / dscale, q_mean); // scale then in the [.25 .75] interval
	log_q_mean = (q_mean.array() != FLT_MAX).select( q_mean.array().log(), q_mean );
	log_one_minus_q_mean =  (q_mean.array() != FLT_MAX).select( ( 1.0f - q_mean.array() ).log(), q_mean );
}

void BetaNode::unscale()
{
	out_mean = q_mean(0);
	if (!prop.valid)
		return;

	float dscale = 2.0f * (prop.max - prop.min) + EPSILONf;
	out_mean = q_mean(0) * dscale + prop.min - dscale / 4.0f;		
}


void BetaNode::saveWeights()
{
	sav_a[0] = a[0];
	sav_a[1] = a[1];
	sav_b[0] = b[0];
	sav_b[1] = b[1];

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == BETA_BETA)
		{
			((BetaBetaDLEdge*)it->second)->sav_w = ((BetaBetaDLEdge*)it->second)->w;
			((BetaBetaDLEdge*)it->second)->sav_q = ((BetaBetaDLEdge*)it->second)->q;
			((BetaBetaDLEdge*)it->second)->sav_s = ((BetaBetaDLEdge*)it->second)->s;
			((BetaBetaDLEdge*)it->second)->sav_t = ((BetaBetaDLEdge*)it->second)->t;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it->second)->sav_wp = ((BetaGaussianDLEdge*)it->second)->wp;
			((BetaGaussianDLEdge*)it->second)->sav_wn = ((BetaGaussianDLEdge*)it->second)->wn;
		}
		else
		{
			std::cerr << "BetaNode::saveWeights supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}



void BetaNode::saveEdgeWeights(bool clear)
{
	if (clear)
	{
		for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
		{
			if (it->second->type == BETA_BETA)
			{
				((BetaBetaDLEdge*)it->second)->old_inc_w = 0.0f;
				((BetaBetaDLEdge*)it->second)->old_inc_q = 0.0f;
				((BetaBetaDLEdge*)it->second)->old_inc_s = 0.0f;
				((BetaBetaDLEdge*)it->second)->old_inc_t = 0.0f;
			}
			else if (it->second->type == BETA_GAUSSIAN)
			{
				((BetaGaussianDLEdge*)it->second)->old_inc_wp = 0.0f;
				((BetaGaussianDLEdge*)it->second)->old_inc_wn = 0.0f;
			}
			else
			{
				std::cerr << "BetaNode::saveEdgeWeights supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
				exit(-1);
			}
		}

		return;
	}

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == BETA_BETA)
		{
			((BetaBetaDLEdge*)it->second)->old_inc_w = ((BetaBetaDLEdge*)it->second)->w;
			((BetaBetaDLEdge*)it->second)->old_inc_q = ((BetaBetaDLEdge*)it->second)->q;
			((BetaBetaDLEdge*)it->second)->old_inc_s = ((BetaBetaDLEdge*)it->second)->s;
			((BetaBetaDLEdge*)it->second)->old_inc_t = ((BetaBetaDLEdge*)it->second)->t;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it->second)->old_inc_wp = ((BetaGaussianDLEdge*)it->second)->wp;
			((BetaGaussianDLEdge*)it->second)->old_inc_wn = ((BetaGaussianDLEdge*)it->second)->wn;
		}
		else
		{
			std::cerr << "BetaNode::saveEdgeWeights supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void BetaNode::restoreSavedWeights()
{
	a[0] = sav_a[0];
	a[1] = sav_a[1];
	b[0] = sav_b[0];
	b[1] = sav_b[1];

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		if (it->second->type == BETA_BETA)
		{
			((BetaBetaDLEdge*)it->second)->w = ((BetaBetaDLEdge*)it->second)->sav_w;
			((BetaBetaDLEdge*)it->second)->q = ((BetaBetaDLEdge*)it->second)->sav_q;
			((BetaBetaDLEdge*)it->second)->s = ((BetaBetaDLEdge*)it->second)->sav_s;
			((BetaBetaDLEdge*)it->second)->t = ((BetaBetaDLEdge*)it->second)->sav_t;
		}
		else if (it->second->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it->second)->wp = ((BetaGaussianDLEdge*)it->second)->sav_wp;
			((BetaGaussianDLEdge*)it->second)->wn = ((BetaGaussianDLEdge*)it->second)->sav_wn;
		}
		else
		{
			std::cerr << "BetaNode::saveWeights supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void BetaNode::copyParameters(DLNode *source_node)
{
	BetaNode *bsource_node = (BetaNode*)source_node;
	a[0] = bsource_node->a[0];
	a[1] = bsource_node->a[1];
	b[0] = bsource_node->b[0];
	b[1] = bsource_node->b[1];

	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge* it = update_edges[e];
		DLEdge* bit = bsource_node->update_edges[e];

		if (it->type == BETA_BETA)
		{
			((BetaBetaDLEdge*)it)->w = ((BetaBetaDLEdge*)bit)->w;
			((BetaBetaDLEdge*)it)->q = ((BetaBetaDLEdge*)bit)->q;
			((BetaBetaDLEdge*)it)->s = ((BetaBetaDLEdge*)bit)->s;
			((BetaBetaDLEdge*)it)->t = ((BetaBetaDLEdge*)bit)->t;
		}
		else if (it->type == BETA_GAUSSIAN)
		{
			((BetaGaussianDLEdge*)it)->wp = ((BetaGaussianDLEdge*)bit)->wp;
			((BetaGaussianDLEdge*)it)->wn = ((BetaGaussianDLEdge*)bit)->wn;
		}
		else
		{
			std::cerr << "BetaNode::copyParameters supports edge weight saving between only Gaussian/Beta nodes" << std::endl;
			exit(-1);
		}
	}
}

void BetaNode::copyBias(DLNode *source_node, int bias_id)
{
	BetaNode *bsource_node = (BetaNode*)source_node;
	a[bias_id] = bsource_node->a[bias_id];
	b[bias_id] = bsource_node->b[bias_id];
}


///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
/////////// BINARY NODE FUNCTIONS ////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////



void BinaryNode::doInference()
{
	if ( is_observed )
		return;
	bool ready = false;
	if ( layer->above_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit )
			ready = true;
	if ( layer->below_layer != NULL )
		if ( layer->below_layer->is_ready_to_transmit )
			ready = true;
	if (!ready)
		return;	

	q_mean.fill(0.0f);

	for (size_t e = 0; e < all_edges.size(); e++)
	{
		DLEdge* dledge = all_edges[e];

		switch( dledge->type )
		{
		case BINARY_BINARY:
			{
				BinaryNode *neighbor = (BinaryNode *)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				BinaryBinaryDLEdge *edge = (BinaryBinaryDLEdge*)dledge;
				q_mean += edge->w * neighbor->q_mean;
				break;
			}
		case BINARY_GAUSSIAN:
			{
				GaussianNode *neighbor = (GaussianNode *)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				BinaryGaussianDLEdge *edge = (BinaryGaussianDLEdge*)dledge;
				q_mean += edge->w * (neighbor->q_mean / neighbor->s);
				break;
			}
		case BINARY_BETA:
			{
				BetaNode *neighbor = (BetaNode *)neighbors[e];
				if (isinv(neighbor->q_mean(0)))
					continue;
				BinaryBetaDLEdge *edge = (BinaryBetaDLEdge*)dledge;
				q_mean += ( edge->wp * neighbor->log_q_mean + edge->wn * neighbor->log_one_minus_q_mean );
				break;
			}
    case BINARY_DOUBLEBETA:
    {
      BetaNode *neighbor = (BetaNode *)neighbors[e];
      if (isinv(neighbor->q_mean(0)))
        continue;
      BinaryDoubleBetaDLEdge *edge = (BinaryDoubleBetaDLEdge*)dledge;
      q_mean += ( (edge->wp - edge->qp) * neighbor->log_q_mean + (edge->wn - edge->qn) * neighbor->log_one_minus_q_mean);
      break;
    }
		default:
			std::cerr << "Internal error: GaussianNode::doInference supports inference updates only from Gaussian/Beta nodes" << std::endl;
			exit(-1);
		} // end of switch
	}

	if ( layer->above_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit)
			q_mean = q_mean.array() + b[1];

	if ( layer->below_layer != NULL )
		if ( layer->below_layer->is_ready_to_transmit )
			q_mean = q_mean.array() + b[0];

	if ( layer->above_layer != NULL && layer->below_layer != NULL )
		if ( layer->above_layer->is_ready_to_transmit && layer->below_layer->is_ready_to_transmit )
			q_mean = .5f * q_mean;

	limit(q_mean, -50.0f, 50.0f ); // prevent numerical overflow/underflow
	q_mean = sigmoid(q_mean);
}

void BinaryNode::updatePriors()
{
	// updatePriors is used only for hidden nodes, so if q_mean(m)=log_q_mean(m) [invalid], don't worry
	p_b = q_mean.mean();
}

void BinaryNode::sample(RAND_GEN& rng)
{
	for (int m = 0; m < q_mean.size(); m++)
	{
		boost::random::uniform_real_distribution<float> rand(0.0f, 1.0f);
    q_mean(m) = rand(rng); //p_b > rand(rng);
	}
}

void BinaryNode::sampleAndDiscretize(RAND_GEN& rng)
{
  for (int m = 0; m < q_mean.size(); m++)
  {
    boost::random::uniform_real_distribution<float> rand(0.0f, 1.0f);
    q_mean(m) = .5f > rand(rng);
  }
}

void BinaryNode::condSample(RAND_GEN& rng)
{
	for (int m = 0; m < q_mean.size(); m++)
	{
		boost::random::uniform_real_distribution<float> rand(0.0f, 1.0f);		
		q_mean(m) = q_mean(m) > rand(rng);
	}
}

void BinaryNode::unscale()
{
	out_mean = q_mean(0) >= .5f;
}



SVECTORf BinaryNode::measureEnergy()
{
	SVECTORf uprob = SVECTORf::Zero( q_mean.size() );
	SVECTORf val = round( q_mean ); // round(q_mean)?

	if ( layer->above_layer != NULL )
		uprob.array() -= val.array() * b[1];

	if ( layer->below_layer != NULL )
    uprob.array() -= val.array() * b[0];

	if ( layer->above_layer != NULL && layer->below_layer != NULL )
		uprob.array() *= .5f;

	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];

		switch( dledge->type )
		{
		case BINARY_BINARY:
			{
				BinaryBinaryDLEdge* gupdate_edge = (BinaryBinaryDLEdge*)dledge;
				BinaryNode* gupdate_neighbor = (BinaryNode*)update_neighbors[e];
				uprob.array() -= gupdate_edge->w * val.array() * round( gupdate_neighbor->q_mean ).array(); // round?
				break;
			}
		case BINARY_GAUSSIAN:
			{
				BinaryGaussianDLEdge* gupdate_edge = (BinaryGaussianDLEdge*)dledge;
				GaussianNode* gupdate_neighbor = (GaussianNode*)update_neighbors[e];
				uprob.array() -= gupdate_edge->w * val.array() * ( gupdate_neighbor->q_mean.array() / gupdate_neighbor->s );
				break;
			}
		case BINARY_BETA:
			{
				BinaryBetaDLEdge* gupdate_edge = (BinaryBetaDLEdge*)dledge;
				BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
				uprob.array() -= gupdate_edge->wp * val.array() * gupdate_neighbor->log_q_mean.array();
				uprob.array() -= gupdate_edge->wn * val.array() * gupdate_neighbor->log_one_minus_q_mean.array();
				break;
			}
    case BINARY_DOUBLEBETA:
    {
      BinaryDoubleBetaDLEdge* gupdate_edge = (BinaryDoubleBetaDLEdge*)dledge;
      BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
      uprob.array() -= gupdate_edge->wp * val.array() * gupdate_neighbor->log_q_mean.array();
      uprob.array() -= gupdate_edge->wn * val.array() * gupdate_neighbor->log_one_minus_q_mean.array();
      uprob.array() -= gupdate_edge->qp * (1.0f - val.array()) * gupdate_neighbor->log_q_mean.array();
      uprob.array() -= gupdate_edge->qn * (1.0f - val.array()) * gupdate_neighbor->log_one_minus_q_mean.array();
      break;
    }
		default:
			std::cerr << "Internal error: Binary::measureEnergy supports expectation updates  when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
			exit(-1);
		} // end of switch
	}

	return uprob;
}

void BinaryNode::updateExpectations(phase_type phase)
{
	if ( phase == POSITIVE_PHASE )
		E_POS_b_mean = q_mean.mean();
	else
		E_NEG_b_mean = q_mean.mean();

	if (lock_parameters)
		return;

	// Update expectations only for CHILDREN and SIBLING edges
	//for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];

		switch( dledge->type )
		{
		case BINARY_BINARY:
			{
				BinaryBinaryDLEdge* gupdate_edge = (BinaryBinaryDLEdge*)dledge;
				BinaryNode* gupdate_neighbor = (BinaryNode*)update_neighbors[e];
				if ( phase == POSITIVE_PHASE )
					gupdate_edge->E_POS_w_mean = ( q_mean.array() * gupdate_neighbor->q_mean.array() ).mean();
				else
					gupdate_edge->E_NEG_w_mean = ( q_mean.array() * gupdate_neighbor->q_mean.array() ).mean();
				break;
			}
		case BINARY_GAUSSIAN:
			{
				BinaryGaussianDLEdge* gupdate_edge = (BinaryGaussianDLEdge*)dledge;
				GaussianNode* gupdate_neighbor = (GaussianNode*)update_neighbors[e];
				if ( phase == POSITIVE_PHASE )
					gupdate_edge->E_POS_w_mean = ( q_mean.array() * (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s) ).mean();
				else
					gupdate_edge->E_NEG_w_mean = ( q_mean.array() * (gupdate_neighbor->q_mean.array() / gupdate_neighbor->s) ).mean();
				break;
			}
		case BINARY_BETA:
			{
				BinaryBetaDLEdge* gupdate_edge = (BinaryBetaDLEdge*)dledge;
				BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
				if ( phase == POSITIVE_PHASE )
				{
					gupdate_edge->E_POS_wp_mean = ( q_mean.array() * gupdate_neighbor->log_q_mean.array() ).mean();
					gupdate_edge->E_POS_wn_mean = ( q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
				}
				else
				{
					gupdate_edge->E_NEG_wp_mean = ( q_mean.array() * gupdate_neighbor->log_q_mean.array() ).mean();
					gupdate_edge->E_NEG_wn_mean = ( q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array() ).mean();
				}
				break;
			}
    case BINARY_DOUBLEBETA:
    {
      BinaryDoubleBetaDLEdge* gupdate_edge = (BinaryDoubleBetaDLEdge*)dledge;
      BetaNode* gupdate_neighbor = (BetaNode*)update_neighbors[e];
      if (phase == POSITIVE_PHASE)
      {
        gupdate_edge->E_POS_wp_mean = (q_mean.array() * gupdate_neighbor->log_q_mean.array()).mean();
        gupdate_edge->E_POS_wn_mean = (q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array()).mean();
        gupdate_edge->E_POS_qp_mean = ( (1.0f - q_mean.array()) * gupdate_neighbor->log_q_mean.array()).mean();
        gupdate_edge->E_POS_qn_mean = ( (1.0f - q_mean.array()) * gupdate_neighbor->log_one_minus_q_mean.array()).mean();
      }
      else
      {
        gupdate_edge->E_NEG_wp_mean = (q_mean.array() * gupdate_neighbor->log_q_mean.array()).mean();
        gupdate_edge->E_NEG_wn_mean = (q_mean.array() * gupdate_neighbor->log_one_minus_q_mean.array()).mean();
        gupdate_edge->E_NEG_qp_mean = ((1.0f - q_mean.array()) * gupdate_neighbor->log_q_mean.array()).mean();
        gupdate_edge->E_NEG_qn_mean = ((1.0f - q_mean.array()) * gupdate_neighbor->log_one_minus_q_mean.array()).mean();
      }
      break;
    }
		default:
			std::cerr << "Internal error: Binary::updateExpectations supports expectation updates  when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
			exit(-1);
		} // end of switch
	}
}

void BinaryNode::updateParameters(int number_of_training_examples, float learning_rate, float momentum, const regularization_type& reg_type, float reg_weight )
{
	float grad_b = (E_POS_b_mean - E_NEG_b_mean);
	float inc_b = momentum * old_inc_b + learning_rate * grad_b;

	if ( layer->below_layer == NULL )
		b[1] += inc_b;
	else
		b[0] += inc_b;

	old_inc_b = inc_b;

	if (lock_parameters)
		return;

	// Update parameters only for CHILDREN and SIBLING edges
	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge *dledge = update_edges[e];	

		switch( dledge->type )
		{
		case BINARY_BINARY:
			{
				BinaryBinaryDLEdge* gupdate_edge = (BinaryBinaryDLEdge*)dledge;
				float grad_w = (gupdate_edge->E_POS_w_mean - gupdate_edge->E_NEG_w_mean);
				float inc_w = momentum * gupdate_edge->old_inc_w + learning_rate * grad_w;

				switch( reg_type )
				{
				case L1:
					{
						inc_w -= learning_rate * reg_weight * sgn( gupdate_edge->w );
						break;
					}
				case L2:
					{
						inc_w -= learning_rate * reg_weight * gupdate_edge->w;
						break;
					}
				case LS1L1:
				case LS2L2:
				case LS1:
				case LS2:
				{
					DLNode *dlneighbor = update_neighbors[e];
					for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
					{
						BinaryBinaryDLEdge* gnupdate_edge = (BinaryBinaryDLEdge*)owned_edges[dlneighbor->spatial_neighbors[es]];
						float weight = reg_weight * dlneighbor->spatial_neighbors_weights[es];
						if (reg_type == LS2)
							inc_w -= learning_rate * weight * (gupdate_edge->w - gnupdate_edge->w);
						else
							inc_w -= learning_rate * weight * sgn(gupdate_edge->w - gnupdate_edge->w);
					}

					if (reg_type == LS1L1)
						inc_w -= learning_rate * reg_weight * sgn(gupdate_edge->w);
					if (reg_type == LS2L2)
						inc_w -= learning_rate * reg_weight * gupdate_edge->w;
					
					break;
				}
				case LNONE:
					break;
				default:
					std::cerr << "Internal error: BinaryNode::updateParameters: unknown regularization type" << std::endl;
					exit(-1);
				} // end of switch statement for regulariaztion

				gupdate_edge->w += inc_w;
				gupdate_edge->old_inc_w = inc_w;
				break;
			} // end of BINARY_BINARY

		case BINARY_GAUSSIAN:
			{
				BinaryGaussianDLEdge* gupdate_edge = (BinaryGaussianDLEdge*)dledge;
				float grad_w = (gupdate_edge->E_POS_w_mean - gupdate_edge->E_NEG_w_mean);
				float inc_w = momentum * gupdate_edge->old_inc_w + learning_rate * grad_w;

				switch( reg_type )
				{
				case L1:
					{
						inc_w -= learning_rate * reg_weight * sgn( gupdate_edge->w );
						break;
					}
				case L2:
					{
						inc_w -= learning_rate * reg_weight * gupdate_edge->w;
						break;
					}
				case LS1L1:
				case LS2L2:
				case LS1:
				case LS2:
					{
						DLNode *dlneighbor = update_neighbors[e];
						for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
						{						
							BinaryGaussianDLEdge* gnupdate_edge = (BinaryGaussianDLEdge*)owned_edges[ dlneighbor->spatial_neighbors[es] ];
							float weight = reg_weight * dlneighbor->spatial_neighbors_weights[es];
							if (reg_type == LS2)
								inc_w -= learning_rate * weight * ( gupdate_edge->w - gnupdate_edge->w );
							else
								inc_w -= learning_rate * weight * sgn( gupdate_edge->w - gnupdate_edge->w );
						}

						if (reg_type == LS1L1)
							inc_w -= learning_rate * reg_weight * sgn(gupdate_edge->w);
						if (reg_type == LS2L2)
							inc_w -= learning_rate * reg_weight * gupdate_edge->w;

						break;
					}
				case LNONE:
					break;
				default:
					std::cerr << "Internal error: BinaryNode::updateParameters: unknown regularization type" << std::endl;
					exit(-1);
				} // end of switch statement for regulariaztion

				gupdate_edge->w += inc_w;
				gupdate_edge->old_inc_w = inc_w;
				break;
			} // end of BINARY_GAUSSIAN

		case BINARY_BETA:
			{
				BinaryBetaDLEdge* gupdate_edge = (BinaryBetaDLEdge*)dledge;
				float grad_wp = (gupdate_edge->E_POS_wp_mean - gupdate_edge->E_NEG_wp_mean);
				float grad_wn = (gupdate_edge->E_POS_wn_mean - gupdate_edge->E_NEG_wn_mean);
				float inc_wp = momentum * gupdate_edge->old_inc_wp + learning_rate * grad_wp;
				float inc_wn = momentum * gupdate_edge->old_inc_wn + learning_rate * grad_wn;

				switch( reg_type )
				{
				case L1:
					{
						inc_wp -= learning_rate * reg_weight * sgn( gupdate_edge->wp );
						inc_wn -= learning_rate * reg_weight * sgn( gupdate_edge->wn );
						break;
					}
				case L2:
					{
						inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
						inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
						break;
					}
				case LS1L1:
				case LS2L2:
				case LS1:
				case LS2:
					{
						DLNode *dlneighbor = update_neighbors[e];
						for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
						{
							BinaryBetaDLEdge* gnupdate_edge = (BinaryBetaDLEdge*)owned_edges[ dlneighbor->spatial_neighbors[es] ];
							float weight = reg_weight * dlneighbor->spatial_neighbors_weights[es];
							if (reg_type == LS2)
							{
								inc_wp -= learning_rate * weight * ( gupdate_edge->wp - gnupdate_edge->wp );
								inc_wn -= learning_rate * weight * ( gupdate_edge->wn - gnupdate_edge->wn );
							}
							else
							{
								inc_wp -= learning_rate * weight * sgn( gupdate_edge->wp - gnupdate_edge->wp );
								inc_wn -= learning_rate * weight * sgn( gupdate_edge->wn - gnupdate_edge->wn );
							}
						}

						if (reg_type == LS1L1)
						{
							inc_wp -= learning_rate * reg_weight * sgn(gupdate_edge->wp);
							inc_wn -= learning_rate * reg_weight * sgn(gupdate_edge->wn);
						}
						if (reg_type == LS2L2)
						{
							inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
							inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
						}

						break;
					} 
				case LNONE:
					break;
				default:
					std::cerr << "Internal error: BinaryNode::updateParameters: unknown regularization type" << std::endl;
					exit(-1);
				} // end of switch statement for regulariaztion

				inc_wp = std::max( inc_wp, EPSILONf - gupdate_edge->wp);
				inc_wn = std::max( inc_wn, EPSILONf - gupdate_edge->wn);
				gupdate_edge->wp += inc_wp;
				gupdate_edge->wn += inc_wn;
				gupdate_edge->old_inc_wp = inc_wp;
				gupdate_edge->old_inc_wn = inc_wn;
				break;
			} // end of BINARY_BETA

    case BINARY_DOUBLEBETA:
      {
        BinaryDoubleBetaDLEdge* gupdate_edge = (BinaryDoubleBetaDLEdge*)dledge;
        float grad_wp = (gupdate_edge->E_POS_wp_mean - gupdate_edge->E_NEG_wp_mean);
        float grad_wn = (gupdate_edge->E_POS_wn_mean - gupdate_edge->E_NEG_wn_mean);
        float grad_qp = (gupdate_edge->E_POS_qp_mean - gupdate_edge->E_NEG_qp_mean);
        float grad_qn = (gupdate_edge->E_POS_qn_mean - gupdate_edge->E_NEG_qn_mean);
        float inc_wp = momentum * gupdate_edge->old_inc_wp + learning_rate * grad_wp;
        float inc_wn = momentum * gupdate_edge->old_inc_wn + learning_rate * grad_wn;
        float inc_qp = momentum * gupdate_edge->old_inc_qp + learning_rate * grad_qp;
        float inc_qn = momentum * gupdate_edge->old_inc_qn + learning_rate * grad_qn;

        switch (reg_type)
        {
        case L1:
        {
          inc_wp -= learning_rate * reg_weight * sgn(gupdate_edge->wp);
          inc_wn -= learning_rate * reg_weight * sgn(gupdate_edge->wn);
          inc_qp -= learning_rate * reg_weight * sgn(gupdate_edge->qp);
          inc_qn -= learning_rate * reg_weight * sgn(gupdate_edge->qn);
          break;
        }
        case L2:
        {
          inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
          inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
          inc_qp -= learning_rate * reg_weight * gupdate_edge->qp;
          inc_qn -= learning_rate * reg_weight * gupdate_edge->qn;
          break;
        }
        case LS1L1:
        case LS2L2:
        case LS1:
        case LS2:
        {
          DLNode *dlneighbor = update_neighbors[e];
          for (size_t es = 0; es < dlneighbor->spatial_neighbors.size(); es++)
          {
            BinaryDoubleBetaDLEdge* gnupdate_edge = (BinaryDoubleBetaDLEdge*)owned_edges[dlneighbor->spatial_neighbors[es]];
            float weight = reg_weight * dlneighbor->spatial_neighbors_weights[es];
            if (reg_type == LS2)
            {
              inc_wp -= learning_rate * weight * (gupdate_edge->wp - gnupdate_edge->wp);
              inc_wn -= learning_rate * weight * (gupdate_edge->wn - gnupdate_edge->wn);
              inc_qp -= learning_rate * weight * (gupdate_edge->qp - gnupdate_edge->qp);
              inc_qn -= learning_rate * weight * (gupdate_edge->qn - gnupdate_edge->qn);
            }
            else
            {
              inc_wp -= learning_rate * weight * sgn(gupdate_edge->wp - gnupdate_edge->wp);
              inc_wn -= learning_rate * weight * sgn(gupdate_edge->wn - gnupdate_edge->wn);
              inc_qp -= learning_rate * weight * sgn(gupdate_edge->qp - gnupdate_edge->qp);
              inc_qn -= learning_rate * weight * sgn(gupdate_edge->qn - gnupdate_edge->qn);
            }
          }

          if (reg_type == LS1L1)
          {
            inc_wp -= learning_rate * reg_weight * sgn(gupdate_edge->wp);
            inc_wn -= learning_rate * reg_weight * sgn(gupdate_edge->wn);
            inc_qp -= learning_rate * reg_weight * sgn(gupdate_edge->qp);
            inc_qn -= learning_rate * reg_weight * sgn(gupdate_edge->qn);
          }
          if (reg_type == LS2L2)
          {
            inc_wp -= learning_rate * reg_weight * gupdate_edge->wp;
            inc_wn -= learning_rate * reg_weight * gupdate_edge->wn;
            inc_qp -= learning_rate * reg_weight * gupdate_edge->qp;
            inc_qn -= learning_rate * reg_weight * gupdate_edge->qn;
          }

          break;
        }
        case LNONE:
          break;
        default:
          std::cerr << "Internal error: BinaryNode::updateParameters: unknown regularization type" << std::endl;
          exit(-1);
        } // end of switch statement for regulariaztion

        inc_wp = std::max(inc_wp, EPSILONf - gupdate_edge->wp);
        inc_wn = std::max(inc_wn, EPSILONf - gupdate_edge->wn);
        inc_qp = std::max(inc_qp, EPSILONf - gupdate_edge->qp);
        inc_qn = std::max(inc_qn, EPSILONf - gupdate_edge->qn);
        gupdate_edge->wp += inc_wp;
        gupdate_edge->wn += inc_wn;
        gupdate_edge->qp += inc_qp;
        gupdate_edge->qn += inc_qn;
        gupdate_edge->old_inc_wp = inc_wp;
        gupdate_edge->old_inc_wn = inc_wn;
        gupdate_edge->old_inc_qp = inc_qp;
        gupdate_edge->old_inc_qn = inc_qn;
        break;
      } // end of BINARY_DOUBLEBETA

		default:
			std::cerr << "Internal error: BinaryNode::updateParameters supports parameter updates when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
			exit(-1);
		} // end of switch
	} // end of for
}

void BinaryNode::init(bool do_not_init_parameters)
{
	old_inc_b = 0.0f;
	E_POS_b_mean = 0.0f;
	E_NEG_b_mean = 0.0f;

	// initialize CHILDREN and SIBLING edges.
	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		switch (it->second->type)
		{
		case BINARY_BINARY:
			{
				BinaryBinaryDLEdge* gupdate_edge = (BinaryBinaryDLEdge*)it->second;
				gupdate_edge->old_inc_w = 0.0f;
				gupdate_edge->E_POS_w_mean = 0.0f;
				gupdate_edge->E_NEG_w_mean = 0.0f;
				break;
			}
		case BINARY_GAUSSIAN:
			{
				BinaryGaussianDLEdge* gupdate_edge = (BinaryGaussianDLEdge*)it->second;
				gupdate_edge->old_inc_w = 0.0f;
				gupdate_edge->E_POS_w_mean = 0.0f;
				gupdate_edge->E_NEG_w_mean = 0.0f;
				break;
			}
		case BINARY_BETA:
			{
				BinaryBetaDLEdge* gupdate_edge = (BinaryBetaDLEdge*)it->second;
				gupdate_edge->old_inc_wp = 0.0f;
				gupdate_edge->old_inc_wn = 0.0f;
				gupdate_edge->E_POS_wp_mean = 0.0f;
				gupdate_edge->E_NEG_wp_mean = 0.0f;
				gupdate_edge->E_POS_wn_mean = 0.0f;
				gupdate_edge->E_NEG_wn_mean = 0.0f;
				break;
			}
    case BINARY_DOUBLEBETA:
      {
        BinaryDoubleBetaDLEdge* gupdate_edge = (BinaryDoubleBetaDLEdge*)it->second;
        gupdate_edge->old_inc_wp = 0.0f;
        gupdate_edge->old_inc_wn = 0.0f;
        gupdate_edge->old_inc_qp = 0.0f;
        gupdate_edge->old_inc_qn = 0.0f;
        gupdate_edge->E_POS_wp_mean = 0.0f;
        gupdate_edge->E_NEG_wp_mean = 0.0f;
        gupdate_edge->E_POS_wn_mean = 0.0f;
        gupdate_edge->E_NEG_wn_mean = 0.0f;
        gupdate_edge->E_POS_qp_mean = 0.0f;
        gupdate_edge->E_NEG_qp_mean = 0.0f;
        gupdate_edge->E_POS_qn_mean = 0.0f;
        gupdate_edge->E_NEG_qn_mean = 0.0f;
        break;
      }
		default:
			{
				std::cerr << "Internal error: BinaryNode::init supports initialization of weights when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
				exit(-1);
			}
		}
	}

	if (do_not_init_parameters)
		return;

	if ( layer->below_layer == NULL )
	{
		if ( isinv(b[1]) )
			b[1] = 0.0f;
	}
	else
	{
		if ( isinv(b[0]) )
			b[0] = 0.0f;
	}

	// initialize CHILDREN and SIBLING edges.
	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		switch (it->second->type)
		{
		case BINARY_BINARY:
			{
				BinaryBinaryDLEdge* gupdate_edge = (BinaryBinaryDLEdge*)it->second;
				gupdate_edge->w = unifRand(-1.0f, 1.0f);
				break;
			}
		case BINARY_GAUSSIAN:
			{
				BinaryGaussianDLEdge* gupdate_edge = (BinaryGaussianDLEdge*)it->second;
				gupdate_edge->w = unifRand(-.1f, .1f);
				break;
			}
		case BINARY_BETA:
			{
				BinaryBetaDLEdge* gupdate_edge = (BinaryBetaDLEdge*)it->second;
				gupdate_edge->wp = unifRand(EPSILONf, .001f);
				gupdate_edge->wn = unifRand(EPSILONf, .001f);
				break;
			}
    case BINARY_DOUBLEBETA:
      { 
        BinaryDoubleBetaDLEdge* gupdate_edge = (BinaryDoubleBetaDLEdge*)it->second;
        gupdate_edge->wp = unifRand(EPSILONf, .001f);
        gupdate_edge->wn = unifRand(EPSILONf, .001f); 
        gupdate_edge->qp = unifRand(EPSILONf, .001f);
        gupdate_edge->qn = unifRand(EPSILONf, .001f);
        break;
      }
		default:
			{
				std::cerr << "Internal error: BinaryNode::init supports initialization of weights when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
				exit(-1);
			}
		}
	}
}



void BinaryNode::saveWeights()
{
	sav_b[0] = b[0];
	sav_b[1] = b[1];

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		switch (it->second->type)
		{
		case BINARY_BINARY:
			{
				((BinaryBinaryDLEdge*)it->second)->sav_w = ((BinaryBinaryDLEdge*)it->second)->w;
				break;
			}
		case BINARY_GAUSSIAN:
			{
				((BinaryGaussianDLEdge*)it->second)->sav_w = ((BinaryGaussianDLEdge*)it->second)->w;
				break;
			}
		case BINARY_BETA:
			{
				((BinaryBetaDLEdge*)it->second)->sav_wp = ((BinaryBetaDLEdge*)it->second)->wp;
				((BinaryBetaDLEdge*)it->second)->sav_wn = ((BinaryBetaDLEdge*)it->second)->wn;
				break;
			}		
    case BINARY_DOUBLEBETA:
      {
        ((BinaryDoubleBetaDLEdge*)it->second)->sav_wp = ((BinaryDoubleBetaDLEdge*)it->second)->wp;
        ((BinaryDoubleBetaDLEdge*)it->second)->sav_wn = ((BinaryDoubleBetaDLEdge*)it->second)->wn;
        ((BinaryDoubleBetaDLEdge*)it->second)->sav_qp = ((BinaryDoubleBetaDLEdge*)it->second)->qp;
        ((BinaryDoubleBetaDLEdge*)it->second)->sav_qn = ((BinaryDoubleBetaDLEdge*)it->second)->qn;
        break;
      }
		default:
			{
				std::cerr << "BinaryNode::saveWeights supports edge weight saving when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
				exit(-1);
			}
		}
	}
}


void BinaryNode::saveEdgeWeights(bool clear)
{
	if (clear)
	{
		for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
		{
			switch (it->second->type)
			{
			case BINARY_BINARY:
				{
					((BinaryBinaryDLEdge*)it->second)->old_inc_w = 0.0f;
					break;
				}
			case BINARY_GAUSSIAN:
				{
					((BinaryGaussianDLEdge*)it->second)->old_inc_w = 0.0f;
					break;
				}
			case BINARY_BETA:
				{
					((BinaryBetaDLEdge*)it->second)->old_inc_wp = 0.0f;
					((BinaryBetaDLEdge*)it->second)->old_inc_wn = 0.0f;
					break;
				}		
      case BINARY_DOUBLEBETA:
        {
          ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_wp = 0.0f;
          ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_wn = 0.0f;
          ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_qp = 0.0f;
          ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_qn = 0.0f;
          break;
        }
			default:
				{
					std::cerr << "BinaryNode::saveEdgeWeights supports edge weight saving when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
					exit(-1);
				}
			}
		}
		return;
	}

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		switch (it->second->type)
		{
		case BINARY_BINARY:
			{
				((BinaryBinaryDLEdge*)it->second)->old_inc_w = ((BinaryBinaryDLEdge*)it->second)->w;
				break;
			}
		case BINARY_GAUSSIAN:
			{
				((BinaryGaussianDLEdge*)it->second)->old_inc_w = ((BinaryGaussianDLEdge*)it->second)->w;
				break;
			}
		case BINARY_BETA:
			{
				((BinaryBetaDLEdge*)it->second)->old_inc_wp = ((BinaryBetaDLEdge*)it->second)->wp;
				((BinaryBetaDLEdge*)it->second)->old_inc_wn = ((BinaryBetaDLEdge*)it->second)->wn;
				break;
			}		
      case BINARY_DOUBLEBETA:
      {
        ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_wp = ((BinaryDoubleBetaDLEdge*)it->second)->wp;
        ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_wn = ((BinaryDoubleBetaDLEdge*)it->second)->wn;
        ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_qp = ((BinaryDoubleBetaDLEdge*)it->second)->qp;
        ((BinaryDoubleBetaDLEdge*)it->second)->old_inc_qn = ((BinaryDoubleBetaDLEdge*)it->second)->qn;
        break;
      }
		default:
			{
				std::cerr << "BinaryNode::saveEdgeWeights supports edge weight saving when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
				exit(-1);
			}
		}
	}
}

void BinaryNode::restoreSavedWeights()
{
	b[0] = sav_b[0];
	b[1] = sav_b[1];

	for( UNORDERED_MAP<DLNode*, DLEdge*>::const_iterator it = owned_edges.begin(); it != owned_edges.end(); ++it )
	{
		switch (it->second->type)
		{
		case BINARY_BINARY:
			{
				((BinaryBinaryDLEdge*)it->second)->w = ((BinaryBinaryDLEdge*)it->second)->sav_w;
				break;
			}
		case BINARY_GAUSSIAN:
			{
				((BinaryGaussianDLEdge*)it->second)->w = ((BinaryGaussianDLEdge*)it->second)->sav_w;
				break;
			}
		case BINARY_BETA:
			{
				((BinaryBetaDLEdge*)it->second)->wp = ((BinaryBetaDLEdge*)it->second)->sav_wp;
				((BinaryBetaDLEdge*)it->second)->wn = ((BinaryBetaDLEdge*)it->second)->sav_wn;
				break;
			}		
    case BINARY_DOUBLEBETA:
    {
      ((BinaryDoubleBetaDLEdge*)it->second)->wp = ((BinaryDoubleBetaDLEdge*)it->second)->sav_wp;
      ((BinaryDoubleBetaDLEdge*)it->second)->wn = ((BinaryDoubleBetaDLEdge*)it->second)->sav_wn;
      ((BinaryDoubleBetaDLEdge*)it->second)->qp = ((BinaryDoubleBetaDLEdge*)it->second)->sav_qp;
      ((BinaryDoubleBetaDLEdge*)it->second)->qn = ((BinaryDoubleBetaDLEdge*)it->second)->sav_qn;
      break;
    }
		default:
			{
				std::cerr << "BinaryNode::saveWeights supports edge weight saving when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
				exit(-1);
			}
		}
	}
}

void BinaryNode::copyParameters(DLNode *source_node)
{
	BinaryNode *bsource_node = (BinaryNode*)source_node;
	b[0] = bsource_node->b[0];
	b[1] = bsource_node->b[1];

	for( size_t e = 0; e < update_edges.size(); e++ )
	{
		DLEdge* it = update_edges[e];
		DLEdge* bit = bsource_node->update_edges[e];

		switch( it->type )
		{
		case BINARY_BINARY:
			{
				((BinaryBinaryDLEdge*)it)->w = ((BinaryBinaryDLEdge*)bit)->w;
				break;
			}
		case BINARY_GAUSSIAN:
			{
				((BinaryGaussianDLEdge*)it)->w = ((BinaryGaussianDLEdge*)bit)->w;
				break;
			}
		case BINARY_BETA:
			{
				((BinaryBetaDLEdge*)it)->wp = ((BinaryBetaDLEdge*)bit)->wp;
				((BinaryBetaDLEdge*)it)->wn = ((BinaryBetaDLEdge*)bit)->wn;
				break;
			}
    case BINARY_DOUBLEBETA:
      {
        ((BinaryDoubleBetaDLEdge*)it)->wp = ((BinaryDoubleBetaDLEdge*)bit)->wp;
        ((BinaryDoubleBetaDLEdge*)it)->wn = ((BinaryDoubleBetaDLEdge*)bit)->wn;
        ((BinaryDoubleBetaDLEdge*)it)->qp = ((BinaryDoubleBetaDLEdge*)bit)->qp;
        ((BinaryDoubleBetaDLEdge*)it)->qn = ((BinaryDoubleBetaDLEdge*)bit)->qn;
        break;
      }
		default:
			{
				std::cerr << "BinaryNode::copyParameters supports edge weight saving when it is connected to Binary/Gaussian/Beta nodes only" << std::endl;
				exit(-1);
			}
		}
	}
}

void BinaryNode::copyBias(DLNode *source_node, int bias_id)
{
	BinaryNode *bsource_node = (BinaryNode*)source_node;
	b[bias_id] = bsource_node->b[bias_id];
}









}
}