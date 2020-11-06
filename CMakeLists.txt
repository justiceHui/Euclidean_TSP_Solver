cmake_minimum_required(VERSION 3.17)
project(Euclidean_TSP_Solver)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,300000000")
ADD_COMPILE_OPTIONS(-std=c++14 -lm -march=native -DLOCAL -ffast-math -ftree-vectorize)

add_executable(Euclidean_TSP_Solver main.cpp General.h Header_EuclideanTSP/DelaunayTriangulation.h Header_EuclideanTSP/Edge.h Header_EuclideanTSP/EuclideanMST.h Header_EuclideanTSP/EuclideanTSP.h)