#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include<iostream>
#include"Sample.h"
#include<vector>
#include "Eigen/Dense"
#include "Eigen/LU"
#include"namepoint.h"
#include "f2c.h"
#include "clapack.h"
#include "blaswrap.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/johnson_all_pairs_shortest.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/limits.hpp>

#ifndef _LALALALAL_
#define _LALALALAL_
struct MyCustomTriangleVertexTriple
{
	size_t id;
  Vector3 v[3];

  MyCustomTriangleVertexTriple() {}
  MyCustomTriangleVertexTriple(Vector3 const & v0_, Vector3 const & v1_, Vector3 const & v2_, size_t _id)
  {
    v[0] = v0_;
    v[1] = v1_;
    v[2] = v2_;
		id = _id;
  }
  MyCustomTriangleVertexTriple(MyCustomTriangleVertexTriple const & src)
  {
    v[0] = src.v[0];
    v[1] = src.v[1];
    v[2] = src.v[2];
		id = src.id;
  }

  // Get the i'th vertex. This is the operative function that a vertex triple needs to have.
  Vector3 const & getVertex(int i) const { return v[i]; }
};

typedef Triangle3<MyCustomTriangleVertexTriple> MyCustomTriangle;
typedef KDTree3<NamedPoint> PKDTree;
typedef KDTree3<MyCustomTriangle> TKDTree;
#endif

#define EPSILON										 1e-6f
// Local features definitions
#define NUM_SCALES														4
#define NUM_CURVATURE_FEATURES_PER_SCALE			16    // k1, k2, k1-k2, k1_abs, k2_abs, k1_abs-k2_abs, (k1+k2)/2, k1*k2, k2/k1, k2/k1+k2 and their abs value
#define NUM_PCA_FEATURES_PER_SCALE					  12	  // l1/suml, l2/suml, l3/suml, (l1+l2)/suml, (l1+l3)/suml, (l2+l3)/suml, l1/l3, l2/l3, l1/l2, (l1+l2)/l3, l1/l3 + l1/l2, l1/l2 + l2/l3  
#define SCALE1_DIV									50.0f
#define SCALE2_DIV									25.0f
#define SCALE3_DIV									10.0f
#define SCALE4_DIV									5.0f
const float SCALES[NUM_SCALES]					  = {(1.0f / SCALE1_DIV), (1.0f / SCALE2_DIV), (1.0f / SCALE3_DIV), (1.0f / SCALE4_DIV)};
// shape context definitions
#define normalizationFactor                            1.0
#define MAX_SC_ANGLE						            90.0f
#define MIN_SC_ANGLE						            -90.0f
#define NUM_BINNING_TYPES_GD								1
const int NUM_GD_BINS[ NUM_BINNING_TYPES_GD ]	  = {5};
const float GD_LOGP[ NUM_BINNING_TYPES_GD ]		  = {1.0f};
const float GD_MAX[ NUM_BINNING_TYPES_GD ]		  = {2.0f};
const int NUM_ANGLE_BINS[ NUM_BINNING_TYPES_GD ]  = {4};

#define NUM_FEATURES_GD											14     // mean, squared mean, tripled mean, quad mean, variance, skewness, kurtosis, 5 percentiles
// SDF features
#define NUM_ANGLES_SDF											3
#define ANGLE1_SDF													15.0f
#define ANGLE2_SDF													30.0f
#define ANGLE3_SDF													45.0f
const float ANGLES_SDF[NUM_ANGLES_SDF]			 = {ANGLE1_SDF, ANGLE2_SDF, ANGLE3_SDF};
#define ANGLE_STEP													15.0f
#define ROT_ANGLE_STEP											45.0f
#define NUM_SDF_FEATURES_PER_ANGLE					1
#define NUM_SDF_FEATURES_PER_BASE						4
const float BASES_SDF[NUM_SDF_FEATURES_PER_BASE] = {1.0f, 2.0f, 4.0f, 8.0f}; // always start from 1, make sure the fiest element of BASES_SDF is 1 (no use of log then).
#define ANGLE_VSI														60.0f
#define NUM_VSI_FEATURES	
// SPIN IMAGES
#define SPIN_DISTANCE_SUPPORT								1.0f
#define SPIN_RESOLUTION											8.0f
#define SPIN_BIN_SIZE												(SPIN_DISTANCE_SUPPORT / SPIN_RESOLUTION)

using namespace std;
typedef long int integer;
typedef boost::property<boost::edge_weight_t, float> EdgeProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeProperty> ProximityGraph;
template<class T> 
struct IndexCmp 
{
	T V;
	IndexCmp(T _V) : V(_V) {}
	bool operator()(const size_t a, const size_t b) const { 
		return V[a] < V[b]; 
	}
};
template <class T>
inline size_t* sortArrayIndices(T* A, size_t size) {
	vector<size_t> VI(size);
	for (size_t i = 0; i < size; i++) {
		VI[i] = i;
	}		
	vector<T> V(A, A+size);
	std::sort( VI.begin(), VI.end(), IndexCmp<vector<T>&>(V) );
	size_t *I = new size_t[size];
	for (size_t i = 0; i < size; i++) {
		I[i] = VI[i];
	}		
	return I;
};

template <class T>
inline void sortArrayIndices(T* A, size_t size, size_t* I) {
	vector<size_t> VI(size);
	for (size_t i = 0; i < size; i++) {
		VI[i] = i;
	}		
	vector<T> V(A, A+size);
	std::sort( VI.begin(), VI.end(), IndexCmp<vector<T>&>(V) );
	for (size_t i = 0; i < size; i++) {
		I[i] = VI[i];
	}		
};

