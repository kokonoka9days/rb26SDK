cmake_minimum_required(VERSION 3.16)
project(demo)

set(CMAKE_CXX_STANDARD 17)

include_directories(rb26SDK)
add_subdirectory(rb26SDK)

find_package(OpenCV REQUIRED)

add_executable(demo demo2.cpp)

target_include_directories(demo PRIVATE rb26SDK)

target_link_libraries(demo PRIVATE
    rb26SDK
)

