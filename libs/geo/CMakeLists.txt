cmake_minimum_required(VERSION 3.15)

project(QtExGeo
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions Geo & Cartography Library"
  HOMEPAGE_URL "io.github.whs31"
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

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Positioning Network)

enable_testing()

file(GLOB_RECURSE QTEX_GEO src/c++/*)
file(GLOB_RECURSE QTEX_GEO_INCLUDE include/*)

set(SRC ${QTEX_GEO} ${QTEX_GEO_INCLUDE})
add_library(${PROJECT_NAME} STATIC ${SRC})
target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Positioning
    Qt${QT_VERSION_MAJOR}::Network
    QtExCore
)
target_include_directories(${PROJECT_NAME} PUBLIC include src/c++)
