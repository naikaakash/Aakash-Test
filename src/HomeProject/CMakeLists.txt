# CMakeList.txt : CMake project for HomeProject, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.5)
project(PM)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Disable unused variable and unused parameter warnings
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable -Wno-unused-parameter")

# Add source to this project's executable.
add_executable (HomeProject
                HomeProject.cpp
                HomeProject.hpp)

#target_compile_options(HomeProject PRIVATE -Wdunused-parameter)

# TODO: Add tests and install targets if needed.

add_subdirectory (cproject)
