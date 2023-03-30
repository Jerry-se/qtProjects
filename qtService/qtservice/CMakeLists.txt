cmake_minimum_required(VERSION 3.14)

project(qtService LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(PROJECT_SOURCES
    qtservice.h qtservice_p.h qtservice.cpp
)

if (WIN32)
    set(PLATFORM_SOURCES qtservice_win.cpp)
else()
    set(PLATFORM_SOURCES
        qtservice_unix.cpp
        qtunixsocket.h qtunixsocket.cpp
        qtunixserversocket.h qtunixserversocket.cpp
    )
endif()

add_library(${PROJECT_NAME} ${PROJECT_SOURCES} ${PLATFORM_SOURCES})
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} -luser32)
endif()
