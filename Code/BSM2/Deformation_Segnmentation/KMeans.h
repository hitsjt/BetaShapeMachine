#ifndef __DEF_KMEANS_H
#define __DEF_KMEANS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


template <class T>
class KMeans 
{
public:
	vector< vector<T> >				CX;					// numclusters x dim
	vector<size_t>						CI;					// numsamples

private:
  size_t										kmeans_replicates;
	size_t										numclusters;
	float											err;
	float											int_err;
	size_t										dim;
	vector< vector<T> >				current_CX; // numclusters x dim
	vector<size_t>						current_CI; // numsamples

	double dist( vector<double>& X1, vector<double>& X2 )
	{
		double distance = 0.0f;
		for (size_t d = 0; d < dim; d++)
			distance += (X1[d] - X2[d])*(X1[d] - X2[d]);
		return distance;
	}

	float dist( vector<float>& X1, vector<float>& X2 )
	{
		float distance = 0.0f;
		for (size_t d = 0; d < dim; d++)
			distance += (X1[d] - X2[d])*(X1[d] - X2[d]);
		return distance;
	}

	float dist( vector<size_t>& X1, vector<size_t>& X2 )
	{
		float distance = 0.0f;
		for (size_t d = 0; d < dim; d++)
			distance += float(X1[d] != X2[d]);
		return distance;
	}

	template <class T>
	void initializeRandom(vector< vector<T> >& X)
	{
		vector<size_t> rand_index;

		for (size_t c = 0; c < numclusters; c++)
		{
			size_t rand_index_c = rand() % X.size();
			for (size_t rep = 0; rep < kmeans_replicates; rep++)
			{
				bool found = false;
				for (size_t c2 = 0; c2 < c; c2++)
					if ( dist( X[ rand_index[c2] ], X[rand_index_c] ) == 0.0f )
						found = true;
				if (!found || rep == kmeans_replicates-1)
				{
					rand_index.push_back( rand_index_c );
					break;
				}
				else
				{
					rand_index_c = rand() % X.size();
				}					
			}
		}

		for (size_t c = 0; c < numclusters; c++)
			for (size_t d = 0; d < dim; d++)
				current_CX[c][d] = X[ rand_index[c] ][d];
	}

	template <class T>
	float run( vector< vector<T> >& X )
	{
		float current_err = 0.0f;
		for (size_t it = 0; it < 10; it++)
		{
			KmeansIteration(X);
			for (size_t c = 0; c < numclusters; c++)
			{
				for (size_t i = 0; i < X.size(); i++)
				{
					if ( current_CI[i] == c )
						current_err += dist( X[i], current_CX[c] );
				}
			}
		}
		return current_err + int_err;
	}


	void KmeansIteration(vector< vector<float> >& X) 
	{
		for (size_t i = 0; i < X.size(); i++)
		{
			size_t closest_cluster = 0;
			float dist_to_closest_cluster = FLT_MAX;
			for (size_t c = 0; c < numclusters; c++)
			{
				float dist_to_cluster = dist( X[i], current_CX[c] );
				if ( dist_to_cluster < dist_to_closest_cluster )
				{
					dist_to_closest_cluster = dist_to_cluster;
					current_CI[i] = c;
				}
			}
		}

		for (size_t c = 0; c < numclusters; c++)
			for (size_t d = 0; d < dim; d++)
				current_CX[c][d] = 0.0f;

		vector< float > num_points_in_cluster( numclusters, 0.0f );
		for (size_t i = 0; i < X.size(); i++)
			num_points_in_cluster[ current_CI[i] ] += 1.0f;

		for (size_t i = 0; i < X.size(); i++)
			for (size_t c = 0; c < numclusters; c++)
				if ( current_CI[i] == c)
					for (size_t d = 0; d < dim; d++)
						current_CX[c][d] += X[i][d];

		for (size_t c = 0; c < numclusters; c++)
			for (size_t d = 0; d < dim; d++)
				current_CX[c][d] /= num_points_in_cluster[c];

		int_err = 0.0f;
	}

