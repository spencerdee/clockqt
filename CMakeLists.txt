cmake_minimum_required(VERSION 3.5)

project(clockqt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_EXE_DIR "${CMAKE_SOURCE_DIR}/build/Debug")

if (UNIX)
    set(QT_VERSION_MAJOR 5)
elseif(WIN32)
    set(QT_VERSION_MAJOR 6)
endif()

find_package(QT NAMES "Qt${QT_VERSION_MAJOR}" REQUIRED COMPONENTS Widgets)
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

add_executable(clockqt ${PROJECT_SOURCES})
target_link_libraries(clockqt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_compile_options(clockqt PRIVATE --std=c++17 -lstdc++fs)

set_target_properties(clockqt PROPERTIES
    ${BUNDLE_ID_OPTION}
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BUILD_EXE_DIR}
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

if (NOT DEFINED ENV{WEATHER_API_KEY})
    message(FATAL_ERROR "Please set the WEATHER_API_KEY environment variable.")
else()
    set(WEATHER_API_KEY $ENV{WEATHER_API_KEY})
endif()

file(COPY ${CMAKE_SOURCE_DIR}/resources/images DESTINATION ${CMAKE_BUILD_EXE_DIR}/)
configure_file(${CMAKE_SOURCE_DIR}/resources/api-keys.csv.in ${CMAKE_BUILD_EXE_DIR}/api-keys.csv @ONLY)

if(QT_VERSION_MAJOR EQUAL ${QT_VERSION})
    qt_finalize_executable(clockqt)
endif()

set(MAIN_CFLAGS)
get_target_property(MAIN_CFLAGS clockqt COMPILE_OPTIONS)
# also see: COMPILE_DEFINITIONS INCLUDE_DIRECTORIES
message("-- Target compiler flags are: ${MAIN_CFLAGS}")

# cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_C_COMPILER:FILEPATH="/usr/bin/gcc" -DCMAKE_CXX_COMPILER:FILEPATH="/usr/bin/g++" --no-warn-unused-cli -SC:"/home/pi/Desktop/Clock/clockqt" -Bc:"/home/pi/Desktop/Clock/clockqt/build"
# cmake --build /home/pi/Desktop/Clock/clockqt/build --config Debug --target clockqt -j 22 --
# cmake --build /home/pi/Desktop/Clock/clockqt/build --config Debug --target all
