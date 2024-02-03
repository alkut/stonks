cmake_minimum_required(VERSION 3.27)
project(stonks)

include(cmake/Options.cmake)
include(cmake/Environmnent.cmake)
include(cmake/CxxFlags.cmake)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

if (${STONKS_ENABLE_TESTS})
    add_subdirectory(tests)
endif ()

if (${STONKS_ENABLE_BENCHMARKS})
    add_subdirectory(benchmarks)
endif ()

if (${STONKS_ENABLE_DOCS})
    include(cmake/FindDoxygen.cmake)
endif ()

if (${STONKS_ENABLE_STONKS_ENABLE_CCACHE})
    include(cmake/FindCcache.cmake)
endif ()

add_executable(stonks main.cpp)

target_include_directories(stonks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(stonks PRIVATE order_book_lib)

if (NOT ${STONKS_BINARY_IN_BUILD})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif ()
