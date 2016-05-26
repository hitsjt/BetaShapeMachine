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

#include "Network.hpp"
#include <cassert>
#include <iostream>

namespace SNL {

NetworkManager::FactoryMap NetworkManager::installed_factories;

bool
NetworkManager::_init()
{
  return true;
}

bool
NetworkManager::_finish()
{
  installed_factories.clear();
  return true;
}

NetworkFactory *
NetworkManager::getFactory(std::string const & type)
{
  FactoryMap::const_iterator installed = installed_factories.find(toLower(type));
  if (installed == installed_factories.end())
  {
    std::cerr << "No factory for networks of type '" << type << "' is installed" << std::endl;
    return NULL;
  }

  return installed->second;
}

bool
NetworkManager::installFactory(std::string const & type, NetworkFactory * factory)
{
  if (!factory)
  {
    std::cerr << "NetworkManager: Null factory cannot be installed" << std::endl;
    return false;
  }

  std::string type_lc = toLower(type);
  FactoryMap::const_iterator installed = installed_factories.find(type_lc);
  if (installed == installed_factories.end())
  {
    installed_factories[type_lc] = factory;
    return true;
  }
  else
    return false;
}

void
NetworkManager::uninstallFactory(std::string const & type)
{
  installed_factories.erase(type);
}

} // namespace SNL
