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
#ifndef __DL13_BACKPROPAGATION_HPP
#define __DL13_BACKPROPAGATION_HPP

#include "DL13_Plugin.hpp"
#include "DL13_NetworkFactory.hpp"
#include "DL13_Common.hpp"
#include "DL13_TrainingData.hpp"
#include "DL13_EigenAddons.hpp"

namespace SNL {;
namespace DL13 {;

class BackPropagation
{
private:	
	SNL::Options options;
	bool suppress_output;

	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		vector< vector< float > > _W, _Q, _S, _T;
		vector< float > _A, _B;

		if ( Archive::is_saving::value )
		{
			_A = convertEigenVectorToStdVector(A);
			_B = convertEigenVectorToStdVector(B);
			_W = convertEigenMatrixToStdVectorVector(W);
			_Q = convertEigenMatrixToStdVectorVector(Q);
			_S = convertEigenMatrixToStdVectorVector(S);
			_T = convertEigenMatrixToStdVectorVector(T);
		}

		ar & options;
		ar & suppress_output;
		ar & _A;
		ar & _B;
		ar & _W;
		ar & _Q;
		ar & _S;
		ar & _T;

		if ( !Archive::is_saving::value )
		{
			A = convertStdVectorToEigenVector(_A);
			B = convertStdVectorToEigenVector(_B);
			W = convertStdVectorVectorToEigenMatrix(_W);
			Q = convertStdVectorVectorToEigenMatrix(_Q);
			S = convertStdVectorVectorToEigenMatrix(_S);
			T = convertStdVectorVectorToEigenMatrix(_T);
		}
	}
public:
	SMATRIXf X; // training data #examples x #number of dimensions
	SMATRIXf Y; // training data #examples x #outputs
	SMATRIXf W, Q, S, T;
	SVECTORf A, B;

	BackPropagation(): suppress_output(false) { };
	BackPropagation(const SMATRIXf& _X, const SMATRIXf& _Y, bool _suppress_output = false, SNL::Options const & _options = SNL::Options() );
	float train(SNL::Options const & _options = SNL::Options());
	SVECTORf predict(const SVECTORf& X0); 
	~BackPropagation() { };
}; // class BackPropagation


}
}



#endif