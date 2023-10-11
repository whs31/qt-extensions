cmake_minimum_required(VERSION 3.15)

project(QtExElevation
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions Elevation Library"
  HOMEPAGE_URL "uav.radar-mms.com"
  LANGUAGES C CXX
)

if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED OFF)
    set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

if(TARGET ${PROJECT_NAME})
    return()
endif()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(GDAL REQUIRED)
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED
  COMPONENTS
    Core
    Positioning
    Concurrent
)

enable_testing()
include_directories(${GDAL_INCLUDE_DIR})
include_directories(src/c++ include)

file(GLOB_RECURSE QTEX_ELEVATION src/c++/*)
file(GLOB_RECURSE QTEX_ELEVATION_INCLUDE include/*)

set(SRC ${QTEX_ELEVATION} ${QTEX_ELEVATION_INCLUDE})
add_library(${PROJECT_NAME} STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Positioning
    Qt5::Concurrent
    ${GDAL_LIBRARY}
    QtExCore
    QtExGeo
)
target_include_directories(${PROJECT_NAME} PUBLIC include src)
