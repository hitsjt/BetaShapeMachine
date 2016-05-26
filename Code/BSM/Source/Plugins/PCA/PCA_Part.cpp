#include "PCA_Common.hpp"
#include "PCA_Part.hpp"

namespace SNL {;
namespace PCA {;

void PCAPart::train(const SMATRIXf& training_data, float keep_variance_percentage)
{
  // training_data is M x D
  // M is #examples, D is #dimensions
  int M = training_data.rows();
  int D = training_data.cols();

  SMATRIXf X = training_data;
  mean = training_data.colwise().mean(); // calculate mean
  X.rowwise() -= mean; // subtract mean

  SMATRIXf C = X.transpose() * X / float(M-1.0f); // compute covariance matrix
  Eigen::SelfAdjointEigenSolver<SMATRIXf> solver;  
  solver.compute(C);
  SCVECTORf e = solver.eigenvalues().reverse().array() + EPSILONf; // compute eigenvalues IN DECREASING ORDER
  e.array() = e.array() / e.sum(); // normalize so sum is 1 
  e = cumsum(e); // cumulative sum
  int d;
  for (d = 0; d < D-1; d++)
  {
    if (e(d) > keep_variance_percentage)
      break;
  }
  int DP = d+1; // this is the number of dimensions to keep
  std::cout << " Keeping " << DP << " dimensions. ";

  SMATRIXf V = solver.eigenvectors(); // compute eigenvectors
  base = SMATRIXf(D, DP); // our PCA base 
  base.fill(0.0f);
  int current_col = 0;
  for (int d = D - 1; d >= 0; d--) // fill the PCA base, note: Eigen computes eigenvalues/vectors in increasing order
  {
    base.col(current_col++) = V.col(d);
    if (current_col == DP)
      break;
  }  
}

SMATRIXf PCAPart::reconstruct(const SMATRIXf& test_data)
{
  // test_data is M x D
  // M is #examples, D is #dimensions
  int M = test_data.rows();
  int D = test_data.cols();

  SMATRIXf X = test_data;

  X.rowwise() -= mean; // subtract mean

  // project data [M x D] x [D x D']
  SMATRIXf R = X * base; // result is M x D'

  // unproject data [M x D'] x [D' x D]
  SMATRIXf RR = (R * base.transpose()).rowwise() + mean; 

  return RR;
}



} // end of namespace PCA
} // end of namespace SNL