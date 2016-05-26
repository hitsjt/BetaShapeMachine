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
