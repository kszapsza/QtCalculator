# tst

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")

add_executable(Calc_tst 
	tests.cpp
    ../src/gui/initializeCalc.cpp
    ../src/gui/Calc.cpp
    ../src/gui/Calc.h
    ../src/gui/Calc.ui
    ../src/gui/scientificCalc.cpp
    ../src/gui/Settings.cpp
    ../src/gui/Settings.h
    ../src/gui/Settings.ui
)
target_link_libraries(Calc_tst PRIVATE ${SRC} gtest Qt5::Widgets)