# tst

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd")

add_executable(Calc_tst 
	tests.cpp
	tests_systems.cpp
    ../src/gui/initializeCalc.cpp
    ../src/gui/Calc.cpp
    ../src/gui/Calc.h
    ../src/gui/Calc.ui
    ../src/gui/scientificCalc.cpp
    ../src/gui/Settings.cpp
    ../src/gui/Settings.h
    ../src/gui/Settings.ui
    ../src/core/core.cpp
    ../src/core/core.h
    ../src/core/utility.h
    ../src/core/utility.cpp
	../src/core/systems.cpp
	../src/core/systems.h)

target_link_libraries(Calc_tst PRIVATE ${SRC} gtest Qt6::Widgets)