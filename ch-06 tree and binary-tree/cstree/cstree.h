/** 20210415 12:45, zyj, GuangDong*/
// cstree.h -- child and sibling
#ifndef CSTREE_H
#define CSTREE_H
#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class cstree
{
	private:
		template <typename T1>
		struct Node
		{
			T1 data;
			struct Node * firstchild, *firstsibling;
			Node(Node * fc = nullptr, Node * fs = nullptr):
				firstchild(fc), firstsibling(fs){}
		};
		typedef Node<T> node;
	private:
		node *_root;
		int _nb_vex;
	public:
		cstree():_root(nullptr),_nb_vex(0){}
};
#endif
