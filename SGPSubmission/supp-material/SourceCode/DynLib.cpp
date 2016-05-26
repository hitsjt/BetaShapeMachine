/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2009 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#include "DynLib.hpp"
#include <cassert>
#include <iostream>

#ifdef SNL_WINDOWS
#  ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#  endif

#  if !defined(NOMINMAX) && defined(_MSC_VER)
#    define NOMINMAX  // required to stop windows.h messing up std::min
#  endif

#  include <windows.h>
#else
#  include <dlfcn.h>
#endif

#ifdef SNL_WINDOWS
#  define SNL_DYNLIB_LOAD( a )       LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#  define SNL_DYNLIB_GETSYM( a, b )  GetProcAddress( a, b )
#  define SNL_DYNLIB_UNLOAD( a )     !FreeLibrary( a )
#else
#  define SNL_DYNLIB_LOAD( a )       dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#  define SNL_DYNLIB_GETSYM( a, b )  dlsym( a, b )
#  define SNL_DYNLIB_UNLOAD( a )     dlclose( a )
#endif

namespace SNL {

// Static variables
DynLibManager::DynLibMap DynLibManager::libs;

static std::string
DynLib_addExtension(std::string const & name)
{
#if defined(SNL_WINDOWS)
  // Although LoadLibraryEx will add .dll itself when you only specify the library name, if you include a relative path then it
  // does not. So, add it to be sure.
  if (toLower(name.substr(name.length() - 4, 4)) != ".dll")
    return name + ".dll";
#elif defined(SNL_OSX)
  // dlopen() does not add .dylib to the filename, like windows does for .dll
  if (toLower(name.substr(name.length() - 6, 6)) != ".dylib")
    return name + ".dylib";
#else
  // dlopen() does not add .so to the filename, like windows does for .dll
  if (name.substr(name.length() - 3, 3) != ".so")  // assume case-sensitive
     return name + ".so";
#endif

  return name;
}

DynLib::DynLib(std::string const & name_)
: name(name_), h_inst(NULL), ref_count(0)
{}

DynLib::~DynLib()
{
  unload();
}

bool
DynLib::load()
{
  if (h_inst)
  {
    addRef();
    return true;
  }

  std::string ext_name = DynLib_addExtension(getName());
  std::cout << "Loading library '" << getName() << '\'' << std::endl;

  h_inst = (SNL_DYNLIB_HANDLE)SNL_DYNLIB_LOAD(ext_name.c_str());

  if (!h_inst)
  {
    std::cerr << "Could not load dynamic library '" << ext_name << "' (" << dynlibError() << ')' << std::endl;
    return false;
  }

  ref_count = 1;
  return true;
}

bool
DynLib::unload()
{
  if (!h_inst) return true;

  std::cout << "Unloading library '" << getName() << '\'' << std::endl;

  if (SNL_DYNLIB_UNLOAD(h_inst))
  {
    std::cerr << "Could not unload dynamic library '" << getName() << "' (" << dynlibError() << ')' << std::endl;
    return false;
  }

  h_inst = NULL;
  ref_count = 0;
  return true;
}

void
DynLib::addRef()
{
  ref_count++;
}

void
DynLib::releaseRef()
{
  assert(ref_count > 0);

  ref_count--;

  if (ref_count <= 0)
    unload();
}

long
DynLib::getRefCount() const
{
  return ref_count;
}

void *
DynLib::getSymbol(std::string const & sym_name) const
{
  if (h_inst)
    return (void *)SNL_DYNLIB_GETSYM(h_inst, sym_name.c_str());
  else
    return NULL;
}

std::string
DynLib::dynlibError() const
{
#if defined(SNL_WINDOWS)
  LPVOID lpMsgBuf;
  FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&lpMsgBuf,
                0,
                NULL);

  std::string ret = (char *)lpMsgBuf;
  LocalFree(lpMsgBuf);  // free the buffer.
  return ret;
#else
  return dlerror();
#endif
}

void
DynLibManager::init()
{}

void
DynLibManager::finish()
{
  // Unload & delete resources in turn
  for (DynLibMap::iterator li = libs.begin(); li != libs.end(); ++li)
    delete li->second;

  // Empty the list
  libs.clear();
}

DynLib *
DynLibManager::load(std::string const & path)
{
  DynLibMap::iterator loaded = libs.find(path);
  if (loaded != libs.end())
  {
    loaded->second->addRef();
    return loaded->second;
  }
  else
  {
    DynLib * lib = new DynLib(path);
    if (!lib->load())
    {
      delete lib;
      return NULL;
    }

    libs[path] = lib;
    return lib;
  }
}

bool
DynLibManager::unload(DynLib * lib)
{
  if (!lib || lib->getRefCount() <= 0) return true;

  lib->releaseRef();

  if (lib->getRefCount() <= 0)  // time to completely unload the lib
  {
    DynLibMap::iterator loaded = libs.find(lib->getName());
    if (loaded != libs.end())
    {
      if (loaded->second != lib)
      {
        std::cerr << "DynLibManager: A different library was loaded with the same name (" << lib->getName() << ')' << std::endl;
        return false;
      }

      libs.erase(loaded);
    }

    delete lib;
  }

  return true;
}

} // namespace SNL
