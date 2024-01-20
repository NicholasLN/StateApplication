cmake_minimum_required(VERSION 3.27)
project(StateApplication)

set(CMAKE_CXX_STANDARD 17)

add_executable(StateApplication main.cpp
        includes/State.cpp
        includes/State.h
        includes/StateManager.cpp)
