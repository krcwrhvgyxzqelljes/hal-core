# - Config file for the orocos-kdl package
# It defines the following variables
#  orocos_kdl_INCLUDE_DIRS - include directories for Orocos KDL
#  orocos_kdl_LIBRARIES    - libraries to link against for Orocos KDL
#  orocos_kdl_PKGCONFIG_DIR - directory containing the .pc pkgconfig files

# Compute paths
get_filename_component(orocos_kdl_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)

# Find dependencies
find_package(Eigen3 QUIET)
if(NOT EIGEN3_FOUND)
  include(${CMAKE_CURRENT_LIST_DIR}/FindEigen3.cmake)
endif()

set(KDL_USE_NEW_TREE_INTERFACE OFF)
if(KDL_USE_NEW_TREE_INTERFACE)
  find_package(Boost REQUIRED)
endif()

if(NOT TARGET orocos-kdl)
  include("${CMAKE_CURRENT_LIST_DIR}/OrocosKDLTargets.cmake")
endif()

set(orocos_kdl_INCLUDE_DIRS
  ${orocos_kdl_PREFIX}/include
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
)
set(orocos_kdl_LIBRARIES orocos-kdl)

# where the .pc pkgconfig files are installed
set(orocos_kdl_PKGCONFIG_DIR "${orocos_kdl_PREFIX}/lib/pkgconfig")
