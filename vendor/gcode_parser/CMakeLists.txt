cmake_minimum_required(VERSION 3.5)
set(PROJECT "gcode_parser") # The name of the file excluding .c or .h
project(${PROJECT} C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set variables.
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Set includepaths for header files etc.
include_directories(${SRC_DIR})
include_directories(${SRC_DIR}/../../vendor/std_functions)

add_library(${PROJECT} SHARED
    ${SRC_DIR}/gcode_parser.cpp
    ${SRC_DIR}/gcode_parser.h
    ${SRC_DIR}/../../vendor/std_functions/std_functions.h
    ${SRC_DIR}/../../vendor/std_functions/std_functions.cpp
)

target_link_libraries(${PROJECT} PRIVATE )

target_compile_definitions(${PROJECT} PRIVATE GCODE_PARSER_LIBRARY)

# Make install
install(TARGETS ${PROJECT} DESTINATION ${BUILD_DIR}/../../../lib)
install(FILES ${SRC_DIR}/gcode_parser.h DESTINATION ${BUILD_DIR}/../../../include)
