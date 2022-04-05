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
add_executable(testModel "tests/testModel.cpp")
add_executable(test3D_Vector "tests/test3D_Vector.cpp")
add_executable(testCell "tests/testCell.cpp")


target_link_libraries(testMaterial PRIVATE LibsModule)
target_link_libraries(testModel PRIVATE LibsModule)
target_link_libraries(test3D_Vector PRIVATE LibsModule)
target_link_libraries(testCell PRIVATE LibsModule)



add_test(testMaterial testMaterial)
add_test(testModel testModel)
add_test(test3D_Vector test3D_Vector)
add_test(testCell testCell)

if(EXISTS ${CMAKE_SOURCE_DIR}/tests/ExampleModel1.mod AND NOT IS_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/ExampleModel1.mod)
	message("Found file to copy")
else()
	message("Not found file")
endif()

if(EXISTS ${CMAKE_BINARY_DIR})
	message("Found destination location")
	

else()
	message("Not found destination")
endif()

file(COPY_FILE
	${CMAKE_SOURCE_DIR}/tests/ExampleModel1.mod 
	${CMAKE_BINARY_DIR}/ExampleModel1.mod)