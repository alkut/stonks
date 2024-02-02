enable_testing()

project(tests)

include(../cmake/FindGTest.cmake)

add_executable(tests test.cpp)

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main order_book_lib)
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/../src)

gtest_add_tests(
        TARGET tests
        TEST_PREFIX BasicTests---
        TEST_SUFFIX ---BasicTests
)
