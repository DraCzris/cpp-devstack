cmake_minimum_required(VERSION 2.8.4)
project(C__DevStack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(C__DevStack ${SOURCE_FILES})