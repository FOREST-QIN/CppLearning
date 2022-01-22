cmake_minimum_required(VERSION 3.21)
project(projects)

set(CMAKE_CXX_STANDARD 14)



add_executable(projects main.cpp Solution.cpp Solution.h TwentyNine/Solution.cpp twenty/Solution.cpp twenty/Solution.h twentyOne/Solution.cpp twentyOne/Solution.h twentyTwo/Solution.cpp twentyTwo/Solution.h)
