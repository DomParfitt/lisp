cmake_minimum_required(VERSION 3.10.2)

project(lisp)

include_directories(include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file(GLOB_RECURSE SOURCES src/*.c)

add_executable(main ${SOURCES})