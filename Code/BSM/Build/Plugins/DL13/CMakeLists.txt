#===============================================================================================================================
#
# Build script for the SNL DL13 plugin.
#
# Copyright (C) Siddhartha Chaudhuri, 2012
#
#===============================================================================================================================

PROJECT(SNLPluginDL13)

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
GET_FILENAME_COMPONENT(ProjectRoot ../../.. ABSOLUTE)

# Path for build products
SET(OutputRoot ${ProjectRoot}/Build/)

# Path to put executables in
#SET(EXECUTABLE_OUTPUT_PATH ${OutputRoot}/bin)
SET(EXECUTABLE_OUTPUT_PATH ${OutputRoot})

# Path to put libraries in
# SET(LIBRARY_OUTPUT_PATH ${OutputRoot}/lib)
SET(LIBRARY_OUTPUT_PATH ${OutputRoot})

# Path for customized CMake modules
IF(NOT CMAKE_MODULE_PATH)
  SET(CMAKE_MODULE_PATH ${ProjectRoot}/Build/Common/CMake/Modules)
ENDIF()
GET_FILENAME_COMPONENT(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ABSOLUTE)

# Path to root folder for source code
SET(SourceRoot ${ProjectRoot}/Source)

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
FIND_PACKAGE(Boost COMPONENTS filesystem serialization exception REQUIRED)
IF(Boost_FOUND)
	MESSAGE( STATUS "Boost Include DIR: " ${Boost_INCLUDE_DIRS} )	
	MESSAGE( STATUS "BOOST Libraries DIR: " ${Boost_LIBRARY_DIRS} )
ENDIF()
	
# Dependency: CLAPACK
# IF(EXISTS ${SNL_INSTALLATIONS_ROOT}/installed-clapack)
  # SET(CLAPACK_ROOT ${SNL_INSTALLATIONS_ROOT}/installed-clapack)
# ELSE()
  # SET(CLAPACK_ROOT ${SNL_INSTALLATIONS_ROOT})
# ENDIF()
# FIND_PACKAGE(CLAPACK REQUIRED)

# Definitions, compiler switches etc.
IF(CMAKE_COMPILER_IS_GNUCXX)

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-strict-aliasing -fopenmp -std=c++11")
  SET(CMAKE_CXX_FLAGS_DEBUG "-g2 -fopenmp -std=c++11")
  SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -fopenmp -std=c++11")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-DNDEBUG -g2 -O2 -fopenmp -std=c++11")

  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fno-strict-aliasing -fopenmp")
  SET(CMAKE_C_FLAGS_DEBUG "-g2 -fopenmp")
  SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O3 -fopenmp")
  SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-DNDEBUG -g2 -O2 -fopenmp")

ELSEIF(MSVC)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /openmp /MP /W1 /EHsc")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc")
ENDIF()

# Shared library flags
ADD_DEFINITIONS(-DSNL_DL13_DLL -DSNL_DL13_DLL_EXPORTS)
ADD_DEFINITIONS(-DSNL_DLL -DSNL_DLL_IMPORTS)

# Include directories
INCLUDE_DIRECTORIES(BEFORE
#                    ${CLAPACK_INCLUDE_DIRS}
                    ${Boost_INCLUDE_DIRS})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})					

# Source file lists
FILE(GLOB SNLPluginDL13Sources
     ${SourceRoot}/Plugins/DL13/*.cpp
	 ${SourceRoot}/Plugins/DL13/SidKDTree/Util.cpp
	 )

# Libraries to link to
SET(SNLPluginDL13Libraries
    SNL
    ${Boost_LIBRARIES}
#    ${CLAPACK_LIBRARIES}
#    ${PLATFORM_LIBRARIES}
)

# Build products
ADD_LIBRARY(SNLPluginDL13 SHARED ${SNLPluginDL13Sources})

# Additional libraries to be linked
TARGET_LINK_LIBRARIES(SNLPluginDL13 ${SNLPluginDL13Libraries})

# Fix library install names on OS X
IF(APPLE)
  INCLUDE(${CMAKE_MODULE_PATH}/OSXFixDylibReferences.cmake)
  OSX_FIX_DYLIB_REFERENCES(SNLPluginDL13 "${SNLPluginDL13Libraries}")
ENDIF()

# Install rules
SET_TARGET_PROPERTIES(SNLPluginDL13
                        PROPERTIES
                          INSTALL_RPATH_USE_LINK_PATH TRUE
                          INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")

INSTALL(TARGETS SNLPluginDL13 DESTINATION lib)
