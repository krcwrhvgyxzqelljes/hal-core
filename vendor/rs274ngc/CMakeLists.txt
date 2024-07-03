cmake_minimum_required(VERSION 3.5)
set(PROJECT "rs274ngc")
project(${PROJECT} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set variables.
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Set includepaths for header files etc.
include_directories(${SRC_DIR})


add_library(${PROJECT} SHARED
  rs274ngc_intf.cpp
  rs274ngc_intf.h
  canon.hh
  canon_pre.cc
  driver.cc
  rs274ngc.hh
  rs274ngc_errors.h
  rs274ngc_pre.cc
  rs274ngc_return.hh
)

target_compile_definitions(${PROJECT} PRIVATE RS274NGC_LIBRARY)

# Link.
target_link_libraries(${PROJECT_NAME} PRIVATE

)

# Make install
install(TARGETS ${PROJECT} DESTINATION ${BUILD_DIR}/../../../bin)
