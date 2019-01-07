cmake_minimum_required(VERSION 3.12)
project(Wet2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Wet2 library.cpp  Tree.cpp main.cpp tests.cpp)