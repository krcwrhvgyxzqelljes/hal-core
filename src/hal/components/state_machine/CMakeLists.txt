cmake_minimum_required(VERSION 3.0)
# Component name.
set(PROJECT "state_machine") # The name of the file excluding .c or .h
set(RTLINK "halcore") # Link to halcore or for Lcnc use linuxcnchal
project(${PROJECT} C ASM) # Asm is optional.

set(CMAKE_CXX_STANDARD 20)

# Set variables.
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(RTAPI_DIR "${SRC_DIR}/../../../rtapi")
set(HAL_DIR "${SRC_DIR}/../../../hal")
set(LIB_DIR "${SRC_DIR}/../../../../lib")
set(RT_DIR "${SRC_DIR}/../../../../rtlib")
# If user decides to create a build dir use the path.
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Set includepaths for header files etc.
include_directories(${SRC_DIR})
include_directories(${RTAPI_DIR})
include_directories(${HAL_DIR})
include_directories(${LIB_DIR})

include_directories(${SRC_DIR}/../../../../vendor/gcode_parser)
include_directories(${SRC_DIR}/../../../../vendor/std_functions)
include_directories(${SRC_DIR}/../../../../vendor/shmem_functions)
include_directories(${SRC_DIR}/../../../../vendor/oce-upstream-V7_5_0beta/build/include/opencascade)
include_directories(${SRC_DIR}/../../../../vendor/scurve/scurve_engine)
include_directories(${SRC_DIR}/../../../../vendor/occ_draw)
include_directories(${SRC_DIR}/../../../../vendor/gcode_parser)
# include_directories(${SRC_DIR}/../../../../vendor/qt_functions)
include_directories(${SRC_DIR}/../../../../vendor/std_functions)

# Opencascade
find_package (OpenCASCADE REQUIRED)

SET(OpenCASCADE_LIBS
    TKGeomAlgo TKMesh TKHLR TKBO TKShHealing
    TKPrim
    TKernel TKMath TKTopAlgo TKService
    TKG2d TKG3d TKV3d TKOpenGl
    TKBRep TKXSBase TKGeomBase TKGeomAlgo
    TKXSDRAW
    TKLCAF TKXCAF TKCAF TKVCAF
    TKCDF TKBin TKBinL TKBinXCAF TKXml TKXmlL TKXmlXCAF
    # -- IGES support
    TKIGES
    # -- STEP support
    TKSTEP TKXDESTEP TKXDEIGES TKSTEPAttr TKSTEPBase TKSTEP209
    # -- STL support
    TKSTL
    # -- OBJ/glTF support
    TKRWMesh TKMeshVS
    # -- VRML support
    TKVRML
    # -- ViewerTest
    TKViewerTest
)

# Compile flags.
SET(GCC_COVERAGE_COMPILE_FLAGS "-I. -I${RTAPI_DIR} -I${HAL_DIR} \
    -DUSPACE -fno-fast-math -fno-unsafe-math-optimizations -DRTAPI -D_GNU_SOURCE
    -Drealtime -D__MODULE__ -DSIM -fPIC -Os")
add_definitions(-DRTAPI -DUSPACE -DRTAPI -D_GNU_SOURCE -D__MODULE__ )

# No "lib" before filename.
set(CMAKE_SHARED_LIBRARY_PREFIX "")

ADD_LIBRARY(${PROJECT} SHARED
    ${SRC_DIR}/state_machine.c
    ${SRC_DIR}/../../../../vendor/shmem_functions/state_machine_shm.h
    ${SRC_DIR}/../../../../vendor/shmem_functions/state_machine_shm.cpp

    ${SRC_DIR}/../../../../vendor/scurve/scurve_engine/scurve_struct.h
    ${SRC_DIR}/../../../../vendor/scurve/scurve_engine/scurve_reset.h
    ${SRC_DIR}/../../../../vendor/scurve/scurve_engine/scurve_engine.h
    ${SRC_DIR}/../../../../vendor/scurve/scurve_engine/scurve_engine.cpp
    ${SRC_DIR}/../../../../vendor/scurve/scurve_engine/scurve_segment.h

    ${SRC_DIR}/../../../../vendor/occ_draw/draw_primitives.h
    ${SRC_DIR}/../../../../vendor/occ_draw/draw_primitives.cpp
    ${SRC_DIR}/../../../../vendor/gcode_parser/gcode_parser.h
    ${SRC_DIR}/../../../../vendor/gcode_parser/gcode_parser.cpp

    # ${SRC_DIR}/../../../../vendor/qt_functions/qt_functions.h
    # ${SRC_DIR}/../../../../vendor/qt_functions/qt_functions.cpp
    ${SRC_DIR}/../../../../vendor/std_functions/std_functions.h
    ${SRC_DIR}/../../../../vendor/std_functions/std_functions.cpp
)

# Compile link with libhalcore.so or linuxcnchal.so
target_include_directories(${PROJECT_NAME} PRIVATE "${BUIlD_DIR}/src/hal/${RTLINK}")
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OpenCASCADE_LIBS}
    pthread rt ${RTLINK})

# make install
install(TARGETS ${PROJECT} DESTINATION ${RT_DIR})
