cmake_minimum_required(VERSION 3.22) #minium version
project( 3D_Vector ) #project name

set( CMAKE_CXX_FLAGS "-std=c++11" ) 
set( CMAKE_BUILD_TYPE "Debug" )


add_library(3D_Vector_Lib SHARED  3D_Vector.cpp)

add_executable(3D_Vector_main main.cpp)


target_link_libraries(3D_Vector 3DVector)