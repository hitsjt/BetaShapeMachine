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

#ifndef __DL13_LOGISTIC_REGRESSION
#define __DL13_LOGISTIC_REGRESSION

#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_TrainingData.hpp"
#include "DL13_EigenAddons.hpp"

namespace SNL {;
namespace DL13 {;

class SNL_DL13_API LogisticRegression
{
private:
	SNL::Options options;
	bool suppress_output;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		vector< vector< float > > _W;

		if ( Archive::is_saving::value )
			_W = convertEigenMatrixToStdVectorVector(W);

		ar & options;
		ar & suppress_output;
		ar & _W;

		if ( !Archive::is_saving::value )
			W = convertStdVectorVectorToEigenMatrix(_W);
	}
public:
	SMATRIXf X; // training data #examples x #number of dimensions
	SMATRIXf Y; // training data #examples x #outputs
	SMATRIXf W;

	LogisticRegression(): suppress_output(false) { };
	LogisticRegression(const SMATRIXf& _X, const SMATRIXf& _Y, bool _suppress_output = false, SNL::Options const & _options = SNL::Options() );
	float train(SNL::Options const & _options = SNL::Options());
	//void test();
	SVECTORf predict(const SVECTORf& X0); 
	~LogisticRegression() { };
}; // class LogisticRegression

} // namespace DL13
} // namespace SNL

#endif
