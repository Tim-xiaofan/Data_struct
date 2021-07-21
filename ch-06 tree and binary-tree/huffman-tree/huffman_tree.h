/** 20210721 21:15, zyj, GuangDong*/
//huffman_tree.h -- huffman tree
#ifndef _HUFFMAN_TREE_H
#define _HUFFMAN_TREE_H
#include <iostream>

using std::cout;
using std::endl;

template <typename Data>
class huffman_tree
{
	private:
		template <typename Data1>
		struct Node
		{
			unsigned weigth;
			int parent, lchild, rchild;
			friend std::ostream & operator<<(std::ostream & os, const struct Node nd)
			{
				os << "weigth = " <<nd.weigth << 
					", parent = " <<nd.parent << 
					", lchild = " <<nd.lchild << 
					", rchild = " <<nd.rchild << endl;
				return os;
			}
		};
	public:
		typedef Node<Data> node;
	private:
		node *_nds;//node array
		int _ct;//node count : 2n - 1
	public:
		huffman_tree() : _nds(nullptr), _ct(0){}
		huffman_tree(Data * codes, unsigned * weigths, int n);
};

template <typename Data>
huffman_tree<Data>::
huffman_tree(Data * codes, unsigned * weigths, int n)
{
	int i, j;

	_ct = 2 * n - 1;
	_nds = new node[_ct + 1];// 0号单元未使用

	/** 初始化节点数组*/
	for(i = 1, j = 0; i <=n && j < n; ++i, ++j)
	{//叶子节点
		_nds[i].weigth = weigths[i];
		_nds[i].parent = 0;
		_nds[i].lchild = 0;
		_nds[i].rchild = 0;
	}
	for(i = n + 1; i <= _ct; ++i)
	{//非叶子节点
		_nds[i].weigth = 0;
		_nds[i].parent = 0;
		_nds[i].lchild = 0;
		_nds[i].rchild = 0;
	}
}
#endif
