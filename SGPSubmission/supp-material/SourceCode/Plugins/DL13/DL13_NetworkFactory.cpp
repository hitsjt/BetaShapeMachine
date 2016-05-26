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
