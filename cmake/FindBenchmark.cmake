find_package(benchmark CONFIG REQUIRED)

if (NOT ${benchmark_FOUND})

    message(STATUS "Can't find Google Benchmark locally, fetching from github")

    include(FetchContent)

    FetchContent_Declare(
            googlebenchmark
            GIT_REPOSITORY https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
    )

    FetchContent_MakeAvailable(googlebenchmark)

endif ()