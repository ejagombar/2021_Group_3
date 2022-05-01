# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

add_library(LibsModule Model.cpp Material.cpp Cell.cpp 3D_Vector.cpp)

add_executable(testLibsModule "main.cpp")
target_link_libraries(testLibsModule PRIVATE LibsModule)