cmake_minimum_required(VERSION 3.15)

project(QtExGeo
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions Geo & Cartography Library"
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

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Core Positioning Network)

enable_testing()
include_directories(src/c++ include)

set(QTEX_GEO
    src/c++/qtexgeo-register.h                                  src/c++/qtexgeo-register.c++
    src/c++/qtexgeo-geomath.h                                   src/c++/qtexgeo-geomath.c++
    src/c++/qtexgeo-orthodrom.h                                 src/c++/qtexgeo-orthodrom.c++
    src/c++/qtexgeo-tileloader.h                                src/c++/qtexgeo-tileloader.c++
    src/c++/qtexgeo-traverse.h                                  src/c++/qtexgeo-traverse.c++
    src/c++/providers/qtexgeo-googlemapsprovider.h              src/c++/providers/qtexgeo-googlemapsprovider.c++
)

set(QTEX_GEO_INCLUDE
    include/QtExGeo/GoogleMapsProvider
    include/QtExGeo/Math
    include/QtExGeo/Orthodrom
    include/QtExGeo/Register
    include/QtExGeo/TileLoader
    include/QtExGeo/Traverse
)


set(SRC ${QTEX_GEO} ${QTEX_GEO_INCLUDE})
add_library(${PROJECT_NAME} STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Positioning
    Qt5::Network
    QtExCore
)
target_include_directories(${PROJECT_NAME} PUBLIC include src)
