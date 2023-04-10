project(ch3)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++11 -g ${CMAKE_CXX_FLAGS}")

add_executable(test_DeStack test_DeStack.cc)
