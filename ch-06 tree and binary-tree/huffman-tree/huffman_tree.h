/** 20210721 21:15, zyj, GuangDong*/
//huffman_tree.h -- huffman tree
#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H
#include <iostream>
#include "sqstack.h"
using std::cout;
using std::endl;
template <typename Data>
class huffman_tree
{
	private:
		struct Node
		{
			unsigned weigth;
			int parent, lchild, rchild;
			friend()
		}
	public:
		typedef Node<Data> node;
	private:
		node *_root;
		int *_ct;//node count
	public:
		huffman_tree() : _root(nullptr), _ct(0){}
		huffman_tree(Data * codes, int n, unsigned * weigths, int m);
};
#endif
