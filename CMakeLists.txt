cmake_minimum_required(VERSION 3.17)
project(GA)

set(CMAKE_CXX_STANDARD 20)

add_executable(GA main.cpp functions/common.h functions/mutations.h functions/crossingovers.h functions/replications.h functions/reductions.h implementations.cpp)