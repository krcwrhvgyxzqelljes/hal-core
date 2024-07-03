cmake_minimum_required(VERSION 3.5)
set(PROJECT "code_parser") # The name of the file excluding .c or .h
project(${PROJECT} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set variables.
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Set includepaths for header files etc.
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/../../vendor/std_functions)

add_executable(${PROJECT}
    main.cpp
    ${SRC_DIR}/functions.h
    ${SRC_DIR}/../../vendor/std_functions/std_functions.h
    ${SRC_DIR}/../../vendor/std_functions/std_functions.cpp
)

# Copy functions.h to build directory
configure_file(functions.h ${PROJECT_BINARY_DIR}/functions.h COPYONLY)

# Make install
install(TARGETS ${PROJECT} DESTINATION ${BUILD_DIR}/../../../bin)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/functions.h DESTINATION ${BUILD_DIR}/../../../bin)
