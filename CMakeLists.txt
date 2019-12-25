cmake_minimum_required(VERSION 3.15)
project(AdvancedProgramming)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(AdvancedProgramming main.cpp Command.cpp Obj.cpp InterpreterFlight.cpp Lexer.cpp ex1.cpp VarCommand.cpp
        ObjCommand.cpp SleepCommand.cpp PrintCommand.cpp openDataCommad.cpp OpenControlCommand.cpp
        IfCommand.cpp WhileCommand.cpp conditionParser.cpp)