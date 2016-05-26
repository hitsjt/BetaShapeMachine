#ifndef __SNL_PCA_Plugin_hpp__
#define __SNL_PCA_Plugin_hpp__

#include "../../Plugin.hpp"
#include "PCA_Common.hpp"

namespace SNL {;
namespace PCA {;

class SNL_PCA_DLL_LOCAL PCA_Plugin : public SNL::Plugin
{
public:
	/** Default constructor. */
	PCA_Plugin();

	/** Destructor. */
	~PCA_Plugin();

	bool install();
	bool startup();
	bool shutdown();
	bool uninstall();

private:
	bool started;

}; // class PCA_Plugin

} // namespace PCA
} // namespace SNL

#endif
