project(Calculate)
set(PROJECT_NAME, Calculate)
cmake_minimum_required(VERSION 2.8)
INCLUDE_DIRECTORIES(./include)
SET(SRC_LIST
        src/main.cpp src/node.cpp src/parser.cpp src/scanner.cpp src/symboltable.cpp
        src/storage.cpp src/calc.cpp src/functiontable.cpp src/exception.cpp
        src/tracer.cpp src/commandparser.cpp src/serial.cpp
        include/node.h include/parser.h include/scanner.h include/symboltable.h
        include/storage.h include/calc.h include/functiontable.h include/exception.h
        include/tracer.h include/debug_new.h include/commandparser.h include/serial.h
)
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_EXE_LINKER_FLAGS -rdynamic)
#set(CMAKE_CXX_FLAGS -rdynamic)
add_executable(${PROJECT_NAME} ${SRC_LIST})
