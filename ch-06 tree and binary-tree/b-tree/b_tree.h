/** 20210913, zyj, GuangDong*/
#ifndef _B_TREE
#define _B_TREE
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

/** key type, order*/
template <typename key_t, int m = 3>
class b_tree
{
	private:
		/** struct defines*/
		template <typename key_t1>
		struct Node
		{
			int key_num;//number of key
			struct Node * parent;
			key_t1 keys[m + 1]; //vector of key, 0 is reserved
			struct Node * children;//vector of children
		};
		template<typename node_t>
		struct Result
		{
			node_t * pt; // node found
			int i;//index of key found
			bool ret;// false for not found, true for found
		};

		/** data defines*/
		Node<key_t> * _root;
		int _node_num;

		/** function defines*/
		static key_t default_cmp(const key_t & a, const key_t & b) { return (a - b);}
		
		template<typename cmp_t>
		Result<Node<key_t> > search(Node<key_t> *root, key_t key, cmp_t);
	public :
		typedef Node<key_t> node;
		typedef Result<node> result;

		b_tree():_root(nullptr), _node_num(0){}
		
		/** search*/
		template<typename cmp_t = key_t (*)(const key_t &, const key_t &)>
		result search(key_t key, const cmp_t & cmp = default_cmp);
};

#endif
