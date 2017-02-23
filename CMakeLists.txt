cmake_minimum_required(VERSION 3.3)
project(YoutubePlanner)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++11")

file(GLOB SOURCES src/*)

add_executable(ytp ${SOURCES})