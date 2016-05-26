//============================================================================
//
// This file is part of the SNL project.
//
// This software is covered by the following BSD license, except for portions
// derived from other works which are covered by their respective licenses.
// For full licensing information including reproduction of these external
// licenses, see the file LICENSE.txt provided in the documentation.
//
// Copyright (c) 2012, Stanford University
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holders nor the names of contributors
// to this software may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
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
