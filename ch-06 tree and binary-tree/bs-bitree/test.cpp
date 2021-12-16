/** 20210911, zyj GuangDong*/
#include <iostream>
#include "bs_bitree.h"
#include <string>
#include <cstring>

using std::cin;

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

int compare(const string & a, const string & b)
{
    return strcmp(a.c_str(), b.c_str());
}

static void
test_bs(void)
{
    using std::string;
	const int size  = 9, size1  = 6;
	int table[size] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    int table1[size1] = {24, 37, 45, 53, 93, 12};
    string table2[12] = {"Jan", "Feb", "Mar", "Apr", "May", "June", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};
	bs_bitree<int> tree;
	bs_bitree<int> tree1;
	bs_bitree<string> tree2;

	tree.bs_construct(table, size);
	//show_tree(tree);
	tree.show_edges();
	
    tree1.bs_construct(table1, size1);
	//show_tree(tree1);
	tree1.show_edges();


    tree2.bs_construct(table2, 12, compare);
	//show_tree(tree1);
	tree2.show_edges();

    return;
    int d;
    cout << "node search : ";
    cin >> d;
    if(tree1.sorted_search(d))
        cout << "found\n";
    else 
      cout << "not found\n";
}

int main(int ac, char * av[])
{
	struct C c;
	c.i = 9;
	std::cout << "c.i = " << c.i << std::endl;
	test_bs();
	return 0; 
}
