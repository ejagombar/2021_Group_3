# CMakeList.txt : CMake project for Custom Model Class, include source and define
# project specific logic here.

# COPY_FILE was added in v3.21
cmake_minimum_required (VERSION 3.21)

add_executable(testMaterial "testMaterial.cpp")
add_executable(testModel "testModel.cpp")
add_executable(test3D_Vector "test3D_Vector.cpp")
add_executable(testCell "testCell.cpp")

target_link_libraries(testMaterial PRIVATE LibsModule)
target_link_libraries(testModel PRIVATE LibsModule)
target_link_libraries(test3D_Vector PRIVATE LibsModule)
target_link_libraries(testCell PRIVATE LibsModule)

add_test(testMaterial testMaterial)
add_test(testModel testModel)
add_test(test3D_Vector test3D_Vector)
add_test(testCell testCell)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ExampleModel1.mod AND NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ExampleModel1.mod)
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
	${CMAKE_CURRENT_SOURCE_DIR}/ExampleModel1.mod 
	${CMAKE_CURRENT_BINARY_DIR}/ExampleModel1.mod)