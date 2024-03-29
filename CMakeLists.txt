cmake_minimum_required(VERSION 3.27)
project(stonks)

project(
        order_book_lib
        LANGUAGES CXX
        DESCRIPTION "main lib for whole project"
        VERSION 1.0.1
        HOMEPAGE_URL https://alkut.github.io/stonks/)

message(STATUS ${order_book_lib_VERSION})

include(cmake/Options.cmake)
include(cmake/Environmnent.cmake)
include(cmake/CxxFlags.cmake)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

if (${STONKS_ENABLE_TESTS})
    add_subdirectory(tests)
endif ()

if (${STONKS_ENABLE_EXAMPLES})
    add_subdirectory(examples)
endif ()

if (${STONKS_ENABLE_BENCHMARKS}
        AND NOT
        CMAKE_BUILD_TYPE
        STREQUAL
        "Debug")
    add_subdirectory(benchmarks)
endif ()

if (${STONKS_ENABLE_DOCS})
    include(cmake/FindDoxygen.cmake)
endif ()

if (${STONKS_ENABLE_STONKS_ENABLE_CCACHE})
    include(cmake/FindCcache.cmake)
endif ()

add_executable(stonks main.cpp)

target_include_directories(stonks PRIVATE ${CMAKE_SOURCE_DIR}/src)

if (NOT ${STONKS_BINARY_IN_BUILD})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif ()
