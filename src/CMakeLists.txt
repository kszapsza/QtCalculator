# src

set(CMAKE_PREFIX_PATH "D:\\Qt\\6.0.0\\msvc2019_64")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd")

add_executable(Calc
    main.cpp
    core/bitwise.cpp
    core/bitwise.h
    core/core.cpp
    core/core.h
    core/data.h
    core/enums.h
    core/systems.cpp
    core/systems.h
    core/utility.cpp
    core/utility.h
    gui/Calc.cpp
    gui/Calc.h
    gui/Calc.ui
    gui/Settings.cpp
    gui/Settings.h
    gui/Settings.ui
    gui/initializeCalc.cpp
    gui/programmerCalc.cpp
    gui/scientificCalc.cpp)

target_link_libraries(Calc PRIVATE
    Qt6::Widgets
)
