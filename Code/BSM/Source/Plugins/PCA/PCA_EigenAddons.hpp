#ifndef __PCA_EIGENADDONS_HPP
#define __PCA_EIGENADDONS_HPP

#include "PCA_Common.hpp"

namespace SNL {;
namespace PCA {;


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
inline SCVECTORf convertStdVectorToEigenVector(const std::vector<_Scalar>& v)
{
	SCVECTORf m;
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
inline SCVECTORf cumsum(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& m)
{
	SCVECTORf cm;
	cm.resize( m.size() );
	cm(0) = m(0);	
	for (int d = 1; d < m.size(); d++)
	{
		cm(d) = cm(d-1) + m(d);
	}
	return cm;
}

}
}

//// SERIALIZE EIGEN MATRIX //////
namespace boost
{;
  template<class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
  inline void serialize(
    Archive & ar,
    Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> & t,
    const unsigned int file_version
    )
  {
    size_t rows = t.rows(), cols = t.cols();
    ar & rows;
    ar & cols;
    if (rows * cols != t.size())
      t.resize(rows, cols);

    for (size_t i = 0; i < t.size(); i++)
      ar & t.data()[i];
  }
}


#endif