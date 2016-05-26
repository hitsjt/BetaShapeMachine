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


#ifndef __SNL_DynLib_hpp__
#define __SNL_DynLib_hpp__

#include "Common.hpp"
#include <map>
#include <string>

#ifdef SNL_WINDOWS
   struct HINSTANCE__;
   typedef struct HINSTANCE__ * hInstance;
#  define SNL_DYNLIB_HANDLE hInstance
#else
#  define SNL_DYNLIB_HANDLE void *
#endif

namespace SNL {

/** A dynamically loaded library. */
class SNL_API DynLib
{
  public:
    /**
     * Returns the address of the given symbol from the loaded library.
     *
     * @param sym_name The name of the symbol to search for
     *
     * @return A handle to the symbol on success, NULL on failure.
     */
    void * getSymbol(std::string const & sym_name) const;

  private:
    friend class DynLibManager;

    /** Constructor. */
    DynLib(std::string const & name_);

    /** Destructor. */
    ~DynLib();

    /** Get the name of the plugin. */
    std::string const & getName() const { return name; }

    /** Load the library. */
    bool load();

    /** Unload the library. */
    bool unload();

    /** Record a reference to the library. */
    void addRef();

    /** Release a reference to the library. */
    void releaseRef();

    /** Get the number of references to the library. */
    long getRefCount() const;

    /** Get any library error. */
    std::string dynlibError() const;

    std::string name;          ///< The name of the library.
    SNL_DYNLIB_HANDLE h_inst;  ///< Handle to the loaded library.
    long ref_count;            ///< Number of clients using the library.

}; // class DynLib

/**
 * Manager for dynamically loaded libraries. Keeps track of all open libraries, opens libraries as needed and returns
 * references to already-open libraries.
 */
class SNL_API DynLibManager
{
  public:
    /** Initialization routine. */
    static void init();

    /** Termination routine. */
    static void finish();

    /**
     * Loads a library, if it has not been loaded yet. If it has already been loaded, this function increments its reference
     * count.
     *
     * @param path The path to the library. The extension can be omitted.
     *
     * @return A handle to the opened library.
     *
     * @see unload()
     */
    static DynLib * load(std::string const & path);

    /**
     * Unloads a library. This function decrements the reference count of the library. The library will be actually unlinked
     * when there are no more references to it.
     *
     * @param lib The library to be unloaded.
     *
     * @see load()
     */
    static bool unload(DynLib * lib);

  private:
    typedef std::map<std::string, DynLib *> DynLibMap;  ///< Maps paths to the corresponding library objects.

    static DynLibMap libs;  ///< Set of loaded libraries.

}; // class DynLibManager

} // namespace SNL

#endif
