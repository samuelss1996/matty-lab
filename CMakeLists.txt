cmake_minimum_required(VERSION 3.8)
project(MaTTY_Lab)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lfl")

include_directories(${CMAKE_SOURCE_DIR}/lexical)
include_directories(${CMAKE_SOURCE_DIR}/syntactic)
include_directories(${CMAKE_SOURCE_DIR}/errors)

set(SOURCE_FILES main.c lexical/lex.yy.c lexical/lex.yy.h syntactic/SyntacticDefinitions.tab.c syntactic/SyntacticDefinitions.tab.h errors/Errors.c errors/Errors.h)
add_executable(MaTTY_Lab ${SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} -lfl)