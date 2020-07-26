cmake_minimum_required(VERSION 3.5)

project(test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(Calc
    src/main.cpp
    src/initializeCalc.cpp
    src/Calc.cpp
    src/Calc.h
    src/Calc.ui
    src/scientificCalc.cpp
    src/Settings.cpp
    src/Settings.h
    src/Settings.ui)

target_link_libraries(Calc PRIVATE Qt5::Widgets)
