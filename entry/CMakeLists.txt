cmake_minimum_required(VERSION 3.17)
project(entry)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(entry STATIC entry.h entry.cpp)
add_library(entry SHARED entry.h entry.cpp)