cmake_minimum_required(VERSION 3.27)
project(example)

set(CMAKE_CXX_STANDARD 20)

find_package(Stonks REQUIRED)

add_executable(example example.cpp)

target_include_directories(example PRIVATE ${Stonks_INCLUDE_DIR})
