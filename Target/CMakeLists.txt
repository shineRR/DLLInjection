cmake_minimum_required(VERSION 3.17)
project(Target)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

add_executable(Target main.cpp)