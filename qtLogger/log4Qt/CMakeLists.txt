cmake_minimum_required(VERSION 3.14)

project(log4qt LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_definitions(-DLOG4QT_STATIC)

include_directories("C:/Users/Jerry/Documents/QtProjects/Log4Qt/src")
link_directories("C:/Users/Jerry/Documents/QtProjects/Log4Qt/build/src/log4qt/Debug")
#link_directories("C:/Users/Jerry/Documents/QtProjects/Log4Qt/build/src/log4qt/Release")

add_executable(${PROJECT_NAME}
    main.cpp
    loggerobject.cpp
    loggerobject.h
    loggerobjectprio.cpp
    loggerobjectprio.h
    loggerstatic.cpp
    loggerstatic.h
)
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(${PROJECT_NAME} log4qt_d.lib)
#target_link_libraries(${PROJECT_NAME} log4qt.lib)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
