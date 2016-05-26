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

#ifndef __SNL_Common_hpp__
#define __SNL_Common_hpp__

#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

#define WIN32_LEAN_AND_MEAN

#if !defined(SNL_DEBUG_BUILD) && defined(_DEBUG)
#  define SNL_DEBUG_BUILD
#endif

// NDEBUG needed for assert to be deactivated on release builds
#if !defined(SNL_DEBUG_BUILD) && !defined(NDEBUG)
#  define NDEBUG
#endif

#ifdef _MSC_VER
#  define SNL_WINDOWS 1
   // NOMINMAX required to stop windows.h messing up std::min
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif

   // Disable pesky warnings of the type: "class <member-classname> needs to have dll-interface to be used by clients of class"
   // and "non dll-interface class <subclass> used as base for dll-interface class <superclass>."
#  pragma warning( disable: 4251 )
#  pragma warning( disable: 4275 )

#elif defined(__FreeBSD__)
#  define SNL_FREEBSD 1
#elif defined(__OpenBSD__)
#  define SNL_OPENBSD 1
#elif defined(__linux__)
#  define SNL_LINUX 1
#elif defined(__APPLE__)
#  define SNL_OSX 1
   // Prevent OS X fp.h header from being included; it defines pi as a constant, which creates a conflict with G3D
#  define __FP__
#else
#  error Unknown platform
#endif

#if defined(SNL_FREEBSD) || defined(SNL_OPENBSD)
#  define SNL_BSD 1
#endif

// Shared library support. See http://gcc.gnu.org/wiki/Visibility . Quoting loosely from that page, and assuming M is a library-
// specific prefix:
//
// - If M_DLL and M_DLL_EXPORTS are defined, we are building our library as a DLL and symbols should be exported. Something
//   ending with _EXPORTS is defined by MSVC by default in all projects.
//
// - If M_DLL_EXPORTS is not defined, we are importing our library and symbols should be imported.
//
// - If we're building with GCC and __GNUC__ >= 4 , then GCC supports the new features.
//
// - For every non-templated non-static function definition in your library (both headers and source files), decide if it is
//   publicly used or internally used:
//
//     - If it is publicly used, mark with M_API like this: extern M_API PublicFunc()
//
//     - If it is only internally used, mark with M_DLL_LOCAL like this: extern M_DLL_LOCAL PublicFunc(). Remember, static
//       functions need no demarcation, nor does anything which is templated.
//
// - For every non-templated class definition in your library (both headers and source files), decide if it is publicly used or
//   internally used:
//
//     - If it is publicly used, mark with M_API like this: class M_API PublicClass
//
//     - If it is only internally used, mark with M_DLL_LOCAL like this: class M_DLL_LOCAL PublicClass
//
// - Individual member functions of an exported class that are not part of the interface, in particular ones which are private,
//   and are not used by friend code, should be marked individually with M_DLL_LOCAL.
//
// - Remember to test your library thoroughly afterwards, including that all exceptions correctly traverse shared object
//   boundaries.
//
#ifdef _MSC_VER  // should be WIN32?
#    define SNL_IMPORT  __declspec(dllimport)
#    define SNL_EXPORT  __declspec(dllexport)
#    define SNL_DLL_LOCAL
#    define SNL_DLL_PUBLIC
#else
#    if (defined __GNUC__ && __GNUC__ >= 4)
#        define SNL_IMPORT      __attribute__ ((visibility("default")))
#        define SNL_EXPORT      __attribute__ ((visibility("default")))
#        define SNL_DLL_LOCAL   __attribute__ ((visibility("hidden")))
#        define SNL_DLL_PUBLIC  __attribute__ ((visibility("default")))
#    else
#        define SNL_IMPORT
#        define SNL_EXPORT
#        define SNL_DLL_LOCAL
#        define SNL_DLL_PUBLIC
#    endif
#endif

// Build flags for the DLL (if any).
#ifdef SNL_DLL
#    ifdef SNL_DLL_EXPORTS
#        define SNL_API  SNL_EXPORT
#    else
#        define SNL_API  SNL_IMPORT
#    endif
#else
#    define SNL_API
#endif

namespace SNL {

/** Convert a string to lowercase. */
SNL_DLL_LOCAL std::string toLower(std::string s);

} // namespace SNL

#endif
