/** 20210914, zyj, GuangDong*/
#ifndef _DL_TREE
#define _DL_TREE
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/** 孩子兄弟表示键树*/
template <typename elem_t>
class dl_tree
{
	public:
		typedef enum {LEAF, BRANCH} kind;//kind of node
		enum {MAXKEYLEN = 16};
	private:
		template<typename elem_t1>
		struct Node
		{
			elem_t1 symbol;//one symbol of a key;
			struct Node *next;
			kind type;
			union
			{
				elem_t1 * infoptr;// 叶结点的记录指针
				struct Node *first;// first child of the node
			};
			Node(kind t):next(nullptr),type(t),infoptr(nullptr){}
		};

		Node<elem_t> * _root;
		int _node_num;
	public:
		typedef Node<elem_t> node;

		dl_tree():_root(new node(BRANCH)), _node_num(0){}
		elem_t * search(const elem_t * key, int len);
};


/**
   在非空双链树T中查找关健字等于K的记录，若存在，则返回指向该记录的指针，否则返回空
 */
template<typename elem_t>
elem_t * dl_tree<elem_t>::
search(const elem_t * key, int len)
{
	node * p  = _root->first; 
	int i = 0;

	while(p && i < len)
	{
		while(p && p->symbol != key[i]) p = p->next;
		if(p && i < len - 1)//search next symbol
		  p = p->first;
		++i;
	}
	if(!p) return nullptr;// not found
	else return p->infoptr;
}

#endif
