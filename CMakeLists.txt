cmake_minimum_required(VERSION 3.15)
project(AdvancedProgramming)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(AdvancedProgramming main.cpp Commands.cpp Obj.cpp InterpreterFlight.cpp Lexer.cpp ex1.cpp)