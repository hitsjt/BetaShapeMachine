#ifndef __SNL_DL13_NetworkFactory_hpp__
#define __SNL_DL13_NetworkFactory_hpp__

#include "../../Network.hpp"
#include "DL13_Common.hpp"
#include <vector>

namespace SNL {;
namespace DL13 {;

/** Factory for creating networks of the type described in our SIGGRAPH 2012 paper. */
class SNL_DL13_DLL_LOCAL DL13_NetworkFactory : public SNL::NetworkFactory
{
public:
	/** Destructor. */
	~DL13_NetworkFactory();

	SNL::Network * createNetwork(std::string const & name);
	void destroyNetwork(SNL::Network * network);

	/** Destroy all networks created with this factory. */
	void destroyAllNetworks();

private:
	std::vector<SNL::Network *> networks;
};

} // namespace DL13
} // namespace SNL

#endif
