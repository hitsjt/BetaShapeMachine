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

#include "DL13_Logistic_Regression.hpp"

namespace SNL {;
namespace DL13 {;

LogisticRegression::LogisticRegression(const SMATRIXf& _X, const SMATRIXf& _Y, bool _suppress_output, SNL::Options const & _options) 
{
	X = _X;
	Y = _Y;
	suppress_output = _suppress_output;
	options.set("iterations", 1000);
	options.merge(_options);
} 

float LogisticRegression::train(SNL::Options const & _options)
{
	options.merge(_options);
	//int iterations = options.get("iterations", 100);
	size_t N = X.rows(); // number of examples
	size_t D = X.cols(); // number of dimensions
	size_t M = Y.cols(); // number of outputs
	float rec_error = FLT_MAX, prev_rec_error = FLT_MAX;

	SVECTORf X_bias(N);
	X_bias.fill(1.0f);
	SMATRIXf XX(N, D+1);
	XX << X, X_bias;
	W.resize(M, D+1);
	W.fill(0.0f);
	SMATRIXf oldW = W;

	SVECTORf R(N);
	SMATRIXf T(N, D+1);
	float step = .25f;

	// X is N x D, W is M x D, Y is N x M
	for (int iter = 0; iter < options.get("iterations", 1000); iter++)
	{
		if (iter == 1)
			step = .5f;
		else if (iter == 2)
			step = 1.0f;

		oldW = W;
		for (size_t m = 0; m < M; m++)
		{
			if (step == 0.0f)
				continue;
			R = ( XX * W.row(m).transpose() );
			limit(R, -50.0f, 50.0f ); // prevent numerical overflow/underflow
			R = R.array().exp();  // N x 1
			limit(R, 0.0f, FLT_MAX - 1.0f);
			R = R.array() / (1.0f + R.array() );

			for (size_t n = 0; n < N; n++)
				T.row(n) = R(n) * (1.0f - R(n)) * XX.row(n);  // N x D

			W.row(m) = W.row(m) + step * ( ( XX.transpose() * T ).inverse() * XX.transpose() * ( Y.col(m) - R ) ).transpose();
		} 

		SMATRIXf YP = ( XX * W.transpose() );  // N x M
		limit(YP, -50.0f, 50.0f ); // prevent numerical overflow/underflow
		YP = YP.array().exp();  // N x M
		YP = YP.array() / (1.0f + YP.array() );
		prev_rec_error = rec_error;
		rec_error = (YP - Y).cwiseAbs().sum() / float(N*M);

		if (!suppress_output)
			std::cout << "=> IRLS Iter=" << iter << ", err=" << rec_error << std::endl;

		if ( (rec_error < EPSILONf) || (step == 0.0f) )
			break;

		if ( rec_error > prev_rec_error || isnan(rec_error)  )
		{
			W = oldW;
			step = 0.0f;
			std::cout << "fixing..." << std::endl;
		}
	} // end of loop of IRLS

	if (!suppress_output)
		std::cout << "=> IRLS final error =" << rec_error << std::endl;

	return rec_error;
}

SVECTORf LogisticRegression::predict(const SVECTORf& X0)
{
	size_t D = W.cols();
	SVECTORf XX(D);
	XX << X0, 1.0f;
	SVECTORf YP = W * XX;  // M x 1
	limit(YP, -50.0f, 50.0f ); // prevent numerical overflow/underflow
	YP = YP.array().exp();
	YP = YP.array() / (1.0f + YP.array() );
	return YP;
}

} // end of namespace DL13
} // end of namespace SNL



