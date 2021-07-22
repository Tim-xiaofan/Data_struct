/** 20210721 21:27, zyj, GuangDong*/
//test.c -- test huffman_tree
#include <iostream>
#include <iomanip>
#include <string>
#include "huffman_tree.h"

using std::cout;
using std::endl;
static char chs[8] =  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
static float w[8] = {0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};

int main(int ac, char * av[])
{
	huffman_tree<char> tree(chs, w, 8);
	tree.print_nds();
	tree.print_codes();
	return 0;
}
