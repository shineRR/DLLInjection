cmake_minimum_required(VERSION 3.17)
project(Helper)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(Helper main.cpp)

target_link_libraries(Helper ${CMAKE_SOURCE_DIR}/../entry/cmake-build-debug/libentry.a)