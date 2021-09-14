/** 20210914, zyj, GuangDong*/
//test.cpp --test double link  tree

#include <iostream>
#include "dl_tree.h"

int main(int ac, char * av[])
{
	const char * str = "012";
	dl_tree<char> tree;
	tree.search(str, 4);
    return 0;
}
