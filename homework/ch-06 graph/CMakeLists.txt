project(ch06)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++11 -O2  ${CMAKE_CXX_FLAGS}")

add_executable(test_ArrayGraph ArrayGraph.cc)
add_executable(test_UnionFind UnionFind.cc)
