#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <memory>
#include <cmath>
#include <limits>
#include  "BinaryTree.h"


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
	{
		std::vector<char> table= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
		BinaryTree<char> root(new BinaryTreeNode<char>('F'));
		root->addLchild('D');
		root->lchild->addRchild('E');
		root->lchild->addLchild('B');
		root->lchild->lchild->addLchild('A');
		root->lchild->lchild->addRchild('C');
		root->addRchild('H');
		root->rchild->addLchild('G');
		root->rchild->addRchild('I');
		for(char ch: table)
		{
			auto ret = root->search(ch, nullptr);
			assert(ret.first);
		}
		{
			auto ret = root->search('J', nullptr);
			assert(!ret.first);
			assert(ret.second->data == 'I');
		}
		{
			auto ret = root->search('A' - 1, nullptr);
			assert(!ret.first);
			assert(ret.second->data == 'A');
		}
	}
	{
		std::vector<char> table= {'A', 'B', 'C', 'D', 'E'};
		BinaryTree<char> root(new BinaryTreeNode<char>('C'));
		root->addLchild('B');
		root->lchild->addLchild('A');
		root->addRchild('D');
		root->rchild->addRchild('E');
		for(char ch: table)
		{
			auto ret = root->search(ch, nullptr);
			assert(ret.first);
		}
		{
			auto ret = root->search('E' + 1, nullptr);
			assert(!ret.first);
			assert(ret.second->data == 'E');
		}
		{
			auto ret = root->search('A' - 1, nullptr);
			assert(!ret.first);
			assert(ret.second->data == 'A');
		}
	}
	{
		std::vector<char> table= {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'I', 'J'};
		BinaryTree<char> root(new BinaryTreeNode<char>('F'));
		root->addLchild('D');
		root->lchild->addRchild('E');
		root->lchild->addLchild('B');
		root->lchild->lchild->addLchild('A');
		root->lchild->lchild->addRchild('C');
		root->addRchild('I');
		root->rchild->addLchild('G');
		root->rchild->addRchild('J');
		for(char ch: table)
		{
			auto ret = root->search(ch, nullptr);
			assert(ret.first);
		}
		{
			auto ret = root->search('H', nullptr);
			assert(!ret.first);
			assert(ret.second->data == 'G');
		}
		{
			auto ret = root->search('A' - 1, nullptr);
			assert(!ret.first);
			assert(ret.second->data == 'A');
		}
	}
	{//one node
		std::vector<char> table= {'S'};
		BinaryTree<char> root(new BinaryTreeNode<char>('S'));
		for(char ch: table)
		{
			auto ret = root->search(ch, nullptr);
			assert(ret.first);
		}
		{
			auto ret = root->search('A', nullptr);
			assert(!ret.first);
			assert(ret.second->data == 'S');
		}
	}
	std::cout << "All test passed\n";
	return 0;
}