	void KmeansIteration(vector< vector<double> >& X) 
	{
		for (size_t i = 0; i < X.size(); i++)
		{
			size_t closest_cluster = 0;
			float dist_to_closest_cluster = FLT_MAX;
			for (size_t c = 0; c < numclusters; c++)
			{
				float dist_to_cluster = dist( X[i], current_CX[c] );
				if ( dist_to_cluster < dist_to_closest_cluster )
				{
					dist_to_closest_cluster = dist_to_cluster;
					current_CI[i] = c;
				}
			}
		}

		for (size_t c = 0; c < numclusters; c++)
			for (size_t d = 0; d < dim; d++)
				current_CX[c][d] = 0.0f;

		vector< float > num_points_in_cluster( numclusters, 0.0f );
		for (size_t i = 0; i < X.size(); i++)
			num_points_in_cluster[ current_CI[i] ] += 1.0f;

		for (size_t i = 0; i < X.size(); i++)
			for (size_t c = 0; c < numclusters; c++)
				if ( current_CI[i] == c)
					for (size_t d = 0; d < dim; d++)
						current_CX[c][d] += X[i][d];

		for (size_t c = 0; c < numclusters; c++)
			for (size_t d = 0; d < dim; d++)
				current_CX[c][d] /= num_points_in_cluster[c];

		int_err = 0.0f;
	}


	void KmeansIteration(vector< vector<size_t> >& X) 
	{
		for (size_t i = 0; i < X.size(); i++)
		{
			size_t closest_cluster = 0;
			float dist_to_closest_cluster = FLT_MAX;
			for (size_t c = 0; c < numclusters; c++)
			{
				float dist_to_cluster = dist( X[i], current_CX[c] );
				if ( dist_to_cluster < dist_to_closest_cluster )
				{
					dist_to_closest_cluster = dist_to_cluster;
					current_CI[i] = c;
				}
			}
		}

		for (size_t c = 0; c < numclusters; c++)
		{
			float min_sum_distances = FLT_MAX;
			for (size_t i = 0; i < X.size(); i++)
			{
				float sum_distances_to_other_labels = 0.0f;
				if (current_CI[i] != c)
					sum_distances_to_other_labels = FLT_MAX;
				for (size_t j = 0; j < X.size(); j++)
				{
					if (current_CI[i] == c && current_CI[j] == c)
						sum_distances_to_other_labels += dist( X[i], X[j] );
				}
				for (size_t c2 = 0; c2 < c; c2++)
					if ( dist( X[i], current_CX[c2] ) == 0.0f )
						sum_distances_to_other_labels = FLT_MAX;

				if ( sum_distances_to_other_labels < min_sum_distances )
				{
					min_sum_distances = sum_distances_to_other_labels;
					for (size_t d = 0; d < dim; d++)
						current_CX[c][d] = X[i][d];
				}
			}
			if ( min_sum_distances == FLT_MAX )
				int_err = FLT_MAX;
			else
				int_err = 0.0f;
		}
	}

public:
	// CX is nclusters x dim
	// X should be numsamples x dim 
	template <class T>
	KMeans(vector< vector<T> >& X, size_t numclusters, size_t _kmeans_replicates = 10)
	{
		if (X.empty())
			return;
		kmeans_replicates = _kmeans_replicates;
		this->dim = X[0].size();
		this->numclusters = numclusters;
		CI.resize( X.size() );
		current_CI.resize( X.size() );
		CX.resize( numclusters );
		current_CX.resize( numclusters );
		for (size_t c = 0; c < numclusters; c++)
		{
			CX[c].resize( this->dim );
			current_CX[c].resize( this->dim );
		}
		err = FLT_MAX;

		for (size_t it = 0; it < kmeans_replicates; it++)
		{
			initializeRandom(X);
			float it_err = run(X);

			if (it_err < err)
			{
				err = it_err;
				for (size_t c = 0; c < numclusters; c++)
					for (size_t d = 0; d < dim; d++)
						CX[c][d] = current_CX[c][d];
				for (size_t i = 0; i < X.size(); i++)
				{
					CI[i] = current_CI[i];
				}
			}			
		}
	}

