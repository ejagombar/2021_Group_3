cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

set(PROJECT_NAME_ QtVTKExample)
set(PROJECT_BIN_NAME_ QtVTKExample)
set(PROJECT_DESCRIPTION_ "QtVTKExample descriptions")
set(PROJECT_PKG_NAME_ "QtVTKExample")
set(PROJECT_PKG_TITLE_ "QtVTKExample Installer")
set(PROJECT_PKG_PUBLISHER_ "David Fang")
set(PROJECT_LICENSE_FILE_ ${CMAKE_CURRENT_SOURCE_DIR}/licence.txt)
set(PROJECT_VERSION_MAJOR_ 2 CACHE STRING "Project major version number.")
set(PROJECT_VERSION_MINOR_ 3 CACHE STRING "Project minor version number.")
set(PROJECT_VERSION_PATCH_ 4 CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)
set(CPACK_IFW_ROOT "C:/Qt/Tools/QtInstallerFramework/4.3/")
set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Aero")

set(BUID_MODE_ $<$<CONFIG:Debug>:Debug>$<$<CONFIG:Release>:Release>)
set(BUID_MODE_DLL_ $<$<CONFIG:Debug>:d.dll>$<$<CONFIG:Release>:.dll>)
set(VTK_bin "${VTK_DIR}/bin/${BUID_MODE_}")
#set(CMAKE_MSVCIDE_RUN_PATH ${VTK_bin})
#LIST(APPEND CMAKE_PROGRAM_PATH  "${VTK_bin}")

PROJECT( QtVTKExample )

# The CMake build process might generate some new files in the current
# directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )


# This allows CMake to run one of Qt's build tools called moc
# if it is needed. moc.exe can be found in Qt's bin directory.
# We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )

# Find the Qt widgets package. This locates the relevant include and
# lib directories, and the necessary static libraries for linking.
find_package( Qt6Widgets )

set( UIS mainwindow.ui )
qt6_wrap_ui( UI_Srcs ${UIS} )

set( ICONS Icons/icons.qrc )
qt6_add_resources( QRC_Srcs ${ICONS} )


# Also link to VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/myapp.rc")

# Define the executable output and its sources
add_executable( QtVTKExample MACOSX_BUNDLE myapp.rc
				main.cpp mainwindow.cpp 
				mainwindow.h 
				mainwindow.ui
                                                                    filter.cpp
                                                                    filter.h
                                                                    ModelRender.cpp
                                                                    ModelRender.h
                                                                    form.h
                                                                    form.ui
                                                                    form.cpp
				${UI_Srcs}
				${QRC_Srcs}
                                ${APP_ICON_RESOURCE_WINDOWS}
				)

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( QtVTKExample Qt6::Widgets )

# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( QtVTKExample ${VTK_LIBRARIES} )

#set(MY_PATH "PATH=%PATH%;${VTK_bin}" )
#set_target_properties(QtVTKExample PROPERTIES VS_DEBUGGER_ENVIRONMENT "{MY_PATH}")
set(CMAKE_MSVCIDE_RUN_PATH ${VTK_bin})

include(IFWin.cmake)

# check if Doxygen is installed
find_package(Doxygen)
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if (BUILD_DOC)
    #    set( DOXYGEN_OUTPUT_DIRECTORY doxygen )
    set(DOXYGEN_COLLABORATION_GRAPH YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_CLASS_DIAGRAMS YES)
    set(DOXYGEN_HIDE_UNDOC_RELATIONS NO)
    set(DOXYGEN_HAVE_DOT YES)
    set(DOXYGEN_CLASS_GRAPH YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_CALLER_GRAPH YES)

    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(docs_doxygen ALL
            COMMAND ${CMAKE_COMMAND} -E echo_append "Doxygen Building API Documentation..."
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            COMMAND ${CMAKE_COMMAND} -E echo "Doxygen Done."
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
            )
else (BUILD_DOC)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (BUILD_DOC)










