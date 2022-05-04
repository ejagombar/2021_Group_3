
qt_finalize_executable(${PROJECT_BIN_NAME_})

set(COMPONENT_NAME_MAIN "${PROJECT_BIN_NAME_}")

include(GNUInstallDirs)
install(TARGETS ${PROJECT_BIN_NAME_} DESTINATION ${CMAKE_INSTALL_BINDIR}/.. COMPONENT ${COMPONENT_NAME_MAIN})

set(CPACK_GENERATOR "IFW")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR_}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR_}")
SET(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH_}")
SET(CPACK_PACKAGE_VERSION
    "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME_})
#SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_IFW_PACKAGE_NAME ${PROJECT_PKG_NAME_})
set(CPACK_IFW_PACKAGE_TITLE ${PROJECT_PKG_TITLE_})
set(CPACK_IFW_PACKAGE_PUBLISHER ${PROJECT_PKG_PUBLISHER_})
set(CPACK_IFW_PACKAGE_WIZARD_SHOW_PAGE_LIST OFF)
set(CPACK_RESOURCE_FILE_LICENSE ${PROJECT_LICENSE_FILE_})

get_filename_component(QT_BIN_ ${QT_QMAKE_EXECUTABLE} DIRECTORY)
install(FILES    
    ${VTK_bin}/vtkcgns-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkChartsCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonColor-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonComputationalGeometry-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonDataModel-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonExecutionModel-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonMath-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonMisc-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonSystem-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkCommonTransforms-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkDICOMParser-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkDomainsChemistry-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkDomainsChemistryOpenGL2-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkdoubleconversion-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkexodusII-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkexpat-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersAMR-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersExtraction-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersFlowPaths-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersGeneral-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersGeneric-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersGeometry-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersHybrid-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersHyperTree-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersImaging-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersModeling-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersParallel-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersParallelImaging-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersPoints-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersProgrammable-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersSelection-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersSMP-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersSources-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersStatistics-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersTexture-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersTopology-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkFiltersVerdict-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkfmt-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkfreetype-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkGeovisCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkgl2ps-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkglew-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkGUISupportQt-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkGUISupportQtQuick-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkGUISupportQtSQL-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkhdf5-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkhdf5_hl-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingColor-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingFourier-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingGeneral-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingHybrid-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingMath-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingMorphological-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingSources-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingStatistics-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkImagingStencil-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkInfovisCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkInfovisLayout-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkInteractionImage-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkInteractionStyle-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkInteractionWidgets-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOAMR-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOAsynchronous-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOCGNSReader-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOChemistry-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOCityGML-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOCONVERGECFD-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOEnSight-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOExodus-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOExport-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOExportGL2PS-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOExportPDF-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOGeometry-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOHDF-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOImage-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOImport-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOInfovis-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOIOSS-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOLegacy-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOLSDyna-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOMINC-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOMotionFX-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOMovie-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIONetCDF-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOOggTheora-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOParallel-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOParallelXML-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOPLY-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOSegY-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOSQL-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkioss-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOTecplotTable-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOVeraOut-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOVideo-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOXML-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkIOXMLParser-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkjpeg-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkjsoncpp-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkkissfft-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtklibharu-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtklibproj-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtklibxml2-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkloguru-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtklz4-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtklzma-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkmetaio-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtknetcdf-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkogg-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkParallelCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkParallelDIY-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkpng-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkpugixml-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingAnnotation-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingContext2D-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingContextOpenGL2-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingFreeType-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingGL2PSOpenGL2-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingImage-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingLabel-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingLOD-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingOpenGL2-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingQt-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingSceneGraph-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingUI-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingVolume-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingVolumeOpenGL2-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkRenderingVtkJS-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtksqlite-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtksys-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkTestingRendering-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtktheora-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtktiff-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkverdict-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkViewsContext2D-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkViewsCore-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkViewsInfovis-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkViewsQt-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkWrappingTools-9.1${BUID_MODE_DLL_}
    ${VTK_bin}/vtkzlib-9.1${BUID_MODE_DLL_}
    ${QT_BIN_}/Qt6OpenGLWidgets${BUID_MODE_DLL_}
    ${QT_BIN_}/Qt6OpenGL${BUID_MODE_DLL_}
    ${CMAKE_CURRENT_SOURCE_DIR}/ucrtbase${BUID_MODE_DLL_}
    DESTINATION ${CMAKE_INSTALL_BINDIR}/..)
#include(InstallRequiredSystemLibraries)

if(WIN32)
find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake.in" "${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake" @ONLY)
set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake)
endif()

include(CPack)
include(CPackIFW)

CPACK_ADD_COMPONENT(${COMPONENT_NAME_MAIN})

# The component HAS to be installed
cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} ESSENTIAL FORCED_INSTALLATION)

# Adds license info to package.xml file
# Also copies licence 'meta' directory to display the license text in the installer.
cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} LICENSES "ICS License" ${CPACK_RESOURCE_FILE_LICENSE})


