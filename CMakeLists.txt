cmake_minimum_required(VERSION 3.21)
project(projects)

set(CMAKE_CXX_STANDARD 14)

file (GLOB files *.cpp */*.cpp */*/*.cpp)
foreach (file ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" exe ${file})
    add_executable (${exe} ${file})
    message (\ \ \ \ --\ src/${exe}.cpp\ will\ be\ compiled\ to\ bin/${exe})
endforeach ()