cmake_minimum_required(VERSION 3.15)

project(QtEx
  VERSION 1.0.0
  DESCRIPTION "Qt Extensions Bundle"
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

add_subdirectory(libs/core)
add_subdirectory(libs/geo)
add_subdirectory(libs/elevation)
add_subdirectory(libs/scenegraph)
#add_subdirectory(libs/application)
#add_subdirectory(libs/networking)

add_library(${PROJECT_NAME} STATIC include/QtEx/QtEx)
target_link_libraries(${PROJECT_NAME} PUBLIC
    QtExCore
    QtExGeo
    QtExElevation
    QtExScenegraph
    #QtExApplication
    #QtExNetworking
)

message(STATUS "[QtEx] Loaded")
