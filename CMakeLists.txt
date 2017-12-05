cmake_minimum_required(VERSION 3.8)
project(MaTTY_Lab)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lfl -lm")

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/errors)
include_directories(${CMAKE_SOURCE_DIR}/keywords)
include_directories(${CMAKE_SOURCE_DIR}/lexical)
include_directories(${CMAKE_SOURCE_DIR}/symbols)
include_directories(${CMAKE_SOURCE_DIR}/syntactic)
include_directories(${CMAKE_SOURCE_DIR}/util)

set(SOURCE_FILES main.c lexical/lex.yy.c lexical/lex.yy.h syntactic/SyntacticDefinitions.tab.c syntactic/SyntacticDefinitions.tab.h errors/Errors.c errors/Errors.h symbols/SymbolsTable.c symbols/SymbolsTable.h util/HashTable.c util/HashTable.h util/LinkedList.c util/LinkedList.h Definitions.h keywords/NativeFunctions.c keywords/NativeFunctions.h)
add_executable(MaTTY_Lab ${SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} -lfl -lm)