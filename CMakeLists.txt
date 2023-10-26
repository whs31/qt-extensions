cmake_minimum_required(VERSION 3.15)

project(QtExtensions
  VERSION 1.0.0
  DESCRIPTION "Qt Extensions Bundle"
  HOMEPAGE_URL "io.github.whs31"
  LANGUAGES C CXX
)

if(TARGET ${PROJECT_NAME})
    return()
endif()

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

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    if(WIN32)
        include(FetchContent)
        FetchContent_Declare(
          googletest
          URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()
    find_package(GTest REQUIRED)
    enable_testing()
endif()

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Location Positioning Network)

add_subdirectory(libs/core)
add_subdirectory(libs/geo)
add_subdirectory(libs/scenegraph)
set(QTEX_INCLUDES
    include/QtExtensions/QtExtensions
    src/c++/qtex-register.c++
    src/c++/qtex-register.h
)

include_directories(include src/c++)
add_library(${PROJECT_NAME} STATIC ${QTEX_INCLUDES})

target_link_libraries(${PROJECT_NAME}
  PRIVATE
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::Quick
  PUBLIC
      QtExCore
      QtExGeo
      QtExScenegraph
)

target_include_directories(${PROJECT_NAME} PUBLIC include src/c++)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    file(GLOB_RECURSE QTEX_TESTS tests/*)
    message(NOTICE "-- [Qt Extensions] Tests enabled")
    add_compile_definitions(QTEX_CORE_ENABLE_TESTS)
    add_executable(${PROJECT_NAME}-Test ${QTEX_INCLUDES} ${QTEX_TESTS})
    target_link_libraries(${PROJECT_NAME}-Test PRIVATE
      GTest::GTest
      Qt${QT_VERSION_MAJOR}::Network
      Qt${QT_VERSION_MAJOR}::Positioning
      Qt${QT_VERSION_MAJOR}::Location
      Qt${QT_VERSION_MAJOR}::Quick
      Qt${QT_VERSION_MAJOR}::Core
      QtExCore
      QtExGeo
      QtExScenegraph
    )
else()
    message(STATUS "[Qt Extensions] Tests disabled")
endif()