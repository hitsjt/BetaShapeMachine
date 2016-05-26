#===============================================================================================================================
#
# Build script for the SNLv2 library.
#
# Copyright (C) Siddhartha Chaudhuri, Evangelos Kalogerakis 2013
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

# If the build type has not been set, force it to be release mode
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release")
ENDIF()

# Subdirectories containing individual build targets
ADD_SUBDIRECTORY(Common)
#ADD_SUBDIRECTORY(Plugins/S12)
ADD_SUBDIRECTORY(Plugins/DL13)
ADD_SUBDIRECTORY(Plugins/PCA)
ADD_SUBDIRECTORY(Test)
# ADD_SUBDIRECTORY(Test EXCLUDE_FROM_ALL) 
