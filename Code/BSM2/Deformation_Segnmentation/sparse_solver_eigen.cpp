
#include "sparse_solver_eigen.h"
#include <omp.h>

SparseSolver::SparseSolver()
{
	mat_ptr_	= 0;
	solver_ptr_ = 0;
}

SparseSolver::~SparseSolver()
{
	Clear();
}

void SparseSolver::Init(const RowMapVec& mat, int nrVars)
{
	int num_rows = mat.size();
	int num_cols = nrVars;
	int num_vars = num_cols;
	int num_nonzero = 0;
	for (int i = 0; i < num_rows; ++i)
	{
		num_nonzero += mat[i].size();
	}

	// type definition
	typedef Eigen::Triplet<FT> triplet;

	// bulid matrix for eigen
	vector<triplet> tripletList;
	tripletList.reserve(num_nonzero);
	for (int i = 0; i < num_rows; ++i)
	{
		for (RowMap::const_iterator it = mat[i].begin(); it != mat[i].end(); ++it)
		{
			tripletList.push_back(triplet(i,it->first,it->second));
		}
	}

	Clear();

	mat_ptr_ = new EigenSparseMat(num_rows,num_cols);
	mat_ptr_->setFromTriplets(tripletList.begin(),tripletList.end());
	mat_ptr_->makeCompressed();

	solver_ptr_ = new EigenSparseSolver;
	solver_ptr_->analyzePattern(*mat_ptr_);
	solver_ptr_->factorize(*mat_ptr_);
}

void SparseSolver::Clear()
{
	if (mat_ptr_)
	{
		delete mat_ptr_;
		mat_ptr_ = 0;
	}

	if (solver_ptr_)
	{
		delete solver_ptr_;
		solver_ptr_ = 0;
	}
}

int SparseSolver::Solve(const vector<vector<FT> >& cons, vector<vector<FT> >& solution)
{
	if (!mat_ptr_ || !solver_ptr_)
	{
		return -1;
	}

	int num_rows = mat_ptr_->rows();
	int num_vars = mat_ptr_->cols();

	int dim = cons.size();
	solution.resize(dim);
//	#pragma omp parallel
	for (int i = 0; i < dim; ++i)
	{
		EigenVec b(num_rows), x;
		for (int j = 0; j < num_rows; ++j)
		{
			b(j) = cons[i][j];
		}
		x = solver_ptr_->solve(b);
		solution[i].resize(num_vars);
		for (int j = 0; j < num_vars; ++j)
		{
			solution[i][j] = x(j);
		}
	}

	return 0;
}

LeastSquaresSparseSolver::LeastSquaresSparseSolver()
{
	A_ptr_ = 0;
	At_ptr_ = 0;
	AtA_ptr_ = 0;
	solver_ptr_ = 0;
}

LeastSquaresSparseSolver::~LeastSquaresSparseSolver()
{
	Clear();
}

void LeastSquaresSparseSolver::Init(const RowMapVec& mat, int nrVars)
{
	int num_rows = mat.size();
	int num_cols = nrVars;
	int num_vars = num_cols;
	int num_nonzero = 0;
	for (int i = 0; i < num_rows; ++i)
	{
		num_nonzero += mat[i].size();
	}

	// type definition
	typedef Eigen::Triplet<FT> triplet;

	// bulid matrix for eigen
	vector<triplet> tripletList;
	tripletList.reserve(num_nonzero);
	for (int i = 0; i < num_rows; ++i)
	{
		for (RowMap::const_iterator it = mat[i].begin(); it != mat[i].end(); ++it)
		{
			tripletList.push_back(triplet(i,it->first,it->second));
		}
	}

	Clear();

	A_ptr_ = new EigenSparseMat(num_rows,num_cols);
	A_ptr_->setFromTriplets(tripletList.begin(),tripletList.end());
	A_ptr_->makeCompressed();

	At_ptr_ = new EigenSparseMat(A_ptr_->transpose());
	At_ptr_->makeCompressed();

	AtA_ptr_ = new EigenSparseMat((*At_ptr_) * (*A_ptr_));
	AtA_ptr_->makeCompressed();

	solver_ptr_ = new EigenSparseSolver;
//	solver_ptr_->compute(tmp_mat);
	solver_ptr_->analyzePattern(*AtA_ptr_);
	solver_ptr_->factorize(*AtA_ptr_);
}

void LeastSquaresSparseSolver::Clear()
{
	if (A_ptr_)
	{
		delete A_ptr_;
		A_ptr_ = 0;
	}

	if (At_ptr_)
	{
		delete At_ptr_;
		At_ptr_ = 0;
	}

	if (AtA_ptr_)
	{
		delete AtA_ptr_;
		AtA_ptr_ = 0;
	}

	if (solver_ptr_)
	{
		delete solver_ptr_;
		solver_ptr_ = 0;
	}
}

int LeastSquaresSparseSolver::Solve(const vector<vector<FT> >& cons, vector<vector<FT> >& solution)
{
	if (!A_ptr_ || !At_ptr_ || !solver_ptr_)
	{
		return -1;
	}

	int num_rows = A_ptr_->rows();
	int num_vars = A_ptr_->cols();

	int dim = cons.size();
	solution.resize(dim);

	for (int i = 0; i < dim; ++i)
	{
		EigenVec b(num_rows), x;
		for (int j = 0; j < num_rows; ++j)
		{
			b(j) = cons[i][j];
		}

		EigenVec Atb = (*At_ptr_) * b;

		x = solver_ptr_->solve(Atb);
		solution[i].resize(num_vars);
		for (int j = 0; j < num_vars; ++j)
		{
			solution[i][j] = x(j);
		}
	}

	return 0;
}