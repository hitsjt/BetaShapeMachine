#include "DL13_NetworkFactory.hpp"
#include "DL13_BoltzmannMachine.hpp"

namespace SNL {;
namespace DL13 {;

DL13_NetworkFactory::~DL13_NetworkFactory()
{
	destroyAllNetworks();
}

SNL::Network *
	DL13_NetworkFactory::createNetwork(std::string const & name)
{
	return new BoltzmannMachine(name);
}

void
	DL13_NetworkFactory::destroyNetwork(SNL::Network * network)
{
	for (std::size_t i = 0; i < networks.size(); ++i)
		if (networks[i] == network)
		{
			networks.erase(networks.begin() + i);
			break;
		}

		delete network;
}

void
	DL13_NetworkFactory::destroyAllNetworks()
{
	for (std::size_t i = 0; i < networks.size(); ++i)
		delete networks[i];

	networks.clear();
}

} // namespace DL13
} // namespace SNL
