cmake_minimum_required(VERSION 3.5)

project(occQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# 如果采用非Qt Creator开发，需要通过告知Qt的安装路径，建议把Qt的安装路径设置到环境变量
# 例如：QT_DIR=C:/Qt/6.4.1/mingw_64
set(CMAKE_PREFIX_PATH $ENV{QT_DIR})

# 有些项目会动态生成头文件，项目中需要引入它，因此需要将output目录也include进来
# 等同于INCLUDE_DIRECTORY(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 设置自动生成ui.h文件
set(CMAKE_AUTOUIC ON)
# 设置自动生成moc文件
set(CMAKE_AUTOMOC ON)
# 设置自动处理.qrc文件
set(CMAKE_AUTORCC ON)

set(RCC_FILES occqt.qrc)

# find_package(OpenGL)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)

add_definitions(-DWNT)
set(CAS_ROOT "C:\\Program Files (x86)\\OCCT")
# set(CAS_INCLUDE_DIR ${CAS_ROOT}/inc)
# set(CAS_LIB_DIR ${CAS_ROOT}/win64/gcc/lib)
set(OpenCASCADE_DIR ${CAS_ROOT}/cmake)
find_package(OpenCASCADE REQUIRED)


include_directories(${OpenCASCADE_INCLUDE_DIR})
# link_directories(${CAS_LIB_DIR})

set(PROJECT_SOURCES
        main.cpp
        occQt.cpp
        occQt.h
        occView.cpp
        occView.h
        occQt.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(occQT
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${RCC_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET occQT APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(occQT SHARED
            ${PROJECT_SOURCES}
            ${RCC_FILES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(occQT
            ${PROJECT_SOURCES}
            ${RCC_FILES}
        )
    endif()
endif()

target_link_libraries(
    occQT PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets 
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets 
    ${OpenCASCADE_LIBRARIES}
)

set_target_properties(occQT PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS occQT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(occQT)
endif()
