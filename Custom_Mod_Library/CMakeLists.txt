# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project (ModelLibrary)
include(CTest)







include_directories(include)


add_subdirectory(src)
add_subdirectory(tests)

link_directories(${CMAKE_SOURCE_DIR}/src)
#link_directories(${CMAKE_SOURCE_DIR}/tests)

add_executable(testMaterial "tests/testMaterial.cpp")

target_link_libraries(testMaterial PRIVATE LibsModule)

add_test(testMaterial testMaterial)

add_executable(testModel "tests/testModel.cpp")
add_executable(test3D_Vector "tests/test3D_Vector.cpp")
add_executable(testCell "tests/testCell.cpp")



target_link_libraries(testModel PRIVATE LibsModule)
target_link_libraries(test3D_Vector PRIVATE LibsModule)
target_link_libraries(testCell PRIVATE LibsModule)




add_test(testModel testModel)
add_test(test3D_Vector test3D_Vector)
add_test(testCell testCell)

if(EXISTS ${CMAKE_SOURCE_DIR}/tests/testFiles/ExampleModel1.mod AND NOT IS_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/testFiles/ExampleModel1.mod)
	message("Found file to copy")
else()
	message("Not found file")
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/build/src/)
	message("Found destination location")
	
	file(COPY_FILE
		${CMAKE_SOURCE_DIR}/tests/testFiles/ExampleModel1.mod
		${CMAKE_SOURCE_DIR}/build/src/)
else()
	message("Not found destination")
endif()














#[[Creating dynamic libraries

add_library(MaterialLib src/Material.cpp include/Material.h)
#add_library(ModelLib SHARED src/Model.cpp include/Model.h)
#add_library(3D_VectorLib SHARED src/3d_Vector.cpp include/3D_Vector.h)
#add_library(CellLib SHARED src/Cell.cpp include/Cell.h)


#Creating main project file

add_executable(${PROJECT_NAME} "tests/testMaterial.cpp")


#Creating test files

add_executable(testMaterial "tests/testMaterial.cpp")
#add_executable(testModel "tests/testModel.cpp")
#add_executable(test3D_Vector "tests/test3D_Vector.cpp")
#add_executable(testCell "tests/testCell.cpp")


#Link libraries to project
target_link_libraries(${PROJECT_NAME} PRIVATE MaterialLib)


#Link Libraries to test files

#target_link_libraries(testMaterial PRIVATE  MaterialLib)
#target_link_libraries(testModel PRIVATE  ModelLib)
#target_link_libraries(test3D_Vector PRIVATE  3D_VectorLib)
#target_link_libraries(testCell PRIVATE  CellLib)


#Creating tests

#add_test(testMaterial testMaterial)
#add_test(testModel testModel)
#add_test(test3D_Vector test3D_Vector)
#add_test(testCell testCell)









add_executable(testModel "tests/testModel.cpp")
add_executable(testMaterial "tests/testMaterial.cpp")
add_executable(test3D_Vector "tests/test3D_Vector.cpp")
add_executable(testCell "tests/testCell.cpp")

#Adds all the directories containing the classes that make up the library

add_subdirectory(Material)
add_subdirectory(Model)
add_subdirectory(3D_Vector)
add_subdirectory(Cell)
add_subdirectory(tests)


#Add libraries and library directories for executable project

target_include_directories(${PROJECT_NAME} PUBLIC Material Model 3D_Vector Cell)
target_link_directories(${PROJECT_NAME} PRIVATE Material Model 3D_Vector Cell)

target_link_libraries(${PROJECT_NAME} StaticMaterialLib StaticModelLib Static3D_VectorLib StaticCellLib)


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

target_include_directories(testCell PUBLIC Cell 3D_Vector)
target_link_directories(testCell SHARED Cell 3D_Vector)
target_link_libraries(testCell StaticCellLib Static3D_VectorLib)


add_test(testModel testModel)
add_test(testMaterial testMaterial)
add_test(test3D_Vector test3D_Vector)
add_test(testCell testCell)



]]

# TODO: Add tests and install targets if needed.
