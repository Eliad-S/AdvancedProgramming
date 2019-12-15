cmake_minimum_required(VERSION 3.15)
project(AdvancedProgramming)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(AdvancedProgramming main.cpp ex1.cpp Obj.cpp Commands.cpp Lexer.cpp)