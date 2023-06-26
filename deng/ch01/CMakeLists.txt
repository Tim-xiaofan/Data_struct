project(ch07)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++14 -O3  ${CMAKE_CXX_FLAGS}")

add_executable(test_countOnes CountOnes.cc)
add_executable(test_ReverseArray ReverseArray.cc)
add_executable(test_Power2 Power2.cc)
add_executable(test_Fibonacci Fibonacci.cpp)
