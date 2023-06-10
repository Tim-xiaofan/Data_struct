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

		// test insert
		{//exist
			auto ret = root->insert('A');
			assert(!ret.first);
			assert(ret.second->data == 'A');
		}
		{//not exist
			auto ret = root->insert('A'-1);
			assert(ret.first);
			assert(ret.second->data == 'A'-1);
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

		// test insert
		{//exist
			auto ret = root->insert('A');
			assert(!ret.first);
			assert(ret.second->data == 'A');
		}
		{//not exist
			auto ret = root->insert('A'-1);
			assert(ret.first);
			assert(ret.second->data == 'A'-1);
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

	//test insert
	{//create a new BST by performing insertion operation
		std::vector<int> table= {45,24,53,45,12,24,90};
		BinaryTree<int> root(new BinaryTreeNode<int>(45));
		for(size_t i = 1; i < table.size(); ++i)
		{
			auto ret = root->insert(table[i]);
			assert(ret.second->data == table[i]);
		}
		BinaryTree<int> expected(new BinaryTreeNode<int>(45));
		expected->addLchild(24);
		expected->lchild->addLchild(12);
		expected->addRchild(53);
		expected->rchild->addRchild(90);
		assert(root->same(*expected));
	}

	//test delete
	{//case1: p has lchild and rchild and q == p and s does't have rchild
		BinaryTree<int> root(new BinaryTreeNode<int>(3));
		root->addLchild(1);
		root->lchild->addLchild(0);
		root->lchild->addRchild(2);
		root->addRchild(5);
		root->rchild->addLchild(4);
		root->rchild->addRchild(6);

		root->delete_(1);

		BinaryTree<int> expected(new BinaryTreeNode<int>(3));
		expected->addLchild(0);
		expected->lchild->addRchild(2);
		expected->addRchild(5);
		expected->rchild->addLchild(4);
		expected->rchild->addRchild(6);

		assert(root->same(*expected));
	}
	{//case2: p has lchild and rchild and q == p and s does have rchild
		BinaryTree<int> root(new BinaryTreeNode<int>(3));
		root->addLchild(1);
		root->lchild->addLchild(0);
		root->lchild->lchild->addLchild(-1);
		root->lchild->addRchild(2);
		root->addRchild(5);
		root->rchild->addLchild(4);
		root->rchild->addRchild(6);

		root->delete_(1);

		BinaryTree<int> expected(new BinaryTreeNode<int>(3));
		expected->addLchild(0);
		expected->lchild->addLchild(-1);
		expected->lchild->addRchild(2);
		expected->addRchild(5);
		expected->rchild->addLchild(4);
		expected->rchild->addRchild(6);

		assert(root->same(*expected));
	}
	{//case3: p has lchild and rchild and q != p and s does not have rchild
		BinaryTree<int> root(new BinaryTreeNode<int>(4));
		root->addLchild(2);
		root->lchild->addLchild(0);
		root->lchild->addRchild(3);
		root->lchild->lchild->addRchild(1);
		root->addRchild(6);
		root->rchild->addLchild(5);
		root->rchild->addRchild(7);
		root->delete_(2);
		BinaryTree<int> expected(new BinaryTreeNode<int>(4));
		expected->addLchild(1);
		expected->lchild->addLchild(0);
		expected->lchild->addRchild(3);
		expected->addRchild(6);
		expected->rchild->addLchild(5);
		expected->rchild->addRchild(7);
		assert(root->same(*expected));
	}
	{//case4: p has lchild and rchild and q != p and s does have rchild
		BinaryTree<int> root(new BinaryTreeNode<int>(5));
		root->addLchild(3);
		root->lchild->addLchild(0);
		root->lchild->addRchild(4);
		root->lchild->lchild->addRchild(2);
		root->lchild->lchild->rchild->addLchild(1);
		root->addRchild(6);
		root->rchild->addLchild(5);
		root->rchild->addRchild(7);

		root->delete_(3);

		BinaryTree<int> expected(new BinaryTreeNode<int>(5));
		expected->addLchild(2);
		expected->lchild->addLchild(0);
		expected->lchild->addRchild(4);
		expected->lchild->lchild->addRchild(1);
		expected->addRchild(7);
		expected->rchild->addLchild(6);
		expected->rchild->addRchild(8);

		assert(root->same(*expected));
	}
	{//case 5: leaf node
		BinaryTree<int> root(new BinaryTreeNode<int>(1));
		root->addLchild(0);
		root->addRchild(1);

		root->delete_(1);

		BinaryTree<int> expected(new BinaryTreeNode<int>(5));
		expected->addRchild(1);
		
		assert(root->same(*expected));
	}
	{//case 6: only lchild
		BinaryTree<int> root(new BinaryTreeNode<int>(2));
		root->addLchild(1);
		root->addRchild(3);
		root->lchild->addLchild(0);

		assert(root->delete_(1));

		BinaryTree<int> expected(new BinaryTreeNode<int>(2));
		expected->addLchild(0);
		expected->addRchild(3);
		
		assert(root->same(*expected));
	}

	{//case 7: only rchild
		BinaryTree<int> root(new BinaryTreeNode<int>(2));
		root->addLchild(1);
		root->addRchild(3);
		root->lchild->addLchild(0);
		root->rchild->addRchild(5);
		root->rchild->rchild->addLchild(4);
		root->rchild->rchild->addRchild(6);

		assert(root->delete_(3));

		BinaryTree<int> expected(new BinaryTreeNode<int>(2));
		expected->addLchild(1);
		expected->lchild->addLchild(0);
		expected->addRchild(5);
		expected->rchild->addLchild(4);
		expected->rchild->addRchild(6);
		
		assert(root->same(*expected));
	}
	std::cout << "All test passed\n";
	return 0;
}
