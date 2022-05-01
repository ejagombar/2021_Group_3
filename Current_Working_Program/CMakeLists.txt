cmake_minimum_required(VERSION 3.16)

project(Worksheet_6_Exercise_3 VERSION 0.1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Qt 6 requires a compiler supporting C++ version 17 or newer. Enforcing this by setting the CMAKE_CXX_STANDARD, 
# CMAKE_CXX_STANDARD_REQUIRED variables will let CMake print an error if the compiler is too old.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
set(CPACK_GENERATOR "NSIS")
else()
set(CPACK_GENERATOR "ZIP")
endif()
include(CPack)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(VTK 6.0 REQUIRED COMPONENTS vtkCommonCore vtkGUISupportQt vtkCommonColor vtkIOGeometry)

add_subdirectory(Custom_Mod_Library)
link_directories(${CMAKE_SOURCE_DIR}/Custom_Mod_Library)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

set( UIS mainwindow.ui )
qt6_wrap_ui( UI_Srcs ${UIS} )

set( ICONS Icons/icons.qrc )
qt6_add_resources( QRC_Srcs ${ICONS} )

message("QT version =  ${QT_VERSION_MAJOR}")

qt_add_executable(Worksheet_6_Exercise_3
                  MANUAL_FINALIZATION
                  ${PROJECT_SOURCES}
                  ${QRC_Srcs}
                  )

target_link_libraries(Worksheet_6_Exercise_3 PRIVATE Qt6::Widgets)
target_link_libraries(Worksheet_6_Exercise_3 PRIVATE VTK::CommonCore VTK::GUISupportQt VTK::CommonColor VTK::IOGeometry)

set_target_properties(Worksheet_6_Exercise_3 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

qt_finalize_executable(Worksheet_6_Exercise_3)

set(CMAKE_INSTALL_DEBUG_LIBRARIES true)
include (InstallRequiredSystemLibraries)

message( "QT dir = ${QRC_Srcs}")
message( "dir = ${VTK_PREFIX_PATH}")
message( "libs = ${VTK_LIBRARIES}")

install(IMPORTED_RUNTIME_ARTIFACTS 
        Qt6::Widgets 
        VTK::CommonCore 
        VTK::GUISupportQt 
        VTK::CommonColor 
        VTK::IOGeometry 
        # remainng libraries are dependencies of the above (but can't work out how to automatically install them)
        VTK::RenderingOpenGL2 
        #Qt6::Gui 
        #Qt6::Core 
        VTK::RenderingCore 
        VTK::FiltersSources 
        VTK::FiltersGeneral 
        VTK::FiltersCore 
        VTK::CommonExecutionModel
        VTK::CommonTransforms 
        VTK::InteractionWidgets 
        VTK::InteractionStyle 
        VTK::jsoncpp 
        VTK::FiltersHybrid 
        VTK::IOImage 
        VTK::IOCore
        VTK::GUISupportQt
        VTK::IOGeometry
        VTK::RenderingOpenGL2
        VTK::RenderingCore
        VTK::CommonColor
        VTK::FiltersSources
        VTK::FiltersGeneral
        VTK::FiltersCore
        VTK::CommonExecutionModel
        VTK::CommonDataModel
        VTK::CommonTransforms
        VTK::CommonCore
        VTK::InteractionWidgets
        VTK::InteractionStyle
        #Qt6::OpenGLWidgets
        VTK::FiltersExtraction
        VTK::CommonSystem
        #Qt6::OpenGL
        VTK::RenderingContext2D
        VTK::FiltersHybrid
        VTK::FiltersModeling
        VTK::FiltersTexture
        VTK::ImagingGeneral
        VTK::ImagingHybrid
        VTK::RenderingAnnotation
        VTK::RenderingFreeType
        VTK::CommonComputationalGeometry
        VTK::ImagingCore
        VTK::CommonMath
        VTK::ImagingSources
        VTK::FiltersGeometry
        VTK::vtksys
        VTK::CommonMisc
        VTK::ImagingColor
        VTK::freetype
        VTK::zlib
        VTK::kissfft
        VTK::FiltersStatistics
        VTK::ParallelDIY
        VTK::ParallelCore
        VTK::IOXML
        VTK::IOXMLParser
        VTK::IOCore
        VTK::expat
        VTK::doubleconversion
        VTK::lz4
        VTK::lzma
        VTK::IOLegacy
        VTK::jsoncpp
        VTK::IOImage
        VTK::DICOMParser
        VTK::metaio
        VTK::png
        VTK::tiff
        VTK::pugixml
        VTK::jpeg
        VTK::RenderingUI
        VTK::glew
        VTK::fmt
        VTK::loguru
        RUNTIME_DEPENDENCY_SET thirdPartyLibs
        DESTINATION bin)

install(TARGETS Worksheet_6_Exercise_3 LibsModule 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)