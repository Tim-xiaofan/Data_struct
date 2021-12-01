/** 20210721 21:27, zyj, GuangDong*/
//test.c -- test huffman_tree
#include <iostream>
#include <iomanip>
#include <cstring>
#include "huffman_tree.h"

using std::cout;
using std::endl;
static const int N =  7;
static char chs[N] =  {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
static float w[N] = {3, 12, 7, 4, 2, 8, 11};
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
