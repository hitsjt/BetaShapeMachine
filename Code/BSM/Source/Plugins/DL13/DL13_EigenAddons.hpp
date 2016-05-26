#ifndef __DL13_EIGENADDONS_HPP
#define __DL13_EIGENADDONS_HPP

#include "DL13_Common.hpp"

namespace SNL {;
namespace DL13 {;


// compute variance, given that mean is computed
template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline _Scalar variance(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v, _Scalar& mean)
{
	return ( v.array() - mean ).square().sum() / _Scalar(v.size());
}

// compute variance, given that mean is computed
template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline _Scalar variance(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v)
{
	_Scalar mean = v.mean();
	return ( v.array() - mean ).square().sum() / _Scalar(v.size());
}

// compute std variation, given that mean is computed
template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline _Scalar stddev(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v, _Scalar& mean)
{
	return sqrt( variance(v, mean) );
}

// compute std variation
template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline _Scalar stddev(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v)
{
	return sqrt( variance(v) );
}



template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline void standardize(Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v)
{
	_Scalar mean = v.mean();
	_Scalar std = sqrt( variance(v, mean) );
	v = ( v.array() - mean) / (std + _Scalar(EPSILONf));
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline std::vector< vector<_Scalar> > convertEigenMatrixToStdVectorVector(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& M)
{
	std::vector< vector<_Scalar> > X( M.rows() );
	for (int i = 0; i < M.rows(); i++)
	{
		X[i].resize( M.cols() );
		for (int j = 0; j < M.cols(); j++)
		{
			X[i][j] = M(i, j);
		}
	}	
	return X;
}

template <typename _Scalar>
inline SMATRIXf convertStdVectorVectorToEigenMatrix(const std::vector< vector<_Scalar> >& X)
{
	SMATRIXf M;
	if ( X.empty() )
		return M;
	M.resize( X.size(), X[0].size() );
	for (int i = 0; i < X.size(); i++)
	{
		for (int j = 0; j < X[0].size(); j++)
		{
			M(i, j) = X[i][j];
		}
	}	
	return M;
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline std::vector<_Scalar> convertEigenVectorToStdVector(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m)
{
	std::vector<_Scalar> v( m.size() );
	for (int i = 0; i < m.size(); i++)
	{
		v[i] = m(i);
	}	
	return v;
}

template <typename _Scalar>
inline SVECTORf convertStdVectorToEigenVector(const std::vector<_Scalar>& v)
{
	SVECTORf m;
	m.resize( v.size() );
	for (int i = 0; i < v.size(); i++)
	{
		m(i) = v[i];
	}	
	return m;
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline void limit(Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m, const _Scalar& a, const _Scalar& b)
{
	for (int d = 0; d < m.size(); d++)
	{
		if ( m(d) < a )
			m(d) = a;
		if ( m(d) > b )
			m(d) = b;
	}
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline  Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> 
				round(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m)
{
	Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> mt = m;

	for (int d = 0; d < m.rows(); d++)
		for (int d2 = 0; d2 < m.cols(); d2++)
			mt(d, d2) = floor( m(d, d2) + (_Scalar)0.5);

	return mt;
}

inline SVECTORf removeElements(const SVECTORf& m, const float a)
{
	SVECTORf mt = m;
	int dt = 0;
	for (int d = 0; d < m.size(); d++)
	{
		if ( m(d) != a )
		{
			mt(dt++) = m(d);
		}		
	}
	mt.conservativeResize(dt);
	return mt;
}

inline SVECTORf removeElementsAccordingToOtherVector(const SVECTORf& m2, const SVECTORf& m, const float a)
{
	if ( m.size() != m2.size() )
		return m2;
	SVECTORf mt = m2;
	int dt = 0;
	for (int d = 0; d < m.size(); d++)
	{
		if ( m(d) != a )
		{
			mt(dt++) = m2(d);
		}		
	}
	mt.conservativeResize(dt);
	return mt;
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> 
		   removeRows(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m, const _Scalar& a)
{
	Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> mt = m;
	int dt = 0;
	for (int d = 0; d < m.rows(); d++)
	{
		bool hasElement = false;
		for (int d2 = 0; d2 < m.cols(); d2++)
			if ( m(d, d2) == a )
				hasElement = true;
		if ( !hasElement )
			mt.row(dt++) = m.row(d);
	}
	mt.conservativeResize(dt, m.cols() );
	return mt;
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> 
		   removeRowsAccordingToOtherMatrix(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m2, const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m, const _Scalar& a)
{
	if ( m.rows() != m2.rows() )
		return m2;
	Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> mt = m2;
	int dt = 0;
	for (int d = 0; d < m.rows(); d++)
	{
		bool hasElement = false;
		for (int d2 = 0; d2 < m.cols(); d2++)
			if ( m(d, d2) == a )
				hasElement = true;
		if ( !hasElement )
			mt.row(dt++) = m2.row(d);
	}
	mt.conservativeResize(dt, m2.cols() );
	return mt;
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline SVECTORf cumsum(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m)
{
	SVECTORf cm;
	cm.resize( m.size() );
	cm(0) = m(0);	
	for (int d = 1; d < m.size(); d++)
	{
		cm(d) = cm(d-1) + m(d);
	}
	return cm;
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline SVECTORf ceiling(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m)
{
	SVECTORf c;
	c.resize( m.size() );
	for (int d = 0; d < m.size(); d++)
	{
		c(d) = ceil( m(d) );
	}
	return c;
}

template <class T>
T unifRand(const T& a, const T& b)
{
  double ad = double(a);
  double bd = double(b);
  double unifrand = double( rand() ) / double(RAND_MAX);
  return T( (bd-ad)*unifrand + ad );
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename _Scalar>
inline _Scalar sigmoid(const _Scalar& s)
{
	return _Scalar(1.0) / ( _Scalar(1.0) + exp(-s) );
}

template <typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
inline Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>
	sigmoid(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v)
{
	return _Scalar(1.0) / ( _Scalar(1.0) + (-v.array()).exp() );
}

template <typename _Scalar>
class RandomVariableProperties
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & valid;
		ar & mean;
		ar & var;
		ar & std;
		ar & max;
		ar & min;
	}
public:
	bool valid;
	_Scalar mean;
	_Scalar var;
	_Scalar std;
	_Scalar max;
	_Scalar min;
	RandomVariableProperties(): 
		valid(false), mean(FLT_MAX), var(FLT_MAX), std(FLT_MAX), max(FLT_MAX), min(FLT_MAX) { };
	RandomVariableProperties(const RandomVariableProperties& _source): 
		valid(_source.valid), mean(_source.mean), var(_source.var), std(_source.std), max(_source.max), min(_source.min) { };
// compute the basic random variable properties for a vector
	template <int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
	inline void getBasicRandomVariableProperties(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v)
	{
		if (v.size() == 0)
		{
			std::cerr << "Internal error: getBasicRandomVariableProperties was called with an empty vector as argument" << std::endl;
			exit(-1);
		}
		mean = v.mean();
		var = variance(v, mean);
		std = sqrt( var );
		max = v.maxCoeff();
		min = v.minCoeff();
		valid = true;
	}


	// standardize vector, return mean/var
	template <int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
	inline void standardize(Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& v)
	{
		if ( !valid )
		{
			std::cerr << "Internal error: RandomVariableProperties::standardize was called before mean/std is computed." << std::endl;
			exit(-1);
		}
		v = ( v.array() - mean) / (std + _Scalar(EPSILONf));
	}

//	template <typename _Scalar>
	inline void standardize(_Scalar& s)
	{
		if ( !valid )
		{
			std::cerr << "Internal error: RandomVariableProperties::standardize was called before mean/std is computed." << std::endl;
			exit(-1);
		}
		s = ( s - mean) / (std + _Scalar(EPSILONf));
	}

//	template <typename _Scalar>
	inline void unstandardize(_Scalar& s)
	{
		if ( !valid )
		{
			std::cerr << "Internal error: RandomVariableProperties::unstandardize was called before mean/std is computed." << std::endl;
			exit(-1);
		}
		s = s * std + mean; 
	}
};


}
}

#endif