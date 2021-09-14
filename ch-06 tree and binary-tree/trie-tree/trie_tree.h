/** 20210914, zyj, GuangDong*/
#ifndef _TRIE_TREE
#define _TRIE_TREE
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/** 孩子兄弟表示键树*/
template <typename elem_t>
class trie_tree
{
	private:
		typedef enum {LEAF, BRANCH} kind;//kind of node
		enum{MAXKEYLEN = 16, d = 27};
		
		template<typename elem_t1>
		struct Key
		{
			elem_t1 elems[MAXKEYLEN];
			int len;
		};
		
		template<typename elem_t1>
		struct Node
		{
			struct
			{
				key_t key;
				elem_t1 * infoptr;
			}lf;//leaf node
			struct
			{
				Node *ptr[d];
			}bh;//branch node

			kind type;
		};

		Node<elem_t> *_root;
		int _node_num;
	public:
		typedef Node<elem_t> node;
		typedef Key<elem_t> key_t;

		trie_tree():_root(nullptr), _node_num(0){}
		bool search(const key_t & key);
};

template<typename elem_t>
bool trie_tree<elem_t>::
search(const typename trie_tree<elem_t>:: key_t & key)
{
	node * p;
	int i;

	for(p = _root, i = 0;
				p && (p->kind == BRANCH) && i < key.len;
				p = p->bh.ptr[ord(key.elems[i])], ++i)//no data in branch
	  ;
	if(p && (p->type == BRANCH) && (p->lf.key == key))
	  return true;
	else 
	  return false;
}

#endif
