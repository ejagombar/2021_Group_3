set(WINDEPLOYQT "C:/Qt/6.2.3/msvc2019_64/bin/windeployqt.exe")
set(COMPONENT_NAME_MAIN "QtVTKExample")
set(CMAKE_CURRENT_SOURCE_DIR "D:/School_Stuff/Group_3D/QtVTKExample_final_2")


execute_process(COMMAND ${WINDEPLOYQT} --verbose 0 --qmldir ${CMAKE_CURRENT_SOURCE_DIR} ${COMPONENT_NAME_MAIN}/data WORKING_DIRECTORY ${CPACK_TEMPORARY_INSTALL_DIRECTORY}/packages)
