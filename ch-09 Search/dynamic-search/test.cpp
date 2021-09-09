/** 20210908 21:28, zyj, GuangDong*/
//test.c -- test dynamic_search.h
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "bitree.h"

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

#define BST 1
#ifdef BST
template<typename Tree>
static void 
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
test_BST(void)
{
	const int size = 9;
	int i, d, table[size] = {45, 24, 53, 45, 12, 24, 90, 28, 27};
	bitree<int> tree;

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

int main(int ac, char * av[])
{
#ifdef BST
	test_BST();
#endif
	return 0;
}
