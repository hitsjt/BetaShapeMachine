#ifndef __SNL_DL13_Plugin_hpp__
#define __SNL_DL13_Plugin_hpp__

#include "../../Plugin.hpp"
#include "DL13_Common.hpp"

namespace SNL {;
namespace DL13 {;

// Forward declaration
class DL13_NetworkFactory;

/** Plugin for probabilistic model of shape used for our SIGGRAPH 2012 paper. */
class SNL_DL13_DLL_LOCAL DL13_Plugin : public SNL::Plugin
{
public:
	/** Default constructor. */
	DL13_Plugin();

	/** Destructor. */
	~DL13_Plugin();

	bool install();
	bool startup();
	bool shutdown();
	bool uninstall();

private:
	DL13_NetworkFactory * factory;
	bool started;

}; // class DL13_Plugin

} // namespace DL13
} // namespace SNL

#endif
