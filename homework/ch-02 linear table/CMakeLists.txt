project(ch2)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++11 -g ${CMAKE_CXX_FLAGS}")

add_executable(test_merge test_merge.cc list.cc)
add_executable(test_mix test_mix.cc list.cc)
add_executable(test_difference test_difference.cc list.cc)
add_executable(test_partition test_partition.cc list.cc)
add_executable(test_reverse test_reverse.cc list.cc)
add_executable(test_delete test_delete.cc list.cc)
