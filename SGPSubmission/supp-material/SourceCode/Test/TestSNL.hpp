//============================================================================
//
// This file is part of the Shapes Generative Model Library (SGML) project.
//
// Copyright (c) 2010-2014 - Evangelos Kalogerakis, Siddhartha Chaudhuri (authors of the code) / Stanford University, UMass-Amherst
//
// SGML is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// SGML is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with SGML.  If not, see <http://www.gnu.org/licenses/>.
//
//============================================================================



#ifndef __TESTSNL_HPP
#define __TESTSNL_HPP

#include "../SNL.hpp"
#include <iostream>
#include <sys/stat.h>
#include <string.h>
#include <boost/timer.hpp>

#ifdef _MSC_VER
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

using namespace std;
using namespace SNL;


bool testDL13(int argc, char * argv[]);

string parent(string const & file_path);
string getFullPath(string const & dir, string const & filename);

#endif 
