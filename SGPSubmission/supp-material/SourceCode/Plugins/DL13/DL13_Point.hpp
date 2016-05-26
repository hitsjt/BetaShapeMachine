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