	// 1d data
	template <class T>
	KMeans(vector< T >& X0, size_t numclusters, size_t _kmeans_replicates = KMEANS_REPLICATES)
	{
		if (X0.empty())
			return;
		kmeans_replicates = _kmeans_replicates;
		vector< vector<T> > X( X0.size() );
		for (size_t i = 0; i < X0.size(); i++)
		{
			X[i].push_back( X0[i] );
		}

		this->dim = X[0].size();
		this->numclusters = numclusters;
		CI.resize( X.size() );
		current_CI.resize( X.size() );
		CX.resize( numclusters );
		current_CX.resize( numclusters );
		for (size_t c = 0; c < numclusters; c++)
		{
			CX[c].resize( this->dim );
			current_CX[c].resize( this->dim );
		}
		err = FLT_MAX;

		for (size_t it = 0; it < kmeans_replicates; it++)
		{
			initializeRandom(X);
			float it_err = run(X);
			if (it_err < err)
			{
				err = it_err;
				for (size_t c = 0; c < numclusters; c++)
					for (size_t d = 0; d < dim; d++)
						CX[c][d] = current_CX[c][d];
				for (size_t i = 0; i < X.size(); i++)
				{
					CI[i] = current_CI[i];
				}
			}			
		}
	}



	static bool selfTest() {
		// X = [randn(50,2)+ones(50,2); randn(50,2)-ones(50,2)];
		// sprintf('%f, ', X(:) )
		std::cout << "Testing k-means functionality...";
		vector< vector<float> > X;
		vector<float> x(2);
		x[0] = 1.5377f;    x[1] = 0.1363f; X.push_back(x);
		x[0] = 2.8339f;    x[1] = 1.0774f; X.push_back(x);
		x[0] = -1.2588f;   x[1] = -0.2141f; X.push_back(x);
		x[0] = 1.8622f;   x[1] = -0.1135f; X.push_back(x);
		x[0] = 1.3188f;    x[1] = 0.9932f; X.push_back(x);
		x[0] = -0.3077f;    x[1] = 2.5326f; X.push_back(x);
		x[0] = 0.5664f;    x[1] = 0.2303f;X.push_back(x);
		x[0] = 1.3426f;    x[1] = 1.3714f; X.push_back(x);
		x[0] = 4.5784f;    x[1] = 0.7744f;X.push_back(x);
		x[0] = 3.7694f;   x[1] =  2.1174f;X.push_back(x);
		x[0] = -0.3499f;   x[1] = -0.0891f;X.push_back(x);
		x[0] = 4.0349f;   x[1] =  1.0326f;X.push_back(x);
		x[0] = 1.7254f;   x[1] =  1.5525f;X.push_back(x);
		x[0] = 0.9369f;    x[1] = 2.1006f;X.push_back(x);
		x[0] = 1.7147f;   x[1] =  2.5442f;X.push_back(x);
		x[0] = 0.7950f;   x[1] =  1.0859f;X.push_back(x);
		x[0] = 0.8759f;  x[1] =  -0.4916f;X.push_back(x);
		x[0] = 2.4897f;  x[1] =   0.2577f;X.push_back(x);
		x[0] = 2.4090f;  x[1] =  -0.0616f;X.push_back(x);
		x[0] = 2.4172f;   x[1] =  3.3505f;X.push_back(x);
		x[0] = 1.6715f;   x[1] =  0.3844f;X.push_back(x);
		x[0] = -0.2075f;    x[1] = 1.7481f;X.push_back(x);
		x[0] = 1.7172f;   x[1] =  0.8076f;X.push_back(x);
		x[0] = 2.6302f;   x[1] =  1.8886f;X.push_back(x);
		x[0] = 1.4889f;  x[1] =   0.2352f;X.push_back(x);
		x[0] = 2.0347f;  x[1] =  -0.4023f;X.push_back(x);
		x[0] = 1.7269f;  x[1] =  -0.4224f;X.push_back(x);
		x[0] = 0.6966f;  x[1] =   1.4882f;X.push_back(x);
		x[0] = 1.2939f;  x[1] =   0.8226f;X.push_back(x);
		x[0] = 0.2127f;  x[1] =   0.8039f;X.push_back(x);
		x[0] = 1.8884f;  x[1] =   2.4193f;X.push_back(x);
		x[0] = -0.1471f;  x[1] =   1.2916f;X.push_back(x);
		x[0] = -0.0689f;   x[1] =  1.1978f;X.push_back(x);
		x[0] = 0.1905f;   x[1] =  2.5877f;X.push_back(x);
		x[0] = -1.9443f;  x[1] =   0.1955f;X.push_back(x);
		x[0] = 2.4384f;   x[1] = 1.6966f;X.push_back(x);
		x[0] = 1.3252f;   x[1] = 1.8351f;X.push_back(x);
		x[0] = 0.2451f;   x[1] = 0.7563f;X.push_back(x);
		x[0] = 2.3703f;  x[1] =  1.2157f;X.push_back(x);
		x[0] = -0.7115f;   x[1] =-0.1658f;X.push_back(x);
		x[0] = 0.8978f;  x[1] = -0.1480f;X.push_back(x);
		x[0] = 0.7586f;   x[1] = 1.1049f;X.push_back(x);
		x[0] = 1.3192f;  x[1] =  1.7223f;X.push_back(x);
		x[0] = 1.3129f;  x[1] =  3.5855f;X.push_back(x);
		x[0] = 0.1351f;   x[1] = 0.3331f;X.push_back(x);
		x[0] = 0.9699f;   x[1] = 1.1873f;X.push_back(x);
		x[0] = 0.8351f;   x[1] = 0.9175f;X.push_back(x);
		x[0] = 1.6277f;   x[1] =-0.9330f;X.push_back(x);
		x[0] = 2.0933f;   x[1] = 0.5610f;X.push_back(x);
		x[0] = 2.1093f;   x[1] =-0.7947f;X.push_back(x);
		x[0] = -0.1596f;   x[1] =-0.4799f;X.push_back(x);
		x[0] = -1.8880f;   x[1] =-1.0200f;X.push_back(x);
		x[0] = -0.8999f;   x[1] =-1.0348f;X.push_back(x);
		x[0] = -1.5445f;   x[1] =-1.7982f;X.push_back(x);
		x[0] = -0.6965f;   x[1] = 0.0187f;X.push_back(x);
		x[0] = -1.6003f;   x[1] =-1.1332f;X.push_back(x);
		x[0] = -0.5100f;   x[1] =-1.7145f;X.push_back(x);
		x[0] = -0.2606f;   x[1] = 0.3514f;X.push_back(x);
		x[0] =  0.7119f;   x[1] =-1.2248f;X.push_back(x);
		x[0] = -1.1941f;  x[1] = -1.5890f;X.push_back(x);
		x[0] = -3.1384f;  x[1] = -1.2938f;X.push_back(x);
		x[0] = -1.8396f;  x[1] = -1.8479f;X.push_back(x);
		x[0] = 0.3546f;  x[1] = -2.1201f;X.push_back(x);
		x[0] = -2.0722f;   x[1] = 1.5260f;X.push_back(x);
		x[0] = -0.0390f;   x[1] = 0.6555f;X.push_back(x);
		x[0] = -0.8760f;  x[1] = -0.6925f;X.push_back(x);
		x[0] = 0.4367f;  x[1] = -2.2571f;X.push_back(x);
		x[0] = -2.9609f;  x[1] = -1.8655f;X.push_back(x);
		x[0] = -1.1977f;  x[1] = -1.1765f;X.push_back(x);
		x[0] = -2.2078f;  x[1] = -0.2086f;X.push_back(x);
		x[0] = 1.9080f;  x[1] = -2.3320f;X.push_back(x);
		x[0] = -0.1748f;  x[1] = -3.3299f;X.push_back(x);
		x[0] = 0.3790f;  x[1] = -2.4491f;X.push_back(x);
		x[0] = -2.0582f;  x[1] = -0.6665f;X.push_back(x);
		x[0] = -1.4686f;  x[1] = -0.6086f;X.push_back(x);
		x[0] = -1.2725f;  x[1] = -0.5483f;X.push_back(x);
		x[0] = 0.0984f;  x[1] = -1.1303f;X.push_back(x);
		x[0] = -1.2779f;  x[1] = -0.8163f;X.push_back(x);
		x[0] = -0.2985f;  x[1] = -1.4762f;X.push_back(x);
		x[0] = -3.0518f;  x[1] = -0.1380f;X.push_back(x);
		x[0] = -1.3538f;  x[1] = -2.3617f;X.push_back(x);
		x[0] = -1.8236f;  x[1] = -0.5450f;X.push_back(x);
		x[0] = -2.5771f;  x[1] = -1.8487f;X.push_back(x);
		x[0] = -0.4920f;  x[1] = -1.3349f;X.push_back(x);
		x[0] = -0.7180f;  x[1] = -0.4472f;X.push_back(x);
		x[0] = -0.9665f;  x[1] =  0.0391f;X.push_back(x);
		x[0] = -2.3337f;   x[1] =-2.1176f;X.push_back(x);
		x[0] = 0.1275f;  x[1] =  0.2607f;X.push_back(x);
		x[0] = -0.6498f;   x[1] =-0.3399f;X.push_back(x);
		x[0] = -1.2991f;   x[1] =-1.0679f;X.push_back(x);
		x[0] = -0.9771f;   x[1] =-1.1952f;X.push_back(x);
		x[0] = -1.2620f; x[1] =  -1.2176f;X.push_back(x);
		x[0] = -2.7502f;  x[1] = -1.3031f;X.push_back(x);
		x[0] = -1.2857f; x[1] =  -0.9770f;X.push_back(x);
		x[0] = -1.8314f; x[1] =  -0.9487f;X.push_back(x);
		x[0] = -1.9792f;  x[1] = -0.1739f;X.push_back(x);
		x[0] = -2.1564f; x[1] =   0.5270f;X.push_back(x);
		x[0] = -1.5336f;  x[1] = -0.5331f;X.push_back(x);
		x[0] = -3.0026f;  x[1] = -1.2097f;X.push_back(x);
		x[0] = -0.0358f;  x[1] = -0.3748f;X.push_back(x);
		 
		bool success;

		KMeans<float> kmeans(X, 2);
		//std::cout << '(' << kmeans.CX[0][0] << ',' << kmeans.CX[0][1] << ')' << std::endl;
		//std::cout << '(' << kmeans.CX[1][0] << ',' << kmeans.CX[1][1] << ')' << std::endl;
		success = ( fabs(kmeans.CX[0][0] - 1.4) < .15 &  fabs(kmeans.CX[0][1] - 1) < .15 & fabs(kmeans.CX[1][0] + 1.25) < .15 & fabs(kmeans.CX[1][1] + 1) < .15 );
		success = success | ( fabs(kmeans.CX[0][0] + 1.25) < .15 &  fabs(kmeans.CX[0][1] + 1) < .15 & fabs(kmeans.CX[1][0] - 1.4) < .15 & fabs(kmeans.CX[1][1] - 1) < .15 );

		vector< vector<size_t> > Z;
		vector<size_t> z(2);
		z[0] = 5; z[1] = 2; Z.push_back(z);
		z[0] = 5; z[1] = 1; Z.push_back(z);
		z[0] = 5; z[1] = 2; Z.push_back(z);
		z[0] = 5; z[1] = 3; Z.push_back(z);
		z[0] = 5; z[1] = 3; Z.push_back(z);
		z[0] = 0; z[1] = 0; Z.push_back(z);
		z[0] = 0; z[1] = 4; Z.push_back(z);
		z[0] = 0; z[1] = 5; Z.push_back(z);
		z[0] = 0; z[1] = 0; Z.push_back(z);
		z[0] = 1; z[1] =  6; Z.push_back(z);
		z[0] = 1; z[1] = 7; Z.push_back(z);
		z[0] = 1; z[1] =  6; Z.push_back(z);
		KMeans<size_t> kmeans3(Z, 3);
		success = success & ( kmeans3.CI[0] != kmeans3.CI[5] ) & ( kmeans3.CI[5] != kmeans3.CI[10] ) & ( kmeans3.CI[0] != kmeans3.CI[10] );
		//std::cout << '(' << kmeans3.CX[0][0] << "," << kmeans3.CX[0][1] << ")" << std::endl;
		//std::cout << '(' << kmeans3.CX[1][0] << "," << kmeans3.CX[1][1] << ")" << std::endl;
		//std::cout << '(' << kmeans3.CX[2][0] << "," << kmeans3.CX[2][1] << ")" << std::endl;
		//for (size_t i = 0; i < Z.size(); i++)
		//	std::cout << Z[i][0] << " " << Z[i][1] << ": "  << kmeans3.CI[i] << std::endl;

		if (success)
			std::cout << "Pass!" << std::endl;
		else
			std::cout << "Fail." << std::endl;
		return success;
	}
};


#endif