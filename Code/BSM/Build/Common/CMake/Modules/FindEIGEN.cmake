# Searches for an installation of the EIGEN library. On success, it sets the following variables:
#
#   EIGEN_FOUND         Set to true to indicate the library was found
#   EIGEN_INCLUDE_DIRS  Directories containing EIGEN header files
#
# To specify an additional directory to search, set EIGEN_ROOT.
#
# Author: Siddhartha Chaudhuri, Evangelos Kalogerakis, 2013
#

# Look for the header, first in the user-specified location and then in the system locations
SET(EIGEN_INCLUDE_DOC "The directory containing the header file EIGEN.h")
FIND_PATH(EIGEN_INCLUDE_DIRS NAMES Eigen PATHS ${EIGEN_ROOT} ${EIGEN_ROOT}/include DOC ${EIGEN_INCLUDE_DOC}
          NO_DEFAULT_PATH)
IF(NOT EIGEN_INCLUDE_DIRS)  # now look in system locations
  FIND_PATH(EIGEN_INCLUDE_DIRS NAMES Eigen DOC ${EIGEN_INCLUDE_DOC})
ENDIF(NOT EIGEN_INCLUDE_DIRS)

IF(NOT EIGEN_INCLUDE_DIRS)
	SET(EIGEN_FOUND FALSE)
ELSE(EIGEN_INCLUDE_DIRS)
	SET(EIGEN_FOUND TRUE)
ENDIF(NOT EIGEN_INCLUDE_DIRS)

IF(EIGEN_FOUND)
  IF(NOT EIGEN_FIND_QUIETLY)
    MESSAGE(STATUS "Found EIGEN: headers at ${EIGEN_INCLUDE_DIRS}, libraries NOT NEEDED")
  ENDIF(NOT EIGEN_FIND_QUIETLY)
ELSE(EIGEN_FOUND)
  IF(EIGEN_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "EIGEN not found")
  ENDIF(EIGEN_FIND_REQUIRED)
ENDIF(EIGEN_FOUND)
