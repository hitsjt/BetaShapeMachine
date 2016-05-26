#ifndef __PCA_COMMON_HPP
#define __PCA_COMMON_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <chrono>
#include <omp.h>
#define EIGEN_NO_DEBUG 1
#include "../../../../Eigen/Dense"
#include "../../../../Eigen/Eigenvalues"
#include "PCA_SymbolVisibility.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include <boost/timer.hpp>

#define EPSILONf          1e-7f
#define EPSILONd          1e-16

#define isinv(x) (x == FLT_MAX)

#ifdef _MSC_VER

#define isnan(x) (_isnan(x))
#define isinf(x) (!_finite(x))
#define getch _getch
#define popen _popen
#define pclose _pclose

#else

#include <fenv.h>
#include <termios.h>
#include <unistd.h>

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

#define SRVECTORf  Eigen::Matrix<float, 1,  Eigen::Dynamic>
#define SCVECTORf  Eigen::Matrix<float, Eigen::Dynamic, 1>
#define SMATRIXf  Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic>
using namespace std;


#endif
