# tst

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

add_executable(Calc_tst 
	tests.cpp
    ../src/initializeCalc.cpp
    ../src/Calc.cpp
    ../src/Calc.h
    ../src/Calc.ui
    ../src/scientificCalc.cpp
    ../src/Settings.cpp
    ../src/Settings.h
    ../src/Settings.ui
)
target_link_libraries(Calc_tst PRIVATE ${SRC} gtest Qt5::Widgets)