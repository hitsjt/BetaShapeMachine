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
#ifndef __SNL_Plugin_hpp__
#define __SNL_Plugin_hpp__

#include "Common.hpp"
#include <list>
#include <map>

namespace SNL {

/** The interface for a plugin that may be statically or dynamically loaded. */
class SNL_API Plugin
{
  public:
    /** Constructor. */
    Plugin(std::string const & name_ = "AnonymousPlugin") : name(name_) {}

    /** Destructor. */
    virtual ~Plugin() {}

    /** Get the name of the plugin. */
    std::string const & getName() const { return name; }

    /**
     * Installation routine for the plugin. This is called when the plugin is first registered with the plugin manager, and
     * executes initialization tasks that depend only on core functionality and not on the availability of other plugins.
     *
     * @see uninstall()
     */
    virtual bool install() = 0;

    /**
     * Startup routine for the plugin. This function assumes all dependencies have been loaded and can hence interact with
     * other plugins. If called multiple times without an intervening shutdown(), the second and subsequent calls should have
     * no effect.
     *
     * @see startup()
     */
    virtual bool startup() = 0;

    /**
     * Shutdown routine for the plugin. This function assumes all dependencies are still loaded and can hence interact with
     * other plugins. If called multiple times without an intervening startup(), the second and subsequent calls should have no
     * effect.
     *
     * @see shutdown()
     */
    virtual bool shutdown() = 0;

    /**
     * Uninstallation routine for the plugin. This is called when the plugin is removed from the plugin manager, and executes
     * cleanup tasks that depend only on core functionality and not on the availability of other plugins.
     *
     * @see install()
     */
    virtual bool uninstall() = 0;

  private:
    std::string name;

}; // class Plugin

// Forward declaration
class DynLib;

/** Manages set of installed plugins (static or dynamic). */
class SNL_API PluginManager
{
  public:
    /**
     * Initialization routine. You must call this at the beginning of the program if you want to use any plugins. It's safe to
     * call this function multiple times -- a second or later call will be ignored unless it was immediately preceded by
     * finish().
     *
     * Once you call init(), you must call finish() at the end of your program to properly clean up.
     *
     * @see finish()
     */
    static bool init();

    /**
     * Termination routine. You must call this at the end of the program after using any plugins. It's safe to call this
     * function multiple times -- a second or later call will be ignored unless it was immediately preceded by init(). It's also
     * safe to call this function without ever having called init() first.
     *
     * @see init()
     */
    static bool finish();

    /**
     * Load a dynamically linked plugin from a path. The plugin's \link Plugin::install() install() \endlink function will be
     * automatically called.
     *
     * @return A pointer to the new plugin on success, NULL on failure or if the plugin has already been loaded.
     *
     * @see unload()
     */
    static Plugin * load(std::string const & path);

    /**
     * Unload a dynamically linked plugin, using the same path specified to load() it. The plugin's \link Plugin::uninstall()
     * uninstall() \endlink function will be automatically called.
     *
     * \warning This does <b>not</b> call the plugin's \link Plugin::shutdown() shutdown() \endlink routine, so be sure to call
     * it explicitly before calling this function.
     *
     * @see load()
     */
    static bool unload(std::string const & path);

    /**
     * Execute the \link Plugin::startup() startup() \endlink routine of all plugins, in the order in which they were installed.
     */
    static bool startupAllPlugins();

    /**
     * Execute the \link Plugin::shutdown() shutdown() \endlink routine of all plugins, in the reverse of the order in which
     * they were installed.
     */
    static bool shutdownAllPlugins();

    /**
     * Unload/uninstall plugins. This will initially call shutdownAllPlugins(), so if you want to shutdown the plugins in an
     * order other than the reverse of the installation order, you should do it manually before calling this function.
     */
    static bool unloadAllPlugins();

    /**
     * This function should be called by <code>dllStartPlugin()</code> to register the plugin. It may also be used to install
     * statically linked plugins.
     *
     * @param plugin A pointer to the plugin to be installed, which should not be null.
     *
     * @return True on success, false on failure.
     *
     * @see uninstall()
     */
    static bool install(Plugin * plugin);

    /**
     * This function should be called by <code>dllStopPlugin()</code> to register the plugin. It may also be used to uninstall
     * statically linked plugins.
     *
     * @param plugin A pointer to the plugin to be uninstalled.
     *
     * @see install()
     */
    static bool uninstall(Plugin * plugin);

  private:
    typedef std::map<std::string, DynLib *>  DynLibMap;   ///< Maps paths to the corresponding dynamic libraries.
    typedef std::list<Plugin *>              PluginList;  ///< List of plugins.

    static bool        initialized;  ///< Has the manager been initialized?
    static DynLibMap   dynlibs;      ///< Set of dynamically loaded libraries.
    static PluginList  plugins;      ///< Set of installed plugins.

}; // class PluginManager

} // namespace SNL

#endif
