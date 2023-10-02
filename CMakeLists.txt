cmake_minimum_required(VERSION 3.15)

project(QtExCore
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions Core Library"
  HOMEPAGE_URL "uav.radar-mms.com"
  LANGUAGES C CXX
)

option(QTEX_CORE_USE_DOUBLE "If option is on, all math functions/classes will default to double instead of float" OFF)
option(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES "Propagate QString/QObject/etc type aliases to global scope" ON)

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

if(WIN32)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

find_package(GTest REQUIRED)
find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Core Quick)

add_subdirectory(libs/expected)
add_subdirectory(libs/range-v3)

enable_testing()
include_directories(src/c++ include)

set(QTEX_CORE
    src/c++/qtexcore-global.h
    src/c++/qtexcore-math.h
    src/c++/qtexcore-test-macro.h
    src/c++/qtexcore-logging.h                                  src/c++/qtexcore-logging.c++
    src/c++/abstract/qtexcore-icolorable.h
    src/c++/abstract/qtexcore-inameable.h
    src/c++/geometry/qtexcore-point1d.c++                       src/c++/geometry/qtexcore-point1d.h
    src/c++/geometry/qtexcore-point2d.c++                       src/c++/geometry/qtexcore-point2d.h
)

set(QTEX_CORE_INCLUDE
    include/QtExCore/Global
    include/QtExCore/Math
    include/QtExCore/Test
    include/QtExCore/Logging
    include/QtExCore/Point1D
    include/QtExCore/Point2D
    include/QtExCore/Abstract/IColorable
    include/QtExCore/Abstract/INameable
)

set(QTEX_CORE_TESTS
    src/c++/qtexcore-math-test.c++
    src/c++/qtexcore-cxxfeautures-test.c++
    src/c++/qtexcore-test-main.c++
    src/c++/qtexcore-logging-test.c++
    src/c++/geometry/qtexcore-points-test.c++
)

set(SRC ${QTEX_CORE} ${QTEX_CORE_INCLUDE})
add_library(${PROJECT_NAME} STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt5::Core
    Qt5::Quick
    GTest::GTest
    expected
    range-v3
)
target_include_directories(${PROJECT_NAME} PUBLIC include src)

if(${QTEX_CORE_USE_DOUBLE})
    add_compile_definitions(QTEX_CORE_USE_DOUBLE)
endif()

if(${QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES})
    add_compile_definitions(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES)
endif()

message(STATUS "[QtEx-Core] Tests disabled")
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    message(WARNING "[QtEx-Core] Tests enabled")
    add_compile_definitions(QTEX_CORE_ENABLE_TESTS)
    add_executable(${PROJECT_NAME}-Test ${QTEX_CORE} ${QTEX_CORE_INCLUDE} ${QTEX_CORE_TESTS})
    target_link_libraries(${PROJECT_NAME}-Test
      Qt5::Quick
      Qt5::Core
      GTest::GTest
      expected
      range-v3
    )
endif()
