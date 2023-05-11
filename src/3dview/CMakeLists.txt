cmake_minimum_required(VERSION 3.5)

project(3D_Viewer VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
find_library(
            viewer_lib 
            NAMES libs21_viewer s21_viewer 
            HINTS "${CMAKE_SOURCE_DIR}"
            #HINTS "/Users/donnette/project/calc/src/calc/"
            #NO_DEFAULT_PATH
)
message(STATUS "LIB_LOCATION : ${viewer_lib}")
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        status.cpp
        status.h
        status.ui
        glwidget.h
        glwidget.cpp
        ./QtGifImage/src/3rdParty/giflib/gif_err.c
        ./QtGifImage/src/3rdParty/giflib/dgif_lib.c
        ./QtGifImage/src/3rdParty/giflib/egif_lib.c 
        ./QtGifImage/src/3rdParty/giflib/gif_hash.c 
        ./QtGifImage/src/3rdParty/giflib/gifalloc.c 
        ./QtGifImage/src/3rdParty/giflib/quantize.c 
        ./QtGifImage/src/gifimage/qgifimage.cpp  
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
  qt_add_executable(3D_Viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3dview APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
      add_library(3D_Viewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
      add_executable(3D_Viewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3D_Viewer PRIVATE ${viewer_lib})

target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)


set_target_properties(3D_Viewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
  qt_finalize_executable(3D_Viewer)
endif()
