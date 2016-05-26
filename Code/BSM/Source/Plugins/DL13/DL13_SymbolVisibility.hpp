#ifndef __SNL_DL13_SymbolVisibility_hpp__
#define __SNL_DL13_SymbolVisibility_hpp__

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
#    define SNL_DL13_IMPORT  __declspec(dllimport)
#    define SNL_DL13_EXPORT  __declspec(dllexport)
#    define SNL_DL13_DLL_LOCAL
#    define SNL_DL13_DLL_PUBLIC
#else
#    if (defined __GNUC__ && __GNUC__ >= 4)
#        define SNL_DL13_IMPORT      __attribute__ ((visibility("default")))
#        define SNL_DL13_EXPORT      __attribute__ ((visibility("default")))
#        define SNL_DL13_DLL_LOCAL   __attribute__ ((visibility("hidden")))
#        define SNL_DL13_DLL_PUBLIC  __attribute__ ((visibility("default")))
#    else
#        define SNL_DL13_IMPORT
#        define SNL_DL13_EXPORT
#        define SNL_DL13_DLL_LOCAL
#        define SNL_DL13_DLL_PUBLIC
#    endif
#endif

// Build flags for the SNL DL13 plugin (if any).
#ifdef SNL_DL13_DLL
#    ifdef SNL_DL13_DLL_EXPORTS
#        define SNL_DL13_API  SNL_DL13_EXPORT
#    else
#        define SNL_DL13_API  SNL_DL13_IMPORT
#    endif
#else
#    define SNL_DL13_API
#endif

#endif
