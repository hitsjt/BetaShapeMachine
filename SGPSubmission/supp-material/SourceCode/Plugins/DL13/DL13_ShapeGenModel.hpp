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

#ifndef __DL13_SHAPEGENMODEL
#define __DL13_SHAPEGENMODEL

#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_TrainingData.hpp"
#include "DL13_EigenAddons.hpp"
#include "DL13_BoltzmannMachine.hpp"
#include "DL13_MeshConstructor.hpp"
#include "DL13_Point.hpp"

namespace SNL {;
namespace DL13 {;

class MeshConstructor;
class Point;

class SNL_DL13_API ShapeDeepGenerativeModel
{
private:
	MeshConstructor* mesh_constructor;

	void nullifyMissingPoints();
	vector< vector<Point> > reconstructInput(std::string const & in_path, bool need_dense_result, int num_iterations, vector<float>& probs, bool smooth_result, bool skip_prob);
  void reInitializeSparsePoints(const vector<Point>&);
  float getUnnormalizedLogProbability(bool check_out_of_range_values = false);

public:	
  float sample_unnormalized_probability;
  int point_sample_id;
  int point_attrib_id;

	BoltzmannMachine * geometry_boltzmann_machine;
	BoltzmannMachine * structure_boltzmann_machine;
	SNL::Options geometry_learning_options;
	SNL::Options structure_learning_options;
  vector<Point> sparse_points;
  vector<Point> dense_points;
	TrainingData *training_data;	


	ShapeDeepGenerativeModel(const string &load_boltzmann_file_path = "", const string &load_training_file_path = "",  const string &training_data_path = "", const SNL::Options &_options = SNL::Options() );
	void train(const string &save_boltzmann_file_path = "", const SNL::Options &_options = SNL::Options() );
	void retrain(const string &save_boltzmann_file_path = "", const SNL::Options &_options = SNL::Options() );
	void trainAttributes(const string &save_boltzmann_file_path = "", const SNL::Options &_options = SNL::Options());
	void trainDenseLayer(const string &save_boltzmann_file_path = "", const SNL::Options &_options = SNL::Options());

  vector<Point> sampleShape(bool need_dense_result);
  vector<Point> reconstructTrainingExample(int m, bool need_dense_result);
  vector<Point> showTrainingExample(int m, bool need_dense_result);
  vector< float > getLogProbabilityForAlignment(std::string const & in_path);
	// this function is used for reconstructing from point cloud data 
  vector< vector<Point> > reconstructFromPartialInput(std::string const & in_path, bool need_dense_result, vector<float>& probs, bool smooth_result = true);
	// this function is used for correcting the input points based on the prior 
  vector< vector<Point> > reconstructInput(std::string const & in_path, bool need_dense_result, int num_iterations = 1, bool smooth_result = false);

  vector<Point> attribShape(const vector<float>& attrib_values, bool need_dense_result);
	void createSparsePointCloud();
	void createDensePointCloud();
  vector<Point> removeInvalidSparsePoints();
  vector<Point> removeInvalidDensePoints();
	void saveSparsePointCloud(std::string const & out_path);
	void saveDensePointCloud(std::string const & out_path);  

	~ShapeDeepGenerativeModel();
}; // class ShapeDeepGenerativeModel

}
}

#endif