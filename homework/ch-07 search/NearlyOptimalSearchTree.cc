#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <memory>
#include <cmath>
#include <limits>
#include  "BinaryTree.h"



template<typename SequenceContainer>
void createNearlyOptimalSearchTree(const SequenceContainer& table, std::vector<double> sw, int low, int high, BinaryTree<typename SequenceContainer::value_type>& t)
{//O(nlogn)
	// get minimum deltaP
	double mini = low;
	double min = std::abs((sw[high] /**+ sw[low-1]*/) - (sw[low] /*+ sw[low-1]*/));
	double dw = sw[high] + ((low)?sw[low-1]:0);
	for(int i =  low + 1; i <= high; ++i)
	{
		double deltaP = std::abs(dw - (sw[i] + sw[i-1]));
		if(deltaP < min)
		{
			min = deltaP;
			mini = i;
		}
	}

	t = std::make_shared<BinaryTreeNode<typename SequenceContainer::value_type>>(table[mini]);
	assert(mini >= low);
	if(mini > low)
	{
		createNearlyOptimalSearchTree(table, sw, low, mini - 1, t->lchild);
	}

	assert(mini <= high);
	if(mini < high)
	{
		createNearlyOptimalSearchTree(table, sw, mini + 1, high, t->rchild);
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	os << "[";
	for (size_t i = 0; i < vec.size(); ++i) {
		os << vec[i];
		if (i != vec.size() - 1) {
			os << ", ";
		}
	}
	os << "]";
	return os;
}

template <typename T>
bool areEqual(const T& a, const T& b, const T& epsilon = std::numeric_limits<T>::epsilon()) {
	return std::abs(a - b) <= epsilon;
}

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
		std::vector<double> w = {1, 1, 2, 5, 3, 4, 4, 3, 5};
		std::vector<double> sw(w.size());
		sw[0] = w[0];
		for(int i = 1; i < static_cast<int>(sw.size()); ++i)
		{
			sw[i] = sw[i-1] + w[i];
		}
		assert(sw == decltype(sw)({1, 2, 4, 9, 12, 16, 20, 23, 28}));
		BinaryTree<char> t;
		createNearlyOptimalSearchTree(table, sw, 0, sw.size() - 1, t);
		BinaryTree<char> root(new BinaryTreeNode<char>('F'));
		root->addLchild('D');
		root->lchild->addRchild('E');
		root->lchild->addLchild('B');
		root->lchild->lchild->addLchild('A');
		root->lchild->lchild->addRchild('C');
		root->addRchild('H');
		root->rchild->addLchild('G');
		root->rchild->addRchild('I');
		assert(root->same(*t));
		for(char ch: table)
		{
			assert(t->search(ch));
		}
		assert(!t->search('x'));
	}
	{
		std::vector<char> table= {'A', 'B', 'C', 'D', 'E'};
		std::vector<double> w = {1, 30, 2, 29, 3};
		std::vector<double> sw(w.size());
		sw[0] = w[0];
		for(int i = 1; i < static_cast<int>(sw.size()); ++i)
		{
			sw[i] = sw[i-1] + w[i];
		}
		assert(sw == decltype(sw)({1, 31, 33, 62, 65}));
		BinaryTree<char> t;
		createNearlyOptimalSearchTree(table, sw, 0, sw.size() - 1, t);
		BinaryTree<char> root(new BinaryTreeNode<char>('C'));
		root->addLchild('B');
		root->lchild->addLchild('A');
		root->addRchild('D');
		root->rchild->addRchild('E');
		assert(root->same(*t));
		for(char ch: table)
		{
			assert(t->search(ch));
		}
		assert(!t->search('x'));
	}
	std::cout << "All test passed\n";
	return 0;
}
