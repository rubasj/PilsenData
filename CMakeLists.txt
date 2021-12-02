cmake_minimum_required(VERSION 3.17)
project(PilsenData C)

set(CMAKE_C_STANDARD 99)

add_executable(PilsenData src/loader.c src/matrix/matrix.c src/matrix/matrix.h src/edge/edge.h src/edge/edge.c src/vector/vector.h src/vector/vector.c src/max_flow/ford_fulkerson.c src/max_flow/ford_fulkerson.h src/minimum_cut/minimum_cut.c src/minimum_cut/minimum_cut.h)