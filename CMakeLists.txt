cmake_minimum_required(VERSION 3.5)
project(cpp_not_so_simple_calculator_helgadani)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Calculator.cpp Calculator.h Tester.hpp)
add_executable(cpp_not_so_simple_calculator_helgadani ${SOURCE_FILES})