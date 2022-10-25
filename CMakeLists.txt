cmake_minimum_required(VERSION 3.23)
project(NSI)

set(CMAKE_CXX_STANDARD 17)

include_directories(LAB1)

add_executable(NSI
        LAB1/lab1.cpp
        LAB1/lab1.h
        LAB2/zad2.cpp l3/lab3.cpp)
