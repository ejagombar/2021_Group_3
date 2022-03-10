# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project (ModelLibrary)
include(CTest)



add_executable(${PROJECT_NAME} "tests/testModel.cpp")

add_executable(testModel "tests/testModel.cpp")
add_executable(testMaterial "tests/testMaterial.cpp")
add_executable(test3D_Vector "tests/test3D_Vector.cpp")

#Adds all the directories containing the classes that make up the library

add_subdirectory(Material)
add_subdirectory(Model)
add_subdirectory(3D_Vector)
add_subdirectory(tests)


#Add libraries and library directories for executable project

target_include_directories(${PROJECT_NAME} PUBLIC Material Model 3D_Vector)
target_link_directories(${PROJECT_NAME} PRIVATE Material Model 3D_Vector)

target_link_libraries(${PROJECT_NAME} StaticMaterialLib StaticModelLib Static3D_VectorLib)


#Add libraries and library directories for test 

target_include_directories(testModel  PUBLIC Model)
target_link_directories(testModel PRIVATE Model)
target_link_libraries(testModel StaticModelLib)

target_include_directories(testMaterial PUBLIC Material)
target_link_directories(testMaterial PRIVATE Material)
target_link_libraries(testMaterial StaticMaterialLib)

target_include_directories(test3D_Vector PUBLIC 3D_Vector)
target_link_directories(test3D_Vector PRIVATE 3D_Vector)
target_link_libraries(test3D_Vector Static3D_VectorLib)



add_test(testModel testModel)
add_test(testMaterial testMaterial)
add_test(test3D_Vector test3D_Vector)





# TODO: Add tests and install targets if needed.
