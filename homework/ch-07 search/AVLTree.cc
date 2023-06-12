#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <memory>
#include <cmath>
#include <limits>
#include "AVLTree.h"

template <typename T>
bool operator==(const std::vector<T>& a, const std::vector<T>& b) {
	if (a.size() != b.size()) {
		return false;
	}

	for (size_t i = 0; i < a.size(); ++i) {
		if (!areEqual(a[i], b[i])) {
			return false;
		}
	}

	return true;
}

int main(void)
{
	//test rightRotate
	{
		AVLTree<int> root = new AVLTreeNode<int>(3);
		AVLTree<int> lchild = root->addLchild(1);
		lchild->addLchild(0);
		lchild->addRchild(2);
		root->addRchild(4);

		rightRotate(root);

		AVLTree<int> expected = new AVLTreeNode<int>(1);
		expected->addLchild(0);
		AVLTree<int> rchild = expected->addRchild(3);
		rchild->addLchild(2);
		rchild->addRchild(4);

		assert(root->same(expected));
	}

	//test leftRotate
	{
		AVLTree<int> root = new AVLTreeNode<int>(1);
		AVLTree<int> rchild = root->addRchild(3);
		rchild->addLchild(2);
		rchild->addRchild(4);
		root->addLchild(0);

		leftRotate(root);

		AVLTree<int> expected = new AVLTreeNode<int>(3);
		AVLTree<int> lchild = expected->addLchild(1);
		lchild->addLchild(0);
		lchild->addRchild(2);
		expected->addRchild(4);
		assert(root->same(expected));
	}

	std::cout << "All tests passed\n";
	return 0;
}
