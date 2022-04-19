cmake_minimum_required(VERSION 3.20)
project(Course_Paper)

set(CMAKE_CXX_STANDARD 14)

add_executable(Course_Paper d_heap.h fibonacci_heap.h multi_level_buckets.h dijkstra.h dijkstra.cpp main.cpp)
