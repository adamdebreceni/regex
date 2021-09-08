project(regex)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

include(cmake/RangeV3.cmake)

add_executable(main main.cpp)
target_link_libraries(main range-v3)
