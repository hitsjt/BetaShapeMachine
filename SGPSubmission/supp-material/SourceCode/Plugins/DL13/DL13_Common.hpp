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

#ifndef __DL13_COMMON_HPP
#define __DL13_COMMON_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <chrono>
#include <omp.h>
#define EIGEN_NO_DEBUG 1
#include "../../../../Eigen/Dense"
#include "DL13_SymbolVisibility.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>
#include <boost/range/counting_range.hpp>
#include <boost/timer.hpp>

#define EPSILONf          1e-7f
#define EPSILONd          1e-16
//#define NANf							std::numeric_limits<float>::quiet_NaN()

#define isinv(x) (x == FLT_MAX)



#ifdef _MSC_VER

#include <boost/unordered_map.hpp>
#include "DL13_Boost_unordered_map_serialization.hpp"
# define   UNORDERED_MAP boost::unordered_map

#define isnan(x) (_isnan(x))
#define isinf(x) (!_finite(x))
#define getch _getch
#define popen _popen
#define pclose _pclose

#else

//#include <tr1/unordered_map>
#include "DL13_Boost_unordered_map_serialization.hpp"
# define   UNORDERED_MAP std::tr1::unordered_map

#  include <fenv.h>
#  include <termios.h>
#  include <unistd.h>

inline int getch(void)
{
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

#endif


//#define FVECTORf  Eigen::Matrix<float, Eigen::Dynamic, 1, 0, 2048, 1>
//#define FMATRIXf  Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, 0, 2048, 16>
#define SVECTORf  Eigen::Matrix<float, Eigen::Dynamic, 1>
#define SMATRIXf  Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>
typedef boost::mt19937 RAND_GEN;
using namespace std;

namespace SNL {;
namespace DL13 {;

template<typename T>
class SortOrder
{
public:
	SortOrder(const std::vector<T> * _sort_array) : sort_array(_sort_array) { }
	bool operator()(int lhs, int rhs) const
	{
		return sort_array->at(lhs) < sort_array->at(rhs);
	}
private:
	const std::vector<T> *sort_array;
};

enum variable_type { INVALID_VARIABLE, DETERMINICTIC, BETA, GAUSSIAN, BINARY };
enum edge_type { INVALID_EDGE, BETA_GAUSSIAN, GAUSSIAN_GAUSSIAN, BETA_BETA, BINARY_BINARY, BINARY_GAUSSIAN, BINARY_BETA, BINARY_DOUBLEBETA };
enum phase_type { POSITIVE_PHASE, NEGATIVE_PHASE };
enum regularization_type { L1, L2, LS1, LS2, LS1L1, LS2L2, LNONE };



} // namespace DL13
} // namespace SNL

#endif
