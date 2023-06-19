project(ch06)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++14 -O2  ${CMAKE_CXX_FLAGS}")

add_executable(test_SequenceSeacrh SequenceSearch.cc)
add_executable(test_BinarySearch BinarySearch.cc)
add_executable(test_NearlyOptimalSearchTree NearlyOptimalSearchTree.cc)
add_executable(test_BinarySearchTree BinarySearchTree.cc)
add_executable(test_AVLTree AVLTree.cc)
add_executable(test_RedBlackTree RedBlackTree.cc)
add_executable(test_BTree BTree.cc)
