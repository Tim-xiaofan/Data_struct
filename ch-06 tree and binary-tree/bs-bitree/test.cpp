/** 20210911, zyj GuangDong*/
#include <iostream>
#include "bs_bitree.h"

struct A
{
	int i;
};

struct B:public A
{
	using A::i;
};

struct C:public B
{
	using B::i;
};


template<typename Tree>
void
show_tree(Tree & tree)
{
	cout << "preorder_traverse : ";
	tree.preorder_traverse();

    cout << "inorder_traverse  : ";
	tree.inorder_traverse();

    cout << "level_traverse    : ";
	tree.level_traverse();
}

static void
test_bs(void)
{
	const int size  = 9;
	int table[size] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	bs_bitree<int> tree;
	tree.bs_construct(table, size);
	show_tree(tree);
	tree.show_edges();
}

int main(int ac, char * av[])
{
	struct C c;
	c.i = 9;
	std::cout << "c.i = " << c.i << std::endl;
	test_bs();
	return 0; 
}
