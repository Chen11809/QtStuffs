cmake_minimum_required(VERSION 3.16)

project(QtSupport6Cmake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Quick
    3DCore
    3DRender
    3DInput
    3DLogic
    3DExtras
    3DAnimation
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appQtSupport6Cmake
    main.cpp
)

qt_add_qml_module(appQtSupport6Cmake
    URI QtSupport6Cmake
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES Heightmap.cpp Heightmap.h PointGrid.cpp PointGrid.h RoughnessCamera3DController.cpp RoughnessCamera3DController.h RoughnessGeometry.cpp RoughnessGeometry.h RoughnessTextureImage.cpp RoughnessTextureImage.h
    QML_FILES RenderEntity.qml RenderScene.qml RenderViewer.qml RoughnessMapMaterial.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQtSupport6Cmake PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQtSupport6Cmake
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set(resource_files
    "points.txt"
    "Images/textureWithHeatmapImage.png"
    "Shaders/gl3/roughnessMap.frag"
    "Shaders/gl3/roughnessMap.vert"
    "Shaders/gl45/roughnessMap.frag"
    "Shaders/gl45/roughnessMap.vert"
)

qt_add_resources(appQtSupport6Cmake
    "Resources"
    PREFIX "/"
    FILES ${resource_files}
)

target_link_libraries(appQtSupport6Cmake
    PRIVATE
    Qt6::Quick
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DLogic
    Qt6::3DExtras
    Qt6::3DAnimation
)

include(GNUInstallDirs)
install(TARGETS appQtSupport6Cmake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
