project(ch07)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++14 -O3  ${CMAKE_CXX_FLAGS}")

add_executable(test_StraightInsertionSort StraightInsertionSort.cc)
add_executable(test_ShellSort ShellSort.cc)
add_executable(test_BubbleSort BubbleSort.cc)
add_executable(test_QuickSort QuickSort.cc)
add_executable(test_SimpleSelectionSort SimpleSelectionSort.cc)
add_executable(test_HeapSort HeapSort.cc)
add_executable(test_MergeSort MergeSort.cc)
