find_package(GTest 1.11 CONFIG)

if (NOT ${GTest_FOUND})

    message(STATUS "Can't find GTest locally, fetching from github")

    include(FetchContent)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)
    set(gtest_force_shared_crt
            ON
            CACHE BOOL "" FORCE)
    set(BUILD_GMOCK
            ON
            CACHE BOOL "" FORCE)
    set(BUILD_GTEST
            ON
            CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

endif ()

include(GoogleTest)
