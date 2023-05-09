project(ch05)

set(CMAKE_CXX_FLAGS "-Wall -Wshadow -std=c++14 -g ${CMAKE_CXX_FLAGS}")

add_executable(test_ParentArray ParentArray.cc)
add_executable(test_ChildSiblingNotaion ChildSiblingNotaion.cc)
add_executable(test_BinaryTree BinaryTree.cc)
add_executable(test_priority_queue priority_queue.cc)
add_executable(test_HuffmanTree HuffmanTree.cc)
add_executable(test_GetPowerSet GetPowerSet.cc)
add_executable(test_ThreadedBinaryTree ThreadedBinaryTree.cc)
