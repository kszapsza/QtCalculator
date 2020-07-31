# tst

set(CMAKE_PREFIX_PATH "D:\\Qt\\5.9.9\\msvc2017_64\\bin")

add_executable(Calc_tst tests.cpp)
target_link_libraries(Calc_tst PRIVATE gtest Qt5::Widgets)