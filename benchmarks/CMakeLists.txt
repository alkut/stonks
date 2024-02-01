project(benchmark_tests)

include(../cmake/FindBenchmark.cmake)

add_executable(benchmark_tests benchmark_tests.cpp)

target_link_libraries(benchmark_tests PRIVATE benchmark::benchmark benchmark::benchmark_main Shlwapi order_book_lib)
target_include_directories(benchmark_tests PRIVATE ${PROJECT_SOURCE_DIR}/../src)

target_compile_definitions(benchmark_tests PRIVATE BENCHMARK_STATIC_DEFINE)