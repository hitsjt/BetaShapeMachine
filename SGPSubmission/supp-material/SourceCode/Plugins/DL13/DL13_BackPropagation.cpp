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

#include "DL13_BackPropagation.hpp"

namespace SNL {;
namespace DL13 {;

BackPropagation::BackPropagation(const SMATRIXf& _X, const SMATRIXf& _Y, bool _suppress_output, SNL::Options const & _options) 
{
	X = _X;
	Y = _Y;
	suppress_output = _suppress_output;
	options.set("learning_epochs", 200000);
	//options.set("num_random_restarts", 1000);
	options.set("initial_learning_rate", 1e-5f);
	options.set("mapping_type", "");	
	options.merge(_options);
} 

float BackPropagation::train(SNL::Options const & _options)
{
	options.merge(_options);
	int learning_epochs = options.get("learning_epochs", 100000);
	int best_iter = 0;
	//int num_random_restarts = options.get("num_random_restarts", 1000);
	float learning_rate = options.get("initial_learning_rate", 1e-3f);
	float rec_error = FLT_MAX, prev_rec_error = FLT_MAX, min_error = FLT_MAX;
	size_t N = X.rows();
	size_t D = X.cols();
	size_t M = Y.cols(); // number of outputs

	if ( options.get("mapping_type", "") == "linear")
	{
		SVECTORf X_bias(N);
		X_bias.fill(1.0f);
		SMATRIXf XX(N, D+1);
		XX << X, X_bias;
		W.resize(M, D+1);
		W.fill(0.0f);

		int iter;
		for (iter = 0; iter < learning_epochs; iter++)
		{
			SMATRIXf Yout = XX * W.transpose();
			SMATRIXf BP = (1.0f/float(N)) * (Y - Yout).transpose() * XX;
			W = W + learning_rate * BP;

			prev_rec_error = rec_error;
			rec_error = ( XX * W.transpose() - Y ).cwiseAbs().sum() / float(N*M);
			if (rec_error >= prev_rec_error)
				learning_rate *= 0.9f;
			else
				learning_rate *= 1.05f;

			if (iter % 100 == 0)
			{
				if (!suppress_output)
					std::cout << "=> BP Iter=" << iter << ", err=" << rec_error << ", rate=" << learning_rate << std::endl;
			}		
			if ( learning_rate < 1e-12f )
			{
				break;
			}

		}
		if (!suppress_output)
			std::cout << "=> BP Last Iter=" << iter << ", err=" << rec_error << ", rate=" << learning_rate << std::endl;		
	}	
	else
	{
		// PRECOMPUTE TRANSPOSES/LOGS OF INPUT PATRICES
		SMATRIXf X_ = X.transpose();
		SMATRIXf Y_ = Y.transpose();
		SMATRIXf logX_ = X_.array().log();
		SMATRIXf logXT_ = logX_.transpose();
		SMATRIXf log_one_minux_X_ = (1.0f-X_.array()).log();
		SMATRIXf log_one_minux_XT_ = log_one_minux_X_.transpose();
		SMATRIXf logY_ = Y_.array().log();
		SMATRIXf log_one_minux_Y_ = (1.0f-Y_.array()).log();
		SMATRIXf Yout_ = Y_;
		SMATRIXf logYout_ = Yout_.array().log();
		SMATRIXf log_one_minus_Yout_ = (1.0f - Yout_.array()).log();

		// INITIALIZATION OF PARAMETERS
		A.resize(M);
		A.fill(0.5f);
		B.resize(M);
		B.fill(0.5f);
		W.resize(M, D);
		W.fill(0.1f);
		Q.resize(M, D);
		Q.fill(0.1f);
		S.resize(M, D);
		S.fill(0.01f);
		T.resize(M, D);
		T.fill(0.01f);

		//SMATRIXf XX(2 * D + 1, N);
		//XX << logX_, 
		//			log_one_minux_X_,
		//	   	SMATRIXf::Ones(1, N);
		//////////SMATRIXf WW =  ( XX * XX.transpose() ).inverse() * XX * Y;
		//SMATRIXf WW = XX.transpose().jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve( Y );
		//W = -WW.block(0, 0, D, M).transpose();
		//Q = -WW.block(D, 0, D, M).transpose();
		//S = -W;
		//T = -Q;
		//A = WW.row(2*D);
		//B = -A.array() + 1.0f;

		SMATRIXf XX(D + 1, N);
		XX << logX_, 
			   	SMATRIXf::Ones(1, N);
		//////////SMATRIXf WW =  ( XX * XX.transpose() ).inverse() * XX * Y;
		SMATRIXf WW = XX.transpose().jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve( Y );
		W = -WW.block(0, 0, D, M).transpose();
		Q.fill(EPSILONf);
		S = -W;
		T = -Q;
		A = WW.row(D).transpose();
		B = -A.array() + 1.0f;

		// PRECOMPUTE MATRICES USED IN BACKPROPAGATION
		SMATRIXf A_ = A.replicate(1, N);
		SMATRIXf B_ = B.replicate(1, N);
		SMATRIXf Wsav = W, Qsav = Q, Ssav = S, Tsav = T, Asav = A, Bsav = B;

		SMATRIXf E_posW = -logY_ * logXT_;
		SMATRIXf E_posQ = -logY_ * log_one_minux_XT_;
		SMATRIXf E_posS = -log_one_minux_Y_ * logXT_;
		SMATRIXf E_posT = -log_one_minux_Y_ * log_one_minux_XT_;
		SVECTORf E_posA = logY_.rowwise().mean();
		SVECTORf E_posB = log_one_minux_Y_.rowwise().mean();

		SMATRIXf E_negW = -logYout_ * logXT_;		
		SMATRIXf E_negQ = -logYout_ * log_one_minux_XT_;		
		SMATRIXf E_negS = -log_one_minus_Yout_ * logXT_;		
		SMATRIXf E_negT = -log_one_minus_Yout_ * log_one_minux_XT_;
		SVECTORf E_negA = logYout_.rowwise().mean();
		SVECTORf E_negB = log_one_minus_Yout_.rowwise().mean();

		SMATRIXf WlogX_ = W * logX_;
		SMATRIXf Qlog_one_minux_X_ = Q * log_one_minux_X_;
		SMATRIXf SlogX_ = S * logX_;
		SMATRIXf Tlog_one_minux_X_ = T * log_one_minux_X_;

		/////// RANDOM RESTARTS
		//A.fill(0.5f);
		//B.fill(0.5f);
		//A_ = A.replicate(1, N);
		//B_ = B.replicate(1, N);
		//for (int riter = 0; riter < num_random_restarts; riter++)
		//{
		//	W.setRandom();
		//	W = (W.array() + 1.0f)*0.5f + EPSILONf;
		//	Q.setRandom();
		//	Q = (Q.array() + 1.0f)*0.5f + EPSILONf;
		//	S.setRandom();
		//	S = (S.array() + 1.0f)*0.05f + EPSILONf;
		//	T.setRandom();
		//	T = (T.array() + 1.0f)*0.05f + EPSILONf;
		//	WlogX_ = W * logX_;
		//	Qlog_one_minux_X_ = Q * log_one_minux_X_;
		//	SlogX_ = S * logX_;
		//	Tlog_one_minux_X_ = T * log_one_minux_X_;

		//	Yout_ = A_ - WlogX_ - Qlog_one_minux_X_;
		//	Yout_ = Yout_.array() / (Yout_ + B_ - SlogX_ - Tlog_one_minux_X_).array();
		//	limit( Yout_, EPSILONf, 1.0f - EPSILONf );
		//	rec_error = ( Yout_ - Y_ ).cwiseAbs().sum() / float(N*M);
		//	if ( rec_error < min_error )
		//	{
		//		min_error = rec_error;
		//		Wsav = W;
		//		Qsav = Q;
		//		Ssav = S;
		//		Tsav = T;
		//	}
		//	if (riter == num_random_restarts - 1)
		//		std::cout << std::endl << "=> Rand iter=" << riter << ", err=" << rec_error << ", min_error=" << min_error << std::endl;
		//} // end of random initialization
		//W = Wsav;
		//Q = Qsav;
		//S = Ssav;
		//T = Tsav;
		//WlogX_ = W * logX_;
		//Qlog_one_minux_X_ = Q * log_one_minux_X_;
		//SlogX_ = S * logX_;			
		//Tlog_one_minux_X_ = T * log_one_minux_X_;

		//// LEARNING
		Yout_ = A_ - WlogX_ - Qlog_one_minux_X_;
		Yout_ = Yout_.array() / (Yout_ + B_ - SlogX_ - Tlog_one_minux_X_).array();
		limit( Yout_, EPSILONf, 1.0f - EPSILONf );
		logYout_ = Yout_.array().log();
		log_one_minus_Yout_ = (1.0f - Yout_.array()).log();
		rec_error = ( Yout_ - Y_ ).cwiseAbs().sum() / float(N*M);
		min_error = rec_error;
		if (!suppress_output)
			std::cout << "=> Initial guess err=" << rec_error << std::endl;				
		int iter;
		for (iter = 0; iter < learning_epochs; iter++)
		{
			E_negW = -logYout_ * logXT_;
			E_negQ = -logYout_ * log_one_minux_XT_;
			E_negS = -log_one_minus_Yout_ * logXT_;
			E_negT = -log_one_minus_Yout_ * log_one_minux_XT_;
			E_negA = logYout_.rowwise().mean();
			E_negB = log_one_minus_Yout_.rowwise().mean();

			W = W + learning_rate * (E_posW - E_negW)/float(N);
			Q = Q + learning_rate * (E_posQ - E_negQ)/float(N);
			S = S + .1f * learning_rate * (E_posS - E_negS)/float(N);
			T = T + .1f * learning_rate * (E_posT - E_negT)/float(N);
			A = A + .1f * learning_rate * (E_posA - E_negA);
			B = B + .1f * learning_rate * (E_posB - E_negB);

			limit( W, EPSILONf, FLT_MAX );
			limit( Q, EPSILONf, FLT_MAX );
			limit( S, EPSILONf, FLT_MAX );
			limit( T, EPSILONf, FLT_MAX );
			A_ = A.replicate(1, N);
			B_ = B.replicate(1, N);

			WlogX_ = W * logX_;
			Qlog_one_minux_X_ = Q * log_one_minux_X_;
			SlogX_ = S * logX_;			
			Tlog_one_minux_X_ = T * log_one_minux_X_;

			Yout_ = A_ - WlogX_ - Qlog_one_minux_X_;
			Yout_ = Yout_.array() / (Yout_ + B_ - SlogX_ - Tlog_one_minux_X_).array();
			limit( Yout_, EPSILONf, 1.0f - EPSILONf );
			logYout_ = Yout_.array().log();
			log_one_minus_Yout_ = (1.0f - Yout_.array()).log();
			prev_rec_error = rec_error;
			rec_error = ( Yout_ - Y_ ).cwiseAbs().sum() / float(N*M);

			if ( rec_error < min_error )
			{
				best_iter = iter;
				min_error = rec_error;
				Wsav = W;
				Qsav = Q;
				Ssav = S;
				Tsav = T;
				Asav = A;
				Bsav = B;
			}

			if (rec_error > prev_rec_error)
				learning_rate *= 0.9f;
			else
				learning_rate *= 1.05f;
			learning_rate = min( learning_rate, .1f);
			if (iter % 1000 == 0)
			{
				if (!suppress_output)
					std::cout << "=> BP Iter=" << iter << ", err=" << rec_error << ", rate=" << learning_rate << std::endl;				
			}		
			if ( learning_rate < EPSILONf )
				break;
		}

		W = Wsav;
		Q = Qsav;
		S = Ssav;
		T = Tsav;
		A = Asav;
		B = Bsav;

		if (!suppress_output)
			std::cout << "=> BP Best Iter=" << best_iter << ", err=" << min_error << std::endl;						
	}

	return min_error;
}

SVECTORf BackPropagation::predict(const SVECTORf& X0)
{
	if ( options.get("mapping_type", "linear") == "linear")
	{
		size_t D = W.cols();
		SVECTORf XX(D);
		XX << X0, 1.0f;
		SVECTORf Yout = W * XX;
		return Yout;
	}
	else
	{
		SVECTORf logX0_ = X0.array().log();
		SVECTORf log_one_minux_X0_ = (1.0f-X0.array()).log();
		SVECTORf Yout = A.array() - (W * logX0_ + Q * log_one_minux_X0_).array();
		Yout = Yout.array() / (Yout.array() + B.array() - (S * logX0_ + T * log_one_minux_X0_).array() );
		return Yout;
	}

	std::cerr << "Internal error: BackPropagation::predict: specified method " << options.get("mapping_type", "") << " is not supported." << std::endl;
	exit(-1);

}

}
}