# src

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")

add_executable(Calc
    main.cpp
    initializeCalc.cpp
    Calc.cpp
    Calc.h
    Calc.ui
    scientificCalc.cpp
    Settings.cpp
    Settings.h
    Settings.ui
)

target_link_libraries(Calc PRIVATE
    Qt5::Widgets
)
