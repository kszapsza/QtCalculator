# src

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")

add_executable(Calc
    "main.cpp"
    gui/initializeCalc.cpp
    gui/Calc.cpp
    gui/Calc.h
    gui/Calc.ui
    gui/scientificCalc.cpp
    gui/Settings.cpp
    gui/Settings.h
    gui/Settings.ui
    "log/basicCore.h"
    "log/scientificCore.h" "log/basicCore.cpp")

target_link_libraries(Calc PRIVATE
    Qt5::Widgets
)
