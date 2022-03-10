# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project (ModelLibrary)
include(CTest)



add_executable(${PROJECT_NAME} "tests/testModel.cpp")

add_executable(test1 "tests/testModel.cpp")
add_executable(testMaterial "tests/testMaterial.cpp")

#Adds all the directories containing the classes that make up the library

add_subdirectory(Material)
add_subdirectory(Model)
add_subdirectory(tests)

target_include_directories(${PROJECT_NAME} PUBLIC Material Model)

target_link_directories(${PROJECT_NAME} PRIVATE Material Model)

target_link_libraries(${PROJECT_NAME} StaticMaterialLib StaticModelLib)


#add_executable(testModel "tests/testModel.cpp")
#add_executable(testMaterial "tests/testMaterial.cpp")

add_test(test1 test1)
add_test(testMaterial testMaterial)

#Adds the directory that holds the test programs 




# TODO: Add tests and install targets if needed.
