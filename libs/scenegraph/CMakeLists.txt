cmake_minimum_required(VERSION 3.15)

project(QtExScenegraph
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions Scenegraph Library"
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
find_package(Qt5 REQUIRED COMPONENTS Core Quick)

enable_testing()
include_directories(src/c++ include)

set(QTEX_SG
    src/c++/qtexsg-scenegraphobject.h                           src/c++/qtexsg-scenegraphobject.c++
    src/c++/qtexsg-scenegraph-utils.h                           src/c++/qtexsg-scenegraph-utils.c++
    src/c++/materials/qtexsg-materials-state.h
    src/c++/materials/qtexsg-materials-fadinggradientshader.h   src/c++/materials/qtexsg-materials-fadinggradientshader.c++
    src/c++/materials/qtexsg-materials-radialgradientshader.h   src/c++/materials/qtexsg-materials-radialgradientshader.c++
    src/c++/gadgets/qtexsg-basicpalette.h                       src/c++/gadgets/qtexsg-basicpalette.c++
)

set(QTEX_SG_INCLUDE
    include/QtExScenegraph/ScenegraphObject
    include/QtExScenegraph/ScenegraphUtils
    include/QtExScenegraph/BasicPalette
    include/QtExScenegraph/Materials/State
    include/QtExScenegraph/Materials/FadingGradient
    include/QtExScenegraph/Materials/RadialGradient
)

set(SRC ${QTEX_SG} ${QTEX_SG_INCLUDE})
add_library(${PROJECT_NAME} STATIC ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Quick
    QtExCore
)

target_include_directories(${PROJECT_NAME} PUBLIC include src)