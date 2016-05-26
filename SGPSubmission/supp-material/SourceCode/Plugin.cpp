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

#include "Plugin.hpp"
#include "DynLib.hpp"
#include "Network.hpp"
#include <iostream>

namespace SNL {

typedef Plugin * (*SNL_DLL_START_PLUGIN)(void);
typedef void     (*SNL_DLL_STOP_PLUGIN) (void);

// Static variables
bool                       PluginManager::initialized = false;
PluginManager::DynLibMap   PluginManager::dynlibs;
PluginManager::PluginList  PluginManager::plugins;

bool
PluginManager::init()
{
  if (initialized) return true;

  if (!NetworkManager::_init())
    return false;

  initialized = true;
  return true;
}

bool
PluginManager::finish()
{
  if (!initialized) return true;

  if (!unloadAllPlugins())
    return false;

  if (!NetworkManager::_finish())
    return false;

  initialized = false;
  return true;
}

Plugin *
PluginManager::load(std::string const & path)
{
  if (!initialized)
  {
    std::cerr << "PluginManager: Manager not initialized" << std::endl;
    return NULL;
  }

  if (dynlibs.find(path) != dynlibs.end()) return NULL;

  DynLib * dynlib = DynLibManager::load(path);
  dynlibs[path] = dynlib;

  SNL_DLL_START_PLUGIN start_func = (SNL_DLL_START_PLUGIN)dynlib->getSymbol("dllStartPlugin");
  return start_func();  // this must call install(), which adds the plugin to the installed list
}

bool
PluginManager::unload(std::string const & path)
{
  if (!initialized)
  {
    std::cerr << "PluginManager: Manager not initialized" << std::endl;
    return false;
  }

  DynLibMap::iterator dyn_loaded = dynlibs.find(path);
  if (dyn_loaded != dynlibs.end())
  {
    SNL_DLL_STOP_PLUGIN stop_func = (SNL_DLL_STOP_PLUGIN)dyn_loaded->second->getSymbol("dllStopPlugin");
    stop_func();  // this must call uninstall(), which removes the plugin from the installed list

    if (!DynLibManager::unload(dyn_loaded->second))
      return false;

    dynlibs.erase(dyn_loaded);
  }

  return true;
}

bool
PluginManager::startupAllPlugins()
{
  if (!initialized)
  {
    std::cerr << "PluginManager: Manager not initialized" << std::endl;
    return false;
  }

  for (PluginList::iterator pi = plugins.begin(); pi != plugins.end(); ++pi)
    if (!(*pi)->startup())
      return false;

  return true;
}

bool
PluginManager::shutdownAllPlugins()
{
  if (!initialized)
  {
    std::cerr << "PluginManager: Manager not initialized" << std::endl;
    return false;
  }

  for (PluginList::reverse_iterator pi = plugins.rbegin(); pi != plugins.rend(); ++pi)
    if (!(*pi)->shutdown())
      return false;

  return true;
}

bool
PluginManager::unloadAllPlugins()
{
  if (!initialized)
  {
    std::cerr << "PluginManager: Manager not initialized" << std::endl;
    return false;
  }

  if (!shutdownAllPlugins())
    return false;

  for (DynLibMap::iterator di = dynlibs.begin(); di != dynlibs.end(); ++di)
  {
    SNL_DLL_STOP_PLUGIN stop_func = (SNL_DLL_STOP_PLUGIN)di->second->getSymbol("dllStopPlugin");
    stop_func();  // this must call uninstall(), which removes the plugin from the installed list

    if (!DynLibManager::unload(di->second))
      return false;
  }

  dynlibs.clear();

  // There should be only static libs left now
  for (PluginList::iterator pi = plugins.begin(); pi != plugins.end(); ++pi)
  {
    std::cout << "PluginManager: Uninstalling plugin '" << (*pi)->getName() << '\'' << std::endl;
    if (!(*pi)->uninstall())
      return false;
  }

  plugins.clear();
  return false;
}

bool
PluginManager::install(Plugin * plugin)
{
  if (!initialized)
  {
    std::cerr << "PluginManager: Manager not initialized" << std::endl;
    return false;
  }

  if (!plugin)
  {
    std::cerr << "PluginManager: Cannot install null plugin pointer" << std::endl;
    return false;
  }

  std::cout << "PluginManager: Installing plugin '" << plugin->getName() << '\'' << std::endl;
  plugins.push_back(plugin);
  return plugin->install();
}

bool
PluginManager::uninstall(Plugin * plugin)
{
  if (!initialized)
  {
    std::cerr << "PluginManager: Manager not initialized" << std::endl;
    return false;
  }

  if (!plugin)
    return true;

  std::cout << "PluginManager: Uninstalling plugin '" << plugin->getName() << '\'' << std::endl;
  if (!plugin->uninstall())
    return false;

  for (PluginList::iterator pi = plugins.begin(); pi != plugins.end(); ++pi)
    if (*pi == plugin)
    {
      plugins.erase(pi);
      break;
    }

  return true;
}

} // namespace SNL
