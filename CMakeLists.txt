cmake_minimum_required(VERSION 3.5)

project(clockqt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_EXE_DIR "${CMAKE_SOURCE_DIR}/build/Debug")

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        src/MainWindow/mainwindow.ui
        src/MainWindow/mainwindow.cpp
        src/MainWindow/mainwindow.h
        src/ClockPage/clockpage.ui
        src/ClockPage/clockpage.cpp
        src/ClockPage/clockpage.h
        src/TickerPage/tickerpage.cpp
        src/TickerPage/tickerpage.h
        src/TickerPage/tickerpage.ui
        src/AlarmPage/alarmpage.cpp
        src/AlarmPage/alarmpage.h
        src/AlarmPage/alarmpage.ui
        src/MenuPage/menupage.cpp
        src/MenuPage/menupage.h
        src/MenuPage/menupage.ui
        src/BackgroundPage/backgroundpage.cpp
        src/BackgroundPage/backgroundpage.h
        src/BackgroundPage/backgroundpage.ui

        src/Common/common.h
        src/Common/common.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(clockqt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET clockqt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

# else()
#     if(ANDROID)
#         add_library(clockqt SHARED
#             ${PROJECT_SOURCES}
#         )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#     else()
#         add_executable(clockqt
#             ${PROJECT_SOURCES}
#         )
#     endif()
endif()

target_link_libraries(clockqt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.clockqt)
endif()
set_target_properties(clockqt PROPERTIES
    ${BUNDLE_ID_OPTION}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_EXE_DIR}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
target_include_directories(clockqt PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ClockPage
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TickerPage
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AlarmPage
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MenuPage
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Common
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BackgroundPage
)

# changed runtime and library destination from
# CMAKE_INSTALL_LIBDIR
# CMAKE_INSTALL_BINDIR
# to executable directory
install(TARGETS clockqt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_BUILD_EXE_DIR}
    RUNTIME DESTINATION ${CMAKE_BUILD_EXE_DIR}
)

message(STATUS ${CMAKE_BUILD_EXE_DIR})

file(COPY ${CMAKE_SOURCE_DIR}/src/images DESTINATION ${CMAKE_BUILD_EXE_DIR}/)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(clockqt)
endif()
