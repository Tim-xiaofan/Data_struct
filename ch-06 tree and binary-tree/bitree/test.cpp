/** 20210415 12:52, zyj, GuangDong*/
//test.c -- test bitree.h
#include <iostream>
#include <iomanip>
#include <string>
#include "bitree.h"

using std::cout;
using std::cin;
using std::endl;

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

int main()
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
	return 0;
}
