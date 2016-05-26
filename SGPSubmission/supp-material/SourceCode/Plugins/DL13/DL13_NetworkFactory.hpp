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
