#ifndef __PCA_PART_HPP
#define __PCA_PART_HPP

#include "PCA_Common.hpp"
#include "PCA_EigenAddons.hpp"


namespace SNL {;
namespace PCA {;

class SNL_PCA_API PCAPart
{
private:
  vector<int> point_ids;
  SRVECTORf mean;
  SMATRIXf base; // original #dimensions D x  #reduced dimensions D' 

  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & point_ids;
    ar & mean;
    ar & base;
  }
public:
  PCAPart() { };
  void setPointIds(const vector<int>& _point_ids) { point_ids = _point_ids;  }
  int getPointId(int n) { return point_ids[n]; }
  void train(const SMATRIXf& training_data, float keep_variance_percentage);
  SMATRIXf reconstruct( const SMATRIXf& test_data );
};


} // end of namespace PCA
} // end of namespace SNL

#endif
