project(ch04)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++11 -g ${CMAKE_CXX_FLAGS}")

add_executable(test_AllDifferent AllDifferent.cc)
add_executable(test_DividePositiveNegative DividePositiveNegative.cc)
add_executable(test_RecursionReverseString RecursionReverseString.cc)
