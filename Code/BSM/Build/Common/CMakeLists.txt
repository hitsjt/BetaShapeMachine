#===============================================================================================================================
#
# Build script for the SNL library.
#
# Copyright (C) Siddhartha Chaudhuri, 2012
#
#===============================================================================================================================

PROJECT(SNLv2)

# Set the minimum required CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# See cmake --help-policy CMP0003 for details on this one
IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

# If you don't want the full compiler output, remove the following line
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Avoid having to repeat condition after ELSE and ENDIF statements
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)

# Postfix for debug builds
SET(CMAKE_DEBUG_POSTFIX "d")

# Project root path
GET_FILENAME_COMPONENT(ProjectRoot ../.. ABSOLUTE)

# Path for build products
SET(OutputRoot ${ProjectRoot}/Build)

# Path to put executables in
#SET(EXECUTABLE_OUTPUT_PATH ${OutputRoot}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${OutputRoot})

# Path to put libraries in
#SET(LIBRARY_OUTPUT_PATH ${OutputRoot}/lib)
SET(LIBRARY_OUTPUT_PATH ${OutputRoot})

# Path for customized CMake modules
IF(NOT CMAKE_MODULE_PATH)
  SET(CMAKE_MODULE_PATH ${ProjectRoot}/Build/Common/CMake/Modules)
ENDIF()
GET_FILENAME_COMPONENT(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ABSOLUTE)

# Path to root folder for source code
SET(SourceRoot ${ProjectRoot}/Source)

# Platform libraries
IF(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  IF(NOT WIN32)
    SET(PLATFORM_LIBRARIES dl)
  ENDIF()
ENDIF()

# Path to folder with installations of the dependencies
IF(NOT SNL_INSTALLATIONS_ROOT)
  SET(SNL_INSTALLATIONS_ROOT ${CMAKE_INSTALL_PREFIX})
ENDIF()
SET(SNL_INSTALLATIONS_ROOT ${SNL_INSTALLATIONS_ROOT} CACHE PATH "Path to folder with installations of dependencies")

# Dependency: Boost
SET(Boost_USE_STATIC_LIBS      ON)
SET(Boost_USE_MULTITHREADED    ON)
SET(Boost_USE_STATIC_RUNTIME   OFF)
INCLUDE(BoostAdditionalVersions)
IF(EXISTS ${SNL_INSTALLATIONS_ROOT}/installed-boost)
  SET(BOOST_ROOT ${SNL_INSTALLATIONS_ROOT}/installed-boost)
ELSE()
  SET(BOOST_ROOT ${SNL_INSTALLATIONS_ROOT})
ENDIF()
FIND_PACKAGE(Boost COMPONENTS filesystem serialization REQUIRED)
IF(Boost_FOUND)
	MESSAGE( STATUS "Boost Include DIR: " ${Boost_INCLUDE_DIRS} )	
	MESSAGE( STATUS "BOOST Libraries DIR: " ${Boost_LIBRARY_DIRS} )
ENDIF()

# Definitions, compiler switches etc.
IF(CMAKE_COMPILER_IS_GNUCXX)

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-strict-aliasing")
  SET(CMAKE_CXX_FLAGS_DEBUG "-g2")
  SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-DNDEBUG -g2 -O2")

  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fno-strict-aliasing")
  SET(CMAKE_C_FLAGS_DEBUG "-g2")
  SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O3")
  SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-DNDEBUG -g2 -O2")

ELSEIF(MSVC)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /openmp /MP")
ENDIF()

# Shared library flags
ADD_DEFINITIONS(-DSNL_DLL -DSNL_DLL_EXPORTS)

# Include directories
INCLUDE_DIRECTORIES(BEFORE
                    ${Boost_INCLUDE_DIRS})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})					


# Source file lists
FILE(GLOB SNLSources ${SourceRoot}/*.cpp)

# Libraries to link to
SET(SNLLibraries 
	${PLATFORM_LIBRARIES}
	${Boost_LIBRARIES}
	)

# Build products
ADD_LIBRARY(SNL SHARED ${SNLSources})

# Additional libraries to be linked
TARGET_LINK_LIBRARIES(SNL ${SNLLibraries})

# Fix library install names on OS X
IF(APPLE)
  INCLUDE(${CMAKE_MODULE_PATH}/OSXFixDylibReferences.cmake)
  OSX_FIX_DYLIB_REFERENCES(SNL "${SNLLibraries}")
ENDIF()

# Write a file containing build flags to be used by a calling application
SET(SNL_BUILD_FLAGS )
IF(SNL_EXTERN_TEMPLATES)
  SET(SNL_BUILD_FLAGS "${SNL_BUILD_FLAGS} -DSNL_EXTERN_TEMPLATES")
ENDIF(SNL_EXTERN_TEMPLATES)
FILE(WRITE "${SourceRoot}/BuildFlags.txt" "${SNL_BUILD_FLAGS}\n")

# Install rules
SET_TARGET_PROPERTIES(SNL PROPERTIES
                          INSTALL_RPATH_USE_LINK_PATH TRUE
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")

SET(UseFilesMatching FALSE)
IF(${CMAKE_MAJOR_VERSION} GREATER 2)
  SET(UseFilesMatching TRUE)
ELSEIF(${CMAKE_MAJOR_VERSION} EQUAL 2)
  IF(${CMAKE_MINOR_VERSION} GREATER 4)
    SET(UseFilesMatching TRUE)
  ENDIF()
ENDIF()

INSTALL(TARGETS SNL DESTINATION lib)
IF(UseFilesMatching)  # CMake 2.6 and above
  INSTALL(DIRECTORY ${SourceRoot}/ DESTINATION include/SNL
          FILES_MATCHING
          REGEX "Test$" EXCLUDE
          # REGEX "Plugins$" EXCLUDE
          REGEX "Tools$" EXCLUDE
          PATTERN "CVS" EXCLUDE
          PATTERN ".svn" EXCLUDE
          PATTERN "*.hpp"
          PATTERN "*.h"
          PATTERN "BuildFlags.txt")
ELSE()
  # Bit flakier method, since we can't install only the files matching a pattern
  INSTALL(DIRECTORY ${SourceRoot}/ DESTINATION include/SNL
          REGEX "Test$" EXCLUDE
          # REGEX "Plugins$" EXCLUDE
          REGEX "Tools$" EXCLUDE
          PATTERN "CVS" EXCLUDE
          PATTERN ".svn" EXCLUDE
          PATTERN "*.cpp" EXCLUDE
          PATTERN "*.c" EXCLUDE)
ENDIF()
