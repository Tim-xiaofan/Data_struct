/** 20210415 12:52, zyj, GuangDong*/
//test.c -- test bitree.h
#include <iostream>
#include <iomanip>
#include <string>
#include "bitree.h"

using std::cout;
using std::endl;

struct G
{
    void operator()(char a) const {cout << a <<" functor\n";}
};

void f(char a) {cout << a <<" funtion \n";}
void show(int a) {cout << a << " ";}

int elements[5]={2,4,5,1,3};

int main()
{
	bitree<int> tree;
	tree.cmp_construct(elements, 5);
	cout << "preorder show : ";
	tree.preorder_traverse(show);
	return 0;
}
