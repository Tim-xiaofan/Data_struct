/** 20210908 21:28, zyj, GuangDong*/
//test.c -- test dynamic_search.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "sorted_bitree.h"

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

template <typename T>
void show_array(const T * a, int size)
{
	int i;
	for(i = 0; i < size; ++i)
	  cout << a[i] << " ";
	cout << endl;
}

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

//#define BST 1
#ifdef BST

static void
test_BST(void)
{
	const int size = 9;
	int i, d, table[size] = {45, 24, 53, 45, 12, 24, 90, 28, 27};
	sorted_bitree<int> tree;

	cout << "table             : ";
	show_array(table, size);

	tree.sorted_construct(table, size);
	show_tree(tree);

	cout << "node_num          : " << tree.node_num() << endl;
	cout << "levels            : ";
	for(i = 0; i < size; ++i)
	  cout << "("<< table[i] << ", level=" << tree.get_level(table[i]) << ")";
	cout << endl;

	cout << "new node : ";
	cin >> d;
	if(tree.sorted_insert(d))
	{
		show_tree(tree);
		cout << "levels            :";
		for(i = 0; i < size; ++i)
		  cout << "(" << table[i] << ", level=" << tree.get_level(table[i]) << ")";
		cout <<"(" <<d << ", l=" << tree.get_level(d) << ")";
		cout << endl;
	}
	cout << "search node : ";
	cin >> d;
	if(tree.sorted_search(d))
	  cout << "found" << endl;
	else
	  cout << "not found" << endl;

	cout << "delete node : ";
	cin >> d;
	if(tree.sorted_delete(d))
	{
		show_tree(tree);
	}
}
#endif

//#define EDGE 1
#ifdef EDGE
static void 
test_edge(void)
{
	const int size = 10;
	int ret, table[size] = {45, 24, 53, 45, 12, 24, 90, 28, 27, 49};
	sorted_bitree<int> tree;
	sorted_bitree<int>::edge E[size]; 

	cout << "table             : ";
	show_array(table, size);

	tree.sorted_construct(table, size);
	show_tree(tree);
	ret = tree.get_edges(E, size);
	cout << "edges             : ";
	show_array(E, ret);
	tree.show_edges();
}
#endif

#define BASE 1
#ifdef BASE
template <typename Data>
struct show
{
    void operator()(const Data & a) const {cout << a <<" ";}
};

int elements[5]={2,4,5,1,3};
int preorder[5] = {3,9,20,15,7};
int inorder[5] = {9,3,15,20,7};
char preorder1[12] = "-+a*b-cd/ef";
char inorder1[12] = "a+b*c-d-e/f";

#define SEP(info) cout << "-----------" << (info) << "-----------\n"
static void test_base(void)
{
	SEP("int");
	bitree<int> tree;
	tree.preinorder_construct(preorder, inorder, 5);
	cout << "after creating from preorder-inorder : \n";
	cout << "preorder show : ";
	tree.preorder_traverse(show<int>());
	cout << "inorder show : ";
	tree.inorder_traverse(show<int>());
	cout << "inorderx show : ";
	tree.inorder_traversex(show<int>());

	SEP("char:cannot work with repeated data");
	bitree<char> tree1;
	tree1.preinorder_construct(preorder1, inorder1, 12);
	cout << "preorder show(bad) : ";
	tree1.preorder_traverse();
	cout << "inorder show(bad) : ";
	tree1.inorder_traverse();
	cout << "inorderx show : ";
	tree1.inorder_traversex();

	int n;
	cout << "number of vexs : ";
	cin >> n;
	cout << "bumber of different trees : " << bitree<int>::count(n) << endl;
}
#endif

int main(int ac, char * av[])
{
#ifdef BST
	test_BST();
#endif
#ifdef EDGE
	test_edge();
#endif
#ifdef BASE
	test_base();
#endif 
	return 0;
}
