project(CalculatorTest)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
SET(SRC_LIST main.cpp tracer.cpp node.cpp
             tracer.h debug_new.h node.h)
#aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

