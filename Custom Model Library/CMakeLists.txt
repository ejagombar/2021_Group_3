# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project (ModelLibrary)

add_executable(${PROJECT_NAME} main.cpp)


#Adds all the directories containing the classes that make up the library

add_subdirectory(Material)

target_include_directories(${PROJECT_NAME} PUBLIC Material) 

target_link_directories(${PROJECT_NAME} PRIVATE Material)


target_link_libraries(${PROJECT_NAME} StaticMaterialLib)



#Adds the directory that holds the test programs 
add_subdirectory(Tests)



# TODO: Add tests and install targets if needed.
