# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project (ModelLibrary)


add_executable(${PROJECT_NAME} tests/main.cpp)

#Adds all the directories containing the classes that make up the library

add_subdirectory(Material)
add_subdirectory(Model)
add_subdirectory(tests)


target_include_directories(${PROJECT_NAME} PUBLIC Material Model tests)

target_link_directories(${PROJECT_NAME} PRIVATE Material Model tests)



target_link_libraries(${PROJECT_NAME} StaticMaterialLib StaticModelLib)

#Adds the directory that holds the test programs 




# TODO: Add tests and install targets if needed.
