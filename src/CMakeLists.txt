# src

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd")

add_executable(Calc
    main.cpp
    gui/initializeCalc.cpp
    gui/Calc.cpp
    gui/Calc.h
    gui/Calc.ui
    gui/scientificCalc.cpp
    gui/Settings.cpp
    gui/Settings.h
    gui/Settings.ui
    core/core.h    
    core/core.cpp
    core/utility.h
    core/utility.cpp)

target_link_libraries(Calc PRIVATE
    Qt5::Widgets
)