inline float getAngleFromUnitVectors(vec v1, vec v2 ) {
	float cosphi = v1 DOT v2;
	float sinphi = len(v1 CROSS v2);

	return (float)( atan2( sinphi, cosphi ) * (180.0f / M_PI) );
}

inline double* covar(double* D, size_t N) {
	double *CD = new double[9];

	CD[0] = 0.0f;
	for (size_t r = 0; r < N; r++)
		CD[0]  += D[r*3] * D[r*3];
	for (size_t j = 0; j <= 1; j++) {
		CD[1 + j*3] = 0.0f;
		for (size_t r = 0; r < N; r++) {
			CD[1 + j*3] +=  D[1 + r*3] * D[j + r*3];
		}
	}
	for (size_t j = 0; j <= 2; j++) {
		CD[2 + j*3] = 0.0f;
		for (size_t r = 0; r < N; r++) {
			CD[2 + j*3] +=  D[2 + r*3] * D[j + r*3];
		}
	}
	CD[3] = CD[1];
	CD[6] = CD[2];
	CD[7] = CD[5];

	return CD;
}
template <class T>
inline vector<T> removePositiveOutliers(vector<T>& v, float percentile) {
	vector<T> result( v.size() );
	for (int i = 0; i < v.size(); i++) {
		result[i] = fabs(v[i]);
	}
	std::sort( result.begin(), result.end() );
	float outlierValue = result[ (size_t)floor(percentile*(float)v.size()) ];
	for (int i = 0; i < v.size(); i++) {
		if (fabs(v[i]) < outlierValue) {
			result[i] = v[i];
		} else {
			result[i] = sgn(v[i]) * outlierValue;
		}
	}
	return result;
}

template <class T>
inline vector<T> removeOutliers(vector<T>& v, float percentile) {
	vector<T> result( v.size() );
	for (int i = 0; i < v.size(); i++) {
		result[i] = v[i];
	}
	std::sort( result.begin(), result.end() );
	float outlierValueMax = result[ (size_t)floor(percentile*(float)v.size()) ];
	float outlierValueMin = result[ (size_t)floor((1.0f-percentile)*(float)v.size()) ];
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < outlierValueMin) {
			result[i] = outlierValueMin;
		} else if (v[i] > outlierValueMax) {
			result[i] = outlierValueMax;
		} else {
			result[i] = v[i];
		}
	}
	return result;
}

template <class T>
inline vector<T> removeOutliers(vector<T>& v, float percentilePositive, float percentileNegative) {
	vector<T> result( v.size() );
	for (int i = 0; i < v.size(); i++) {
		result[i] = v[i];
	}
	std::sort( result.begin(), result.end() );
	float outlierValueMax = result[ (size_t)floor(percentilePositive*(float)v.size()) ];
	float outlierValueMin = result[ (size_t)floor(percentileNegative*(float)v.size()) ];
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < outlierValueMin) {
			result[i] = outlierValueMin;
		} else if (v[i] > outlierValueMax) {
			result[i] = outlierValueMax;
		} else {
			result[i] = v[i];
		}
	}
	return result;
}


class Bin2D {
public:
	float x1;
	float x2;
	float y1;
	float y2;
	float cx, cy;
	float value;
	Bin2D() { value = 0.0f; }
	Bin2D(float startx, float endx, float starty, float endy): x1(startx), x2(endx), y1(starty), y2(endy) { value = 0.0f; }
	bool contains(float x, float y) { return (x >= x1) & (x <= x2) & (y >= y1) & (y <= y2); }
	void increaseValue(float v) { value += v; }
	void reset() { value = 0.0f; }
	void setCenter() { cx = (x1 + x2) / 2.0f; cy = (y1 + y2) / 2.0f; }
};

static inline std::ostream &operator << (std::ostream &os, const Bin2D &b) { 
	os << "x=[" << b.x1 << ", " << b.x2 << "], y=[" << b.y1 << ", " << b.y2 << "], value=" << b.value << std::endl;
	return os;
}
template <class T>
inline T logabs(T d) {
	return fabs( log( abs(d) + EPSILON ) );
}

template <class T>
inline T cosd(T d) {
	return cos( (d / 180.0f) * (float)M_PI );
}

template <class T>
inline T sind(T d) {
	return sin( (d / 180.0f) * (float)M_PI );
}



template <class T>
inline T median(vector<T> v) {
	std::sort(v.begin(), v.end());
	if ( v.size() % 2 == 0 ) {
		return ( v[ v.size() / 2 ] +  v[ (v.size() / 2) - 1 ] ) / 2.0f;
	} else {
		return v[ v.size() / 2 ];
	}
}

class Compute_Feature
{
public:
	Compute_Feature(void);
	~Compute_Feature(void);
	Compute_Feature(vector<Sample> point_set);
	vector<Sample>  sample_set;
	void exportPCA(); // 3*1 eigen vector
	void exportNormalMap(); // 4*4*3 for each sample
	void exportShapeContex(); // 4*5 for each sample
	void exportShapeContexNew(); // 4*5 for each sample
	void exportSpinImageNew();
	void exportCurvature();
	void exportSpinImage();
	void exportSDF(TriMesh *mesh);
	void exportDifferent();
	void computeGeodesicDistances();
	void exportPCAFeaturesPerPoint();
	float** geodesic_distances;	
	size_t** geodesic_closest_samples;
	vector<vector<int>> near_points;
	void getClosestSamples(vector<size_t>& closestSamples, vector<float>& closestDistances,  size_t c, float maxDistance, size_t minNumPoints, float normalThreshold);
	void bulitNear();
	float getfeatureVar(vector<float> feature);
	int normal_map_res;
	vector<Sample> GetFeaturedSample(int type = 0);
	float rayShoot(vec& line, point& origin, float limdist);
	TKDTree* tree;				
	vector<vector<float>> sdfs;
};

