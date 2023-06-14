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

	//test leftBalance
	{//case 1: LL
		AVLTree<int> A = new AVLTreeNode<int>(4, 2);
		AVLTree<int> B = A->addLchild(2, 1);
		B->addLchild(1, 1)->addLchild(0, 0);;
		B->addRchild(3, 0);
		A->addRchild(5, 0);

		leftBalance(A);

		AVLTree<int> expected = new AVLTreeNode<int>(2, 0);
		expected->addLchild(1, 1)->addLchild(0, 0);;
		expected->addRchild(4, 0)->addRchild(5, 0);;
		expected->rchild->addLchild(3, 0);

		assert(A->same(expected));
	}
	{//case 2: LR
		AVLTree<int> A = new AVLTreeNode<int>(4, 2);
		AVLTree<int> B = A->addLchild(1, -1);
		B->addLchild(0, 0);
		B->addRchild(3, 1)->addLchild(2, 0);
		A->addRchild(5, 0);

		leftBalance(A);

		AVLTree<int> expected = new AVLTreeNode<int>(3, 0);
		expected->addLchild(1, 0)->addLchild(0, 0);
		expected->lchild->addRchild(2, 0);
		expected->addRchild(4, -1)->addRchild(5, 0);

		assert(A->same(expected));
	}

	//test rightBalance
	{//case RR
		AVLTree<int> root = new AVLTreeNode<int>(1, -2);
		AVLTree<int> rchild = root->addRchild(3, -1);
		rchild->addRchild(4, -1)->addRchild(5, 0);
		rchild->addLchild(2, 0);
		root->addLchild(0, 0);

		rightBalance(root);

		AVLTree<int> expected = new AVLTreeNode<int>(3, 0);
		AVLTree<int> lchild = expected->addLchild(1, 0);
		lchild->addLchild(0, 0);
		lchild->addRchild(2, 0);
		expected->addRchild(4, -1)->addRchild(5, 0);

		assert(root->same(expected));
	}
	{//RL
		AVLTree<int> root = new AVLTreeNode<int>(1, -2);
		AVLTree<int> rchild = root->addRchild(4, 1);
		rchild->addLchild(3, 1)->addLchild(2, 0);
		rchild->addRchild(5, 0);
		root->addLchild(0, 0);

		rightBalance(root);

		AVLTree<int> expected = new AVLTreeNode<int>(3, 0);
		expected->addRchild(4, -1)->addRchild(5, 0);
		expected->addLchild(1, 0)->addLchild(0, 0);
		expected->lchild->addRchild(2, 0);

		assert(root->same(expected));
	}

	//test insert
	{
		AVLTree<int> root = nullptr;
		std::vector<int> table = {13, 24, 37, 90, 53};
		for(int i: table)
		{
			bool taller;
			assert(insert(root, i, taller));
		}

		AVLTree<int> expected = new AVLTreeNode<int>(24, -1);
		expected->addRchild(53, 0)->addRchild(90, 0);
		expected->rchild->addLchild(37, 0);
		expected->addLchild(13, 0);

		assert(root->same(expected));
	}

	std::cout << "All tests passed\n";
	return 0;
}
