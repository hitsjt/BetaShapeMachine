
#ifndef _SPARSE_SOLVER_EIGEN_H_
#define _SPARSE_SOLVER_EIGEN_H_

#include <map>
#include <vector>
#include "Eigen/Sparse"
using std::map;
using std::vector;

class SparseSolver
{
public:
	typedef double					FT;
	typedef map<int,FT>				RowMap;
	typedef vector<map<int,FT> >	RowMapVec;
	typedef Eigen::SparseMatrix<FT> EigenSparseMat;
	//typedef Eigen::SimplicialLDLT<EigenSparseMat > EigenSparseSolver;
	typedef Eigen::ConjugateGradient<EigenSparseMat > EigenSparseSolver;
	typedef Eigen::Matrix<FT, Eigen::Dynamic, 1> EigenVec;

public:
	SparseSolver();
	~SparseSolver();

	void Init(const RowMapVec& mat, int nrVars);
	void Clear();

	int Solve(const vector<vector<FT> >& cons, vector<vector<FT> >& solution);

private:
	EigenSparseMat* mat_ptr_;
	EigenSparseSolver* solver_ptr_;
};

class LeastSquaresSparseSolver
{
public:
	typedef double					FT;
	typedef map<int,FT>				RowMap;
	typedef vector<map<int,FT> >	RowMapVec;
	typedef Eigen::SparseMatrix<FT> EigenSparseMat;
	typedef Eigen::SimplicialLDLT<EigenSparseMat > EigenSparseSolver;
	typedef Eigen::Matrix<FT, Eigen::Dynamic, 1> EigenVec;
public:
	LeastSquaresSparseSolver();
	~LeastSquaresSparseSolver();

	void Init(const RowMapVec& mat, int nrVars);
	void Clear();

	int Solve(const vector<vector<FT> >& cons, vector<vector<FT> >& solution);

public:
	EigenSparseMat* A_ptr_;
	EigenSparseMat* At_ptr_;
	EigenSparseMat* AtA_ptr_;
	EigenSparseSolver* solver_ptr_;
};

#endif//_SPARSE_SOLVER_EIGEN_H_