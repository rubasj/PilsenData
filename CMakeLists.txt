cmake_minimum_required(VERSION 3.17)
project(PilsenData C)

set(CMAKE_C_STANDARD 99)

add_executable(PilsenData src/main.c src/matrix.c src/matrix.h)