/** 20210721 21:27, zyj, GuangDong*/
//test.c -- test huffman_tree
#include <iostream>
#include <iomanip>
#include <cstring>
#include "huffman_tree.h"

using std::cout;
using std::endl;
static char chs[8] =  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
static float w[8] = {0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};
static const char *code = "01111011101111110010000001";
static const char *code1 = "11";
static char decode[32];

int main(int ac, char * av[])
{
	int olen = 32;
	huffman_tree<char> tree(chs, w, 8);
	tree.print_nds();
	tree.print_codes();
	tree.decode(code, strlen(code), decode, olen);
	decode[olen] = '\0';
	cout << "code : " << code << endl;
	cout << "decode : " << decode << endl;
	olen = 32;
	tree.decode(code1, strlen(code1), decode, olen);
	decode[olen] = '\0';
	cout << "code : " << code1 << endl;
	cout << "decode : " << decode << endl;
	return 0;
}
