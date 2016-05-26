#ifndef __DL13_POINT
#define __DL13_POINT

#include "Trimesh2/Vec.hpp"

namespace SNL {;
namespace DL13 {;

class Point
{
public:
  point p;
  int   id;
  int part_id;
  bool has_symmetric_part;
  bool is_self_symmetric;

  Point(float px, float py, float pz, int _id, int _part_id, bool _has_symmetric_part = false, bool _is_self_symmetric = false)
  {
    p = point(px, py, pz);
    id = _id;
    part_id = _part_id;
    has_symmetric_part = _has_symmetric_part;
    is_self_symmetric = _is_self_symmetric;
  }
};

}
}

#endif
