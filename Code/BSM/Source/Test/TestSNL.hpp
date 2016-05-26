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



bool testS12(int argc, char * argv[]);
bool testDL13(int argc, char * argv[]);
bool testPCA(int argc, char * argv[]);
bool alignModel(int argc, char * argv[]);

string parent(string const & file_path);
string getFullPath(string const & dir, string const & filename);

#endif 
