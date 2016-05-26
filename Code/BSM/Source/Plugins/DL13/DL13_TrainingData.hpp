#ifndef __DL13_TRAININGDATA_HPP
#define __DL13_TRAININGDATA_HPP

#include <boost/filesystem.hpp>
#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_EigenAddons.hpp"


namespace SNL {;
namespace DL13 {;

class SNL_DL13_API TrainingData
{

private:	
	float internal_populateSpatialNeighbors(const float radius);

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		vector< float > _tmp;
		if ( Archive::is_saving::value )
		{
			_tmp = convertEigenVectorToStdVector(percentage_of_sparse_points_per_part);
		}

		ar & number_of_training_examples;
		ar & number_of_training_examples_attributes;
		ar & number_of_dense_points;
		ar & number_of_sparse_points;
		ar & number_of_attributes;
		ar & _tmp;
		ar & data_filenames;
		ar & fitting_error;

		ar & dense_point_data; 
		ar & dense_normal_data;
		ar & dense_template_id;
		ar & dense_part_id;
		ar & dense_point_distance_error;
		ar & dense_normal_distance_error;

		ar & sparse_point_data;
		ar & sparse_normal_data;
		ar & sparse_template_id;
		ar & sparse_part_id;
		ar & sparse_point_distance_error;
		ar & sparse_normal_distance_error;
		ar & symmetry_type;

		ar & part_centroids;

		ar & spatial_neighbors_candidates;
		ar & spatial_neighbors_ids;
		ar & spatial_neighbors_weights;

		ar & nearest_sparse_points_for_each_dense_point;

		ar & attribute_data;

		ar & adjusted_radius;

		if ( !Archive::is_saving::value )
		{
			percentage_of_sparse_points_per_part = convertStdVectorToEigenVector(_tmp);
		}

	}

public:
	int number_of_training_examples, number_of_training_examples_attributes;
	int number_of_dense_points;
	int number_of_sparse_points;
	int number_of_attributes;
	float adjusted_radius;
	SVECTORf percentage_of_sparse_points_per_part;

	vector<string> data_filenames;
	vector<float> fitting_error;

	vector< vector< vector<float> > > dense_point_data; // M (#examples x #number_points x 3)
	vector< vector< vector<float> > >  dense_normal_data;
	vector< vector<short> >  dense_template_id;
	vector< vector<short> >  dense_part_id;
	vector< vector<float> >  dense_point_distance_error;
	vector< vector<float> >  dense_normal_distance_error;

	vector< vector< vector<float> > > sparse_point_data;
	vector< vector< vector<float> > >  sparse_normal_data;
	vector< vector<short> >  sparse_template_id;
	vector< vector<short> >  sparse_part_id;
	vector< vector<float> >  sparse_point_distance_error;
	vector< vector<float> >  sparse_normal_distance_error;
	vector< vector<short> >  symmetry_type;

	vector< vector< vector< float> > >  part_centroids;

	vector< map<int, bool>  > spatial_neighbors_candidates;
	vector< vector<int> > spatial_neighbors_ids;
	vector< vector<float> > spatial_neighbors_weights;	

	vector< vector< float > > attribute_data;

	vector< vector< unsigned short > > nearest_sparse_points_for_each_dense_point;

	TrainingData(string const & in_path = "", float threshold = FLT_MAX,  int limit_number_of_examples_to_read = INT_MAX, bool is_binary = true, 
							 int _number_of_attributes = 0, int _number_of_sparse_points = 0, int _number_of_dense_points = 0); 
	void populateSpatialNeighbors(const float radius = .1f);
	void findDenseToSparseAssociations(int num_nearest = 100);
	void findPartCentroids(); 
	void findPartReflectiveSymmetries();
	bool load(std::string const & in_path);
	void save(std::string const & out_path) const;
}; // class TrainingData 

}
}

#endif