//void LogisticRegression::test()
//{
//
//	SMATRIXf X;
//	X.resize(100, 4);
//	X << 5.1000, 3.5000, 1.4000, 0.2000,
//		4.9000, 3.0000, 1.4000, 0.2000,
//		4.7000, 3.2000, 1.3000, 0.2000,
//		4.6000, 3.1000, 1.5000, 0.2000,
//		5.0000, 3.6000, 1.4000, 0.2000,
//		5.4000, 3.9000, 1.7000, 0.4000,
//		4.6000, 3.4000, 1.4000, 0.3000,
//		5.0000, 3.4000, 1.5000, 0.2000,
//		4.4000, 2.9000, 1.4000, 0.2000,
//		4.9000, 3.1000, 1.5000, 0.1000,
//		5.4000, 3.7000, 1.5000, 0.2000,
//		4.8000, 3.4000, 1.6000, 0.2000,
//		4.8000, 3.0000, 1.4000, 0.1000,
//		4.3000, 3.0000, 1.1000, 0.1000,
//		5.8000, 4.0000, 1.2000, 0.2000,
//		5.7000, 4.4000, 1.5000, 0.4000,
//		5.4000, 3.9000, 1.3000, 0.4000,
//		5.1000, 3.5000, 1.4000, 0.3000,
//		5.7000, 3.8000, 1.7000, 0.3000,
//		5.1000, 3.8000, 1.5000, 0.3000,
//		5.4000, 3.4000, 1.7000, 0.2000,
//		5.1000, 3.7000, 1.5000, 0.4000,
//		4.6000, 3.6000, 1.0000, 0.2000,
//		5.1000, 3.3000, 1.7000, 0.5000,
//		4.8000, 3.4000, 1.9000, 0.2000,
//		5.0000, 3.0000, 1.6000, 0.2000,
//		5.0000, 3.4000, 1.6000, 0.4000,
//		5.2000, 3.5000, 1.5000, 0.2000,
//		5.2000, 3.4000, 1.4000, 0.2000,
//		4.7000, 3.2000, 1.6000, 0.2000,
//		4.8000, 3.1000, 1.6000, 0.2000,
//		5.4000, 3.4000, 1.5000, 0.4000,
//		5.2000, 4.1000, 1.5000, 0.1000,
//		5.5000, 4.2000, 1.4000, 0.2000,
//		4.9000, 3.1000, 1.5000, 0.2000,
//		5.0000, 3.2000, 1.2000, 0.2000,
//		5.5000, 3.5000, 1.3000, 0.2000,
//		4.9000, 3.6000, 1.4000, 0.1000,
//		4.4000, 3.0000, 1.3000, 0.2000,
//		5.1000, 3.4000, 1.5000, 0.2000,
//		5.0000, 3.5000, 1.3000, 0.3000,
//		4.5000, 2.3000, 1.3000, 0.3000,
//		4.4000, 3.2000, 1.3000, 0.2000,
//		5.0000, 3.5000, 1.6000, 0.6000,
//		5.1000, 3.8000, 1.9000, 0.4000,
//		4.8000, 3.0000, 1.4000, 0.3000,
//		5.1000, 3.8000, 1.6000, 0.2000,
//		4.6000, 3.2000, 1.4000, 0.2000,
//		5.3000, 3.7000, 1.5000, 0.2000,
//		5.0000, 3.3000, 1.4000, 0.2000,
//		7.0000, 3.2000, 4.7000, 1.4000,
//		6.4000, 3.2000, 4.5000, 1.5000,
//		6.9000, 3.1000, 4.9000, 1.5000,
//		5.5000, 2.3000, 4.0000, 1.3000,
//		6.5000, 2.8000, 4.6000, 1.5000,
//		5.7000, 2.8000, 4.5000, 1.3000,
//		6.3000, 3.3000, 4.7000, 1.6000,
//		4.9000, 2.4000, 3.3000, 1.0000,
//		6.6000, 2.9000, 4.6000, 1.3000,
//		5.2000, 2.7000, 3.9000, 1.4000,
//		5.0000, 2.0000, 3.5000, 1.0000,
//		5.9000, 3.0000, 4.2000, 1.5000,
//		6.0000, 2.2000, 4.0000, 1.0000,
//		6.1000, 2.9000, 4.7000, 1.4000,
//		5.6000, 2.9000, 3.6000, 1.3000,
//		6.7000, 3.1000, 4.4000, 1.4000,
//		5.6000, 3.0000, 4.5000, 1.5000,
//		5.8000, 2.7000, 4.1000, 1.0000,
//		6.2000, 2.2000, 4.5000, 1.5000,
//		5.6000, 2.5000, 3.9000, 1.1000,
//		5.9000, 3.2000, 4.8000, 1.8000,
//		6.1000, 2.8000, 4.0000, 1.3000,
//		6.3000, 2.5000, 4.9000, 1.5000,
//		6.1000, 2.8000, 4.7000, 1.2000,
//		6.4000, 2.9000, 4.3000, 1.3000,
//		6.6000, 3.0000, 4.4000, 1.4000,
//		6.8000, 2.8000, 4.8000, 1.4000,
//		6.7000, 3.0000, 5.0000, 1.7000,
//		6.0000, 2.9000, 4.5000, 1.5000,
//		5.7000, 2.6000, 3.5000, 1.0000,
//		5.5000, 2.4000, 3.8000, 1.1000,
//		5.5000, 2.4000, 3.7000, 1.0000,
//		5.8000, 2.7000, 3.9000, 1.2000,
//		6.0000, 2.7000, 5.1000, 1.6000,
//		5.4000, 3.0000, 4.5000, 1.5000,
//		6.0000, 3.4000, 4.5000, 1.6000,
//		6.7000, 3.1000, 4.7000, 1.5000,
//		6.3000, 2.3000, 4.4000, 1.3000,
//		5.6000, 3.0000, 4.1000, 1.3000,
//		5.5000, 2.5000, 4.0000, 1.3000,
//		5.5000, 2.6000, 4.4000, 1.2000,
//		6.1000, 3.0000, 4.6000, 1.4000,
//		5.8000, 2.6000, 4.0000, 1.2000,
//		5.0000, 2.3000, 3.3000, 1.0000,
//		5.6000, 2.7000, 4.2000, 1.3000,
//		5.7000, 3.0000, 4.2000, 1.2000,
//		5.7000, 2.9000, 4.2000, 1.3000,
//		6.2000, 2.9000, 4.3000, 1.3000,
//		5.1000, 2.5000, 3.0000, 1.1000,
//		5.7000, 2.8000, 4.1000, 1.3000;
//
//	SMATRIXf Y(100, 2);
//	Y.fill(1.0f);
//	Y.block(0, 0, 50, 1).fill(0.0f);
//	Y.col(1) = 1.0f - Y.col(0).array();
//
//	LogisticRegression t(X, Y);
//	t.train();
//
//	std::cout << t.W << std::endl;
//
//	for (int n = 0; n < 100; n++)
//	{
//		std::cout << "t[n]: " << t.predict( X.row(n) ).transpose() << std::endl;
//		std::cout << "y[n]: " << Y.row(n) << std::endl;
//	}
//}

