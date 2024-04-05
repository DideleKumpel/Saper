cmake_minimum_required(VERSION 3.26)
project(saper)

set(CMAKE_CXX_STANDARD 17)

add_executable(saper main.cpp
        CinErrorHandler.cpp
        CinErrorHandler.h)
