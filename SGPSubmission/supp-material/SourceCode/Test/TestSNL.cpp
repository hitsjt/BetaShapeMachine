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


#include "TestSNL.hpp"

string
parent(string const & file_path)
{
	char cCurrentPath[4096];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return "";
	}
	else
	{
		return string( cCurrentPath );
	}

	//size_t last_slash = file_path.find_last_of('/');
	//if (last_slash == string::npos)
	//	return "";
	//else if (last_slash == 0)  // parent is root folder
	//	return "/";
	//else
	//	return file_path.substr(0, last_slash);
}


string
getFullPath(string const & dir, string const & filename)
{
  return dir.empty() ? filename : (dir[dir.length() - 1] == '/' ? dir + filename : dir + '/' + filename);
}

int
main(int argc, char * argv[])
{
  // We're going to use plugins, so we need to call this at the beginning of the program
  SNL::PluginManager::init();

  bool status = false;
  

  // Do the tests
  if ( argc >= 2 )
  {
    std::string arg(argv[1]);
    std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
 

//	  if ( strcmp( argv[1], "-s12" ) || strcmp( argv[1], "s12" )
//		  || strcmp( argv[1], "S12" ) || strcmp( argv[1], "-S12" ) )
//	  {
//		  status = testS12(argc, argv);
//		  return status;
//	  }
    if ( (arg == "-dl13") || (arg == "dl13") )
	  {
		  status = testDL13(argc, argv);
		  return status;
	  }
  }
  else
  {
    status = testDL13(argc, argv);
    return status;
  }


  if (!status)
  {
    cerr << "Test failed" << endl;
    return status;
  }

  // Hooray, all tests passed
  cerr << "Test completed" << endl;
  return status;
}

