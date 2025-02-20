cmake_minimum_required(VERSION 3.5)

project(scurve_3axis_jog LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

include_directories(
    ${CURRENT_SOURCE_DIR}  # Include the current source directory
    ${CURRENT_SOURCE_DIR}/../scurve_engine  # Include the directory of the scurve_motion module
)

set(SOURCES
    main.cpp
    mainwindow.cpp
    qcustomplot.cpp
    ../scurve_engine/scurve_engine.cpp
)

set(HEADERS
    mainwindow.h
    qcustomplot.h
     ../scurve_engine/scurve_engine.h
)

set(FORMS
    mainwindow.ui
)

add_executable(scurve_3axis_jog ${SOURCES} ${HEADERS} ${FORMS})

target_link_libraries(scurve_3axis_jog PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::PrintSupport
)
