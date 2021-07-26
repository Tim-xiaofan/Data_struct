/** 20210721 21:27, zyj, GuangDong*/
//test.c -- test huffman_tree
#include <iostream>
#include <iomanip>
#include <cstring>
#include "power_set.h"
#include "List.h"

using std::cout;
using std::endl;

int main(int ac, char * av[])
{
	List<int> set(3);
	set.append(0);
	set.append(1);
	set.append(2);
	cout << "set : ";set.show();

	power_set<int> pset(set);
	return 0;
}
