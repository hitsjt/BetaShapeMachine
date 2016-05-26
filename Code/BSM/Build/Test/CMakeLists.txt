#===============================================================================================================================
#
# Build script for the SNL tests.
#
# Copyright (C) Siddhartha Chaudhuri, Evangelos Kalogerakis 2013
#
#===============================================================================================================================

PROJECT(SNLTest)

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
SET(OutputRoot ${ProjectRoot}/Build/)

# Path to put executables in
# SET(EXECUTABLE_OUTPUT_PATH ${OutputRoot}/bin)
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
FIND_PACKAGE(Boost COMPONENTS filesystem system REQUIRED)
IF(Boost_FOUND)
	MESSAGE( STATUS "Boost Include DIR: " ${Boost_INCLUDE_DIRS} )	
	MESSAGE( STATUS "BOOST Libraries DIR: " ${Boost_LIBRARY_DIRS} )
ENDIF()

# Dependency: FreeGLUT
IF(EXISTS ${SNL_INSTALLATIONS_ROOT}/installed-freeglut)
  SET(FREEGLUT_ROOT ${SNL_INSTALLATIONS_ROOT}/installed-freeglut)
ELSE()
  SET(FREEGLUT_ROOT ${SNL_INSTALLATIONS_ROOT})
ENDIF()
SET(FREEGLUT_INCLUDE_DIRS ${FREEGLUT_ROOT}/include)
SET(FREEGLUT_LIBRARY_DIRS ${FREEGLUT_ROOT}/lib)
MESSAGE( STATUS "FreeGLUT Include DIR: " ${FREEGLUT_INCLUDE_DIRS} )	
MESSAGE( STATUS "FreeGLUT Libraries DIR: " ${FREEGLUT_LIBRARY_DIRS} )

# Definitions, compiler switches etc.
IF(CMAKE_COMPILER_IS_GNUCXX)

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-strict-aliasing -fopenmp")
  SET(CMAKE_CXX_FLAGS_DEBUG "-g2 -fopenmp")
  SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -fopenmp")
  SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-DNDEBUG -g2 -O2 -fopenmp")

  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fno-strict-aliasing -fopenmp")
  SET(CMAKE_C_FLAGS_DEBUG "-g2 -fopenmp")
  SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O3 -fopenmp")
  SET(CMAKE_C_FLAGS_RELWITHDEBINFO "-DNDEBUG -g2 -O2 -fopenmp")

ELSEIF(MSVC)
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox /W1")
  SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:1073741824 ")  
ENDIF()

# Shared library flags
ADD_DEFINITIONS(-DSNL_DLL -DSNL_DLL_IMPORTS)

# Include directories
INCLUDE_DIRECTORIES(BEFORE
                    ${SourceRoot}
					${Boost_INCLUDE_DIRS}
					${FREEGLUT_INCLUDE_DIRS}
					)
					

# Link directories
LINK_DIRECTORIES(${OutputRoot}/lib
				${Boost_LIBRARY_DIRS}
				${FREEGLUT_LIBRARY_DIRS}				
				)

#===========================================================
# TestS**
#===========================================================

# Source file lists
SET(SNLTestSources 
	${SourceRoot}/Test/TestDL13.cpp
#	${SourceRoot}/Test/TestS12.cpp
	${SourceRoot}/Test/testPCA.cpp
	${SourceRoot}/Test/TestSNL.cpp
	${SourceRoot}/Test/Render.cpp
	${SourceRoot}/Test/GLCamera.cpp	
	${SourceRoot}/Test/AlignModel.cpp
	)

# Libraries to link to
SET(SNLTestLibraries
      SNL
#      SNLPluginS12
	  SNLPluginDL13
	  SNLPluginPCA
	  ${Boost_LIBRARIES}
      ${G3D_LIBRARIES}
      ${PLATFORM_LIBRARIES}	  
	  )

# Build products
ADD_EXECUTABLE(SNLTest ${SNLTestSources})

# Additional libraries to be linked
TARGET_LINK_LIBRARIES(SNLTest ${SNLTestLibraries})

# Fix library install names on OS X
IF(APPLE)
  INCLUDE(${CMAKE_MODULE_PATH}/OSXFixDylibReferences.cmake)
  OSX_FIX_DYLIB_REFERENCES(SNLTest "${SNLTestLibraries}")
ENDIF()
