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

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    find_package(GTest REQUIRED)
    enable_testing()
endif()

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Core Quick Location Positioning Network)

add_subdirectory(libs/core)
add_subdirectory(libs/geo)
add_subdirectory(libs/elevation)
add_subdirectory(libs/scenegraph)
#add_subdirectory(libs/application)
#add_subdirectory(libs/networking)
set(QTEX_INCLUDES
    include/QtEx/QtEx
)

set(QTEX_TESTS

)

include_directories(include)
add_library(${PROJECT_NAME} STATIC ${QTEX_INCLUDES})
target_link_libraries(${PROJECT_NAME} PUBLIC
    QtExCore
    QtExGeo
    QtExElevation
    QtExScenegraph
    #QtExApplication
    #QtExNetworking
)
target_include_directories(${PROJECT_NAME} PUBLIC include)

message(STATUS "[QtEx] Tests disabled")
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    message(WARNING "[QtEx] Tests enabled")
    add_compile_definitions(QTEX_CORE_ENABLE_TESTS)
    add_executable(${PROJECT_NAME}-Test ${QTEX_INCLUDES} ${QTEX_TESTS})
    target_link_libraries(${PROJECT_NAME}-Test
      Qt5::Network
      Qt5::Positioning
      Qt5::Location
      Qt5::Quick
      Qt5::Core
      GTest::GTest
      QtExCore
      QtExGeo
      QtExElevation
      QtExScenegraph
    )
endif()

