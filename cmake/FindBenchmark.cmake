find_package(benchmark CONFIG)

if (NOT ${benchmark_FOUND})

    message(STATUS "Can't find Google Benchmark locally, fetching from github")

    include(FetchContent)

    FetchContent_Declare(
            googlebenchmark
            URL https://github.com/google/benchmark/archive/refs/tags/v1.8.3.zip
    )

    FetchContent_MakeAvailable(googlebenchmark)

endif ()