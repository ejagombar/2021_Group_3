# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)


include(CTest)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)

link_directories(${CMAKE_SOURCE_DIR}/src)
link_directories(${CMAKE_SOURCE_DIR}/tests)




