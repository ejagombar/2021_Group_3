# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project (ModelLibrary)
include(CTest)



add_executable(${PROJECT_NAME} "tests/testModel.cpp")

add_executable(testModel "tests/testModel.cpp")
add_executable(testMaterial "tests/testMaterial.cpp")

#Adds all the directories containing the classes that make up the library

add_subdirectory(Material)
add_subdirectory(Model)
add_subdirectory(tests)


#Add libraries and library directories for executable project
target_include_directories(${PROJECT_NAME} PUBLIC Material Model)
target_link_directories(${PROJECT_NAME} PRIVATE Material Model)

target_link_libraries(${PROJECT_NAME} StaticMaterialLib StaticModelLib)


#Add libraries and library directories for test 
target_include_directories(testModel  PUBLIC Material Model)
target_link_directories(testModel PRIVATE Material Model)
target_link_libraries(testModel StaticMaterialLib StaticModelLib)

target_include_directories(testMaterial PUBLIC Material Model)
target_link_directories(testMaterial PRIVATE Material Model)
target_link_libraries(testMaterial StaticMaterialLib StaticModelLib)


add_test(testModel testModel )
add_test(testMaterial testMaterial)





# TODO: Add tests and install targets if needed.
