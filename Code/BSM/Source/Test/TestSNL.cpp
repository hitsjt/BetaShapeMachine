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

    if ( (arg == "-pca") || (arg == "pca") )
    {
      status = testPCA(argc, argv);
      return status;
    }

    if ((arg == "-align-dl13") || (arg == "align-dl13"))
    {
      status = alignModel(argc, argv);
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

