/** 20210515 12:54, zyj, GuangDong*/
//test.c -- test bithrtree.h
#include <iostream>
#include <iomanip>
#include <string>
#include "bithrtree.h"

using std::cout;
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
	bithrtree<int> tree;
	tree.preinorder_construct(preorder, inorder, 5);
	cout << "preorder show : ";
	tree.preorder_traverse(show<int>());
	cout << "inorder show : ";
	tree.inorder_traverse(show<int>());
	cout << "inorderx show : ";
	tree.inorder_traversex(show<int>());
	
	SEP("threading");
	tree.inorder_threading();
	cout << "inorder threading traverse : ";
	tree.inorder_thrtraverse();
	return 0;
}
