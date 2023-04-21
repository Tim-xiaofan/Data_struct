project(ch05)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++14 -O2${CMAKE_CXX_FLAGS}")

add_executable(test_ParentArray ParentArray.cc)
add_executable(test_ChildSiblingNotaion ChildSiblingNotaion.cc)
