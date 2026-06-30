cmake_minimum_required(VERSION 3.20)

project(posix_cpp)

add_library(posix_cpp
    posix.cpp
)

target_include_directories(posix_cpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
