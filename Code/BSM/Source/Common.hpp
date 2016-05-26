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
